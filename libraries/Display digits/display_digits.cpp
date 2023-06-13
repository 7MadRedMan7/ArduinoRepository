#include "display_digits.h"
#include <SPI.h>
#include "init_devices.h"
#include "init_variables.h"

void display_d::display_digits(byte reg, byte data) {
    digitalWrite(PIN_SS_MAX, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(reg);
    SPI.transfer(data);
    SPI.endTransaction();
    digitalWrite(PIN_SS_MAX, HIGH);
}