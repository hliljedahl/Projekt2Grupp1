#include "DHTesp.h"

DHTesp dht;

void setup() {
  Serial.begin(115200);
  dht.setup(2);
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());
  
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  
  Serial.print("Status: ");
  Serial.print(dht.getStatusString());
  Serial.print("\t\t");
  Serial.print("H: ");
  Serial.print(humidity, 1);
  Serial.print(" %");
  Serial.print("\t\t");
  Serial.print("T: ");
  Serial.print(temperature, 1);
  Serial.print(" *C");
  Serial.print("\t\t");
  Serial.print("HI: ");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.println(" *C");
}

