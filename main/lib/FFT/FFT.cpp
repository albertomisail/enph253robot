#include "FFT.h"

// Define cbi, sbi macros if not defined already (clear bit, set bit)
#ifndef cbi
template<typename T, typename U>
void FFT::cbi(T& x, U& y)
{
    x &= ~(1<<y);
}
template<typename T, typename U>
void FFT::sbi(T& x, U& y)
{
    x |= (1<<y);
}
#endif

inline int8_t FFT::sin_t(int16_t x)
{
    const uint8_t section = (x>>8)&(3);
    const uint8_t mod = x&255;
    switch(section) {
        case 0: return sinVals[mod];
        case 1: return sinVals[255-mod];
        case 2: return -sinVals[mod];
        default: return -sinVals[255-mod];
    }
}

inline int8_t FFT::cos_t(int16_t x)
{
    return sin_t(x);
}

inline void FFT::setupSample() const
{
    // Registers in the ADC which we can alter
    adc_reg_map *regs = dev->regs;

    // I think this means that we only want to sample from one pin
    adc_set_reg_seqlen(dev, 1);

    // May or may not be magic
    regs->SQR3 = Constants::IR_BEACON_PIN;
    regs->CR2 |= ADC_CR2_SWSTART;
}

inline int16_t FFT::waitForSample() const {
    adc_reg_map *regs = dev->regs;

    // SR is status register, so we wait until the status register is set to 1
    while (!(regs->SR & ADC_SR_EOC));

    return (uint16)(regs->DR & ADC_DR_DATA);
}

int16_t FFT::baselineAverage() const {
    setupSample();
    int32_t sum = 0;
    for(int i = 0;i<sampleCount;++i)
    {
        sum += waitForSample();
        setupSample();
    }
    waitForSample();
    sum += (sampleCount/2);
    return sum/sampleCount;
}

void FFT::init() {
    pinMode(Constants::IR_BEACON_PIN, INPUT_ANALOG);
    // dev is the adc_device object corresponding to this pin.
    dev = PIN_MAP[Constants::IR_BEACON_PIN].adc_device;
    if(dev == NULL)
    {
        oled.clrScr();
        oled.print(const_cast<char*>("NO SUCH ADC DEV"), 0, 0);
        oled.update();
        delay(2000);
    }
    adc_set_prescaler(adc_prescaler::ADC_PRE_PCLK2_DIV_8);
    adc_set_sample_rate(dev, adc_smp_rate::ADC_SMPR_71_5);
}

inline int32_t FFT::sampleFrequency(const int16_t& ang_delta,
                                    const int16_t& times,
                                    const int16_t& baseline) const {
    int32_t sinAmt=0, cosAmt=0;
    setupSample();
    int16_t ang = 0;
    for(int it=0;it<times;++it)
    {
        int16_t sampleValue = waitForSample();
        setupSample();
        sinAmt += ((sampleValue-baseline)>>2)*sin_t(ang);
        ang += ang_delta;
    }
    waitForSample();
    return (int32_t) sqrt((float)sinAmt*sinAmt + (float)cosAmt*cosAmt);
}

FFTPair FFT::sample() const {
    FFTPair ans;
    // Must disable interrupts during sampling to avoid unpredictable
    // sampling intervals
    noInterrupts();
    int16_t baseline = baselineAverage();
    ans.lowAmount = sampleFrequency(loAngDelta, sampleCount, baseline);
    ans.highAmount = sampleFrequency(hiAngDelta, sampleCount/4, baseline)*4;
    interrupts();
    return ans;
}

FFT fft;
