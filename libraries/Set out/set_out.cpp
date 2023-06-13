#include "set_out.h"
#include "init_variables.h"

extern init_var init_variables;

void set_out::set_dout() {
	init_variables.dout = (init_variables.data & 0x1) ? 1 : 0;
	digitalWrite(PIN_DOUT, init_variables.dout);
	init_variables.data >>= 1;
	delayMicroseconds(1);
	digitalWrite(PIN_DCLK, 1);
	delayMicroseconds(1);
	digitalWrite(PIN_DCLK, 0);
}
void set_out::set_laout() {
	init_variables.laout = (init_variables.la_din & 0x1) ? 1 : 0;
	digitalWrite(PIN_LAOUT, init_variables.laout);
	init_variables.la_din >>= 1;
	delayMicroseconds(1);
	digitalWrite(PIN_LACLK, 1);
	delayMicroseconds(1);
	digitalWrite(PIN_LACLK, 0);
}