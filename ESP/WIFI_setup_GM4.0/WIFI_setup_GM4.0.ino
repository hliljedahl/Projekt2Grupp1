
#include <ESP8266WiFi.h>
#include <DNSServer.h>
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

DNSServer dns_server;
ESP8266WebServer web_server(80);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
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
    Serial.print("Configuration");
    Serial.println(WiFi.softAPIP());
    web_server.on("/settings", []() {
      String s = "<h1>WiFi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
      s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
      s += network_list;
      s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";
      web_server.send(200, "text/html", make_page("WiFi Settings", s));
    });
    web_server.on("/setap", []() {
      for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
      }
      String ssid = urlDecode(web_server.arg("ssid"));
      Serial.print("SSID: ");
      Serial.println(ssid);
      String pass = urlDecode(web_server.arg("pass"));
      Serial.print("Password: ");
      Serial.println(pass);
      Serial.println("Saving SSID...");
      for (int i = 0; i < ssid.length(); ++i) {
        EEPROM.write(i, ssid[i]);
      }
      Serial.println("Savinf Password...");
      for (int i = 0; i < pass.length(); ++i) {
        EEPROM.write(32 + i, pass[i]);
      }
      EEPROM.commit();
      Serial.println("Write EEPROM done!");
      String s = "<h1>Configuration complete.</h1><p>device will be connected to \"";
      s += ssid;
      s += "\" after the restart.";
      web_server.send(200, "text/html", make_page("WIFI Settings", s));
      ESP.restart();
    });
    web_server.onNotFound([]() {
      String s = "<h1>Configuration mode</h1><p><a href=\"/settings\">WiFi Settings</a></p>";
      web_server.send(200, "text/html", make_page("Configuration mode", s));
    });
  }
  else { 
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.localIP());
    web_server.on("/", []() {
      String s = "<h1>12346789</h1><p><a href=\"/reset\">Reset WiFi Settings</a></p>";
      web_server.send(200, "text/html", make_page("Reset", s)); 
    });
    web_server.on("/reset", []() {
      for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
      String s = "<h1>WiFi settings was reset.</h1><p>Please wait for the device to reset.</p>";
      web_server.send(200, "text/html", make_page("Reset WiFi Settings", s));
    });
  }
  web_server.begin();
}

void setupMode() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  delay(100);
  Serial.println("");
  for (int i = 0; i < n; ++i) {
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
  Serial.print("Starting Access Point at \"");
  Serial.print(AP_SSID);
  Serial.println("\"");
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

String urlDecode(String input) {
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
