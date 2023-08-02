#include "motor.h"

AF_DCMotor* _motor_l;
AF_DCMotor* _motor_r;

uint8_t speed_l = MOTOR_SPEED;
uint8_t speed_r = MOTOR_SPEED;

motor_inst_func _adjustMotorCallback = nullptr;
void _callback() {
    _adjustMotorCallback(_motor_l, _motor_r);
}

/////////////////////////////////////////////////////////////////////

void motorInit(uint8_t l_num, uint8_t r_num, motor_inst_func adjustMotorCallback) {
    _motor_l = new AF_DCMotor(l_num);
    _motor_r = new AF_DCMotor(r_num);

    _motor_l->setSpeed(MOTOR_SPEED);
    _motor_r->setSpeed(MOTOR_SPEED);
    _motor_l->run(RELEASE);
    _motor_r->run(RELEASE);

    _adjustMotorCallback = adjustMotorCallback;
    
    if (adjustMotorCallback != nullptr) {
        main_timer->every(100, _callback);
    }
}

void motorInit(uint8_t l_num, uint8_t r_num) {
    motorInit(l_num, r_num, (motor_inst_func) nullptr);
}

void motorStop() {
    _motor_l->run(RELEASE);
    _motor_r->run(RELEASE);
}

void motorGo(uint8_t direction) {
    switch (direction) {
    case FORWARD:
        _motor_l->run(FORWARD);
        _motor_r->run(FORWARD);
        break;
    case BACKWARD:
        _motor_l->run(BACKWARD);
        _motor_r->run(BACKWARD);
        break;
    case RELEASE:
        motorStop();
        break;
    default:
        break;
    }
}

void motorSetSpeed(uint8_t l, uint8_t r) {
    _motor_l->setSpeed(l);
    _motor_r->setSpeed(r);
    speed_l = l;
    speed_r = r;
}

void motorSetSpeed(uint8_t speed) {
    motorSetSpeed(speed);
}

void motorTurn(bool direction) {
    // Only point turn.

    switch (direction) {
    case LEFT:
        _motor_l->run(BACKWARD);
        _motor_r->run(FORWARD);
        break;
    case RIGHT:
        _motor_l->run(FORWARD);
        _motor_r->run(BACKWARD);
        break;
    default:
        break;
    }
}