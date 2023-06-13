#include <init_variables.h>
#include <blink_ctrl_led.h>
#include <change_la_digits.h>
#include <change_num_panel.h>
#include <change_panel_digits.h>
#include <change_pin_digits.h>
#include <check_keys.h>
#include <clear_ctrl_led.h>
#include <clear_leds.h>
#include <delay.h>
#include <display_digits.h>
#include <display_leds.h>
#include <init_devices.h>
#include <light_ctrl_led.h>
#include <pulse_dclk.h>
#include <read_keyboard.h>
#include <save_num_panel.h>
#include <usb_disk.h>
#include <set_out.h>
#include <pulse_laclk.h>
#include <send_data.h>

change_panel_dig change_panel_digits;
change_panel change_num_panel;
init_var init_variables;
blink_ctrl blink_ctrl_led;
change_la change_la_digits;
change_pin_dig change_pin_digits;
check_k check_keys;
clear_ctrl clear_ctrl_led;
clear_led clear_leds;
dl delay_ack;
display_d display;
display_l display_leds;
init_d init_devices;
light_ctrl light_ctrl_led;
pulse_clk pulse_dclk;
pulse_lclk pulse_laclk;
read_kb read_keyboard;
save_panel save_num_panel;
usb_d usb_disk;
set_out set_out;
send_d send_data;

void setup() {
  init_variables.init_variables();
  init_devices.init_devices();
  init_variables.test_sygnal = 0xF;
  init_devices.clear_leds();
  init_devices.clear_digits();
}

void loop() {
  read_keyboard.read_keyboard();
}
