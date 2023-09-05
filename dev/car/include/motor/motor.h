#ifndef MOTOR_H
#define MOTOR_H

#include <AFMotor.h>
#define MOTOR_SPEED    255
#define MOTOR_UPDATE   50

#define STOP      0
#define DRIVING   1
#define TURNING   2

// 자동차 회전 방향
#define LEFT           0
#define RIGHT          1

// 회전할 때 걸리는 시간 (ms)
#define TURNING_TIME   500

/*
Declaration:
void function_name(AF_DCMotor* motor_l, AF_DCMotor* motor_r) {
    ...
}
*/
typedef void (*motor_callback)(AF_DCMotor* l, AF_DCMotor* r);

void motorInit(uint8_t l_num, uint8_t r_num, uint8_t speed, motor_callback adjustMotorCallback);
void motorInit(uint8_t l_num, uint8_t r_num);

bool isDriving();

// 모터를 작동시키는 함수
void motorStop();
void motorGo(uint8_t cmd);
void motorSetSpeed(uint8_t l, uint8_t r);
void motorSetSpeed(uint8_t speed);
void motorTurn(uint8_t direction);

#include "motor.cpp"
#endif