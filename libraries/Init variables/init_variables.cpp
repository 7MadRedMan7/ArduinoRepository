#include "init_variables.h"

void init_var::init_variables() {
	byte n = 0;
	Serial.println("Init variables works");
	key_enable = 0;
	saved_panel = false;
	work_on = true;
	num_pin = 2;
	num_ch_la = 0;
	ctrl_led = 0;
	work_mode_led = 1;
	test_on = 0;
	//for (int i = 0; i < 1000; i++) {
		//for (int j = 0; j < 72; j++) {
		//	test_data[i][j] = 0;
	//	}
	//}
#ifdef TEST_DATA
	for (int i = 0; i < MAX_PANEL; i++) {
		for (int j = 2; j < 68; j++ ) {
			test_data[i][j] = 0;
		}
	}
	for (int i = 0; i < MAX_PANEL; i++) {
		for (int j = 2; j < 16; j++) {
			la_data[i][j] = 0;
		}
	}
#endif
}