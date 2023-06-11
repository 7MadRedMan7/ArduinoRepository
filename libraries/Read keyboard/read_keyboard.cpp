#include "read_keyboard.h"
#include <init_devices.h>
#include <Wire.h>
#include "init_variables.h"

extern init_var init_variables;


byte read_kb::read_keyboard() {
    int scan[4] = { 0xFE, 0xFD, 0xFB, 0xF7};
    int ret_ckey = 0x00;
    byte ckey[2];
    static byte prev_ckey[12];
    int n = 0;
    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(ADDR_KEY);
        Wire.write(0xff);
        Wire.write(scan[i]);
        Wire.endTransmission();
        Wire.requestFrom(ADDR_KEY, 2);

        while (Wire.available()) {
            ckey[1] = Wire.read() & 0xF0;     // Receive a byte as character
            // Print the character
        }

        if (ckey[1] != 0xF0) {
            //Якщо клавіша натиснута

            if (prev_ckey[i] != ckey[1]) {
                prev_ckey[i] = ckey[1];
                ckey[1] >>= 4;
                ckey[1] &= 0xF;
                init_variables.key_enable |= 0x1;
                ret_ckey = ((~ckey[1] & 0xf) << (i * 4));
            }
            else {
                init_variables.key_enable &= 0xFE;
            }
        }
        else {
            prev_ckey[i] = ckey[1];
        }
    }
    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(ADDR_KB);
        Wire.write(scan[i]);
        Wire.write(0xff);
        Wire.endTransmission();
        Wire.requestFrom(ADDR_KB, 2);
        
        while (Wire.available()) {
            ckey[n++] = Wire.read() & 0xF0;     // Receive a byte as character
            // Print the character
        }

        if (ckey[0] != 0xF0) {
            //Якщо клавіша натиснута

            if (prev_ckey[i+4] != ckey[0]) {
                prev_ckey[i+4] = ckey[0];
                ckey[0] >>= 4;
                ckey[0] &= 0xF;
                init_variables.key_enable |= 0x2;
                ret_ckey = ((~ckey[0] & 0xf) << (i * 4));
            }
            else {
                init_variables.key_enable &= 0xFD;
            }
        }
        else {
            prev_ckey[i+4] = ckey[0];
        }
    }
    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(ADDR_KB);
        Wire.write(0xff);
        Wire.write(scan[i]);
        Wire.endTransmission();
        Wire.requestFrom(ADDR_KB, 2);

        while (Wire.available()) {
            ckey[1] = Wire.read() & 0xF0;     // receive a byte as character
            // print the character
        }

        if (ckey[1] != 0xF0) {
            //якщо клавіша натиснута

            if (prev_ckey[i+8] != ckey[1]) {
                prev_ckey[i+8] = ckey[1];
                ckey[1] >>= 4;
                ckey[1] &= 0xF;
                init_variables.key_enable |= 0x4;
                ret_ckey = ((~ckey[1] & 0xf) << (i * 4));
            }
            else {
                init_variables.key_enable &= 0xFB;
            }
        }
        else {
            prev_ckey[i+8] = ckey[1];
        }
    }

    if (init_variables.key_enable)
    {
        Serial.println(ret_ckey, HEX);
    }
    if (init_variables.key_enable == 0x4) {
        switch (ret_ckey)
        {
        case 1:
            init_variables.num_panel = 1;
            break;
        case 2:
            init_variables.num_panel = 2;
            break;
        case 4:
            init_variables.num_panel = 3;
            break;
        case 8:
            init_variables.num_panel = 4;
            break;
        case 10:
            init_variables.num_panel = 5;
            break;
        case 20:
            init_variables.num_panel = 5;
            break;
        case 40:
            init_variables.num_panel = 6;
            break;
        case 80:
            init_variables.num_panel = 7;
            break;
        case 100:
            init_variables.num_panel = 8;
            break;
        case 200:
            init_variables.num_panel = 8;
            break;
        case 400:
            init_variables.num_panel = 9;
            break;
        case 800:
            init_variables.num_panel = 10;
            break;
        case 1000:
            init_variables.num_panel = 11;
            break;
        case 2000:
            init_variables.num_panel = 11;
            break;
        case 4000:
            init_variables.num_panel = 12;
            break;
        case 8000:
            init_variables.num_panel = 13;
            break;
        }
    Serial.println(init_variables.num_panel, HEX);
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
