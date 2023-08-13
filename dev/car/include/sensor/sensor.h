#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

void lineTraceInit(uint8_t l_pin, uint8_t r_pin);
void distanceInit(uint8_t trig, uint8_t echo);

double getDistance();
int getLineLSensorVal();
int getLineRSensorVal();
int getLightVal();

#include "sensor.cpp"
#endif