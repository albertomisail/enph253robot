#include <Arduino.h>
#include <OLED_I2C.h>
#include <Screen.h>
#include <MyOLED.h>

/**
 * PID values determined from lab jul 6:
 *
 * P:
 * I:
 * D:
 *
 *
 */

extern uint8_t SmallFont[];

int16_t THRESHOLD;
uint8_t IR_PIN = PA2;
uint8_t POWER_PIN = PA4;

void setup() {
    // put your setup code here, to run once:
    oled.begin();
    oled.setFont(SmallFont);
    pinMode(IR_PIN, INPUT);
    pinMode(POWER_PIN, OUTPUT);
    // for(const auto& x : trig_pin) {
    //     pinMode(x, OUTPUT);
    // }
    // for(const auto& x : echo_pin) {
    //     pinMode(x, INPUT);
    // }

    //screen.begin();
    THRESHOLD = screen.vals[0];
    //base_speed = pidScreen.vals[0];
}

void loop() {
    int base = analogRead(IR_PIN);
    digitalWrite(POWER_PIN, HIGH);
    delay(50);
    digitalWrite(POWER_PIN, LOW);
    int after = analogRead(IR_PIN);
    oled.clrScr();
    oled.print("diff: ", 0, 0);
    oled.printNumI((after-base), 35, 0);
    oled.update();
    delay(100);
}
