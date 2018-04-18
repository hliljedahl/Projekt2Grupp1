#include "DHT.h"

#define DHTTYPE DHT22
#define DHTPIN 8

DHT dht(DHTPIN, DHTTYPE);

float t_val[3] = {0};

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  get_val(t_val);
  Serial.print(t_val[0]);
  Serial.print("  ");
  Serial.print(t_val[1]);
  Serial.print("  ");
  Serial.println(t_val[2]);
}

float get_val(float val[]) {
  if (isnan(val[0]) || isnan(val[1])) {
    return;
  }
  val[0] = dht.readHumidity();
  val[1] = dht.readTemperature();
  val[2] = dht.computeHeatIndex(val[1], val[0], false);
}

