#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#include <Timer.h>
#define MAX_COMMAND_ARG 3

Timer* main_timer = nullptr;  //* 전역 타이머 객체 포인터

enum Cmd {
    Null,
    Stop,
    Go,
    Speed,
    Turn,
    Sensor,
};

void commandInit(Timer* timer);
void runCommand(Cmd cmd, String args[], String& response);
void runString(String command_string, String& response);

#include "command.cpp"
#endif