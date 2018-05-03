#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include "DHTesp.h"

String VERSION = "3.0.3";

struct WIFI {
  const char *AP_SSID = "ESP CONFIG";
  String ssid = "";
  String pass = "";
};
WIFI wifi;

struct NODE {
  String temp_name = "";  //temp
  String id_1 = "Temperature";
  String humi_name = "";  //hum
  String id_2 = "Humidity";
  String zone = "";
  String ip = "";
};
NODE node;

const IPAddress AP_IP(192, 168, 1, 1);

unsigned long t_previousMillis = 0;
const long t_refreshInterval = 45000;

float t_val[3] = {0};

boolean config_mode;
boolean info_flag;

String network_list;
String msg;

DNSServer dns_server;
ESP8266WebServer web_server(80);
DHTesp sensor;

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(500);
  EEPROM.begin(512);
  delay(500);
  sensor.setup(2);
  delay(500);
  //reset_config();
  if (EEPROM.read(511) == 0) {
    reset_config();
  }
  if (restore_config()) {
    if (connect_wifi()) {
      config_mode = false;
      start_web_server();
    }
  } else {
    config_mode = true;
    setup_ap();
  }
}

void loop() {
  Serial.println("Handle client");
  if (config_mode) {
    dns_server.processNextRequest();
  }
  web_server.handleClient();
  if (!config_mode) {
    if (info_flag) {
      EEPROM.write(511, 1);
      delay(10);
      EEPROM.commit();
      delay(200);
      save_node_info();
      send_erase_msg();
      send_info_msg();
      start_web_server();
      info_flag = false;
      check_wifi_connection();
      delay(100);
    }
    unsigned long t_currentMillis = millis();
    if (t_currentMillis - t_previousMillis >= t_refreshInterval) {
      t_previousMillis = t_currentMillis;
      get_val(t_val);
    }
  }
}

void send_erase_msg() {
  Serial.println("");
  Serial.print("Remove: ");
  Serial.println(node.ip);
  msg = "http://www.lonelycircuits.se/data/remove_sensor_ip.php?ip=";
  msg += node.ip;
  HTTPClient http;  //Declare object of class HTTPClient
  http.begin(msg);  //Specify request destination
  http.addHeader("Content-Type", "text/plain");  //Specify content-type header
  int httpCode = http.POST(msg);  //Send the request
  String payload = http.getString();  //Get the response payload
  Serial.println("_______________________");
  Serial.print("HTTP return code: ");
  Serial.println(httpCode);
  Serial.println("");
  Serial.println("Request response payload: ");
  Serial.println(payload);
  Serial.println("_______________________");
  Serial.println("(Close connection)");
  http.end();
  delay(500);
}

void start_web_server() {
  if (config_mode) {
    web_server.on("/settings", []() {
      web_server.send(200, "text/html", make_page("", config_page()));
    });
    web_server.on("/config", []() {
      config_wifi();
      init_setup();
    });
    web_server.onNotFound([]() {
      web_server.send(200, "text/html", make_page("", config_msg_page()));
    });
  }
  else {
    node.ip = WiFi.localIP().toString();
    Serial.print("Starting Web Server at ");
    Serial.println(node.ip);
    web_server.on("/", []() {
      web_server.send(200, "text/html", make_page("", reset_page()));
    });
    web_server.on("/reset", []() {
      info_flag = true;
      web_server.send(200, "text/html", make_page("", reset_msg_page()));
      send_reset_msg();
      reset_config();
      init_setup();
    });
  }
  web_server.begin();
}

//################################## Database message #####################################

void send_reset_msg() {
  node.humi_name = "";
  node.temp_name = "";
  for (int i = 150; i < 200; i++) {
    node.humi_name += char(EEPROM.read(i));
  }
  for (int i = 200; i < 250; i++) {
    node.temp_name += char(EEPROM.read(i));
  }
  Serial.println("___________________________________________");
  Serial.println("Sending reset message to database");
  Serial.print("Remove humidity sensor: ");
  Serial.println(node.humi_name);
  Serial.print("Remove temperature sensor: ");
  Serial.println(node.temp_name);
  Serial.println("___________________________________________");
  delay(500);
}

void send_info_msg() {
  for (int i = 0; i < 2; i++) {
    if (i == 0) {
      msg = "http://www.lonelycircuits.se/data/add_sensor.php?zone=";
      msg += node.zone;
      msg += "&name=\"";
      msg += node.temp_name;
      msg += "\"&type=\"";
      msg += node.id_1;
      msg += "\"&ip=";
      msg += node.ip;
    }
    else if (i == 1) {
      msg = "http://www.lonelycircuits.se/data/add_sensor.php?zone=";
      msg += node.zone;
      msg += "&name=\"";
      msg += node.humi_name;
      msg += "\"&type=\"";
      msg += node.id_2;
      msg += "\"&ip=";
      msg += node.ip;
    }
    HTTPClient http;  //Declare object of class HTTPClient
    http.begin(msg);  //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    //Serial.print("Msg: ");
    //Serial.println(msg);
    int httpCode = http.POST(msg);  //Send the request
    String payload = http.getString();  //Get the response payload
    Serial.println("____________________________________________");
    Serial.print("HTTP return code: ");
    Serial.println(httpCode);
    Serial.println("");
    Serial.print("Request response payload: ");
    Serial.println(payload);
    Serial.println("____________________________________________");
    Serial.println("(Close connection)");
    http.end();
    delay(200);
  }
}

