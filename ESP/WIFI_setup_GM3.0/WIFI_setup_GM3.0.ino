#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>

struct WIFI {
  const char *AP_SSID = "ESP CONFIG";
  String ssid = "";
  String pass = "";
};
WIFI wifi;

struct NODE {
  String id = "";
  String zone = "";
};

NODE node;

const IPAddress AP_IP(192, 168, 1, 1);

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
  setup_mode();
}

void loop() {
  if (setting_mode) {
    dns_server.processNextRequest();
  }
  web_server.handleClient();
}

boolean restore_config() {
  Serial.println("Reading EEPROM...");
  wifi.ssid = "";
  wifi.pass = "";
  if (EEPROM.read(0) != 0) {
    for (int i = 0; i < 32; ++i) {
      wifi.ssid += char(EEPROM.read(i));
    }
    Serial.print("SSID: ");
    Serial.println(wifi.ssid);
    for (int i = 32; i < 96; ++i) {
      wifi.pass += char(EEPROM.read(i));
    }
    Serial.print("Password: ");
    Serial.println(wifi.pass);
    WiFi.begin(wifi.ssid.c_str(), wifi.pass.c_str());
    return true;
  }
  else {
    Serial.println("Config not found.");
    return false;
  }
}

boolean checkConnection() {
  int count = 0;
  Serial.print("Waiting for WiFi connection");
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
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.softAPIP());
    web_server.on("/settings", []() {
      String s = "<h1>WiFi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
      s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
      s += network_list;
      s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";
      web_server.send(200, "text/html", makePage("", s));
    });
    web_server.on("/node.info", []() {
      String s = "<h1>WiFi Settings</h1><p>Please enter your password by selecting the SSID.</p>";   
      s += "<input type=\"text\" name=\"node.id\" placeholder=\"Node id\"></br>"; 
      s += "<input type=\"text\" name=\"node.zone\" placeholder=\"Zone name\"></br>"; 
      web_server.send(200, "text/html", makePage("", s));
    });
    web_server.on("/setap", []() {
      for (int i = 0; i < 96; i++) {
        EEPROM.write(i, 0);
      }
      wifi.ssid = url_decode(web_server.arg("ssid"));
      Serial.print("SSID: ");
      Serial.println(wifi.ssid);
      wifi.pass = url_decode(web_server.arg("pass"));
      Serial.print("Password: ");
      Serial.println(wifi.pass);
      Serial.println("Writing SSID to EEPROM...");
      for (int i = 0; i < wifi.ssid.length(); i++) {
        EEPROM.write(i, wifi.ssid[i]);
      }
      Serial.println("Writing Password to EEPROM...");
      for (int i = 0; i < wifi.pass.length(); i++) {
        EEPROM.write(32 + i, wifi.pass[i]);
      }
      EEPROM.commit();
      Serial.println("Write EEPROM done!");
      String s = "<h1>Setup complete.</h1><p>device will be connected to \"";
      s += wifi.ssid;
      s += "\" after the restart.";

      web_server.send(200, "text/html", makePage("", s));
      ESP.restart();
    });
    web_server.onNotFound([]() {
      String s = "<h1>Configuration</h1><p><a href=\"/settings\">WiFi Settings</a></p>";
      web_server.send(200, "text/html", makePage("", s));
    });
  }
  else {
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.localIP());
    web_server.on("/", []() {
      String s = "<p><b>Data<b/></p><p><a href=\"/reset\">Reset WiFi Settings</a></p>";
      web_server.send(200, "text/html", makePage("", s));
    });
    web_server.on("/reset", []() {
      for (int i = 0; i < 96; i++) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
      String s = "<h1>WiFi settings was reset.</h1><p>Please remove and connect device again.</p>";
      web_server.send(200, "text/html", makePage("", s));
    });
  }
  web_server.begin();
}

void setup_mode() {
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
  WiFi.softAP(wifi.AP_SSID);
  dns_server.start(53, "*", AP_IP);
  start_web_server();
  Serial.print("Starting Access Point at \"");
  Serial.print(wifi.AP_SSID);
  Serial.println("\"");
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

String makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}  
