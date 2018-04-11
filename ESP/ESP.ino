#include <ESP8266WiFi.h>
#include <Wire.h> 
 
const char* ssid = "0010.0100";//type your ssid
const char* password = "summit14";//type your password
char temp = 0;
 
//int ledPin = 4; // GPIO2 of ESP8266
WiFiServer server(80);//Service Port
 
void setup() {
  Serial.begin(4800);
  Wire.begin(0,2);
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
  // Check if a client has connected
  WiFiClient client = server.available();

  if(WiFi.status() != WL_CONNECTED) {
        Serial1.println("[loop] no wifi");
        WiFi.begin(ssid, password);

         while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
         }
         Serial.println("");
         Serial.println("WiFi connected");
   
        // Start the server
        server.begin();
        delay(100);
  }

  if (!client) {
    return;
  }

// Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request

  //Kommunikation med PIC

  delay(1);

  if(Serial.available() > 0){
    temp = Serial.read();
  }

   
  // Return the response
  //Header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  //Body
  client.println("<html>");

  client.println(temp);
   
 
  client.println("</html>");
  //slut body
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
