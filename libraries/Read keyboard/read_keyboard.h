#ifndef READ_KEYBOARD
#define READ_KEYBOARD
#include <Arduino.h>

class read_kb {
public:
	byte read_keyboard();
private:
	int scan_dout;

};

#endif

