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

// --- VARIABLES --- //

// color sensor frequencies

int red_frequency = 0;
int green_frequency = 0;
int blue_frequency = 0;




// ----- ARDUINO SETUP ----- //

void setup() {
    Serial.begin(9600);       // set up serial at 9600Hz

    // SETUP PINS //

    // color sensor

    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(SENSOR_OUT, INPUT);

    // color sensor frequency scaling (20% default)
    scaleFrequency();

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

    // print detected frequencies
    Serial.print("red: ");
    Serial.print(red_frequency);
    Serial.print("   |   ");
    Serial.print("green: ");
    Serial.print(green_frequency);
    Serial.print("   |   ");
    Serial.print("blue: ");
    Serial.println(blue_frequency);

}