#include <Servo.h>
 
 
 
// ----- CONSTANTS ----- //
 
// PINS //
 
// color sensor
 
int S0 = 4;     // scale output frequency
int S1 = 5;     // scale output frequency
int S2 = 6;     // set photodiode type
int S3 = 7;     // set photodiode type
int SENSOR_OUT = 8;     // sensor output / arduino input
 
/*
 
S0 and S1 scale the output frequency as follows:
 
Color   |   S0   |   S1
--------------------------
--------------------------
0%      |   LOW  |   LOW
--------------------------
2%      |   LOW  |  HIGH
--------------------------
20%     |  HIGH  |   LOW
--------------------------
100%    |  HIGH  |  HIGH
 
 
 
S2 and S3 set the photodiode type as follows:
 
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
 
int WHITE_SERVO_PIN = 3;    // pin 3 is PWM (490Hz)
int BLACK_SERVO_PIN = 9;    // pin 9 is PWM (490Hz)
int COLOR_SERVO_PIN = 11;   // pin 11 is PWM (490Hz)
 
// CALIBRATION //
 
int RED_LOWER_BOUND = 45;
int RED_UPPER_BOUND = 188;
 
int GREEN_LOWER_BOUND = 90;
int GREEN_UPPER_BOUND = 151;
 
int BLUE_LOWER_BOUND = 96;
int BLUE_UPPER_BOUND = 156;
 
int WHITE_UPPER_BOUND = 255;
int BLACK_LOWER_BOUND = 0;
 
// COLORS //
 
String WHITE = "white";
String BLACK = "black";
String COLOR = "color";

// COLOR SENSOR //

int COLOR_DETECTION_DELAY = 5000;       // detect color 5s after servos were reset
 
// SERVOS //
 
Servo WHITE_SERVO;                      // servo that will push the item onto white basket
Servo BLACK_SERVO;                      // servo that will push the item onto black basket
Servo COLOR_SERVO;                      // servo that will push the item onto color basket
 
int SERVO_POSITION_UPDATE_DELAY = 5;    // waits 15ms for the servo to reach the position
int SERVO_MOVEMENT_SPEEED = 10;         // delta(angle) per iteration of loop

int SERVOS_RESET_DELAY = 5000;          // reset servos position 5s after plate was tilted
 
 
 
 
// ----- CLASSES ----- //
 
 
 
 
// ----- FUNCTIONS ----- //
 
void scaleFrequency(int percentage = 20) {   // percentage = (0 or 2 or 20 or 100); default = 20
 
    switch (percentage) {   // scale the output frequency according to the table above
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
 
 
int readColorValue(String color) {      // color = ("red" or "green" or "blue")
 
    int c = 0;  // red -> 0
    if (color == "green") {
        c = 1;  // green -> 1
    } else if (color == "blue") {
        c = 2;  // blue -> 2
    }
 
    switch (c) {    // set the photodiode values according to the table above
        case 0:
            digitalWrite(S2, LOW);
            digitalWrite(S3, LOW);
            return pulseIn(SENSOR_OUT, LOW);
            break;
        case 1:
            digitalWrite(S2, HIGH);
            digitalWrite(S3, HIGH);
            return pulseIn(SENSOR_OUT, LOW);
            break;
        case 2:
            digitalWrite(S2, LOW);
            digitalWrite(S3, HIGH);
            return pulseIn(SENSOR_OUT, LOW);
            break;
    }
}
 
 
void move_servo(Servo servo, int angle) {
 
    // for (int angle = 0; angle <= 180; angle += 1) {      // goes from 0 degrees to 180 degrees
 
    //     // in steps of 1 degree
    //     servo.write(angle);                              // tell servo to go to position in variable 'angle'
 
    //     // wait 15ms for the servo to reach the position and wait 15ms for the clothes to fall into basket
    //     delay(SERVO_POSITION_UPDATE_DELAY); //speed of the servo
    // }
    // delay(200); //break between dropping the clothes and pulling the lid up
    // for (int angle = 180; angle >= 0; angle -= 1) {     // goes from 180 degrees to 0 degrees
    //     servo.write(angle);                             // tell servo to go to position in variable 'angle'
    //     delay(SERVO_POSITION_UPDATE_DELAY);             // waits 15ms for the servo to reach the position
    // }

    servo.write(angle);
    delay(SERVO_POSITION_UPDATE_DELAY);
 
}


void reset_servos(String origin) {

    Servo servo1;
    Servo servo2;

    Serial.print("resetting servos from ");
    Serial.print(origin);
    Serial.println("...");

    if (origin == WHITE) {

        servo1 = BLACK_SERVO;
        servo2 = COLOR_SERVO;

    } else if (origin == BLACK) {

        servo1 = WHITE_SERVO;
        servo2 = COLOR_SERVO;

    } else {

        servo1 = WHITE_SERVO;
        servo2 = BLACK_SERVO;

    }

    for (int angle = 180; angle > 0; angle -= SERVO_MOVEMENT_SPEEED) {
        move_servo(servo1, angle);
        move_servo(servo2, angle);
    }

    Serial.println("servos reset!");

}


void tilt_main_plate(String color) {

    Serial.print("tilting main plate to ");
    Serial.print(color);
    Serial.println("...");

    if (color == WHITE) {
        tilt_white();
    } else if (color == BLACK) {
        tilt_black();
    } else {
        tilt_color();
    }

    Serial.println("main plate tilted!");

}


void tilt_white() {

    for (int angle = 0; angle < 180; angle += SERVO_MOVEMENT_SPEEED) {
        move_servo(BLACK_SERVO, angle);
        move_servo(COLOR_SERVO, angle);
    }

}


void tilt_black() {

    for (int angle = 0; angle < 180; angle += SERVO_MOVEMENT_SPEEED) {
        move_servo(WHITE_SERVO, angle);
        move_servo(COLOR_SERVO, angle);
    }

}


void tilt_color() {

    for (int angle = 0; angle < 180; angle += SERVO_MOVEMENT_SPEEED) {
        move_servo(WHITE_SERVO, angle);
        move_servo(BLACK_SERVO, angle);
    }

}
 
 
 
// ----- VARIABLES ----- //
 
// color sensor frequencies
 
int red_frequency = 0;
int green_frequency = 0;
int blue_frequency = 0;
 
// color sensor RGB values
 
int red_value = 0;
int green_value = 0;
int blue_value = 0;
 
// color detection
 
String object_type = WHITE;
bool ready_to_detect_color = true;
 
// servos
 
bool ready_to_tilt = false;                 // true if servos should be moving
int servo_tilt_time_stamp = millis();       // store the last time the servos tilted the main plate

bool ready_to_reset = false;                // true if servos should return to standby position
bool servos_in_standby = true;              // true if servos are in their standby position
int servo_reset_time_stamp = millis();      // store the last time the servos were reset
 
 
 
 
// ----- ARDUINO SETUP ----- //
 
void setup() {
 
    Serial.begin(9600);       // set up serial at 9600Hz
    delay(500);
    Serial.println("loading...");
 
    // SETUP PINS //
 
    // color sensor
 
    pinMode(S0, OUTPUT);    // photodiodes are all output
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(SENSOR_OUT, INPUT);     // OUT pin is input
 
    // color sensor frequency scaling (20% default)
    scaleFrequency();
 
    // servos
 
    WHITE_SERVO.attach(WHITE_SERVO_PIN);
    COLOR_SERVO.attach(BLACK_SERVO_PIN);
    BLACK_SERVO.attach(COLOR_SERVO_PIN);

    move_servo(WHITE_SERVO, 0);
    move_servo(BLACK_SERVO, 0);
    move_servo(COLOR_SERVO, 0);

    delay(1000);
    Serial.println("Arduino ready!");
 
}
 
 
 
 
// ----- ARDUINO MAIN LOOP ----- //
 
void loop() {
 
    // --- COLOR SENSOR UPDATE --- //

    // color detection

    if (ready_to_detect_color) {
 
        // read values from TCS3200
        red_frequency = readColorValue("r");
        delay(100);
        green_frequency = readColorValue("g");
        delay(100);
        blue_frequency = readColorValue("b");
        delay(100);
    
        // get colors from frequencies by mapping them onto a value in the range [0; 255]
        red_value = max(min(map(red_frequency, RED_LOWER_BOUND, RED_UPPER_BOUND, 255, 0), 255), 0);
        green_value = max(min(map(green_frequency, GREEN_LOWER_BOUND, GREEN_UPPER_BOUND, 255, 0), 255), 0);
        blue_value = max(min(map(blue_frequency, BLUE_LOWER_BOUND, BLUE_UPPER_BOUND, 255, 0), 255), 0);
    
        // print RGB values (for serial)
        // Serial.print("blue:");
        // Serial.println(blue_value);

        // Serial.print("red:");
        // Serial.println(red_value);

        // Serial.print("green:");
        // Serial.println(green_value);
    
        // update color type
        if ((red_value >= WHITE_UPPER_BOUND) && (green_value >= WHITE_UPPER_BOUND) && (blue_value >= WHITE_UPPER_BOUND)) {
            object_type = WHITE;
            Serial.println("white detected");
        } else if ((red_value <= BLACK_LOWER_BOUND) && (green_value <= BLACK_LOWER_BOUND) &&( blue_value <= BLACK_LOWER_BOUND)) {
            object_type = BLACK;
            Serial.println("black detected");
        } else {
            object_type = COLOR;
            Serial.println("color detected");
        }

        ready_to_detect_color = false;      // stop detecting color (unnecessary computations)
        ready_to_tilt = true;               // tilt the servos in the correct position
        Serial.println("ready to tilt");
    
    }

    // color sensor clock

    if (servos_in_standby && millis() - servo_reset_time_stamp >= COLOR_DETECTION_DELAY) {
        ready_to_detect_color = true;
        Serial.println("ready to detect color");
    }
 
 
 
    // --- SERVO POSITION UPDATE --- //
 
    // servos movement
 
    if (ready_to_tilt) {

        tilt_main_plate(object_type);
        servo_tilt_time_stamp = millis();           // reset
        ready_to_tilt = false;                      // reset
        servos_in_standby = false;

    } else if (ready_to_reset) {

        reset_servos(object_type);
        servo_reset_time_stamp = millis();          // reset
        ready_to_reset = false;                     // reset
        servos_in_standby = true;

    }

    // servos clock

    if (!servos_in_standby && millis() - servo_tilt_time_stamp >= SERVOS_RESET_DELAY) { 
        ready_to_reset = true;
        Serial.println("ready to reset");
    }
 
}