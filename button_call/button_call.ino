#include <Keypad_I2C.h>

Keypad_I2C keypad;

void setup() {
  keypad.begin();
  Serial.begin(115200);
}

void loop() {
  byte key = keypad.read_kb();
  
  if (key & 0x80) { // Перевірка, чи є клавіша натиснутою
    Serial.println(key, HEX); // Виводимо значення натиснутої клавіші в HEX форматі
  }
  
  delay(10); // Затримка для запобігання зайвих операцій на клавіатурі
}
