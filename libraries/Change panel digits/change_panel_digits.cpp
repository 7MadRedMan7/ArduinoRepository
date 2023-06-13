#include "change_panel_digits.h"
#include <init_variables.h>
#include <display_digits.h>

extern init_var init_variables;
extern display_d display;
void change_panel_dig::change_panel_digits() {
	init_variables.num_panel_arr[2] = init_variables.num_panel_arr[1];
	init_variables.num_panel_arr[1] = init_variables.num_panel_arr[0];
	init_variables.num_panel_arr[0] = init_variables.one_dig_num_panel;
	display.display_digits(1, init_variables.num_panel_arr[0]);
	display.display_digits(2, init_variables.num_panel_arr[1]);
	display.display_digits(3, init_variables.num_panel_arr[2]);
}

void change_panel_dig::change_num_digits() {
	init_variables.num_pin_arr[0] = init_variables.num_pin % 10;       // Отримуємо першу цифру
	init_variables.num_pin_arr[1] = (init_variables.num_pin / 10) % 10; // Отримуємо другу цифру
	display.display_digits(4, init_variables.num_pin_arr[0]);
	display.display_digits(5, init_variables.num_pin_arr[1]);
	init_variables.test_on = 1;
    // Отримуємо третю цифру
}
void change_panel_dig::change_la_digits() {
	init_variables.num_la_arr[0] = init_variables.num_ch_la % 10;       // Отримуємо першу цифру
	init_variables.num_la_arr[1] = (init_variables.num_ch_la / 10) % 10; // Отримуємо другу цифру
	display.display_digits(6, init_variables.num_la_arr[0]);
	display.display_digits(7, init_variables.num_la_arr[1]);
	// Отримуємо третю цифру
}
