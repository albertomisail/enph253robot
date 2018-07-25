#pragma once
#include <Arduino.h>

class MenuItem {
public:
    const static uint8_t MAX_MENU_ITEMS = 30;
private:
    char* name;
    int16_t myMin, myMax;
    uint8_t myInd;

public:
    static MenuItem* menuItems[MAX_MENU_ITEMS];
    //MenuItem();
    static int menuItemCount;
    int16_t val;

    MenuItem() {}

    /*constexpr*/ MenuItem(char* _name, int16_t _myMin, int16_t _myMax)
        : name(_name), myMin(_myMin), myMax(_myMax), val(0)
    {
        myInd = menuItemCount;
        menuItems[menuItemCount++] = this;
    }
    /*constexpr*/ MenuItem(char* _name, int16_t _myMin, int16_t _myMax, int16_t _defaultValue)
        : name(_name), myMin(_myMin), myMax(_myMax), val(_defaultValue)
    {
        myInd = menuItemCount;
        menuItems[menuItemCount++] = this;
    }
    /*constexpr*/ char* getName()
    {
        return name;
    }

    MenuItem& operator= (MenuItem&& m)
    {
        name = m.name;
        myMin = m.myMin;
        myMax = m.myMax;
        myInd = m.myInd;
        val = m.val;
        menuItems[myInd] = this;
        return *this;
    }

    int16_t getVal();
    void setVal(int16_t _val);
    int16_t getMin();
    int16_t getMax();
    static size_t size() {
        return menuItemCount;
    }
};
