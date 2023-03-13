#include <SPI.h>

#define NUM_DIGITS 3
#define DIN_PIN 11

byte digits[NUM_DIGITS]; // an array to hold the digits to be displayed

void setup() {
  // Инициируем интерфейс SPI в режиме ведущего
  SPI.begin();
  // Устанавливаем логическую "1" на выводе Slave Select
  pinMode(SS, HIGH);
  initDisplay(); // initialize the MAX7219 LED driver
}

void sendCommand(byte reg, byte data) {
  digitalWrite(SS, LOW);
  // Начинаем передачу данных, передавая функции объект настроек шины
  // SPISettings( Скорость в Гц, Порядок передачи битов, Режим шины)
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(reg);
  SPI.transfer(data);
    // Завершаем передачу данных
  SPI.endTransaction();
  // Завершаем работу с ведомым
  digitalWrite(SS, HIGH);
}

void initDisplay() {
  sendCommand(0x09, 0xFF); // decode mode off
  sendCommand(0x0a, 0x0f); // brightness to maximum (0x00 to 0x0f)
  sendCommand(0x0b, 0x07); // scan limit to all digits (0x01 to 0x08)
  sendCommand(0x0c, 0x01); // power up
  sendCommand(0x0f, 0x00); // display test off
}

void loop() {
  // // increment the seconds variable
  unsigned long seconds = millis() / 1000;
  // update the digits array with the current number of seconds
  updateDigits(seconds);
  // display the updated digits on the 7-segment display via the MAX7219 LED driver
  displayDigits();
}



void updateDigits(unsigned long num) {
  // convert the number to a string
  String strNum = String(num % 1000);
  // pad the string with leading zeros if necessary
  while (strNum.length() < NUM_DIGITS) {
    strNum = "0" + strNum;
  }
  // convert each digit to a byte and store in the digits array
  for (int i = 0; i < NUM_DIGITS; i++) {
    digits[i] = strNum.charAt(i) - '0';
  }
}

void displayDigits() {
  // send the updated digits to the MAX7219 LED driver
  for (int i = NUM_DIGITS - 1; i >= 0; i--) {
    sendCommand(i + 1, digits[i]);
  }
}
