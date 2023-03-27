#define PCF8575TS_ADDRESS 0x20 // I2C address of PCF8575TS
#define LED_PIN 0 // Pin number to connect LED to

void i2c_send_byte(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(addr);
  Wire.write(data);
  Wire.endTransmission();
}

void setup() {
  Wire.begin();
  i2c_send_byte(PCF8575TS_ADDRESS, 0x00); // Set all pins to output mode
}

void loop() {
  i2c_send_byte(PCF8575TS_ADDRESS, 1 << LED_PIN); // Turn on LED by setting LED_PIN high
  delay(1000); // Wait for 1 second
  i2c_send_byte(PCF8575TS_ADDRESS, 0); // Turn off all pins by setting all bits low
  delay(1000); // Wait for 1 second
}