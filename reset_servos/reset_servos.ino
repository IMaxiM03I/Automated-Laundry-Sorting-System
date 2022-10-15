#include <Servo.h>


int WHITE_SERVO_PIN = 3;    // pin 3 is PWM (490Hz)
int BLACK_SERVO_PIN = 9;    // pin 9 is PWM (490Hz)
int COLOR_SERVO_PIN = 11;   // pin 11 is PWM (490Hz)

Servo WHITE_SERVO;                      // servo that will push the item onto white basket
Servo BLACK_SERVO;                      // servo that will push the item onto black basket
Servo COLOR_SERVO;                      // servo that will push the item onto color basket

int SERVO_POSITION_UPDATE_DELAY = 150;    // waits 15ms for the servo to reach the position

bool done = false;


void setup() {

    Serial.begin(9600);

    WHITE_SERVO.attach(WHITE_SERVO_PIN);
    BLACK_SERVO.attach(BLACK_SERVO_PIN);
    COLOR_SERVO.attach(COLOR_SERVO_PIN);

    delay(2000);

}


void loop() {

    if (!done) {

        Serial.println("resetting white...");
        WHITE_SERVO.write(180);
        delay(SERVO_POSITION_UPDATE_DELAY);
        WHITE_SERVO.write(0);
        delay(SERVO_POSITION_UPDATE_DELAY);
        Serial.println("white reset!");
        
        delay(3000);

        Serial.println("resetting black...");
        BLACK_SERVO.write(180);
        delay(SERVO_POSITION_UPDATE_DELAY);
        BLACK_SERVO.write(0);
        delay(SERVO_POSITION_UPDATE_DELAY);
        Serial.println("black reset!");

        delay(3000);

        Serial.println("resetting color...");
        COLOR_SERVO.write(180);
        delay(SERVO_POSITION_UPDATE_DELAY);
        COLOR_SERVO.write(0);
        delay(SERVO_POSITION_UPDATE_DELAY);
        Serial.println("color reset!");

        done = true;

    }

}