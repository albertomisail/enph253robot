#pragma once
#include <Arduino.h>

class MenuItem {
public:
    const static uint8_t MAX_MENU_ITEMS = 30;
private:
    const char* name;
    const int16_t myMin, myMax;

public:
    static MenuItem* menuItems[MAX_MENU_ITEMS];
    //MenuItem();
    static int menuItemCount;
    int16_t val;

    /*constexpr*/ MenuItem(const char* _name, int16_t _myMin, int16_t _myMax)
        : name(_name), myMin(_myMin), myMax(_myMax), val(0)
    {
        menuItems[menuItemCount++] = this;
    }
    /*constexpr*/ MenuItem(const char* _name, int16_t _myMin, int16_t _myMax, int16_t _defaultValue)
        : name(_name), myMin(_myMin), myMax(_myMax), val(_defaultValue)
    {
        menuItems[menuItemCount++] = this;
    }
    /*constexpr*/ char* getName()
    {
        return const_cast<char*>(name);
    }
    int16_t getVal();
    void setVal(int16_t _val);
    int16_t getMin();
    int16_t getMax();
    static size_t size() {
        return menuItemCount;
    }
};