//################################### Wifi connection #####################################

bool check_wifi_connection() {
  int c = 0;
  for (int i = 0; i < 32; i++) {
    wifi.ssid += char(EEPROM.read(i));
  }
  for (int i = 32; i < 96; i++) {
    wifi.pass += char(EEPROM.read(i));
  }
  Serial.print("Checking connection");
  while ( c < 40 ) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("..Connection ok!");
      return true;
    }
    WiFi.begin(wifi.ssid.c_str(), wifi.pass.c_str());
    delay(500);
    Serial.print(".");
    c++;
  }
  Serial.println("Timed out.");
}

boolean connect_wifi() {
  int count = 0;
  Serial.print("Waiting for WiFi connection");
  while ( count < 50 ) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected!");
      return true;
    }
    delay(500);
    Serial.print(".");
    count++;
  }
  Serial.println("Timed out.");
  reset_config();
  return false;
}

//############################### Setup AP & wifi config ##################################

void config_wifi() {
  for (int i = 0; i < 96; i++) {
    EEPROM.write(i, 0);
  }
  wifi.ssid = url_decode(web_server.arg("ssid"));
  wifi.pass = url_decode(web_server.arg("pass"));
  node.humi_name = url_decode(web_server.arg("humi_name"));
  node.temp_name = url_decode(web_server.arg("temp_name"));
  node.zone = url_decode(web_server.arg("node_zone"));
  for (int i = 0; i < string_length(wifi.ssid); i++) {
    EEPROM.write(i, wifi.ssid[i]);
  }
  for (int i = 0; i < string_length(wifi.pass); i++) {
    EEPROM.write(32 + i, wifi.pass[i]);
  }
  EEPROM.commit();
  print_config(wifi.ssid, wifi.pass, node.temp_name, node.humi_name, node.zone);
  web_server.send(200, "text/html", make_page("", complete_msg_page()));
  restore_config();
}

void setup_ap() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int nr = WiFi.scanNetworks();
  delay(10);
  Serial.println("");
  for (int i = 0; i < nr; i++) {
    network_list += "<option value=\"";
    network_list += WiFi.SSID(i);
    network_list += "\">";
    network_list += WiFi.SSID(i);
    network_list += "</option>";
  }
  delay(5);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifi.AP_SSID);
  dns_server.start(53, "*", AP_IP);
  start_web_server();
  Serial.print("Access Point: ");
  Serial.println(wifi.AP_SSID);
}

//############################## Erase, save & restore ##################################

void reset_config() {
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  Serial.println("Config erased");
}

boolean restore_config() {
  Serial.println("Reading EEPROM...");
  wifi.ssid = "";
  wifi.pass = "";
  if (EEPROM.read(0) != 0) {
    for (int i = 0; i < 32; i++) {
      wifi.ssid += char(EEPROM.read(i));
    }
    Serial.print("SSID: ");
    Serial.println(wifi.ssid);
    for (int i = 32; i < 96; i++) {
      wifi.pass += char(EEPROM.read(i));
    }
    Serial.print("Password: ");
    Serial.println(wifi.pass);
    WiFi.begin(wifi.ssid.c_str(), wifi.pass.c_str());
    delay(500);
    return true;
  }
  else {
    info_flag = true;
    Serial.println("Config not found.");
    return false;
  }
}

void save_node_info() {
  Serial.println();
  Serial.println("Save node info");
  Serial.println("___________________________________________");
  Serial.print("Humidity sensor: ");
  Serial.println(node.humi_name);
  Serial.print("Temperature sensor: ");
  Serial.println(node.temp_name);
  Serial.println("___________________________________________");
  for (int i = 0; i < string_length(node.humi_name); i++) {
    EEPROM.write(150 + i, node.humi_name[i]);
  }
  for (int i = 0; i < string_length(node.temp_name); i++) {
    EEPROM.write(200 + i, node.temp_name[i]);
  }
  EEPROM.commit();
}

//################################################################################

void init_setup() {
  if (restore_config()) {
    if (connect_wifi()) {
      config_mode = false;
      start_web_server();
      //return; b
    }
  } else {
    config_mode = true;
    setup_ap();
  }
}

