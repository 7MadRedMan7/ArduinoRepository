#include <Display_leds.h>
Display_leds led16;
  // адреса першого модуля PCF8575TS

void setup() {
  led16.begin();
  led16.leds= 0;
}

void loop() {
  led16.leds= led16.leds+1;
  led16.Display_LEDs();
  delay(500);


}