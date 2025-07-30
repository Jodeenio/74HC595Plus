#include "74HC595Plus.h"

const byte segmentDigits[39] = {
  0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
  0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111,
  0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001,
  0b01110001, 0b00111101, 0b01110110, 0b00000110, 0b00011110,
  0b01110110, 0b00111000, 0b00010101, 0b00110111, 0b00111111,
  0b01110011, 0b01100111, 0b00110001, 0b01101101, 0b01111000,
  0b00111110, 0b00111110, 0b00101010, 0b01110110, 0b01101110,
  0b01011011,
  0b01000000, // -
  0b10000000, // .
  0b01100011  // °
};

HC595Plus::HC595Plus(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) {
    _sr = new ShiftRegister74HC595<2>(dataPin, clockPin, latchPin);
}

HC595Plus::~HC595Plus() {
    delete _sr;
}

void HC595Plus::begin() {
    _sr->begin();
    _sr->clear();
}

byte HC595Plus::charToSegments(char c) {
    if (c >= '0' && c <= '9') return segmentDigits[c - '0'];
    if (c >= 'A' && c <= 'Z') return segmentDigits[c - 'A' + 10];
    if (c >= 'a' && c <= 'z') return segmentDigits[c - 'a' + 10];
    if (c == '-') return segmentDigits[36];
    if (c == '.') return segmentDigits[37];
    if (c == '°') return segmentDigits[38];
    return 0;
}

void HC595Plus::displayChar(char c, int pos) {
    byte segData = charToSegments(c);
    byte data[2] = {~segData, ~(1 << pos)};
    _sr->setAll(data);
}

void HC595Plus::displayText(const char* str, int offset) {
    int len = strlen(str);
    int period = 0;
    for (int i = 0; i < len && (i + offset) < (8 + period); i++) {
        char current = str[(len - 1) - i];
        if ((unsigned char)current == 0xC2 && (unsigned char)str[(len - i)] == 0xB0) {
            current = '°';
        }
        byte segData = charToSegments(current);
        byte data[2] = {~segData, ~(1 << ((i + offset) - period))};
        if (segData == segmentDigits[37]) period++;
        _sr->setAll(data);
        delay(1);
    }
}

void HC595Plus::displayDigitAnimation(DigitAnimation& anim, int offset, int speed) {
    unsigned long current = millis();
    if (current - anim.lastUpdate >= speed) {
        anim.lastUpdate = current;
        byte segData = anim.animation[anim.index];
        byte data[2] = {~segData, ~(1 << offset)};
        _sr->setAll(data);
        anim.index = (anim.index + 1) % anim.frames;
    }
}

void HC595Plus::displaySegmentAnimation(Animation& anim, int speed) {
    unsigned long current = millis();
    if (current - anim.lastUpdate >= speed) {
        anim.lastUpdate = current;
        byte data[2] = {
            ~anim.animation[anim.index][0],
            ~(1 << anim.animation[anim.index][1])
        };
        _sr->setAll(data);
        anim.index = (anim.index + 1) % anim.frames;
    }
}