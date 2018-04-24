#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT22
#define DHTPIN 0

const IPAddress AP_IP(192, 168, 1, 1);
const char*AP_SSID = "ESP CONFIG-01";
boolean setting_mode;
String network_list;

float t_val[3] = {0};

DNSServer dns_server;
DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer web_server(80);

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  delay(10);
  reset_config();
  if (restore_config()) {
    if (checkConnection()) {
      setting_mode = false;
      start_web_server();
      return;
    }
  }
  setting_mode = true;
  setupMode();
}

void loop() {
  if (setting_mode) {
    dns_server.processNextRequest();
  }
  web_server.handleClient();
}

boolean restore_config() {
  Serial.println("Reading EEPROM...");
  String ssid = "";
  String pass = "";
  if (EEPROM.read(0) != 0) {
    for (int i = 0; i < 32; ++i) {
      ssid += char(EEPROM.read(i));
    }
    Serial.print("SSID: ");
    Serial.println(ssid);
    for (int i = 32; i < 96; ++i) {
      pass += char(EEPROM.read(i));
    }
    Serial.print("Password: ");
    Serial.println(pass);
    WiFi.begin(ssid.c_str(), pass.c_str());
    return true;
  }
  else {
    Serial.println("Config not found.");
    return false;
  }
}

boolean checkConnection() {
  int count = 0;
  Serial.print("Waiting for Wi-Fi connection");
  while ( count < 30 ) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println();
      Serial.println("Connected!");
      return (true);
    }
    delay(500);
    Serial.print(".");
    count++;
  }
  Serial.println("Timed out.");
  return false;
}

void start_web_server() {
  if (setting_mode) {
    Serial.println("Configuration");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    configure_wifi();
  }
  else {
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    start_server();
  }
  web_server.begin();
}

void configure_wifi() {
  web_server.on("/settings", []() {
    String s = make_settings_page();
    web_server.send(200, "text/html", make_page("WiFi Settings", s));
  });
  web_server.on("/setap", []() {
    for (int i = 0; i < 96; i++) {
      EEPROM.write(i, 0);
    }
    String ssid = url_decode(web_server.arg("ssid"));
    Serial.print("SSID: ");
    Serial.println(web_server.arg("ssid")); 
    String pass = url_decode(web_server.arg("pass"));
    Serial.print("Password: ");
    Serial.println(web_server.arg("pass")); 
    for (int i = 0; i < ssid.length(); i++) {
      EEPROM.write(i, ssid[i]);
    }
    for (int i = 0; i < pass.length(); i++) {
      EEPROM.write(32 + i, pass[i]);
    }
    EEPROM.commit();
    String s = make_reset_page(ssid);
    web_server.send(200, "text/html", make_page("WIFI Settings", s));
    ESP.restart();
  });
  web_server.onNotFound([]() {
    String s = make_config_page();
    web_server.send(200, "text/html", make_page("Configuration mode", s));
  });
}

void start_server() {
  web_server.on("/", []() {
    String s = make_data_page();
    web_server.send(200, "text/html", make_page("Reset", s));
  });
  web_server.on("/reset", []() {
    for (int i = 0; i < 96; ++i) {
      EEPROM.write(i, 0);
    }
    EEPROM.commit();
    String s = make_reset_msg_page();
    web_server.send(200, "text/html", make_page("Reset WiFi Settings", s));
  });
}

void setupMode() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int nr = WiFi.scanNetworks();
  delay(100);
  Serial.println("");
  for (int i = 0; i < nr; i++) {
    network_list += "<option value=\"";
    network_list += WiFi.SSID(i);
    network_list += "\">";
    network_list += WiFi.SSID(i);
    network_list += "</option>";
  }
  delay(100);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(AP_SSID);
  dns_server.start(53, "*", AP_IP);
  start_web_server();
  Serial.print("Access Point SSID: ");
  Serial.println (AP_SSID);
}

String url_decode(String input) {
  String s = input;
  s.replace("%20", " ");
  s.replace("+", " ");
  s.replace("%21", "!");
  s.replace("%22", "\"");
  s.replace("%23", "#");
  s.replace("%24", "$");
  s.replace("%25", "%");
  s.replace("%26", "&");
  s.replace("%27", "\'");
  s.replace("%28", "(");
  s.replace("%29", ")");
  s.replace("%30", "*");
  s.replace("%31", "+");
  s.replace("%2C", ",");
  s.replace("%2E", ".");
  s.replace("%2F", "/");
  s.replace("%2C", ",");
  s.replace("%3A", ":");
  s.replace("%3A", ";");
  s.replace("%3C", "<");
  s.replace("%3D", "=");
  s.replace("%3E", ">");
  s.replace("%3F", "?");
  s.replace("%40", "@");
  s.replace("%5B", "[");
  s.replace("%5C", "\\");
  s.replace("%5D", "]");
  s.replace("%5E", "^");
  s.replace("%5F", "-");
  s.replace("%60", "`");
  return s;
}

void reset_config() {
  for (int i = 0; i < 96; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}


void get_val(float t_val[]) {
  if (isnan(t_val[0]) || isnan(t_val[1])) {
    return;
  }
  t_val[0] = dht.readHumidity();
  t_val[1] = dht.readTemperature();
  t_val[2] = dht.computeHeatIndex(t_val[1], t_val[0], false);
}

String make_data_page() {
  get_val(t_val);
  String s = "<h1><b>" + String(t_val[1]) + "</b></h1><p><a href=\"/reset\">Reset WiFi Settings</a></p>";
  return s;
}

String make_config_page() {
  String s = "<h1>Configuration mode</h1><p><a href=\"/settings\">WiFi Settings</a></p>";
  return s;
}


String make_reset_page(String wifi_ssid) {
  String s = "<h1>Configuration complete.</h1><p>device will be connected to \"";
  s += wifi_ssid;
  s += "\" after the restart.";
  return s;
}

String make_settings_page() {
  String s = "<h1>WiFi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
  s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
  s += network_list;
  s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";
  return s;
}

String make_reset_msg_page() {
  String s = "<p><b>WiFi settings was reset.</b></p><p>Please wait for the device to reset.</p>";
  return s;
}

String make_page(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}
