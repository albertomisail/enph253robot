#include "MenuScreen.h"

char* MenuScreen::getName(int i) const {
    if(i < MenuItem::menuItemCount) {
        return MenuItem::menuItems[i]->getName();
    }
    return DONE_MESSAGE;
}

void MenuScreen::positionMenuItems()
{
    uint8_t currentx = 0, currenty = 0;
    // print 1 additional field that says "DONE".
    for(int i=0;i<MenuItem::menuItemCount+1;++i)
    {
        uint8_t len = strlen(getName(i));
        if(currentx + len*CHAR_WIDTH+NUM_WIDTH > WIDTH) {
            currentx = 0, currenty += LINE_HEIGHT;
        }
        xpos[i] = currentx, ypos[i] = currenty;
        npos[i] = currentx+CHAR_WIDTH*len+5;
        currentx += len*CHAR_WIDTH;
    }
}

void MenuScreen::initializeMenuScreen() const
{
    oled.clrScr();
    oled.invertText(false);
    for(int i=0;i<MenuItem::menuItemCount+1;++i)
    {
        oled.print(getName(i), xpos[i], ypos[i]);
        if(MenuItem::menuItemCount != i)
        {
            oled.printNumI(MenuItem::menuItems[i]->getVal(), npos[i], ypos[i]);
        }
    }
    oled.update();
}

void MenuScreen::run()
{
    initializeMenuScreen();
    int8_t lastButtonState = -1;
    int8_t buttonState = -1;
    uint8_t potFactor = 4096/MenuItem::menuItemCount+1;
    while(true)
    {
        int16_t potValue = analogRead(Constants::POT_PIN);
        uint8_t choice = potValue/potFactor;
        if(choice != currentMenuItem) {
            oled.invertText(false);
            oled.print(getName(currentMenuItem), xpos[currentMenuItem], ypos[currentMenuItem]);
            oled.printNumI(MenuItem::menuItems[currentMenuItem]->getVal(),
                           npos[currentMenuItem], ypos[currentMenuItem]);
            oled.invertText(true);
            currentMenuItem = choice;
            oled.print(getName(currentMenuItem), xpos[currentMenuItem], ypos[currentMenuItem]);
            oled.printNumI(MenuItem::menuItems[currentMenuItem]->getVal(),
                           npos[currentMenuItem], ypos[currentMenuItem]);
            oled.update();
        }

        buttonState = digitalRead(Constants::GO_BTN_PIN);
        if(buttonState == 1 && lastButtonState == 0) {
            if(processMenuItem(choice))
            {
                return;
            }
        }
        lastButtonState = buttonState;
        delay(10);
    }
}

bool MenuScreen::processMenuItem(int i)
{
    if(i >= MenuItem::menuItemCount) {
        return true;
    }

    MenuItem *menuItem = MenuItem::menuItems[i];
    oled.clrScr();
    oled.print(menuItem->getName(), 0, 0);
    int8_t lastButtonState = -1, buttonState = 0;
    int16_t potValue;
    while(true)
    {
        potValue = analogRead(Constants::POT_PIN);
        buttonState = digitalRead(Constants::GO_BTN_PIN);
        int16_t convertedValue = potValue*(menuItem->getMax()-menuItem->getMin())/4096 + menuItem->getMin();
        oled.printNumI(convertedValue, 0, 10);
        oled.update();

        if(buttonState == 1 && lastButtonState == 0) {
            menuItem->setVal(convertedValue);
            initializeMenuScreen();
            return false;
        }
        lastButtonState = buttonState;

        delay(10);
    }
}
