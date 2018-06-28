
#include <phys253.h>
#include <LiquidCrystal.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clear bit: and with 11110111
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) // set bit: or with 00001000
#endif

const uint8_t ir_pin = 4;
int8_t sin_vals[] = {0,1,2,2,3,4,5,5,6,7,8,9,9,10,11,12,12,13,14,15,16,16,17,18,19,19,20,21,22,22,23,24,25,26,26,27,28,29,29,30,31,32,32,33,34,35,35,36,37,38,38,39,40,41,41,42,43,44,44,45,46,46,47,48,49,49,50,51,51,52,53,54,54,55,56,56,57,58,58,59,60,61,61,62,63,63,64,65,65,66,67,67,68,69,69,70,71,71,72,72,73,74,74,75,76,76,77,78,78,79,79,80,81,81,82,82,83,84,84,85,85,86,86,87,88,88,89,89,90,90,91,91,92,93,93,94,94,95,95,96,96,97,97,98,98,99,99,100,100,101,101,102,102,102,103,103,104,104,105,105,106,106,106,107,107,108,108,109,109,109,110,110,111,111,111,112,112,112,113,113,113,114,114,114,115,115,115,116,116,116,117,117,117,118,118,118,118,119,119,119,120,120,120,120,121,121,121,121,122,122,122,122,122,123,123,123,123,123,124,124,124,124,124,124,125,125,125,125,125,125,125,126,126,126,126,126,126,126,126,126,126,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127};

int skipped = 0;

const uint8_t prescale = 4;

void setup() {
    
    #include<phys253setup.txt>
    Serial.begin(9600);
    // Set prescaler to 16 - see 
    // http://yaab-arduino.blogspot.com/2015/02/fast-sampling-from-analog-input.html
    if(prescale&4) {
        sbi(ADCSRA, ADPS2);
    } else {
        cbi(ADCSRA, ADPS2);
    }

    if(prescale&2) {
        sbi(ADCSRA, ADPS1);
    } else {
        cbi(ADCSRA, ADPS1);
    }

    if(prescale&1) {
        sbi(ADCSRA, ADPS0);
    } else {
        cbi(ADCSRA, ADPS0);
    }
}


const uint8_t ZERO = 0;
const uint8_t ONE = 1;
const uint8_t TWO = 2;
const uint8_t THREE = 3;
const uint8_t EIGHT = 8;
const uint8_t TWOFIVEFIVE = 255;

inline int8_t sin_t(int16_t x) {
    
    // x is in 1/4096th's of a full revolution
    const uint8_t section = (x>>8)&(3);
    const uint8_t mod = x&255;
    switch(section) {
        case 0: return sin_vals[mod];
        case 1: return sin_vals[255-mod];
        case 2: return -sin_vals[mod];
        default: return -sin_vals[255-mod];
    }
    /*
    switch(section) {
        case 0: return mod;
        case 1: return 255-mod;
        case 2: return -mod;
        default: return -(255-mod);
    } */
}

inline int8_t cos_t(int16_t x) {
    return sin_t(x+768);
    /*
    uint8_t section = (x>>8)&(3);
    uint8_t mod = x&255;
    switch(section) {
        case 0: return sin_vals[255-mod];
        case 1: return -sin_vals[mod];
        case 2: return -sin_vals[255-mod];
        default: return sin_vals[mod];
    } */
}

long lo_amt = 0, hi_amt = 0, min_read, max_read;

long ins[10];
int16_t vals[100], lsin[100], lcos[100];
int loc = 0;

