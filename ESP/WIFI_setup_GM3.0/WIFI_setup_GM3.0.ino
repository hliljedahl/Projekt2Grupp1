#include <ESP8266WiFi.h>

#define DHTTYPE DHT22
#define DHTPIN 0

struct WIFI {
  String ssid = "-1";
  String password = "-1";
};

WIFI wifi;

unsigned long previousMillis = 0;
const long refreshInterval = 1000;

unsigned long c_previousMillis = 0;
const long c_refreshInterval = 5000;

float t_val[3] = {0};

const char *esp_ssid = "0010.0100";
const char *esp_password = "summit14";

String html_page[4] = {};
String html_msg_page[3] = {};

WiFiServer server(80);

void setup() {
  wifiConfig(wifi.ssid, wifi.password);
}

void loop() { 
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
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
