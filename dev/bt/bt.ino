#include <SoftwareSerial.h>

const byte led = 13;
uint16_t count = 0;

SoftwareSerial BTSerial(7, 8);

void setup() {
    BTSerial.begin(9600);

    pinMode(led, OUTPUT);

    digitalWrite(led, LOW);
}

void loop() {
    if (BTSerial.available()) {
        char input[128];
        BTSerial.readBytes(input, 128);
        
        BTSerial.write(input);
        
        // if (input == "on") {
        //     count++;
        //     digitalWrite(led, HIGH);

        //     BTSerial.println("Counter Value: aaa");
        // }
        // if (input == "off") {
        //     count++;
        //     digitalWrite(led, LOW);

        //     BTSerial.println("Counter Value: bbb");
        // }
    }
}