#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//http://www.lonelycircuits.se/data/add_sensor.php?zone=XXX&name="YYY"&type="ZZZ"&ip=

String node_ip;

void setup() {

  Serial.begin(115200);
  WiFi.begin("0010.0100", "summit14");
  Serial.println("Waiting for connection..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

void loop() {
  node_ip = WiFi.localIP().toString();
  Serial.print("IP: ");
  Serial.println(node_ip);
  if (WiFi.status() != WL_CONNECTED) { //Check WiFi connection status
    Serial.println("Error in WiFi connection");
  } else {
    String msg = "http://www.lonelycircuits.se/data/add_sensor.php?zone=Zone4&name=\"WC88\"&type=\"Hum\"&ip=";
    msg += node_ip;
    HTTPClient http;  //Declare object of class HTTPClient
    http.begin(msg);  //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    Serial.print("Msg: ");
    Serial.println(msg);
    int httpCode = http.POST(msg);  //Send the request
    String payload = http.getString();  //Get the response payload
    Serial.print("HTTP return code: ");
    Serial.println(httpCode);
    Serial.print("Request response payload: ");
    Serial.println(payload);
    Serial.println("Close connection");
    http.end();
  }
  delay(60000);
}
