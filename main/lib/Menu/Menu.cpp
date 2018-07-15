#include "Menu.h"

Menu::Menu() {}

int16_t readEEPROMValue(int i)
{
    int16_t top = EEPROM.read(i*2);
    int16_t bot = EEPROM.read(i*2+1);
    return (top<<8)|bot;
}

void Menu::loadEEPROM() {
    for(int i=0;i<MenuItem::menuItemCount;++i)
    {
        MenuItem::menuItems[i]->setVal(readEEPROMValue(i));
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
}

void Menu::run() {
    MenuScreen menuScreen;
    // Preload eeprom values into Constants
    menuScreen.run();
}
