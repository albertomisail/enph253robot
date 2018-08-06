#pragma once

class OLED {
public:
    void begin();
    void clrScr();
    void print(char* s, int, int);
    void printNumI(int, int, int);
    void update();
	void invertText(bool);
	void clrPixel(int, int);
};

extern OLED oled;
