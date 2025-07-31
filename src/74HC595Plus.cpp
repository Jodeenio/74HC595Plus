#include "74HC595Plus.h"

int length;

const byte segmentDigits[39] = {
  // 0–9
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  // A–Z (10–35)
  0b01110111, // A
  0b01111100, // B
  0b00111001, // C
  0b01011110, // D
  0b01111001, // E
  0b01110001, // F
  0b00111101, // G
  0b01110110, // H
  0b00000110, // I
  0b00011110, // J
  0b01110110, // K (same as H)
  0b00111000, // L
  0b00010101, // M (don't use)
  0b00110111, // N (don't use)
  0b00111111, // O
  0b01110011, // P
  0b01100111, // Q
  0b00110001, // R
  0b01101101, // S
  0b01111000, // T
  0b00111110, // U
  0b00111110, // V (same as U)
  0b00101010, // W (don't use)
  0b01110110, // X (same as H/K)
  0b01101110, // Y
  0b01011011, // Z (same as 2)
  // Symbols (36-)
  0b01000000, // -
  0b10000000, // .
  0b01100011 // °
};

// Digit select: only one digit on (first digit = rightmost)
const byte singledigitSelect[8] = {
  0b01111111, //0
  0b10111111, //1
  0b11011111, //2
  0b11101111, //3
  0b11110111, //4
  0b11111011, //5
  0b11111101, //6
  0b11111110, //7
};

HC595Plus::HC595Plus(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) {
    _sr = new ShiftRegister74HC595<2>(dataPin, clockPin, latchPin);
}

HC595Plus::~HC595Plus() {
    delete _sr;
}

void HC595Plus::begin() {
    _sr->setAllLow();
};

void HC595Plus::displayAnimate(Animation& anim, int speed) {
  unsigned long now = millis();
  const unsigned long interval = speed; // 1ms per digit (adjust as needed)
  byte segData = anim.animation[anim.index][0];
  byte data[2] = {~segData, ~singledigitSelect[anim.animation[anim.index][1]]};
  _sr->setAll(data);

  if (millis() - anim.lastUpdate >= interval) {
    anim.lastUpdate = millis();
    // Move to next digit
    anim.index = (anim.index + 1) % anim.frames;
  };
}

void HC595Plus::displayAnimateDig(DigitAnimation& anim, int offset, int speed) {
  unsigned long now = millis();
  InternalAnimState* animState = nullptr;

  // Find existing slot or make new
  for (int i = 0; i < MAX_ANIMATIONS; ++i) {
    if (slots[i].anim == &anim && slots[i].offset == offset) {
      animState = &slots[i].state;
      break;
    } else if (slots[i].anim == nullptr) {
      slots[i].anim = &anim;
      slots[i].offset = offset;
      animState = &slots[i].state;
      break;
    }
  }

  if (!animState) return; // No room for new animations

  byte segData = anim.animation[animState->index];
  byte data[2] = {~segData, ~singledigitSelect[offset]};
  _sr->setAll(data);

  // Advance frame
  if (now - animState->lastUpdate >= (unsigned long)speed) {
    animState->lastUpdate = now;
    animState->index = (animState->index + 1) % anim.frames;
  }
}

void HC595Plus::displayNumber(float num, int offset, int decimal) {
  char strlength[8];
  int actualDecimal = (decimal >= 0) ? decimal : 3;
  dtostrf(num, 8, actualDecimal, strlength);
  length = strlen(strlength);
  if (decimal < 0) {
    while (length > 0 && strlength[length - 1] == '0') {
      strlength[--length] = '\0';  // Remove trailing zero
    }
    if (length > 0 && strlength[length - 1] == '.') {
      strlength[--length] = '\0';  // Remove trailing decimal point
    }
  }
  refreshDisplay(strlength, length, offset);
}

void HC595Plus::displayTxt(const char* str, int offset) {
  length = (strlen(str));
  refreshDisplay(str, length, offset);
}

void HC595Plus::refreshDisplay(const char* strlength, int length, int char_offset) {
  int period =0;
  for (int i = 0; i < length && (i + char_offset) < (8 + period); i++) {
    byte segData = charToSegments(strlength[(length-1)-i]);
    byte data[2] = {~segData, ~singledigitSelect[(i+char_offset) - period]}; // Invert for common-anode
    if (segData == segmentDigits[37] or segData == segmentDigits[38]) {
      period++;
    };
    _sr->setAll(data);
    delayMicroseconds(800); // small delay for persistence
  }
}

byte HC595Plus::charToSegments(char c) {
  if (c >= '0' && c <= '9') return segmentDigits[c - '0'];
  if (c == '-') return segmentDigits[36];
  if (c == '.') return segmentDigits[37];
  if ((unsigned char)c == 0xB0) return segmentDigits[38];
  if (c >= 'A' && c <= 'Z') return segmentDigits[c - 'A' + 10];
  if (c >= 'a' && c <= 'z') return segmentDigits[c - 'a' + 10];
  return 0x00; // blank
}
