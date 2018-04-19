#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "DHT.h"

#define DHTTYPE DHT22
#define DHTPIN 0

struct WIFI {
  String ssid = "-1";
  String password = "-1";
};

WIFI wifi;

unsigned long previousMillis = 0;
const long refreshInterval = 10000;
float t_val[3] = {0};

const char *esp_ssid = "ESP";
const char *esp_password = "123456789";

String html_page[4] = {};
String html_msg_page[3] = {};

boolean setup_flag = true;

DHT dht(DHTPIN, DHTTYPE);
WiFiServer WIFIserver(80);
ESP8266WebServer APserver(80);

void create_page(String c_p[]);
void create_login_msg(String m_p[]);
void wifiConfig(String wifi_ssid, String wifi_password);
void print_pas_use(String wifi_use, String wifi_pas);
void saveSetting(String ssid, String password);

void setup(void) {
  Serial.begin(9600);
  dht.begin();
  delay(10);
  APconfig();
  while (setup_flag) {
    APserver.handleClient();
  }
  wifiConfig(wifi.ssid, wifi.password);
}

void loop(void) {
  Serial.println("Connected to wifi");
  delay(2000);
  APserver.stop();
  /*String wifi_s = wifi.ssid;
    String wifi_p = wifi.password;
    Serial.print(wifi_s);
    Serial.print(" ");
    Serial.println(wifi_p);*/
  const char *wifi_s = "0010.0100";
  const char *wifi_p = "summit14";
  while (true) {
    WiFiClient client = WIFIserver.available();
    if (WiFi.status() != WL_CONNECTED) {
      Serial1.println("No wifi");
      WiFi.begin(wifi_s, wifi_p);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
      }
      WIFIserver.begin();
      delay(100);
    }

    if (!client) {
      return;
    }

    Serial.println("new client");
    while (!client.available()) {
      delay(1);
    }
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    delay(1);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    get_val(t_val);
    client.print("<b>");
    client.print("t:");
    client.print(t_val[1]);
    client.print(":h:");
    client.print(t_val[0]);
    client.print(":i:");
    client.print(t_val[2]);
    client.print(":");
    client.print("</b>");
    client.println("<br><br>");
    delay(1);
    Serial.println("Client disconnected");
    Serial.println("");

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= refreshInterval) {
      previousMillis = currentMillis;
      break;
    }
  }
}

void get_val(float t_val[]) {
  if (isnan(t_val[0]) || isnan(t_val[1])) {
    return;
  }
  t_val[0] = dht.readHumidity();
  t_val[1] = dht.readTemperature();
  t_val[2] = dht.computeHeatIndex(t_val[1], t_val[0], false);
}

void APconfig() {
  WiFi.mode(WIFI_AP);
  delay(250);
  WiFi.softAP(esp_ssid, esp_password);
  delay(250);
  IPAddress myIP = WiFi.softAPIP() ;
  delay(2000);
  Serial.println("");
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
  APserver.on("/", HTTP_GET, handleRoot);
  APserver.on("/login", HTTP_POST, handleLogin);
  APserver.onNotFound(handleNotFound);
  APserver.begin();
  Serial.println("AP configured!");
}

void wifiConfig(String wifi_ssid, String wifi_password) {
  Serial.print("Connecting to: ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  WIFIserver.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void saveSetting(String use, String pas) {
  /*
    Save settings to eeprom
  */
  wifi.ssid = use;
  wifi.password = pas;
}

void handleRoot() {
  create_page(html_page);
  APserver.send(200, "text/html", html_page[0] + html_page[1] + html_page[2] + html_page[3]);
}

void handleLogin() {
  if (APserver.arg("username") == NULL || APserver.arg("password") == NULL) {
    APserver.send(400, "text/plain", "400: Invalid Request");
    return;
  }
  else {
    create_login_msg(html_msg_page);
    APserver.send(200, "text/html", html_msg_page[0] + html_msg_page[1] + html_msg_page[2]);
    setup_flag = false;
  }
}

void create_login_msg(String m_p[]) {
  m_p[0] = "<h1>Thanks!</h1> ";
  m_p[1] = "<p><b> Username: </b>" + APserver.arg("username") + "</p>";
  m_p[2] = "<p><b> Password: </b>" + APserver.arg("password") + "</p>";
  saveSetting(APserver.arg("username"), APserver.arg("password"));
  print_pas_use(APserver.arg("username"),APserver.arg("password"));
}

void print_pas_use(String wifi_use, String wifi_pas){
  Serial.print("Username: ");
  Serial.println(wifi_use);
  Serial.print("Password: ");
  Serial.println(wifi_pas);
}

void handleNotFound() {
  APserver.send(404, "text/plain", "404: Not found");
}

void create_page(String c_p[]) {
  c_p[0] = "<form action=\"/login\" method=\"POST\">";
  c_p[1] = "<input type=\"text\" name=\"username\" placeholder=\"Usernamen\"></br>";
  c_p[2] = "<input type=\"password\" name=\"password\" placeholder=\"Password\"></br>";
  c_p[3] = "<input type=\"submit\" value=\"Login\"></form>";
}
