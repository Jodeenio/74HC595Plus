# 74HC595Plus
Simple feature-rich 8 Digit 7-segment display driver for dual 74HC595 shift register displays.

## Functions
### Display Text
Can be called with minimum of 1 parameter. Optional parameter is the **offset from the <ins>right of display</ins>**.
```
display.displayTxt("Char String");
display.displayTxt("Char String", 4); //offset 4 digits to the left
```
