#include <74HC595Plus.h>

HC595Plus display(12, 11, 10);  // data, clock, latch

const byte load_1[6] = {
  0b00100000, // 0
  0b00010000, // 1
  0b00001000, // 2
  0b00000100, // 3
  0b00000010, // 4
  0b00000001  // 5
};
DigitAnimation load1 = {load_1, 6}; //byte array, array size

const byte load_2[4] = {
  0b00100000, // 0
  0b01000000, // 1
  0b00000010, // 2
  0b00000001  // 3
};
DigitAnimation load2 = {load_2, 4}; //byte array, array size

void setup() {
  display.begin(); //optional clear on startup
}

void loop() {
  display.displayAnimateDig(load1); // Animation object, default offset, default speed (100ms)
  display.displayAnimateDig(load2, 4); // Animation object, offset, default speed (100 ms)
  display.displayAnimateDig(load2, 7, 50); // Animation object, offset, speed (ms)
}