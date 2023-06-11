#include "display_leds.h"
#include <init_variables.h>
#include <init_devices.h>
#include <Wire.h>

 void display_l::display_leds(int test_sygnal) {
    int display = ~(0x0001 << test_sygnal);
    Wire.beginTransmission(ADDR_LED_TEST);
    Wire.write(display & 0xff);
    Wire.write((display >> 8) & 0xff);
    Wire.endTransmission();
}