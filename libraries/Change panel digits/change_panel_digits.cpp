#include "change_panel_digits.h"
#include <init_variables.h>
#include <display_digits.h>

extern init_var init_variables;
extern display_d display;
void change_panel_dig::change_panel_digits() {
	init_variables.num_panel_arr[2] = init_variables.num_panel_arr[1];
	init_variables.num_panel_arr[1] = init_variables.num_panel_arr[0];
	init_variables.num_panel_arr[0] = init_variables.num_panel;
	display.display_digits(1, init_variables.num_panel_arr[0]);
	display.display_digits(2, init_variables.num_panel_arr[1]);
	display.display_digits(3, init_variables.num_panel_arr[2]);
}