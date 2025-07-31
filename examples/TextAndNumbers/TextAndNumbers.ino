#include <74HC595Plus.h>

HC595Plus display(12, 11, 10);  // data, clock, latch

void setup() {
  display.begin(); //optional clear on startup
}

void loop() {
  display.displayTxt("°c"); // text string, default offset
  display.displayTxt("s.h.", 6); // text string, offset
  display.displayNumber(-37, 2); // float/int value, offset
}