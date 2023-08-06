#include <Timer.h>
#include <SoftwareSerial.h>
#include "include/command.h"
#include "include/motor/motor.h"

#define TEST_LIGHT
// #define TEST_DRIVE

const uint8_t pinRx = A4;
const uint8_t pinTx = A5;
// const uint8_t lightPin = A2;
const uint8_t echoPin = 10;  // servo pin1
const uint8_t trigPin = 9;  // servo pin2

SoftwareSerial BtSerial(pinTx, pinRx);  // (bluetoothRx, bluetoothTx)
Timer timer;

void setup() {
    commandInit(&timer);
    motorInit(1, 4);
    distanceInit(trigPin, echoPin);
    // lightInit();
    // lineTraceInit();

    Serial.begin(9600);
    BtSerial.begin(9600);
    
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

    if (BtSerial.available()) {
        Serial.println("Connected");

        bt_input = BtSerial.readString();

        BtSerial.print(bt_input.c_str());

        if (bt_input != "") {
            runString(bt_input);
        }
    }

    Serial.println(getDistance());

    timer.update();
}


