// #include <Servo.h>




// // --- CLASSES --- //

// // --- CONSTANTS --- //

// // PINS //

// // color sensor

// int S0 = 4;
// int S1 = 5;
// int S2 = 7;
// int S3 = 6;
// int SENSOR_OUT = 8;

// /*
// Color   |   S2   |   S3   
// --------------------------
// --------------------------
// RED     |   LOW  |   LOW
// --------------------------
// GREEN   |  HIGH  |  HIGH
// --------------------------
// BLUE    |   LOW  |  HIGH
// --------------------------
// CLEAR   |  HIGH  |   LOW
// */

// // --- VARIABLES --- //

// // color sensor frequencies

// int red_frequency = 0;
// int green_frequency = 0;
// int blue_frequency = 0;


// // --- FUNCTIONS --- //

// int readColorValue(String color) {      // color = ("r" or "g" or "b")

//     int c = 0;    // red = 0
//     if (color == "g") {     // green = 1
//       c = 1;
//     } else if (color == "b") {   // blue = 2
//       c = 2;
//     }

//     switch (c) {

//         // read RED value
//         case 0:
//             digitalWrite(S2, LOW);
//             digitalWrite(S3, LOW);
//             return pulseIn(SENSOR_OUT, LOW);
//             break;

//         // read GREEN value
//         case 1:
//             digitalWrite(S2, HIGH);
//             digitalWrite(S3, HIGH);
//             return pulseIn(SENSOR_OUT, LOW);
//             break;

//         // read BLUE value
//         case 2:
//             digitalWrite(S2, LOW);
//             digitalWrite(S3, HIGH);
//             return pulseIn(SENSOR_OUT, LOW);
//             break;
//     }
// }


// void scaleFrequency(int percentage = 20) {   // percentage = (0 or 2 or 20 or 100); default = 20

//     switch (percentage) {

//         // scale to 0%
//         case 0:
//             digitalWrite(S0, LOW);
//             digitalWrite(S1, LOW);
//             break;

//         // scale to 2%
//         case 2:
//             digitalWrite(S0, LOW);
//             digitalWrite(S1, HIGH);
//             break;

//         // scale to 20%
//         case 20:
//             digitalWrite(S0, HIGH);
//             digitalWrite(S1, LOW);
//             break;

//         // scale to 100%
//         case 100:
//             digitalWrite(S0, HIGH);
//             digitalWrite(S1, HIGH);
//             break;
//     }
// }




// // ----- ARDUINO SETUP ----- //

// void setup() {
  
//     Serial.begin(9600);       // set up serial at 9600Hz

//     // SETUP PINS //

//     // color sensor

//     pinMode(S0, OUTPUT);
//     pinMode(S1, OUTPUT);
//     pinMode(S2, OUTPUT);
//     pinMode(S3, OUTPUT);
//     pinMode(SENSOR_OUT, INPUT);

//     // color sensor frequency scaling (20% default)
//     scaleFrequency();

// }


// // ----- ARDUINO MAIN LOOP ----- //

// void loop() {

//     // read values from TCS3200
//     red_frequency = readColorValue("r");
//     delay(100);
//     green_frequency = readColorValue("g");
//     delay(100);
//     blue_frequency = readColorValue("b");
//     delay(100);

//     // print detected frequencies
//     Serial.print("red: ");
//     Serial.print(red_frequency);
//     Serial.print("   |   ");
//     Serial.print("green: ");
//     Serial.print(green_frequency);
//     Serial.print("   |   ");
//     Serial.print("blue: ");
//     Serial.println(blue_frequency);

// }










/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}


void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(100);
}