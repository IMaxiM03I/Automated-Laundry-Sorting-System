#include <Servo.h>




// --- CLASSES --- //

// --- FUNCTIONS --- //

void scaleFrequency(int percentage = 20) {   // percentage = (0 or 2 or 20 or 100); default = 20

    switch (percentage) {
        case 0:
            digitalWrite(S0, LOW);
            digitalWrite(S1, LOW);
            break;
        case 2:
            digitalWrite(S0, LOW);
            digitalWrite(S1, HIGH);
            break;
        case 20:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, LOW);
            break;
        case 100:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, HIGH);
            break;
    }

}


int readColorValue(string color) {      // color = ("r" or "g" or "b")

    switch (color) {
        case "r":
            digitalWrite(S2, LOW);
            digitalWrite(S3, LOW);
            return pulseIn(SENSOR_OUT, LOW);
            break;
        case "g":
            digitalWrite(S2, HIGH);
            digitalWrite(S3, HIGH);
            return pulseIn(SENSOR_OUT, LOW);
            break;
        case "b":
            digitalWrite(S2, LOW);
            digitalWrite(S3, HIGH);
            return pulseIn(SENSOR_OUT, LOW);
            break;
    }
}

// --- CONSTANTS --- //

// PINS //

// color sensor

int S0 = 4;
int S1 = 5;
int S2 = 6;
int S3 = 7;
int SENSOR_OUT = 8;

/*
Color   |   S2   |   S3   
--------------------------
--------------------------
RED     |   LOW  |   LOW
--------------------------
GREEN   |  HIGH  |  HIGH
--------------------------
BLUE    |   LOW  |  HIGH
--------------------------
CLEAR   |  HIGH  |   LOW
*/

// servos

int SERVO_1_PIN = 3;    // pin 3 is PWM (490Hz)
int SERVO_2_PIN = 9;    // pin 9 is PWM (490Hz)
int SERVO_3_PIN = 11;   // pin 11 is PWM (490Hz)

// calibration

int RED_LOWER_BOUND = 70;
int RED_UPPER_BOUND = 120;

int GREEN_LOWER_BOUND = 100;
int GREEN_UPPER_BOUND = 199;

int BLUE_LOWER_BOUND = 38;
int BLUE_UPPER_BOUND = 84;

// --- VARIABLES --- //

// color sensor frequencies

int red_frequency = 0;
int green_frequency = 0;
int blue_frequency = 0;

// color sensor colors

int red_color = 0;
int green_color = 0;
int blue_color = 0;

// servos

Servo servo1;
Servo servo2;
Servo servo3;




// ----- ARDUINO SETUP ----- //

void setup() {
    Serial.begin(9600);       // set up serial at 9600Hz
    delay(500);
    Serial.println("loading...")

    // SETUP PINS //

    // color sensor

    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(SENSOR_OUT, INPUT);

    // color sensor frequency scaling (20% default)
    scaleFrequency();

    // servos

    servo1.attach(SERVO_1_PIN);
    servo2.attach(SERVO_2_PIN);
    servo3.attach(SERVO_3_PIN);

}


// ----- ARDUINO MAIN LOOP ----- //

void loop() {

    // read values from TCS3200
    red_frequency = readColorValue("r");
    delay(100);
    green_frequency = readColorValue("g");
    delay(100);
    blue_frequency = readColorValue("b");
    delay(100);

    // get colors from frequencies by mapping them onto a value in the range [0; 255]
    red_color = map(red_frequency, RED_LOWER_BOUND, RED_UPPER_BOUND, 255, 0);
    green_color = map(green_frequency, GREEN_LOWER_BOUND, GREEN_UPPER_BOUND, 255, 0);
    blue_color = map(blue_frequency, BLUE_LOWER_BOUND, BLUE_UPPER_BOUND, 255, 0);

    // print detected color
    if (red_color > green_color && red_color > blue_color) {
        Serial.print("red detected");
    }

    if (green_color > red_color && green_color > blue_color) {
        Serial.print("green detected");
    }

    if (blue_color > red_color && blue_color > green_color) {
        Serial.print("blue detected");
    }

}