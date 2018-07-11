#include <Arduino.h>
#include <MotorBase.h>
#include <OLED_I2C.h>
#include <PIDScreen.h>
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

const unsigned int K_P = 3;
const unsigned int K_I = 2;
const unsigned int K_D = 4;
const unsigned int B_S = 6;

const unsigned int SENSOR_LEFT = PA4;
const unsigned int SENSOR_RIGHT = PA5;
const unsigned int MOTOR_LEFT = 0;
const unsigned int MOTOR_RIGHT = 1;
/*const */int THRESHOLD_LEFT = 100;
/*const */int THRESHOLD_RIGHT = 100;
const int MAX_INTEGRAL_VALUE = 5;

int base_speed = 255;

int error = 0;
int previous_error = 0;
float delta_t = 0;
float previous_time = 0;

unsigned int counter = 1;
unsigned int loop_counter = 0;

int k_i, k_d = 0;
int k_p =92;
char str[50];
char str2[50];
int last_g = 0;

float i = 0;

void setup() {
    motor.init();
    // put your setup code here, to run once:
    oled.begin();
    oled.setFont(SmallFont);
    // for(const auto& x : trig_pin) {
    //     pinMode(x, OUTPUT);
    // }
    // for(const auto& x : echo_pin) {
    //     pinMode(x, INPUT);
    // }

    //pidScreen.begin();
    /*
    k_p = pidScreen.vals[0];
    k_i = pidScreen.vals[1];
    k_d = pidScreen.vals[2];
    base_speed = pidScreen.vals[3];
    THRESHOLD_LEFT = pidScreen.vals[4]<<4;
    THRESHOLD_RIGHT= pidScreen.vals[5]<<4;
    */
    //base_speed = pidScreen.vals[0];
}

void loop() {
    /*oled.print("HI", 0, 0);
    oled.update(); */

    oled.clrScr();
    int val = (analogRead(POT_PIN)>>3)-255;
    oled.printNumI(val, 0, 0);
    oled.update();
    motor.speed(0, val);
    motor.speed(1, val);

    delay(15);

    // put your main code here, to run repeatedly:
    /*
    oled.clrScr();
    oled.printNumI(pval, 0, 0);
    oled.update(); */
    /*
    float now = millis();
    delta_t = now - previous_time;

    float sensor_left_reading = analogRead(SENSOR_LEFT);
    float sensor_right_reading = analogRead(SENSOR_RIGHT);

    if(loop_counter % 1000 == 0){
        oled.clrScr();
        oled.print("P:", 0, 0);
        oled.print("I:", 0, 10);
        oled.print("D:", 0, 20);
        oled.print("S:", 0, 30);
        oled.print("E:", 0, 40);
        oled.printNumI(k_p, 20, 0);
        oled.printNumI(k_i, 20, 10);
        oled.printNumI(k_d, 20, 20);
        oled.printNumI(base_speed, 20, 30);
        oled.printNumI(previous_error, 20, 40);
        oled.print("L: ", 0, 50);
        oled.print("R: ", 50, 50);
        oled.printNumI((int) sensor_left_reading, 15, 50);
        oled.printNumI((int) sensor_right_reading, 65, 50);
        oled.update();
    }

    if(sensor_left_reading >= THRESHOLD_LEFT && sensor_right_reading >= THRESHOLD_RIGHT){
        error = 0;
    }
    else if(sensor_left_reading >= THRESHOLD_LEFT && sensor_right_reading < THRESHOLD_RIGHT){
        error = 1;
    }
    else if(sensor_left_reading < THRESHOLD_LEFT && sensor_right_reading >= THRESHOLD_RIGHT){
        error = -1;
    }
    else{
        if(previous_error == 5 || previous_error == -5){
        error = previous_error;
        }
        else{
        error = 5 * previous_error;
        }
    }

    float p = k_p * error;

    i = k_i * error * now + i;
    if(i > MAX_INTEGRAL_VALUE){
        i = MAX_INTEGRAL_VALUE;
    }
    else if(i < -MAX_INTEGRAL_VALUE){
        i = -MAX_INTEGRAL_VALUE;
    }

    float d = 0;

    if(error == previous_error){
        counter++;
    }
    else{
        counter = 1;
    }
    d = k_d * (error - previous_error) / (delta_t * counter);

    int g = (int) (p + i + d);

    motor.speed(MOTOR_LEFT, -base_speed - g);
    motor.speed(MOTOR_RIGHT, base_speed - g);

    previous_error = error;
    previous_time = now;
    loop_counter++; */
}
