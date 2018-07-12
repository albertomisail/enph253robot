#pragma once
#include <Arduino.h>

class MenuItem {
private:
    const char* name;
    const int16_t myMin, myMax;
    // TODO track menu items

public:
    //MenuItem();
    int16_t val;

    constexpr MenuItem(const char* _name, int16_t _myMin, int16_t _myMax)
        : name(_name), myMin(_myMin), myMax(_myMax), val(0)
    {}
    constexpr MenuItem(const char* _name, int16_t _myMin, int16_t _myMax, int16_t _defaultValue)
        : name(_name), myMin(_myMin), myMax(_myMax), val(_defaultValue)
    {}
    constexpr char* getName()
    {
        return const_cast<char*>(name);
    }
    int16_t getVal();
    void setVal(int16_t _val);
    constexpr int16_t getMin();
    constexpr int16_t getMax();
};
