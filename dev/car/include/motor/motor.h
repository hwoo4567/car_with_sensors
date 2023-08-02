#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_SPEED    255
#define LEFT           false
#define RIGHT          true

#include <AFMotor.h>

/*
Declaration:
void function_name(AF_DCMotor* motor_l, AF_DCMotor* motor_r) {
    ...
}
*/
typedef void (*motor_inst_func)(AF_DCMotor* l, AF_DCMotor* r);

void motorInit(uint8_t l_num, uint8_t r_num, motor_inst_func adjustMotorCallback);
void motorInit(uint8_t l_num, uint8_t r_num);
void motorStop();
void motorGo(uint8_t cmd);
void motorSetSpeed(uint8_t l, uint8_t r);
void motorSetSpeed(uint8_t speed);
void motorTurn(bool direction);

#include "motor.cpp"
#endif