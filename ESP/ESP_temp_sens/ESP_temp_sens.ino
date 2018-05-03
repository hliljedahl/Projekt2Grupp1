#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTTYPE DHT22
#define DHTPIN 2

const char* ssid = "0010.0100"; //type your ssid
const char* password = "summit14";  //type your password

unsigned long previousMillis = 0;
const long refreshInterval = 5000;

float t_val[3] = {0};
double temp = 0;

DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  while (true) {
    WiFiClient client = server.available();
    if (WiFi.status() != WL_CONNECTED) {
      Serial1.println("No wifi");
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
      }
      server.begin();
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

    temp=Thermister(analogRead(0));
    Serial.println(temp);
    client.print("<b>");
    client.print("t:");
    client.print(t_val[1]);
    client.print(":h:");
    client.print(t_val[0]);
    client.print(":i:");
    client.print(t_val[2]);
    client.print(":t2:");
    client.print(temp);
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

void tempSens(double temp) {
  
  int val=analogRead(0);      //Read the analog port 0 and store the value in val
  temp=Thermister(val);
  
}

double Thermister(int RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
 double Temp;
 Temp = log(((10240000/RawADC) - 10000));
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;              // Convert Kelvin to Celsius
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit - comment out this line if you need Celsius
 return Temp;
}
