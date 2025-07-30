#ifndef HC595PLUS_H
#define HC595PLUS_H

#include <Arduino.h>
#include <ShiftRegister74HC595.h>

struct DigitAnimation {
    const byte* animation;
    int frames;
    int index;
    unsigned long lastUpdate;

    DigitAnimation(const byte* anim, int len)
        : animation(anim), frames(len), index(0), lastUpdate(0) {}
};

struct Animation {
    const byte (*animation)[2];
    int frames;
    int index;
    unsigned long lastUpdate;

    Animation(const byte anim[][2], int len)
        : animation(anim), frames(len), index(0), lastUpdate(0) {}
};

class HC595Plus {
public:
    HC595Plus(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
    ~HC595Plus();

    void begin();
    void displayChar(char c, int pos);
    void displayText(const char* str, int offset);
    void displayDigitAnimation(DigitAnimation& anim, int offset, int speed);
    void displaySegmentAnimation(Animation& anim, int speed);

    static byte charToSegments(char c);

private:
    ShiftRegister74HC595<2>* _sr;
};

extern const byte segmentDigits[39];

#endif