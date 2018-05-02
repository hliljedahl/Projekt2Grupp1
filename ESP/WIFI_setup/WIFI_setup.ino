#include <ESP8266WiFi.h>

boolean result = false;

WiFiServer server(80);

void setup() {
 Serial.begin(9600);
 Serial.println();
 Serial.print("Setting Soft-AP..");
 result = WiFi.softAP("fuckshit", "kuken100");
 if(result){
  Serial.println("Ready");
 }
 else{
  Serial.println("Error!");
 }
}

void loop() {
  Serial.printf("Station connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}