long diff_cnt = 0;
// in 
long freq_amt(long samplePeriod, long goalPeriod) {
    uint8_t analog_reference = 1;
    ADMUX = (analog_reference << 6) | ir_pin;
    sbi(ADCSRA, ADSC);
    
    min_read = 1023;
    max_read = 0;
    skipped = 0;
    lo_amt = 0;
    diff_cnt = 0;
    hi_amt = 0;
    int bck = 0;
    loc=0;
    float sample_rate = 16000.0/13.9/(1<<prescale); // kHz, need to update this because of extra cycles between beginning and ending..
    float lo_freq = 1;
    float hi_freq = 10;
    int lo_ang_delta = int(lo_freq/sample_rate*1024); // in revolutions
    int hi_ang_delta = int(hi_freq/sample_rate*1024); // in revolutions
    //had = lo_ang_delta;
    long lo_cos = 0;
    long hi_cos = 0;
    long lo_sin = 0;
    long hi_sin = 0;
    int16_t lo_ang = 0;
    int16_t hi_ang = 0;
    int s_count = 101;
    long avg = 0;
    int16_t tt, ll = 0;
    int amt = 0;
    for(int it=0;it<s_count;++it) {
        while(bit_is_set(ADCSRA, ADSC));
        //avg = avg + ( (uint8_t) (ADCH<<6)|(ADCL>>2));
        vals[loc] = (uint8_t) (ADCL>>2) | (ADCH<<6);
        avg += vals[loc++];
        ADMUX = (analog_reference << 6) | ir_pin;
        sbi(ADCSRA, ADSC);
        for(int j=0;j<10;++j);
    }
    loc=0;
    avg = (avg+(s_count>>1))/s_count;
    int s_count_ten = s_count/4;
    unsigned long ss = micros();
    diff_cnt = 0;
    for(int it=0;it<s_count;++it) {
        while(bit_is_set(ADCSRA, ADSC));// ++skipped;
        //int16_t tval = (lo_byte>>2) | (hi_byte<<6);
        int16_t tval = (uint8_t) (ADCL>>2) | (ADCH<<6);
        ADMUX = (analog_reference << 6) | ir_pin;
        sbi(ADCSRA, ADSC);
        tval -= avg;
        lo_cos += tval*cos_t(lo_ang);
        lo_sin += tval*sin_t(lo_ang);

        lo_ang += lo_ang_delta;
        lo_ang &= 1023;
    }
    unsigned long ff = micros();
    diff_cnt = ff-ss;
    for(int it=0;it<s_count/4;++it) {
        while(bit_is_set(ADCSRA, ADSC));// ++skipped;
        //int16_t tval = (lo_byte>>2) | (hi_byte<<6);
        int16_t tval = (uint8_t) (ADCL>>2) | (ADCH<<6);
        ADMUX = (analog_reference << 6) | ir_pin;
        sbi(ADCSRA, ADSC);
        
        tval -= avg;
        hi_cos += tval*cos_t(hi_ang);
        hi_sin += tval*sin_t(hi_ang);
        
        hi_ang += hi_ang_delta;
        hi_ang &= 1023;
    }

    float lo_amt_f = sqrt((float) lo_cos*lo_cos + (float) lo_sin*lo_sin);
    float hi_amt_f = sqrt((float) hi_cos*hi_cos + (float) hi_sin*hi_sin);
    lo_amt = lo_amt_f;
    hi_amt = hi_amt_f*4;
    //lo_amt = lo_cos;// + lo_sin;
    //hi_amt = hi_cos;// + hi_sin;
}

int my_analog_read(int ir_pin)
{
    uint8_t analog_reference = 1;
    ADMUX = (analog_reference << 6) | ir_pin;
    sbi(ADCSRA, ADSC);

        for(int i=0;i<1000;++i);
  
        while(bit_is_set(ADCSRA, ADSC));
        int lo_byte = ADCL;
        int hi_byte = ADCH;
        long tval = (hi_byte<<8) | lo_byte;

        return tval;
}


void loop() {

    int val = my_analog_read(ir_pin);

    unsigned long start = micros();
    long lo_tot = 0;
    long hi_tot = 0;
    int sample_cnt = 10;
    for(int i=0;i<sample_cnt;++i) {
        freq_amt(0,0);
        lo_tot += lo_amt/sample_cnt;
        hi_tot += hi_amt/sample_cnt;
    }
    unsigned long fin = micros();

    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(lo_tot);
    LCD.setCursor(10, 0);
    LCD.print(diff_cnt);
    LCD.setCursor(0, 1);
    LCD.print(hi_tot);
    delay(500);

/*
    for(int i=0;i<99;++i) {
        Serial.print(vals[i]);
        Serial.print(" ");
        Serial.print(lsin[i]);
        Serial.print(" ");
        Serial.println(lcos[i]);
    }*/
    /*
    for(int i=0;i<2048;++i) {
      Serial.print(sin_t(i));
      Serial.print(" ");
      Serial.println(cos_t(i));
    } */
    /*
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(fin-start);
    LCD.setCursor(0, 1);
    LCD.print(had);
    delay(1300);
    /*
    LCD.clear();
    delay(50);
    LCD.setCursor(0,0);
    LCD.print(fin-start);
    delay(300);
    LCD.clear();
    delay(50);
    LCD.setCursor(0,0);
    LCD.print(min_read);
    LCD.print(", ");
    LCD.print(max_read);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    delay(300);
    LCD.setCursor(0, 0);
    LCD.print(lo_amt);
    LCD.setCursor(0, 1);
    LCD.print(hi_amt);
    
    /*
    LCD.setCursor(0,0);
    for(int i=0;i<5;++i) {
      LCD.print(ins[i]);
      LCD.print(",");
    }
    LCD.setCursor(0,1);
    for(int i=3;i<10;++i) {
      LCD.print(ins[i]);
      LCD.print(",");
    }
    */
    //delay(1000); 
    /*
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(sin_t(512));
    LCD.print(",");
    LCD.print(sin_t(1024));
    LCD.setCursor(0, 1);
    LCD.print(cos_t(512));
    LCD.print(",");
    LCD.print(cos_t(1024));
    delay(1000); */
    LCD.clear();
    delay(100);
}