void get_val(float t_val[]) {
  Serial.println("Refresh Temp");

  float humidity = sensor.getHumidity();
  float temperature = sensor.getTemperature();

  t_val[0] = sensor.getHumidity();
  t_val[1] = sensor.getTemperature();
  t_val[2] = sensor.computeHeatIndex(temperature, humidity, false);
}

int string_length(String str) {
  int c = 0;
  str += '\n';
  while (str[c] != '\n') {
    c++;
  }
  return c;
}

//################################################################################

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

//################################################################################

void print_config(String ssid, String password, String node1_name,  String node2_name, String zone) {
  Serial.println("Writing EEPROM...");
  Serial.println("________________________________________");
  Serial.print("SSID: ");
  Serial.print(ssid);
  Serial.print(" | ");
  Serial.print("Password: ");
  Serial.println(password);
  Serial.println("________________________________________");
  Serial.println("");
  Serial.println("Node info");
  Serial.println("____________________");
  Serial.print("Temp name: ");
  Serial.println(node1_name);
  Serial.print("Hum name: ");
  Serial.println(node2_name);
  Serial.print("Zone: ");
  Serial.println(zone);
  Serial.println("____________________");
}

//##################################### HTML #####################################

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

String complete_msg_page() {
  String s = "<h1>Setup complete.</h1><p>Device will be connected to \"";
  s += wifi.ssid;
  s += "\" after the restart.";
  return s;
}

String config_msg_page() {
  String s = "<p><b>Configuration</b></p><p><a href=\"/settings\">WiFi Settings</a></p>";
  return s;
}

String reset_page() {
  String s = "<p><b>t:";
  s += t_val[1];
  s += ":h:";
  s += t_val[0];
  s += ":i:";
  s += t_val[2];
  s += ":<b/></p>";
  s += "<p><a href=\"/reset\">Reset WiFi Settings</a></p>";
  s += "<p>";
  s += "Version: ";
  s += VERSION;
  s += "</p>";
  s += "<p>";
  s += "Name: ";
  s += node.temp_name;
  s += " & ";
  s += node.humi_name;
  s += "</p>";
  return s;
}

String reset_msg_page() {
  String s = "<h1>WiFi settings was reset.</h1><p>Please remove and connect device again.</p>";
  return s;
}
String config_page() {
  String s = "<head><style>";
  s += "body {";
  s += "background-color: lightblue;";
  s += "}";
  s += "h1 {";
  s += "color: white;";
  s += "text-align: center;";
  s += "}";
  s += "label{";
  s += "color: white;";
  s += "}";
  s += "p {";
  s += "color: white;";
  s += "font-family: Raleway;";
  s += "font-size: 20px;";
  s += "}";
  s += "</head></style>";
  s += "<h1>Configuration</h1>";
  s += "<p>Please enter your password by selecting the SSID.</p>";
  s += "<form method=\"get\" action=config><label><Strong>SSID:</Strong></label>";
  s += "<span style=\"padding-left:59px\"><select name=\"ssid\"></span>";
  s += network_list;
  s += "</select>";
  s += "<br>";
  s += "<Strong><label>Password:</label></Strong>";
  s += "<span style=\"padding-left:29px\">";
  s += "<input length=64 type=\"password\" name=\"pass\" id=\"pass\">";
  s += "<br>";
  s += "<font color=\"white\" size=\"2\">Show Password</font>";
  s += "<span style=\"padding-left:17px\">";
  s += "<input type=\"checkbox\" onclick=\"hideFunction()\">";
  s += "</span>";
  s += "<script>";
  s += "function hideFunction() {";
  s += "var x = document.getElementById(\"pass\");";
  s += "if (x.type === \"password\") {";
  s += "x.type = \"text\";";
  s += "} else {";
  s += "x.type = \"password\";";
  s += " }";
  s += " }";
  s += "</script>";
  s += "<br>";
  s += "<p>Enter name for sensors and zone.</p>";
  s += "<Strong><label>Humidity:</label></Strong>";
  s += "<span style=\"padding-left:29px\">";
  s += "<input type=\"text\" name=\"humi_name\"onfocus=\"this.value=''\" value=\"Hum\">";
  s += "<br>";
  s += "<Strong><label>Temperature:</label></Strong>";
  s += "<span style=\"padding-left:6px\">";
  s += "<input type=\"text\" name=\"temp_name\" onfocus=\"this.value=''\"value=Temp>";
  s += "<br>";
  s += "</span>";
  s += "<Strong><label>Zone:</label></Strong>";
  s += "<span style=\"padding-left:60px\">";
  s += "<input type=\"text\" name=\"node_zone\" onfocus=\"this.value=''\" value=\"Zone1\">";
  s += "<br>";
  s += "<span style=\"padding-left:152px\">";
  s += "<input type=\"submit\"value=\"Apply\">";
  s += "</form></span></span>";
  return s;
}

