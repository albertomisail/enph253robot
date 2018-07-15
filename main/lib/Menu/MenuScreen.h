#pragma once
#include <Arduino.h>
#include <Constants.h>
#include "MenuItem.h"
#include <OLED_I2C.h>

class MenuScreen {
public:
    const uint8_t WIDTH = 100, HEIGHT=60, LINE_HEIGHT = 10, CHAR_WIDTH = 7;
    char* DONE_MESSAGE = "DONE";
private:
    char* getName(int i) const;
    uint8_t xpos[MenuItem::MAX_MENU_ITEMS+1], ypos[MenuItem::MAX_MENU_ITEMS+1];
    uint8_t currentMenuItem = 0;
    void positionMenuItems();
    bool processMenuItem(int i);
    void initializeMenuScreen() const;
public:
    void run();
};
