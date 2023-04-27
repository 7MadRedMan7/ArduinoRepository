#include "Display_indicator.h"
#include <SPI.h>



void Display_indicator::begin() {
    SPI.begin();
    pinMode(SS_1, HIGH);
    sendCommand(0x09, 0xFF); // decode mode off
    sendCommand(0x0a, 0x00); // brightness to maximum (0x00 to 0x0f)
    sendCommand(0x0b, 0x07); // scan limit to all digits (0x01 to 0x08)
    sendCommand(0x0c, 0x01); // power up  
    sendCommand(0x0f, 0x00); // initialize the MAX7219 LED driver
}

void Display_indicator::displayDigits() {
    // send the updated digits to the MAX7219 LED driver
    for (int i = 0; i < NUM_DIGITS; i++) {
        sendCommand(i + 1, digits[i]);
    }
}

void Display_indicator::sendCommand(byte reg, byte data) {
    digitalWrite(SS_1, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(reg);
    SPI.transfer(data);
    SPI.endTransaction();
    digitalWrite(SS_1, HIGH);
}
