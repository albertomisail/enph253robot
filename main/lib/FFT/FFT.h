#pragma once
#include <Arduino.h>
#include "Constants.h"
#include <OLED_I2C.h>

class FFTPair {
public:
    int32_t highAmount, lowAmount;
};

class FFT {
private:
#ifndef cbi
    template<typename T, typename U>
    void cbi(T& x, U& y);
    template<typename T, typename U>
    void sbi(T& x, U& y);
#endif
    // NOTE: sample rate _should_ be 72MHz/prescaler/adc_smp_rate...
    //constexpr static float sampleRate = 72000/8/84; // to be set later
    constexpr static float sampleRate = 104.42;
    constexpr static float loFreq = 1, hiFreq = 10;
    constexpr static int16_t loAngDelta = (int16_t) (loFreq/sampleRate*1024);
    constexpr static int16_t hiAngDelta = (int16_t) (hiFreq/sampleRate*1024);
    constexpr static int16_t sampleCount = 500;
    constexpr static int8_t sinVals[] = {0,1,2,2,3,4,5,5,6,7,8,9,9,10,11,12,12,13,14,15,16,16,17,18,19,19,20,21,22,22,23,24,25,26,26,27,28,29,29,30,31,32,32,33,34,35,35,36,37,38,38,39,40,41,41,42,43,44,44,45,46,46,47,48,49,49,50,51,51,52,53,54,54,55,56,56,57,58,58,59,60,61,61,62,63,63,64,65,65,66,67,67,68,69,69,70,71,71,72,72,73,74,74,75,76,76,77,78,78,79,79,80,81,81,82,82,83,84,84,85,85,86,86,87,88,88,89,89,90,90,91,91,92,93,93,94,94,95,95,96,96,97,97,98,98,99,99,100,100,101,101,102,102,102,103,103,104,104,105,105,106,106,106,107,107,108,108,109,109,109,110,110,111,111,111,112,112,112,113,113,113,114,114,114,115,115,115,116,116,116,117,117,117,118,118,118,118,119,119,119,120,120,120,120,121,121,121,121,122,122,122,122,122,123,123,123,123,123,124,124,124,124,124,124,125,125,125,125,125,125,125,126,126,126,126,126,126,126,126,126,126,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127};

    adc_dev *dev;

    static int8_t sin_t(int16_t x);
    static int8_t cos_t(int16_t x);
    int16_t baselineAverage() const;
    int32_t sampleFrequency(const int16_t&, const int16_t&, const int16_t&);

public:
    int32_t sampleTime;
    void setupSample() const;
    int16_t waitForSample() const;
    void init();
    FFTPair sample();
};

extern FFT fft;
