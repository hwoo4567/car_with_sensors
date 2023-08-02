#define THRESHOLD 700

const uint8_t sensor1 = A0;
const uint8_t sensor2 = A1;
const uint8_t led_blue = 12;

int val1 = 0;
int val2 = 0;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(led_blue, OUTPUT);

    Serial.begin(9600);
}
 
void loop() {
    val1 = analogRead(sensor1);
    val2 = analogRead(sensor2);

    Serial.print(val1);
    Serial.print(" ");
    Serial.println(val2);

    if (val1 > THRESHOLD) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }

    if (val2 > THRESHOLD) {
        digitalWrite(led_blue, HIGH);
    } else {
        digitalWrite(led_blue, LOW);
    }

    delay(100);
}
