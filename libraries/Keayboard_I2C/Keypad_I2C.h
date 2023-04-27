#ifndef KEYPAD_I2C
#define KEYPAD_I2C

#include <Arduino.h>

class Keypad_I2C {
public:
	static void begin();
	byte read_kb();
private:
	int scan_dout;
};

#endif
