#include <Wire.h>

float valArray[2] = {};
unsigned long previousMillis = 0; 
const long interval = 1000;   

void setup() {
  Serial.begin(4800);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; 
    Serial.println("-1");
  }

  /*int i = 0;
    while (Serial.available() > 0) {
    //Serial.println(Serial.read());
    valArray[i] = Serial.read();
    i++;
    }
    Serial.println(show_temp(valArray[0],valArray[1]));*/
  //Serial.println(valArray[0]);
  //Serial.println("__ ");
  //Serial.println(valArray[1]);
  //temp = (valArray[0]<<8)+valArray[1];
  //Serial.println(temp/10.0);

}

float show_temp(int t1, int t2) {
  float temp = 0;
  float d = (float)t2 / 100;
  temp = t1 + d;
  return temp;
}
