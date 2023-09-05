#include <stdio.h>
#include <stdarg.h>
#define THRESHOLD 700

const uint8_t sensor1 = A0;
const uint8_t sensor2 = A1;
const uint8_t light_sensor = A2;
const uint8_t led_blue = 12;

int val1 = 0;
int val2 = 0;
int light_val = 0;

void SerialPrintf(const char *s, ...){
    va_list args;
    va_start(args, s);
    int n = vsnprintf(NULL, 0, s, args);
    char* str = new char[n+1];
    vsprintf(str, s, args);
    va_end(args);
    Serial.print(str);
    delete [] str; //메모리 해제
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);
}
 
void loop() {
    val1 = analogRead(sensor1);
    val2 = analogRead(sensor2);
    light_val = analogRead(light_sensor);

    SerialPrintf("line: %d %d, light: %d\n", val1, val2, light_val);

    if (val1 > THRESHOLD) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }

    delay(100);
}


// const uint8_t echoPin = 10;  // servo pin1
// const uint8_t trigPin = 9;  // servo pin2

// void setup() {
// 	Serial.begin(9600);
// 	pinMode(trigPin, OUTPUT);
// 	pinMode(echoPin, INPUT);
// }

// void loop() {
//     digitalWrite(trigPin, LOW);
//     delayMicroseconds(2);
//     digitalWrite(trigPin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trigPin, LOW);

//     unsigned long duration = pulseIn(echoPin, HIGH); 
// 	double distance = ((double) duration) * 17 / 1000; 
	
// 	Serial.print(distance);
// 	Serial.println("cm");
// 	delay(100);
// }