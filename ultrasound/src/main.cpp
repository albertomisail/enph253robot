#include <Arduino.h>
#include <OLED_I2C.h>

extern uint8_t SmallFont[];

OLED oled(PB7, PB6, 8);

const uint8_t trig_pin[] = {PB12};
const uint8_t echo_pin[] = {PB13};

static_assert(sizeof trig_pin == sizeof echo_pin);

void setup() {
    // put your setup code here, to run once:
    oled.begin();
    oled.setFont(SmallFont);
    for(const auto& x : trig_pin) {
        pinMode(x, OUTPUT);
    }
    for(const auto& x : echo_pin) {
        pinMode(x, INPUT);
    }
}

float getDistance(int8_t sensor) {
    digitalWrite(trig_pin[sensor], LOW);
    delayMicroseconds(10);
    digitalWrite(trig_pin[sensor], HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin[sensor], LOW);
    float microseconds = pulseIn(echo_pin[sensor], HIGH, 60000);
    return microseconds/58;
}

void loop() {
    oled.clrScr();
    for(int i=0;i<3;++i)
    {
        oled.printNumI(i, 0, i*10);
        oled.print(":", 7, i*10);
        if(static_cast<size_t>(i) < sizeof trig_pin) {
            double dist = getDistance(i);
            oled.printNumF(dist, 10, 20, i*10);
        }
    }
    delay(60);
    oled.update();
    //delay(500);
    oled.clrScr();
    oled.update();
    //delay(200);
    // put your main code here, to run repeatedly:
}
