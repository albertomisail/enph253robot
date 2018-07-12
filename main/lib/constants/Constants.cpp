#include "Constants.h"

uint8_t Constants::lowPwmPins[2] = {PA0, PA2};
uint8_t Constants::highPwmPins[2] = {PA1, PA3};

void Constants::load(int16_t addr)
{
    // TODO: What happens if overflowing EEPROM?
    for(int i=0;i<static_cast<int>(size());++i)
    {
        *((char*)this+i) = EEPROM.read(addr+i);
    }
}

void Constants::dump(int16_t addr)
{
    // TODO: What happens if overflowing EEPROM?
    for(int i=0;i<static_cast<int>(size());++i)
    {
        EEPROM.write(addr+i, *((char*)this+i));
    }
}

constexpr size_t Constants::size() {
    return sizeof(Constants);
}
