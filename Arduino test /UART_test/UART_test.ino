void setup() {
  Serial.begin(4800);

}

void loop() {
  while (Serial.available() > 0) {
    Serial.println(Serial.read());
  }
}
