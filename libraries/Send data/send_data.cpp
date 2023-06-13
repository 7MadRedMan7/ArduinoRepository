#include "send_data.h"
#include "set_out.h"
#include "init_variables.h"

extern init_var init_variables;
extern set_out set_out;


void send_d::send_data() {
    digitalWrite(PIN_REQ, 1);
    do {
#ifdef DUT_DIS
        init_variables.acknowladge = 1;
#else
        init_variables.acknowladge = digitalRead(PIN_ACK);
#endif
    } while (init_variables.acknowladge == false);
    for (init_variables.var_num_pin = 2; init_variables.var_num_pin < 68; init_variables.var_num_pin++) {
        init_variables.data = init_variables.test_data[init_variables.num_panel][init_variables.var_num_pin];
        for (init_variables.num_bit = 0; init_variables.num_bit < 4; init_variables.num_bit++) {
            set_out.set_dout();
        }
    }

    for (init_variables.var_la_pin = 1; init_variables.var_la_pin < 16; init_variables.var_la_pin++) {
        init_variables.la_din = init_variables.la_data[init_variables.num_panel][init_variables.var_la_pin];
        for (init_variables.num_bit = 0; init_variables.num_bit < 8; init_variables.num_bit++) {
            set_out.set_laout();
        }
    }
    digitalWrite(PIN_REQ, 0);
}