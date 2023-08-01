#include <Timer.h>
#include "command.h"
#include "motor.h"

Timer* main_timer = nullptr;
int* prevMoveCmdId = nullptr;

// *******************************************

void _stopAll() {
    motorStop();

    if (prevMoveCmdId != nullptr) {
        main_timer->stop(*prevMoveCmdId);
    }
    prevMoveCmdId = nullptr;
}

void stop(String args[]) {
    _stopAll();
}

void go(String args[]) {
    _stopAll();

    if (args[0] == "forward") {
        motorGo(FORWARD);
    }
    if (args[0] == "backward") {
        motorGo(BACKWARD);
    }

    // .toInt() : 숫자로 시작되지 않거나 값이 0일 때 return 0;
    int move_millisec = args[1].toInt();
    if (move_millisec > 0) {
        *prevMoveCmdId = main_timer->after(move_millisec, _stopAll);
    }
}

void speed(String args[]) {
    int val = args[0].toInt();
    motorSetSpeed( (val <= 255 && val >= 0) ? val : 0 );
}

void turn(String args[]) {
    _stopAll();

    if (args[0] == "left") {
        motorTurn(LEFT);
    }
    if (args[0] == "right") {
        motorTurn(RIGHT);
    }

    // .toInt() : 숫자로 시작되지 않거나 값이 0일 때 return 0;
    int move_millisec = args[1].toInt();
    if (move_millisec > 0) {
        *prevMoveCmdId = main_timer->after(move_millisec, _stopAll);
    }
}

uint16_t sensor(String args[]) {
    return 0;
}

// *******************************************

void commandInit(Timer* timer) {
    main_timer = timer;
    main_timer->every(100, motorAdjust);
}

void runCommand(Cmd cmd, String args[]) {
    switch (cmd)
    {
    case Stop:
        stop(args);
        break;
    case Go:
        go(args);
        break;
    case Speed:
        speed(args);
        break;
    case Turn:
        turn(args);
        break;
    case Sensor:
        sensor(args);
        break;

    default:
        break;
    }
}

Cmd toCommand(const char* input) {
    if (strcmp(input, "stop") == 0) {
        return Cmd::Stop;
    }
    else if (strcmp(input, "go") == 0) {
        return Cmd::Go;
    }
    else if (strcmp(input, "speed") == 0) {
        return Cmd::Speed;
    }
    else if (strcmp(input, "turn") == 0) {
        return Cmd::Turn;
    }
    else if (strcmp(input, "sensor") == 0) {
        return Cmd::Sensor;
    }
    return Cmd::Null;
}

void runString(String command_string) {
    Cmd command;
    String command_args[MAX_COMMAND_ARG];
    uint8_t i = 0;
    const char sep[] = " ";

    char * command_char = new char[command_string.length() + 1];
    strcpy(command_char, command_string.c_str());
    command_char[command_string.length()] = '\0';
    
    char* arg = strtok(command_char, sep);
    command = toCommand(arg);
    arg = strtok(NULL, sep);  // next: args...

    while (arg != NULL) {
        command_args[i] = String(arg);
        arg = strtok(NULL, sep);
        i++;
    }

    delete[] command_char;

    runCommand(command, command_args);
}