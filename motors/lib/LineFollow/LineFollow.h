#pragma once
#include <Arduino.h>

class LineFollow {
private:
public:
    static int k_i, k_p, k_d;
    static void poll();
    static void setup();
};
