#include "sensor.h"

// Sensors for line tracing
uint8_t line_l, line_r;
int _line_l_val, _line_r_val;  // 0 - 1023

// Sensor pins for distance check
uint8_t _trig_pin;
uint8_t _echo_pin;

double _distance; 

// !WARNING: This function contains delay() function
void _updateDistance() {
    unsigned long duration;

    digitalWrite(_trig_pin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig_pin, LOW);

    duration = pulseIn(_echo_pin, HIGH); 

    _distance = ((double) duration) * 17.0 * 0.001;
}

void _updateLineSensors() {
    _line_l_val = analogRead(line_l);
    _line_r_val = analogRead(line_r);
}

/////////////////////////////////////////////////////////////////////

// Init functions must be called after commandInit() was called.

void distanceInit(uint8_t trig, uint8_t echo) {
    _trig_pin = trig;
    _echo_pin = echo;
    pinMode(_trig_pin, OUTPUT);
    pinMode(_echo_pin, INPUT);

    main_timer->every(100, _updateDistance);
}

void lineTraceInit(uint8_t l_pin, uint8_t r_pin) {
    line_l = l_pin;
    line_r = r_pin;

    main_timer->every(100, _updateLineSensors);
}

double getDistance() {
    return _distance;
}
int getLineLSensorVal() {
    return _line_l_val;
}
int getLineRSensorVal() {
    return _line_r_val;
}