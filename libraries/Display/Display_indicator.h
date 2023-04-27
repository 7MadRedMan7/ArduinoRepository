#ifndef DISPLAY_INDICATOR
#define DISPLAY_INDICATOR

#include <Arduino.h>
#define NUM_DIGITS 7
#define SS_1 8
class Display_indicator {
private:
    


public:
    void begin();
    void displayDigits();
    void sendCommand(byte reg, byte data);
    byte digits[NUM_DIGITS];

};

#endif
