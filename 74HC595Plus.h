#ifndef HC595PLUS_H
#define HC595PLUS_H

#include <Arduino.h>
#include <ShiftRegister74HC595.h>

struct DigitAnimation {
    const byte* animation;
    int frames;

    DigitAnimation(const byte* anim, int len)
        : animation(anim), frames(len) {}
};

struct InternalAnimState {
  int index = 0;
  unsigned long lastUpdate = 0;
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
    void displayTxt(const char* str, int offset = 0);
    void displayNumber(float num, int offset = 0, int decimal = -1);
    void displayAnimateDig(DigitAnimation& anim, int offset = 0, int speed = 100);
    void displayAnimate(Animation& anim, int speed = 100);

    static byte charToSegments(char c);

private:
    ShiftRegister74HC595<2>* _sr;
    static const int MAX_ANIMATIONS = 8;
    struct AnimationSlot {
        DigitAnimation* anim;
        int offset;
        InternalAnimState state;
    } slots[MAX_ANIMATIONS];
    void refreshDisplay(const char* strlength, int length, int char_offset);
};

extern const byte segmentDigits[39];

#endif