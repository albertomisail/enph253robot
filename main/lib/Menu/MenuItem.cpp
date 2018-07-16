#include "MenuItem.h"

int MenuItem::menuItemCount = 0;
MenuItem* MenuItem::menuItems[MAX_MENU_ITEMS];

int16_t MenuItem::getVal()
{
    return val;
}
void MenuItem::setVal(int16_t _val)
{
    val = _val;
}
int16_t MenuItem::getMin()
{
    return myMin;
}
int16_t MenuItem::getMax()
{
    return myMax;
}
