#include <Arduino.h>
#include "motor.h"

AF_DCMotor* motor_l;
AF_DCMotor* motor_r;

uint8_t speed_l = MOTOR_SPEED;
uint8_t speed_r = MOTOR_SPEED;

void motorInit(uint8_t l_num, uint8_t r_num) {
    motorInit(l_num, r_num, 0);
}

void motorInit(uint8_t l_num, uint8_t r_num, uint8_t line_trance_sensor_pin) {
    motor_l = new AF_DCMotor(l_num);
    motor_r = new AF_DCMotor(r_num);

    motor_l->setSpeed(MOTOR_SPEED);
    motor_r->setSpeed(MOTOR_SPEED);
    motor_l->run(RELEASE);
    motor_r->run(RELEASE);
}

void motorStop() {
    motor_l->run(RELEASE);
    motor_r->run(RELEASE);
}

void motorGo(uint8_t direction) {
    switch (direction) {
    case FORWARD:
        motor_l->run(FORWARD);
        motor_r->run(FORWARD);
        break;
    case BACKWARD:
        motor_l->run(BACKWARD);
        motor_r->run(BACKWARD);
        break;
    case RELEASE:
        motorStop();
        break;
    }
}

void motorSetSpeed(uint8_t speed) {
    motor_l->setSpeed(speed);
    motor_r->setSpeed(speed);
    speed_l = speed;
    speed_r = speed;
}

void motorTurn(uint8_t direction) {
    // Only point turn.

    switch (direction) {
    case LEFT:
        motor_l->run(BACKWARD);
        motor_r->run(FORWARD);
        break;
    case RIGHT:
        motor_l->run(FORWARD);
        motor_r->run(BACKWARD);
        break;
    case RELEASE:
        motorStop();
        break;
    }
}

void motorAdjust() {

}