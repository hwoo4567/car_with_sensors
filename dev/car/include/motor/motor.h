#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_SPEED    255
#define LEFT           0
#define RIGHT          1

void motorInit(uint8_t l_num, uint8_t r_num, uint8_t line_trance_sensor_pin);
void motorInit(uint8_t l_num, uint8_t r_num);
void motorStop();
void motorGo(uint8_t cmd);
void motorSetSpeed(uint8_t speed);
void motorTurn(uint8_t direction);

#include "motor.cpp"
#endif