#include <74HC595Plus.h>

HC595Plus display(12, 11, 10);  // data, clock, latch

const byte swipe_[16][2] = {
  // segment data, digit selection
  {0b01000000, 0}, // 0
  {0b01000000, 1}, // 1
  {0b01000000, 2}, // 2
  {0b01000000, 3}, // 3
  {0b01000000, 4}, // 4
  {0b01000000, 5}, // 5
  {0b01000000, 6}, // 6
  {0b01000000, 7}, // 7
  {0b01000000, 7}, // 7
  {0b01000000, 6}, // 6
  {0b01000000, 5}, // 5
  {0b01000000, 4}, // 4
  {0b01000000, 3}, // 3
  {0b01000000, 2}, // 2
  {0b01000000, 1}, // 1
  {0b01000000, 0}, // 0
};
Animation swipe = {swipe_, 16}; // byte array, array size

const byte circle_[20][2] = {
  // segment data, digit selection
  {0b00000010, 0}, // 0
  {0b00000100, 0}, // 1
  {0b00001000, 0}, // 2
  {0b00001000, 1}, // 3
  {0b00001000, 2}, // 4
  {0b00001000, 3}, // 5
  {0b00001000, 4}, // 6
  {0b00001000, 5}, // 7
  {0b00001000, 6}, // 8
  {0b00001000, 7}, // 9
  {0b00010000, 7}, // 10
  {0b00100000, 7}, // 11
  {0b00000001, 7}, // 12
  {0b00000001, 6}, // 13
  {0b00000001, 5}, // 14
  {0b00000001, 4}, // 15
  {0b00000001, 3}, // 16
  {0b00000001, 2}, // 17
  {0b00000001, 1}, // 18
  {0b00000001, 0}, // 19
};
Animation circle = {circle_, 20}; // byte array, array size

void setup() {
  display.begin(); //optional clear on startup
}

void loop() {
  display.displayAnimate(circle); // Animation object, default speed (100ms)
  display.displayAnimate(swipe, 200); // Animation object, speed (ms)
}
