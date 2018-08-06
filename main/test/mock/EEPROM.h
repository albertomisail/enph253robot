#pragma once

class EEPROMBase {
public:
    int16_t read(int16_t);
    void write(int16_t, int16_t);
};

extern EEPROMBase EEPROM;
