#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_SPEED    255
#define LEFT           0
#define RIGHT          1
#include <AFMotor.h>
#include "motor.cpp"

void motorInit(uint8_t l_num, uint8_t r_num);
void motorInit(uint8_t l_num, uint8_t r_num, uint8_t line_trance_sensor_pin);
void motorStop();
void motorGo(uint8_t cmd);
void motorSetSpeed(uint8_t speed);
void motorTurn(uint8_t direction);

#endif