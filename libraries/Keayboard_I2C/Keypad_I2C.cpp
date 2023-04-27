#include "Keypad_I2C.h"
#include <Wire.h>


void Keypad_I2C::begin() {
    Wire.begin();
    Wire.beginTransmission(0x20);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
}

byte Keypad_I2C::read_kb() {
    byte scan[4] = { 0xFE, 0xFD, 0xFB, 0xF7 };
    byte ret_ckey = 0x00;
    int ckey[4];
    static byte prev_ckey[4];

    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(0x20);
        Wire.write(0xff);
        Wire.write(scan[i]);
        Wire.endTransmission();
        Wire.requestFrom(0x20, 2);

        while (Wire.available()) {
            ckey[i] = Wire.read() & 0xF0;     // Receive a byte as character
            // Print the character
        }

        if (ckey[i] != 0xF0) {
            //Якщо клавіша натиснута

            if (prev_ckey[i] != ckey[i]) {
                prev_ckey[i] = ckey[i];

                ckey[i] >>= 4;
                ckey[i] &= 0xF;
                ckey[i] |= 0x80;
                ret_ckey = ckey[i];
            }

            else {
                ckey[i] = 0x00;
            }
        }

        else {
            prev_ckey[i] = ckey[i];
            ckey[i] = 0x00;
        }
    }

    if (ret_ckey & 0x80)
    {
        Serial.println(ret_ckey, HEX);
    }

    Wire.beginTransmission(0x20);
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();

    return ret_ckey;
}
