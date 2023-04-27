#ifndef DISPLAY_LEDS
#define DISPLAY_LEDS
#define PCF8575_ADDR2 0x21  // адреса другого модуля PCF8575TS

#include <Arduino.h>

class Display_leds {
private:



public:
    void begin();
    void Display_LEDs();
    int leds;
};

#endif
#pragma once
