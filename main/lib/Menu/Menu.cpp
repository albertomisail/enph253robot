#include "Menu.h"

Menu::Menu() {}

int16_t Menu::readEEPROMValue(int i)
{
    int16_t top = EEPROM.read(i*2);
    int16_t bot = EEPROM.read(i*2+1);
    return (top<<8)|bot;
}

void Menu::loadEEPROM() {
    int16_t hasBeenSet = readEEPROMValue(MenuItem::menuItemCount);
    if(hasBeenSet == MARKED_WRITTEN)
    {
        for(int i=0;i<MenuItem::menuItemCount;++i)
        {
            MenuItem::menuItems[i]->setVal(readEEPROMValue(i));
        }
    }
}

void Menu::writeEEPROM() {
    for(int i=0;i<MenuItem::menuItemCount;++i)
    {
        if(readEEPROMValue(i) != MenuItem::menuItems[i]->getVal())
        {
            EEPROM.write(i*2+1, (MenuItem::menuItems[i]->getVal())&255);
            EEPROM.write(i*2, (MenuItem::menuItems[i]->getVal())>>8);
        }
    }
    if(readEEPROMValue(MenuItem::size()) != MARKED_WRITTEN)
    {
        EEPROM.write(MenuItem::size()*2+1, MARKED_WRITTEN&255);
        EEPROM.write(MenuItem::size()*2, MARKED_WRITTEN>>8);
    }
}

void Menu::run() {
    pinMode(Constants::POT_PIN, INPUT);
    pinMode(Constants::GO_BTN_PIN, INPUT);
    MenuScreen menuScreen;
    // Preload eeprom values into Constants
    loadEEPROM();
    menuScreen.run();
    writeEEPROM();
}
