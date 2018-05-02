#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESP";
const char *password = "123456789";

String html_page[4] = {};

ESP8266WebServer server(80);

void create_page(String p[]);

void setup(void) {
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("HotSpt IP:");
  Serial.println(myIP);

  server.on("/", HTTP_GET,handleRoot); //Which routine to handle at root location
  server.on("/login", HTTP_POST,handleLogin);
  server.onNotFound(handleNotFound);
  server.begin();
  
  Serial.println("Server started");
}

void loop(void) {
  server.handleClient();  //Handle client requests
}

void handleRoot() {
  create_page(html_page);
  server.send(200, "text/html", html_page[0] + html_page[1] + html_page[2] + html_page[3]);
}

void handleLogin() {
  //server.send(200, "text/html", "<h1>Welcome, " + server.arg("username") + "!</h1><p>Login successful</p>");
  if ( ! server.hasArg("username") || ! server.hasArg("password")
       || server.arg("username") == NULL || server.arg("password") == NULL) {
    server.send(400, "text/plain", "400: Invalid Request");
    return;
  }
  if (server.arg("username") == "esp123" && server.arg("password") == "123esp") {
    server.send(200, "text/html", "<h1>Welcome, " + server.arg("username") + "!</h1><p>Login successful</p>");
  }
  else {
    server.send(401, "text/plain", "401: Unauthorized");
  }
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found"); 
} 

void create_page(String p[]) {
  p[0] = "<form action=\"/login\" method=\"POST\">";
  p[1] = "<input type=\"text\" name=\"username\" placeholder=\"Usernamen\"></br>";
  p[2] = "<input type=\"password\" name=\"password\" placeholder=\"Password\"></br>";
  p[3] = "<input type=\"submit\" value=\"Login\"></form>";
}
