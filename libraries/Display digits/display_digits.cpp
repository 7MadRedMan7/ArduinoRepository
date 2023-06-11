#include "display_digits.h"
#include <SPI.h>
#include "init_devices.h"

void display_d::display_digits(byte reg, byte data) {
    digitalWrite(SS_1, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(reg);
    SPI.transfer(data);
    SPI.endTransaction();
    digitalWrite(SS_1, HIGH);
}