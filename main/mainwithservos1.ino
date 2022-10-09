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

int SERVO_1_PIN = 3;    // pin 3 is PWM (490Hz)
int SERVO_2_PIN = 9;    // pin 9 is PWM (490Hz)
int SERVO_3_PIN = 11;   // pin 11 is PWM (490Hz)

// calibration

int RED_LOWER_BOUND = 45;
int RED_UPPER_BOUND = 188;

int GREEN_LOWER_BOUND = 90;
int GREEN_UPPER_BOUND = 151;

int BLUE_LOWER_BOUND = 96;
int BLUE_UPPER_BOUND = 156;

int WHITE_UPPER_BOUND = 255;
int BLACK_LOWER_BOUND = 0;




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




// ----- VARIABLES ----- //

// color sensor frequencies

int red_frequency = 0;
int green_frequency = 0;
int blue_frequency = 0;

// color sensor RGB values

int red_value = 0;
int green_value = 0;
int blue_value = 0;

// object color type

String object_type = "white";

// servos

Servo servo1;
Servo servo2;
Servo servo3;




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

    servo1.attach(SERVO_1_PIN);
    servo2.attach(SERVO_2_PIN);
    servo3.attach(SERVO_3_PIN);

}




// ----- ARDUINO MAIN LOOP ----- //

void loop() {

  // --- COLOR SENSOR UPDATE --- //

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

  // // print detected color (either red, green or blue)
  // if (red_value > green_value && red_value > blue_value) {
  //     Serial.print("red detected: ");
  //     Serial.println(red_value);
  // }

  // if (green_value > red_value && green_value > blue_value) {
  //     Serial.print("green detected: ");
  //     Serial.println(green_value);
  // }

  // if (blue_value > red_value && blue_value > green_value) {
  //     Serial.print("blue detected: ");
  //     Serial.println(blue_value);
  // }

  // print RGB values
  Serial.print("blue:");
  Serial.println(blue_value);

  Serial.print("red:");
  Serial.println(red_value);

  Serial.print("green:");
  Serial.println(green_value);

  // update color type
  if (red_value >= WHITE_UPPER_BOUND && green_value >= WHITE_UPPER_BOUND && blue_frequency >= WHITE_UPPER_BOUND) {
      object_type = "white";
  } else if (red_value <= BLACK_LOWER_BOUND && green_value <= BLACK_LOWER_BOUND && blue_value <= BLACK_LOWER_BOUND) {
      object_type = "black";
  } else {
      object_type = "color";
  }


  // --- SERVO POSITION UPDATE //
  

  if (object_type == "white") {

  int pos = 0;    // variable to store the servo position


    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15 + 15);                   // waits 15ms for the servo to reach the position and waits 15ms for the clothes to fall into basket
    }
    
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }


  } else if (object_type == "color") {

  int pos = 0;    // variable to store the servo position


    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15 + 15);                   // waits 15ms for the servo to reach the position and waits 15ms for the clothes to fall into basket
    }
    
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    
  } else if (object_type == "black") {

  int pos = 0;    // variable to store the servo position


    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo3.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15 + 15);                   // waits 15ms for the servo to reach the position and waits 15ms for the clothes to fall into basket
    }
    
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo3.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

  
  }
}
