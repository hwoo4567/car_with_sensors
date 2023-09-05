#include <Timer.h>
#include <SoftwareSerial.h>
#include "include/command.h"
#include "include/motor/motor.h"

#define TEST_LIGHT
// #define TEST_DRIVE
#define LIGHT_SENSOR_ON  // 빛 센서를 사용한 자동차 정지 기능, 불 끄고 어두운 환경에서 써야 함

#define LINE_SENSOR_THRESHOLD 400  // 검은색-하얀색 구분 임계값
#define LIGHT_VALUE_THRESHOLD 100  // 빛 감지 임계값
#define DEFUALT_SPEED         200

const uint8_t pinRx = A4;    // RXD로 연결된 핀
const uint8_t pinTx = A5;    // TXD로 연결된 핀
const uint8_t lightPin = A2; // 빛 센서로 연결된 핀
const uint8_t lineL = A0, lineR = A1;  // 적외선 센서로 연결된 핀 (왼쪽, 오른쪽)
const uint8_t echoPin = 10;    // servo pin1
const uint8_t trigPin = 9;     // servo pin2

SoftwareSerial BtSerial(pinTx, pinRx);  // (bluetoothRx, bluetoothTx)
Timer timer;

// timer...
int* turn_code = nullptr;

/////////////////////////////////////////////////////////////////////

/*
 * 모터 출력을 조정하는 함수
 * 적외선 센서 값에 따라 모터의 출력을 조절한다
 * 전역변수: speed_l, speed_r
 * 
 * ex)
 * motor_l->setSpeed(speed_l - 30);  // 속도를 30 줄인다
*/
void adjustMotor(AF_DCMotor* motor_l, AF_DCMotor* motor_r) {
    int lineL = getLineLSensorVal();
    int lineR = getLineRSensorVal();
    
    if (isStopped()) {
        motor_l->setSpeed(speed_l);
        motor_r->setSpeed(speed_r);
    }
    if (isTurning()) {
        motor_l->setSpeed(255);
        motor_r->setSpeed(255);
    }
    if (isDriving()) {
        // 왼쪽이 하얀색일 때
        if (lineL > LINE_SENSOR_THRESHOLD) {
            motor_r->setSpeed(0);
        } else {
            motor_r->setSpeed(speed_r);
        }

        // 오른쪽이 하얀색일 때
        if (lineR > LINE_SENSOR_THRESHOLD) {
            motor_l->setSpeed(0);
        } else {
            motor_l->setSpeed(speed_l);
        }

        // 양쪽 하얀색
        if (lineL > LINE_SENSOR_THRESHOLD && lineR > LINE_SENSOR_THRESHOLD) {
            motorStop();
        }
    }
}

/*
 * 항상 실행되는 함수
 * 센서의 값을 받고 연산한다
*/
void checkSensor() {
    double distance = getDistance();  // cm
    int brightness = getLightVal();   // 0 - 1023

    if (distance < 10) {
        motorStop();
    }

#ifdef LIGHT_SENSOR_ON
    if (isDriving() && brightness > LIGHT_VALUE_THRESHOLD) {
        main_timer->after(500, motorStop);
    }
#endif
}

/////////////////////////////////////////////////////////////////////

void setup() {
    commandInit(&timer);
    motorInit(1, 4, DEFUALT_SPEED, adjustMotor);
    distanceInit(trigPin, echoPin);
    lightInit(lightPin);
    lineTraceInit(lineL, lineR);

    Serial.begin(9600);
    BtSerial.begin(9600);

    timer.every(20, checkSensor);
    
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
    String response;

    if (BtSerial.available()) {
        Serial.println("Connected");

        bt_input = BtSerial.readString();
        
        if (bt_input != "") {
            runString(bt_input, response);
            BtSerial.println(response);  // 통신 종결자: \r\n
        }
    }

    timer.update();
}


