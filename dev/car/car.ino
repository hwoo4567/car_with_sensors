#include <Timer.h>
#include <SoftwareSerial.h>
#include "command/command.h"
#include "command/motor.h"

#define TEST_LIGHT
// #define TEST_DRIVE

const uint8_t pinRx = A4;
const uint8_t pinTx = A5;
SoftwareSerial BTSerial(pinTx, pinRx);  // (bluetoothRx, bluetoothTx)
Timer timer;

void setup() {
    motorInit(1, 4);
    commandInit(&timer);

    Serial.begin(9600);
    BTSerial.begin(9600);
    
#ifdef TEST_LIGHT
    pinMode(LED_BUILTIN, OUTPUT);

    for (uint8_t i = 0; i < 5; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }
#endif
#ifdef TEST_DRIVE
    motorGo(FORWARD);
    delay(2000);
    motorStop();
#endif
}
 
void loop() {
    String bt_input;

    if (BTSerial.available()) {
        Serial.println("Connected");

        bt_input = BTSerial.readString();

        BTSerial.print(bt_input.c_str());

        if (bt_input != "") {
            runString(bt_input);
        }
    }

    timer.update();
}


