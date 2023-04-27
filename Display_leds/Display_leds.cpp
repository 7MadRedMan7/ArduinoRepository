#include "Display_leds.h"
#include <Wire.h>



void Display_leds::begin() {
    Wire.begin();
    Wire.beginTransmission(PCF8575_ADDR2);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
}


void Display_leds::Display_LEDs() {
    Wire.beginTransmission(PCF8575_ADDR2);
    Wire.write(leds & 0xff);
    Wire.write((leds >> 8) & 0xff);
    Wire.endTransmission();
}
