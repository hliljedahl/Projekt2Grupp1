#include <EEPROM.h>

#define EEPROM_ADDR 0

struct WIFI {
  String ssid = "-1";
  String password = "-1";
};

WIFI wifi;

void setup(void) {
  Serial.begin(9600);

}

void loop(void) {
  store_val((int)"a",0);
  delay(5000);
  read_from_eeprom();

}

void store_val(long val, int byte_pos) {
  //Serial.println("Write stop value to memmory");

  switch (byte_pos) {
    case 0: // up
      EEPROM.write(EEPROM_ADDR, (val & 0xFF));
      EEPROM.write(EEPROM_ADDR + 1, ((val >> 8) & 0xFF));
      EEPROM.write(EEPROM_ADDR + 2, ((val >> 16) & 0xFF));
      EEPROM.write(EEPROM_ADDR + 3, ((val >> 24) & 0xFF));
      break;

    case 1: // down
      EEPROM.write(EEPROM_ADDR + 4, (val & 0xFF));
      EEPROM.write(EEPROM_ADDR + 5, ((val >> 8) & 0xFF));
      EEPROM.write(EEPROM_ADDR + 6, ((val >> 16) & 0xFF));
      EEPROM.write(EEPROM_ADDR + 7, ((val >> 24) & 0xFF));
      break;

    case 2: // last known
      EEPROM.write(EEPROM_ADDR + 8, (val & 0xFF));
      EEPROM.write(EEPROM_ADDR + 9, ((val >> 8) & 0xFF));
      EEPROM.write(EEPROM_ADDR + 10, ((val >> 16) & 0xFF));
      EEPROM.write(EEPROM_ADDR + 11, ((val >> 24) & 0xFF));
      break;
  }
}

bool read_from_eeprom() {
  Serial.println("Read stored data");
  long mArray[12] = {};

  for (int i = 0; i < 12; i++) {
    mArray[i] = EEPROM.read(EEPROM_ADDR + i);
  }

  wifi.ssid = (((mArray[0] << 0) & 0xFF) + ((mArray[1] << 8) & 0xFFFF) + ((mArray[2] << 16) & 0xFFFFFF) + ((mArray[3] << 24) & 0xFFFFFFFF)); 
  Serial.println((String)wifi.ssid);
 
}

/*void CLEAR_EEPROM() {
  int c = 0;
  float p = 0;
  Serial.println("Start clearing..");
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
    Serial.print(100 * p, 1);
    Serial.println("%");
    c++;
    p = c / 1024.0;
  }
  Serial.println("..Done cleaning!");
}*/
