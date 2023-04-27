#include <Display_indicator.h>
 
Display_indicator indicator7;

void setup() {
  indicator7.begin();
}




void loop() {
  // // increment the seconds variable
  unsigned long seconds = millis() / 1000;
  // update the digits array with the current number of seconds
  updateDigits(seconds);
  Serial.println(seconds);
  // display the updated digits on the 7-segment display via the MAX7219 LED driver
  indicator7.displayDigits();
  delay(100);
}



void updateDigits(unsigned long num) {
  // convert the number to a string
  // String strNum = String(num % 10000000);
  // // pad the string with leading zeros if necessary
  // while (strNum.length() < NUM_DIGITS) {
  //   strNum = "0" + strNum;
  // }
  // // convert each digit to a byte and store in the digits array
  // for (int i = 0; i < NUM_DIGITS; i++) {
  //   digits[i] = strNum.charAt(i) - '0';
  // }
  for (int i = 0; i < NUM_DIGITS; i++) {
    indicator7.digits[i] = num&0xf;
    num=num>>4;
  }
}


