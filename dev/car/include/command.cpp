#include "command.h"
#include "motor/motor.h"
#include "sensor/sensor.h"
#include <AFMotor.h>

int* prevMoveCmdId = nullptr;

/////////////////////////////////////////////////////////////////////

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

String go(String args[]) {
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

    return String(isDriving());
}

String speed(String args[]) {
    int val = args[0].toInt();
    motorSetSpeed( (val <= 255 && val >= 0) ? val : 0 );
    return String("Speed: ") + String(speed_l) + " " + String(speed_r);
}

void turn(String args[]) {
    _stopAll();

    if (args[0] == "left") {
        motorTurn(LEFT);
    }
    else if (args[0] == "right") {
        motorTurn(RIGHT);
    }
}

void turn90(String args[]) {
    _stopAll();

    if (args[0] == "left") {
        motorTurn(LEFT);
    }
    else if (args[0] == "right") {
        motorTurn(RIGHT);
    }

    *prevMoveCmdId = main_timer->after(TURNING_TIME, _stopAll);
}

String sensor(String args[]) {
    String result = "";

    result += String(getDistance()) + " ";
    result += String(getLightVal()) + " ";
    result += String(getLineLSensorVal()) + " ";
    result += String(getLineRSensorVal());

    return result;
}

String say(String args[]) {
    String result;

    for (uint8_t i = 0; i < MAX_COMMAND_ARG; i++) {
        result += args[i] + " ";
    }

    return result;
}

/////////////////////////////////////////////////////////////////////

//* Command initialization must be called first among other init functions
void commandInit(Timer* timer) {
    main_timer = timer;
}

void runCommand(Cmd cmd, String args[], String& response) {
    switch (cmd)
    {
    case Stop:
        stop(args);
        break;
    case Go:
        response = go(args);
        break;
    case Speed:
        response = speed(args);
        break;
    case Turn:
        turn(args);
        break;
    case Turn90:
        turn90(args);
        break;
    case Sensor:
        response = sensor(args);
        break;
    case SAY:
        response = say(args);
    default:
        break;
    }
}

inline bool strEquals(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

Cmd _charToCmd(const char* input) {
    if (strEquals(input, "stop")) {
        return Cmd::Stop;
    }
    else if (strEquals(input, "go")) {
        return Cmd::Go;
    }
    else if (strEquals(input, "speed")) {
        return Cmd::Speed;
    }
    else if (strEquals(input, "turn")) {
        return Cmd::Turn;
    }
    else if (strEquals(input, "turn90")) {
        return Cmd::Turn90;
    }
    else if (strEquals(input, "sensor")) {
        return Cmd::Sensor;
    }
    else if (strEquals(input, "say")) {
        return Cmd::SAY;
    }
    return Cmd::Null;
}

void runString(String command_string, String& response) {
    const char* sep = " ";
    String command_args[MAX_COMMAND_ARG];
    Cmd command;
    uint8_t i = 0;

    char * command_char = new char[command_string.length() + 1];
    strcpy(command_char, command_string.c_str());
    command_char[command_string.length()] = '\0';
    
    char* arg = strtok(command_char, sep);
    command = _charToCmd(arg);
    arg = strtok(NULL, sep);  // next: args...

    while (arg != NULL) {
        command_args[i] = String(arg);
        arg = strtok(NULL, sep);
        i++;
    }

    delete[] command_char;

    runCommand(command, command_args, response);
}