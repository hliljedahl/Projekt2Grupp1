#include <Adafruit_AM2320.h>
#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN 2

unsigned long previousMillis = 0;
const long refreshInterval = 2000;

float t_val[3] = {0};

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(10);
}

void loop() {
  //get_val(t_val);
  //unsigned long currentMillis = millis();
  //if (currentMillis - previousMillis >= refreshInterval) {
  //previousMillis = currentMillis;

  t_val[0] = dht.readHumidity();
  t_val[1] = dht.readTemperature();
  t_val[2] = dht.computeHeatIndex(t_val[1], t_val[0], false);

  Serial.print("t:");
  Serial.print(t_val[1]);
  Serial.print(":h:");
  Serial.print(t_val[0]);
  Serial.print(":i:");
  Serial.println(t_val[2]);
  delay(3000);
  //}
}

void get_val(float t_val[]) {
  /*if (isnan(t_val[0]) || isnan(t_val[1])) {
    return;
    }*/
  t_val[0] = dht.readHumidity();
  t_val[1] = dht.readTemperature();
  t_val[2] = dht.computeHeatIndex(t_val[1], t_val[0], false);
}

