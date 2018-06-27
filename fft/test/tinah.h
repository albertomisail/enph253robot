#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <cassert>

const int ADCSRA = 0;
const int ADSC = 0;
const int ADPS0 = 1;
const int ADPS1 = 2;
const int ADPS2 = 3;

uint8_t ADCL = 0;
uint8_t ADCH = 0;

namespace TINAH {
    double sin_loc = 1;
    double offset = 50;
    double amplitude = 20;
    double wave_freq = 1.2; // kHz
    //int8_t ADCSRA_VAL = 0;
    double PI = 3.14159265358979;
    uint8_t REGS[100];


    int get_prescaler() {
        return 1<<((REGS[ADCSRA] >> ADPS0) & 7);
    }

    double get_frequency() { // kHz
        return 16000.0/13/get_prescaler();
    }

    void increment_sin() {
        sin_loc += 2*PI*wave_freq/get_frequency();
    }
    int16_t get_val() {
        return (int) (sin(sin_loc)*amplitude + offset);
    }

};


void sbi(int a, int b) {
    /*
    switch(b) {
        case ADSC: TODO; break;
        case ADPS0: TINAH::my_prescaler |= 1; break;
        case ADPS1: TINAH::my_prescaler |= 2; break;
        case ADPS2: TINAH::my_prescaler |= 4; break;
        default: break;
    } */
    TINAH::REGS[a] |= (1<<b);
}

void cbi(int a, int b) {
    const static int all = (1<<8) - 1;
    TINAH::REGS[a] &= (all^(1<<b));
}

bool bit_is_set(int a, int b) {
    // TODO: HANDLE SPECIAL CASES LIKE ADCSRA ADSC...
    if(a == ADCSRA && b == ADSC) {
        cbi(ADCSRA, ADSC);
        int16_t val = TINAH::get_val();
        TINAH::increment_sin();
        ADCL = val & 255;
        ADCH = (val>>8) & 255;
		//assert((ADCL | (ADCH<<8)) < 1024);
    }
    return (TINAH::REGS[a] & (1<<b)) != 0;
}

int ADMUX;

struct MyLCD {
    void clear() {
        std::cout << std::endl;
    }
    void setCursor(int a, int b) {
        std::cout << std::endl;
    }
    void print(int a) {
        std::cout << a << std::endl;
    }
    void print(std::string s) {
        std::cout << s << std::endl;
    }
    void print(char* c) {
        std::cout << c << std::endl;
    }

};

void delay(int millis) {
    usleep(millis*1000);
}

MyLCD LCD;
