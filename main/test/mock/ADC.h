#pragma once
#include "defines.h"

struct adc_prescaler {
	constexpr static int ADC_PRE_PCLK2_DIV_8 = 0;
};

struct adc_smp_rate {
	constexpr static int ADC_SMPR_71_5 = 0;
};

struct adc_reg_map {
    int DR;
	int SQR3;
	int CR2;
	int SR;
};

struct adc_dev {
    adc_reg_map* regs;
};

struct adc_pin_thing {
	adc_dev* adc_device;
};

void adc_set_prescaler(int);
void adc_set_sample_rate(adc_dev*, int);
void adc_set_reg_seqlen(adc_dev*, int);

constexpr int ADC_DR_DATA = 2,
              ADC_CR2_SWSTART = 4,
              ADC_SR_EOC = 8;

adc_pin_thing PIN_MAP[40];

