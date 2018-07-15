#pragma once
#include "MenuItem.h"
#include "MenuScreen.h"
#include <Arduino.h>
#include <EEPROM.h>

class Menu {
private:
    const static int16_t EEPROM_ADDR = 0;
    void loadEEPROM();
    static int16_t readEEPROMValue(int i);
    void writeEEPROM();
public:
    Menu();
    void run();
};
