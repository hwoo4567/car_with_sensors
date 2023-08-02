#include <SoftwareSerial.h>

const uint8_t txPin = 7;
const uint8_t rxPin = 8;
SoftwareSerial BTSerial(txPin, rxPin);
uint16_t count = 0;

void setup() {
    BTSerial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    if (BTSerial.available()) {
        String input = BTSerial.readString();
        
        if (input == "on") {
            count++;
            digitalWrite(LED_BUILTIN, HIGH);

            BTSerial.println("Counter Value: aaa");
        }
        if (input == "off") {
            count++;
            digitalWrite(LED_BUILTIN, LOW);

            BTSerial.println("Counter Value: bbb");
        }
    }
}