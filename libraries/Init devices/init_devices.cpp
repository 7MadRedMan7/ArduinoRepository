#include "init_devices.h"
#include <Wire.h>
#include <SPI.h>
#include "display_digits.h"

extern display_d display;


 void init_d::init_devices() {
    SPI.begin();
    pinMode(SS_1, HIGH);
    display.display_digits(0x09, 0xFF); // decode mode off
    display.display_digits(0x0a, 0x00); // brightness to maximum (0x00 to 0x0f)
    display.display_digits(0x0b, 0x07); // scan limit to all digits (0x01 to 0x08)
    display.display_digits(0x0c, 0x01); // power up  
    display.display_digits(0x0f, 0x00);
    Wire.begin();
    Wire.beginTransmission(ADDR_LED_TEST);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
    Wire.beginTransmission(ADDR_KEY);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
    Wire.beginTransmission(ADDR_KB);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
}
void init_d::clear_leds() {
    Wire.beginTransmission(ADDR_LED_TEST);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
}
void init_d::clear_digits() {
    int num_dig = 7;
    for (int i = 0; i < num_dig; i++) {
        display.display_digits(i + 1, 0xF);
    }
}