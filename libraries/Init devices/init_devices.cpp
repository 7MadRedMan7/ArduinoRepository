#include "init_devices.h"
#include <Wire.h>
#include <SPI.h>
#include "display_digits.h"
#include "change_panel_digits.h"
#include <init_variables.h>


extern display_d display;
extern init_var init_variables;


 void init_d::init_devices() {
    SPI.begin();
    pinMode(PIN_SS_MAX, HIGH);
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
    digitalWrite(PIN_DCLK, 0);
    digitalWrite(PIN_DOUT, 0);
    digitalWrite(PIN_LACLK, 0);
    digitalWrite(PIN_LAOUT, 0);
}
void init_d::clear_leds() {
    Wire.beginTransmission(ADDR_LED_TEST);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
}
void init_d::clear_digits() {
    int num_dig = 7;
    init_variables.num_panel_arr[0] = 0;
    init_variables.num_panel_arr[1] = 0;
    init_variables.num_panel_arr[2] = 0;
    for (int i = 0; i < num_dig; i++) {
        display.display_digits(i + 1, 0xF);
    }
}
void init_d::clear_num_digits() {
    int num_d = 7;
       init_variables.num_pin = 2;
       init_variables.num_ch_la = 0;
        for (int i = 3; i < num_d; i++) {
            display.display_digits(i + 1, 0xF);
        }
}