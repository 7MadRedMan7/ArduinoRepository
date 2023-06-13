#ifndef INIT_VARIABLES
#define INIT_VARIABLES
#define PIN_DOUT 7
#define PIN_SS_MAX 8
#define PIN_DCLK 4
#define PIN_LACLK 3
#define PIN_LAOUT 2
#define PIN_REQ 6
#define TEST_DATA 1
#define PIN_ACK 5
#define MAX_PANEL 500
#define DUT_DIS 

#include <Arduino.h>

class init_var {
public:
	void init_variables();
	bool edit_test;
	bool saved_panel;
	bool edit_num_panel;
	bool enable_blink_panel_digits;
	int test_data[MAX_PANEL][72];
	int la_data[MAX_PANEL][16];
	byte la_din;
	int test_sygnal;
	int num_pin;
	int num_pin_arr[2];
	int one_dig_num_panel;
	int num_panel_arr[3];
	int num_panel;
	int num_ch_la;
	int num_la_arr[2];
	bool dout;
	bool laout;
	int num_keys;
	int var_num_pin;
	int num_bit;
	bool acknowladge;
	byte data;
	int var_la_pin;
	int leds;
	bool work_on;
	byte key_enable;
	bool ctrl_led;
	bool work_mode_led;
	bool test_on;
	int test_led; 
private:
	
};

#endif