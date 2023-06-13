#ifndef INIT_DEVICES
#define INIT_DEVICES
#define ADDR_LED_TEST 0x21 
#define ADDR_KEY 0x20
#define ADDR_KB 0x24

#include <Arduino.h>

class init_d {
public:
	static void init_devices();
	void clear_leds();
	void clear_digits();
	void clear_num_digits();
private:

};

#endif
