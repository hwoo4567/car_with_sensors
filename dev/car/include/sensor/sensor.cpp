#include "sensor.h"
#define UPDATE_INTERVAL 100  // ms

// Sensors for line tracing
uint8_t _line_l_pin, _line_r_pin;
uint8_t _light_sensor;  // light sensor pin
int _line_l_val, _line_r_val;  // 0 - 1024
int _light_sensor_val;

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
    _line_l_val = analogRead(_line_l_pin);
    _line_r_val = analogRead(_line_r_pin);
}

void _updateLightSensor() {
    _light_sensor_val = analogRead(_light_sensor);
}

/////////////////////////////////////////////////////////////////////

// Init functions must be called after commandInit() was called.

void distanceInit(uint8_t trig, uint8_t echo) {
    _trig_pin = trig;
    _echo_pin = echo;
    pinMode(_trig_pin, OUTPUT);
    pinMode(_echo_pin, INPUT);

    main_timer->every(UPDATE_INTERVAL, _updateDistance);
}

void lineTraceInit(uint8_t l_pin, uint8_t r_pin) {
    _line_l_pin = l_pin;
    _line_r_pin = r_pin;

    main_timer->every(UPDATE_INTERVAL, _updateLineSensors);
}

void lightInit(uint8_t light_pin) {
    _light_sensor = light_pin;

    main_timer->every(UPDATE_INTERVAL, _updateLightSensor);
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
int getLightVal() {
    return _light_sensor_val;
}