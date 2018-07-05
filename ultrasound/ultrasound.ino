/*
   TINAH template
*/

#include <phys253.h>
#include <LiquidCrystal.h>

const uint8_t trig_pin[] = {5, 6, 7};
const uint8_t echo_pin[] = {10, 8, 9};

void setup()
{
  //#include<phys253setup.txt>
  Serial.begin(9600);
  pinMode(trig_pin[0], OUTPUT);
  pinMode(trig_pin[1], OUTPUT);
  pinMode(trig_pin[2], OUTPUT);
  
  pinMode(echo_pin[0], INPUT);
  pinMode(echo_pin[1], INPUT);
  pinMode(echo_pin[2], INPUT);
  
  //pinMode(0, INPUT);
  //DDRD = B11111111;
  //pinMode(echo_pin, INPUT);
}

float getDistance(int sensor) {
    //pinMode(trig_pin, OUTPUT);
    digitalWrite(trig_pin[sensor], LOW);
    delayMicroseconds(10);
    digitalWrite(trig_pin[sensor], HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin[sensor], LOW);
    float microseconds = pulseIn(echo_pin[sensor], HIGH, 10000);
    return microseconds/58;
}

void loop()
{
    for(int i=0;i<3;++i) {
        LCD.clear();
        LCD.print("sensor ");
        LCD.print(i);
        LCD.print(":");
        LCD.print(getDistance(i));
        LCD.print("cm");
        delay(1000);
    }
}

