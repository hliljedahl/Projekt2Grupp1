#include <EEPROM.h>

String l = "OK";

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
  reset_config();
  EEPROM.write(511, 1); 
  EEPROM.commit();
}

void loop() {
  /*for (int i = 0; i < 512; i++) {
    Serial.print("[");
    Serial.print(i);
    Serial.print("] ");
    Serial.println(EEPROM.read(i));
    delay(250);
  }*/

  delay(2000);

  if(EEPROM.read(511) == 1){
    Serial.println("OK");
  }
}

void reset_config() {
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  Serial.println("Config erased");
}

int string_length(String str) {
  int c = 0;
  str += '\n';
  while (str[c] != '\n') {
    c++;
  }
  return c;
}
