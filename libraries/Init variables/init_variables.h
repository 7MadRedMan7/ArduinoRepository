#ifndef INIT_VARIABLES
#define INIT_VARIABLES

#include <Arduino.h>

class init_var {
public:
	void init_variables();
	bool edit_test;
	bool edit_num_panel;
	bool enable_blink_panel_digits;
	byte test_data[1000][72];
	byte la_data[1000][16];
	byte la_din;
	int test_sygnal;
	int num_pin;
	int num_panel_arr[3];
	int num_panel;
	int num_la_pin;
	int num_keys;
	int var_num_pin;
	int num_bit;
	bool request;
	bool acknowladge;
	byte data;
	int var_la_pin;
	int leds;
	byte key_enable;
private:
	
};

#endif