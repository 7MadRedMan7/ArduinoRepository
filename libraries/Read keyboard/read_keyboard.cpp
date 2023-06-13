#include "read_keyboard.h"
#include <init_devices.h>
#include <Wire.h>
#include "init_variables.h"
#include "change_panel_digits.h"
#include <send_data.h>
#include "display_digits.h"
#include "display_leds.h"


extern init_var init_variables;
extern init_d init_devices;
extern change_panel_dig change_panel_digits;
extern send_d send_data;
extern display_d display;
extern display_l display_leds;

byte read_kb::read_keyboard() {
    int scan[4] = { 0xFE, 0xFD, 0xFB, 0xF7};
    int ret_ckey = 0x00;
    byte ckey[3][2];
    static byte prev_ckey[3][4];
    int n = 0;
    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(ADDR_KEY);
  //      Wire.write(0x0f);
        Wire.write(0xff & ((init_variables.work_mode_led)?0x7F:0xFF) & ((init_variables.ctrl_led) ? 0xBF : 0xFF));
        Wire.write(scan[i]);
        Wire.endTransmission();
        Wire.requestFrom(ADDR_KEY, 2);

        while (Wire.available()) {
            ckey[0][1] = Wire.read() & 0xF0;     // Receive a byte as character
            // Print the character
        }

        if (ckey[0][1] != 0xF0) {
            //Якщо клавіша натиснута

            if (prev_ckey[0][i] != ckey[0][1]) {
                prev_ckey[0][i] = ckey[0][1];
                ckey[0][1] >>= 4;
                ckey[0][1] &= 0xF;
                init_variables.key_enable |= 0x1;
                ret_ckey = ((~ckey[0][1] & 0xf) << (i * 4));
            }
            else {
                init_variables.key_enable &= 0xFE;
            }
        }
        else {
            prev_ckey[0][i] = ckey[0][1];
        }
    }
    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(ADDR_KB);
        Wire.write(scan[i]);
        Wire.write(0xff);
        Wire.endTransmission();
        Wire.requestFrom(ADDR_KB, 2);
        n=0;
        while (Wire.available()) {
            ckey[1][n++] = Wire.read() & 0xF0;     // Receive a byte as character
            // Print the character

        }
        if (ckey[1][0] != 0xF0) {
            //Якщо клавіша натиснута

            if (prev_ckey[1][i] != ckey[1][0]) {
                prev_ckey[1][i] = ckey[1][0];
                ckey[1][0] >>= 4;
                ckey[1][0] &= 0xF;
                init_variables.key_enable |= 0x2;
                ret_ckey = ((~ckey[1][0] & 0xf) << (i * 4));
            }
            else {
                init_variables.key_enable = 0x0;
            }
        }
        else {
            prev_ckey[1][i] = ckey[1][0];
        }

    }

    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(ADDR_KB);
        Wire.write(0xff);
        Wire.write(scan[i]);
        Wire.endTransmission();
        Wire.requestFrom(ADDR_KB, 2);

        while (Wire.available()) {
            ckey[2][1] = Wire.read() & 0xF0;     // receive a byte as character
            // print the character
        }

        if (ckey[2][1] != 0xF0) {
            //якщо клавіша натиснута

            if (prev_ckey[2][i] != ckey[2][1]) {
                prev_ckey[2][i] = ckey[2][1];
                ckey[2][1] >>= 4;
                ckey[2][1] &= 0xF;
                init_variables.key_enable |= 0x4;
                ret_ckey = ((~ckey[2][1] & 0xf) << (i * 4));
            }
            else {
                init_variables.key_enable &= 0xFB;
            }
        }
        else {
            prev_ckey[2][i] = ckey[2][1];
        }
    }

 
    if (init_variables.key_enable == 0x2) {
        switch (ret_ckey)
        {
        case 2:
            init_variables.one_dig_num_panel = 1;
            change_panel_digits.change_panel_digits();
            init_variables.saved_panel = 0;
            init_variables.ctrl_led = 0;
            break;
        case 4:
            init_variables.one_dig_num_panel = 2;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 8:
            init_variables.one_dig_num_panel = 3;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 32:
            init_variables.one_dig_num_panel = 4;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 64:
            init_variables.one_dig_num_panel = 5;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 128:
            init_variables.one_dig_num_panel = 6;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 512:
            init_variables.saved_panel = 0;
            init_variables.one_dig_num_panel = 7;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 1024:
            init_variables.one_dig_num_panel = 8;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 2048:
            init_variables.one_dig_num_panel = 9;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 8192:
            init_devices.clear_digits();
            init_devices.clear_leds();
            init_devices.clear_num_digits();
            init_variables.saved_panel = 0;
            Serial.println("Cleared");
            init_variables.ctrl_led = 0;
            break;
        case 16384:
            init_variables.one_dig_num_panel = 0;
            init_variables.saved_panel = 0;
            change_panel_digits.change_panel_digits();
            init_variables.ctrl_led = 0;
            break;
        case 32768:
                for (int i = 3; i >= 0; i--) {
                    init_variables.num_panel = init_variables.num_panel * 10 + init_variables.num_panel_arr[i];
                }

                Serial.println("Saved to panel");
                Serial.println(init_variables.num_panel);
                
                init_variables.saved_panel = true;
                break;
                if (init_variables.work_on == false) {
                
                }

        }
    //Serial.println(init_variables.num_panel, HEX);
    }
    if (init_variables.key_enable == 0x1) {
        switch (ret_ckey)
        {
        case 1:
            if (init_variables.work_on == 0) {
                init_variables.num_ch_la++;
                if (init_variables.num_ch_la > 16) {
                    init_variables.num_ch_la = 0;
                    change_panel_digits.change_la_digits();
                }
                else if (init_variables.num_ch_la < 0) {
                    init_variables.num_ch_la = 16;
                    change_panel_digits.change_la_digits();
                }
                else {
                    Serial.println(init_variables.num_ch_la);
                    change_panel_digits.change_la_digits();

                }
                Serial.print("Test_la_num+1  ");
            }
            break;
        case 2:
            if (init_variables.work_on == 0) {
                init_variables.num_ch_la--;
                if (init_variables.num_ch_la > 16) {
                    init_variables.num_ch_la = 0;
                    change_panel_digits.change_la_digits();
                }
                else if (init_variables.num_ch_la < 0) {
                    init_variables.num_ch_la = 16;
                    change_panel_digits.change_la_digits();
                }
                else {
                    Serial.println(init_variables.num_ch_la);
                    change_panel_digits.change_la_digits();

                }
                Serial.print("Test_la_num-1  ");
            }
            break;
        case 4:
            if (init_variables.work_on == 0) {
                init_variables.num_pin++;
                if (init_variables.num_pin > 68) {
                    init_variables.num_pin = 2;
                    change_panel_digits.change_num_digits();
                    change_panel_digits.change_la_digits();
                }
                else if (init_variables.num_pin < 2) {
                    init_variables.num_pin = 68;
                    change_panel_digits.change_num_digits();
                    change_panel_digits.change_la_digits();
                }
                else {
                    Serial.println(init_variables.num_pin);
                    change_panel_digits.change_num_digits();
                    init_devices.clear_leds();
                    display_leds.display_leds(init_variables.test_data[init_variables.num_panel][init_variables.num_pin]);
                    for (int i = 0; i < 16; i++) {
                        if (init_variables.la_data[init_variables.num_panel][i] == init_variables.num_pin) {
                            init_variables.num_ch_la = i;
                            break;
                        }
                        else {
                            init_variables.num_ch_la = 0;
                        }
                    }
                    change_panel_digits.change_la_digits();

                }
                Serial.print("Test_num+1  ");
            }
            break;
        case 8:
            if (init_variables.work_on == 0) {
                init_variables.num_pin--;
                if (init_variables.num_pin > 68) {
                    init_variables.num_pin = 2;
                    change_panel_digits.change_num_digits();
                    change_panel_digits.change_la_digits();
                }
                else if (init_variables.num_pin < 2) {
                    init_variables.num_pin = 68;
                    change_panel_digits.change_num_digits();
                    change_panel_digits.change_la_digits();
                }
                else {
                    Serial.println(init_variables.num_pin);
                    change_panel_digits.change_num_digits();
                    init_devices.clear_leds();
                    change_panel_digits.change_la_digits();
                    display_leds.display_leds(init_variables.test_data[init_variables.num_panel][init_variables.num_pin]);
                    for (int i = 0; i < 16; i++) {
                        if (init_variables.la_data[init_variables.num_panel][i] == init_variables.num_pin) {
                            init_variables.num_ch_la = i;
                            break;
                        }
                        else {
                            init_variables.num_ch_la = 0;
                        }
                    }
                    change_panel_digits.change_la_digits();
                }
                Serial.print("Test_num-1  ");
            }
            break;
        case 16:
            // Serial.println("This panel and la tests are saved ");

            break;
        case 32:
            Serial.println("This panel tests and la tests are saved");
            init_variables.test_data[init_variables.num_panel][init_variables.num_pin] = init_variables.test_led;
            init_variables.la_data[init_variables.num_panel][init_variables.num_ch_la] = init_variables.num_pin;
            break;
        case 64:
            if (init_variables.saved_panel == 1 && init_variables.work_on == true) {
                Serial.println("Control mode");
                send_data.send_data(); 
                init_variables.ctrl_led = 1;
            }
            break;
        case 128:
            
            init_variables.work_on = !init_variables.work_on;
            init_variables.ctrl_led = 0;
            if (init_variables.work_on==0&& init_variables.saved_panel == true) {
                Serial.println("Edit mode");
                change_panel_digits.change_num_digits();
                change_panel_digits.change_la_digits();
                init_variables.work_mode_led = 0;

            }  
            if (init_variables.work_on == 1 && init_variables.saved_panel == true) {
                init_devices.clear_num_digits();
                init_devices.clear_leds();
                Serial.println("Work mode");
                init_variables.test_on == 0;
            }
            if (init_variables.work_on == 1) {
                init_variables.work_mode_led = 1;
            }
            break;
        case 256:
            //Serial.println("Button#1 9 ");
            break;
        case 512:
            //Serial.println("Button#1 10 ");
            break;
        case 1024:
            //Serial.println("Button#1 11 ");
            break;
        case 2048:
            //Serial.println("Button#1 12 ");
            break;
        case 8192:
            //Serial.println("Button#1 13 ");
            break;
        case 16384:
           
            break;
        }
    }
    if (init_variables.key_enable == 0x4) {
        switch (ret_ckey)
        {
        case 1:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true&& init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(0);
                init_variables.test_led = 0;
                Serial.println(init_variables.test_led);
                Serial.println("Test# ");

            }
            break;
        case 2:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(1);
                init_variables.test_led = 1;
            }
            break;
        case 4:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(2);
                init_variables.test_led = 2;
            }
            break;
        case 8:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(3);
                init_variables.test_led = 4;
            }
            break;
        case 16:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(4);
                init_variables.test_led = 4;
            }
            break;
        case 32:
            
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(5);
                init_variables.test_led = 5;
            }
            break;
        case 64:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(6);
                init_variables.test_led = 6;
            }
            break;
        case 128:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(7);
                init_variables.test_led = 7;
            }
            break;
        case 256:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(8);
                init_variables.test_led = 8;
            }
            break;
        case 512:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(9);
                init_variables.test_led = 9;
            }
            break;
        case 1024:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(10);
                init_variables.test_led = 10;
            }
            break;
        case 2048:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(11);
                init_variables.test_led = 11;
            }
            break;
        case 4096:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(12);
                init_variables.test_led = 12;
            }
            break;
        case 8192:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(13);
                init_variables.test_led = 13;
            }
            break;
        case 16384:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(14);
                init_variables.test_led = 14;
            }
            break;
        case 32768:
            if (init_variables.work_on == 0 && init_variables.saved_panel == true && init_variables.test_on == 1) {
                init_devices.clear_leds();
                display_leds.display_leds(15);
                init_variables.test_led = 15;
            }
            break;
        }
        //Serial.println(init_variables.num_panel, HEX);
    }
    Wire.beginTransmission(ADDR_KEY);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();

    Wire.beginTransmission(ADDR_KB);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();

    return ret_ckey;
}
