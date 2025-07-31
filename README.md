# 74HC595Plus Arduino Library
Simple feature-rich 8 Digit 7-segment display driver for dual 74HC595 shift register displays.

## Setup
Setup is simple and straight forward
### Add Library to Arduino IDE
Install in Arduino IDE Library Manager or:\
**[Download 74HC595Plus](https://github.com/Jodeenio/74HC595Plus/archive/refs/heads/main.zip) Library**  
Install in Arduino IDE: Click **Sketch > Include Library > Add .ZIP Library...** Select Library file, Done.  
Manual Install: Unzip Library file, locate Arduino library folder, place unzipped file in folder. Done.
### Setup Code
Include 74HC595Plus and **Create Instance** of **HC595Plus** Class providing the 3 digital pins for your display:
```
#include <74HC595Plus.h>

HC595Plus display(12, 11, 10);  // data, clock, latch
```
The "display" object can be named anything you wish eg. d1(data, clock, latch).

## Examples
Multiple example sketches can be found in the library files or Arduino IDE showcasing the flexability and ease of control over your 7 segment display. Example sketches can be accessed in Arduino IDE: **File > Examples > 74HC595Plus**

These include:  
**[Text and Number](https://github.com/Jodeenio/74HC595Plus/blob/main/Example/TextAndNumbers/TextAndNumbers.ino)**\
**[Animation of a single digit](https://github.com/Jodeenio/74HC595Plus/blob/main/Example/SingleDigitAnimation/SingleDigitAnimation.ino)**\
**[Whole display Animations](https://github.com/Jodeenio/74HC595Plus/blob/main/Example/WholeDisplayAnimation/WholeDisplayAnimation.ino)**
## Functions
### Display Text
Can be called with minimum of 1 parameter. Optional parameter is the **offset from the <ins>right of display</ins>**.
```
display.displayTxt("Char String");
display.displayTxt("Char String", 4); //offset 4 digits to the left
```
Some letters are not able to be displayed on a 7 Segment screen, they will output the closest possible version of that character but use is <ins>not recommended</ins>. These characters are **K, M, N, V, W, X**
### Display Number
Can be called with minimum of 1 parameter. 2 optional parameters can be given; the *offset* from the **<ins>right of display</ins>** and the *decimal places* after the number.  
Function supports both **int values and float values** and will <ins>default to 3 decimal places</ins> if no decimal parameter is provided with float values.
```
display.displayNumber(0); //Displays number 0 with no offset, no decimal places
display.displayNumber(12.345678, 3); //Displays 12.345, offset 3 digits to the left, default 3 dec places
display.displayNumber(12.345678, 0, 6); // Displays 12.345678 , no offset, 6 dec places
```
### Animate Digits
Can be called with minimum of 1 parameter. 2 optional parameters can be given; the *offset* from the **<ins>right of display</ins>** and the *speed* the animation plays at.  
\
Animation sequences are stored as **const byte arrays** and require a **DigitAnimation** constructor with the array name and size.
```
const byte load_1[6] = {
  0b00100000, // 0
  0b00010000, // 1
  0b00001000, // 2
  0b00000100, // 3
  0b00000010, // 4
  0b00000001  // 5
};
DigitAnimation load1 = {load_1, 6}; //byte array, array size
```
The function is called in *void loop()*. Multiple instances of different and the same animation can be played simultaneously at different speeds. Speed is set via the 3rd parameter as ms per frame. If no speed is given the animation will <ins>default to 100ms per frame</ins>.
```
display.displayAnimateDig(load1); // DigitAnimation object, default offset, default speed (100ms)
display.displayAnimateDig(load1, 4); // DigitAnimation object, offset, default speed (100 ms)
display.displayAnimateDig(load1, 7, 50); // DigitAnimation object, offset, speed (ms)
```
### Animate Whole Screen
Can be called with minimum of 1 parameter. 2 optional parameters can be given; the *offset* from the **<ins>right of display</ins>** and the *speed* the animation plays at.  
\
Animation sequences are stored as **2D const byte arrays**. The first value is the **segment data** (same as DigitAnimation) and the second is the **digit** to display the data on. An **Animation** constructor with the array name and size is reqired.
```
const byte swipe_[16][2] = {
  // segment data, digit selection
  {0b01000000, 0}, // 0
  {0b01000000, 1}, // 1
  {0b01000000, 2}, // 2
  ................
  {0b01000000, 2}, // 2
  {0b01000000, 1}, // 1
  {0b01000000, 0}, // 0
};
Animation swipe = {swipe_, 16}; // byte array, array size
```
The function is called in *void loop()*. Multiple instances of different and the same animation can be played simultaneously at different speeds. Speed is set via the 2nd parameter as ms per frame. If no speed is given the animation will <ins>default to 100ms per frame</ins>.
```
display.displayAnimate(swipe); // DigitAnimation object, default speed (100 ms)
display.displayAnimate(swipe, 50); // DigitAnimation object, speed (ms)
```
\
Tested with [Duinotec 8 Digit 7 Segment Display](https://www.jaycar.com.au/arduino-compatible-8-digit-7-segment-display/p/XC3714?srsltid=AfmBOop9T8EvsVPwGqQq3cXnKH6dCJ4oXV07JPoionLpyZuc56vtna2L)  
This Library has been built on top of the [ShiftRegister74HC595 Library](https://github.com/Simsso/ShiftRegister74HC595/tree/master) by [Timo Denk](https://github.com/Simsso) (MIT).
