#include "MenuItem.h"

int16_t MenuItem::getVal()
{
    return val;
}
void MenuItem::setVal(int16_t _val)
{
    val = _val;
}
constexpr int16_t MenuItem::getMin()
{
    return myMin;
}
constexpr int16_t MenuItem::getMax()
{
    return myMax;
}
