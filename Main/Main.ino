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

void setup() {
  init_variables.init_variables();
  init_devices.init_devices();
  init_variables.test_sygnal = 0xF;
  init_devices.clear_leds();
  init_devices.clear_digits();
}
void set_data(){
  init_variables.var_num_pin = 2;
  init_variables.num_bit = 0;
  init_variables.request = true;
  init_variables.request = init_variables.acknowladge;
  for(init_variables.var_num_pin < 68; init_variables.var_num_pin++;){
    init_variables.data = init_variables.test_data[init_variables.num_panel][init_variables.num_pin];
    for(init_variables.num_bit < 4; init_variables.num_bit++;){
      set_out.set_dout();
      init_variables.data >>=1;
      pulse_dclk.pulse_dclk();
    }
    init_variables.num_bit = 0;
  }
  init_variables.var_la_pin = 1;
  for(init_variables.var_la_pin < 16; init_variables.var_la_pin++;){
    init_variables.la_din = init_variables.la_data[init_variables.num_panel][init_variables.var_la_pin];
    for(init_variables.num_bit < 8; init_variables.num_bit++;){
      set_out.set_laout();
      init_variables.la_din >>= 1;
      pulse_laclk.pulse_laclk();
    }
   init_variables.num_bit = 0;
  }
  init_variables.request = false;
  delay_ack.delay_ack();
  init_variables.request = init_variables.acknowladge;
  light_ctrl_led.light_ctrl_led();
}


void loop() {
//init_devices.clear_leds();
//set_data();

  // blink_ctrl_led.blink_ctrl_led();
  // change_la_digits.change_la_digits();
  // change_num_panel.change_num_panel();
  read_keyboard.read_keyboard();
      if (init_variables.key_enable)
    {
        
  change_panel_digits.change_panel_digits();
   }

   // change_pin_digits.change_pin_digits();
  // check_keys.check_keys_panel();
  // check_keys.check_keys_test();
  // clear_ctrl_led.clear_ctrl_led();
  // clear_leds.clear_leds();
  // delay_ack.delay_ack();
  
  //
  //display_leds.display_leds(init_variables.test_sygnal);
  // light_ctrl_led.light_ctrl_led();
  // pulse_dclk.pulse_dclk();
  // read_keyboard.read_keyboard();
  // save_num_panel.save_num_panel();
  // usb_disk.usb_disk();
  // set_out.set_dout();
  // set_out.set_laout();
delay(10);
}
