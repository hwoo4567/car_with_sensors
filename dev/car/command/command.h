#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#define MAX_COMMAND_ARG 3

enum Cmd {
    Null,
    Stop,
    Go,
    Speed,
    Turn,
    Sensor,
};

void commandInit(Timer* timer);
void runCommand(Cmd cmd, String args[]);
void runString(String command_string);

#include "command.cpp"
#endif