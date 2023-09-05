#include "motor.h"

AF_DCMotor* _motor_l;
AF_DCMotor* _motor_r;

uint8_t speed_l = MOTOR_SPEED;
uint8_t speed_r = MOTOR_SPEED;

uint8_t _driving = STOP;

motor_callback _adjustMotorCallback = nullptr;
void _callback() {
    _adjustMotorCallback(_motor_l, _motor_r);
}

/////////////////////////////////////////////////////////////////////

void motorInit(uint8_t l_num, uint8_t r_num, uint8_t speed, motor_callback adjustMotorCallback) {
    _motor_l = new AF_DCMotor(l_num);
    _motor_r = new AF_DCMotor(r_num);

    _motor_l->setSpeed(speed);
    _motor_r->setSpeed(speed);
    speed_l = speed;
    speed_r = speed;

    _motor_l->run(RELEASE);
    _motor_r->run(RELEASE);

    _adjustMotorCallback = adjustMotorCallback;
    
    if (adjustMotorCallback != nullptr) {
        main_timer->every(MOTOR_UPDATE, _callback);
    }
}

void motorInit(uint8_t l_num, uint8_t r_num) {
    motorInit(l_num, r_num, MOTOR_SPEED, (motor_callback) nullptr);
}

inline bool isDriving() { return _driving == DRIVING; }
inline bool isTurning() { return _driving == TURNING; }
inline bool isStopped() { return _driving == STOP; }

void motorStop() {
    _motor_l->run(RELEASE);
    _motor_r->run(RELEASE);

    _driving = STOP;
}

void motorGo(uint8_t direction) {
    _driving = DRIVING;

    switch (direction) {
    case FORWARD:
        _motor_l->run(FORWARD);
        _motor_r->run(FORWARD);
        break;
    case BACKWARD:
        _motor_l->run(BACKWARD);
        _motor_r->run(BACKWARD);
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
    motorSetSpeed(speed, speed);
}

void motorTurn(uint8_t direction) {
    // Only point turn.
    _driving = TURNING;

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