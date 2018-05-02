#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_AM2320.h>

#include <DHT.h>
#include <DHT_U.h>

#include "DHT.h"

#define DHTPIN 8  

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(4800);
}

void loop() {
  float h = dht.readHumidity();
  //read temperature in Fahrenheit
  float f = dht.readTemperature(true);

  Serial.println(h);
  delay(5000);

}
