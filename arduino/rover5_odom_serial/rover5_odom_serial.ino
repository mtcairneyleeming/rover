#include <ros.h>
#include <sensor_msgs/JointState.h>


/*
 * For 4 encoders, output in the form of integer over serial
 * recieved by a differential_drive pid_velocity node (http://wiki.ros.org/differential_drive)
 * for final use with ROS standard navigation packages
 * 
 * encoder code taken from http://www.robotshop.com/media/files/PDF/rover-5-introduction-rs017.pdf, 
 * repeated to serve all four encoders
 *  
 *  N.B. massive duplication of code required as there is no easy way to iterate through variable names
 *  N.B. idea for future checks - ensure that wheels on the same side are registering roughly the same value - implement as a node on the network that is nonblocking and outputs to a central console
 */
#include <avr/pgmspace.h>
#include <stdio.h> // for function sprintf

//pins encoders are attached to 
const int onePinA PROGMEM = 10;
const int onePinB PROGMEM = 11;
const int twoPinA PROGMEM = 4;
const int twoPinB PROGMEM = 5;
/*const int thrPinA PROGMEM = 6;
const int thrPinB PROGMEM = 7;
const int fouPinA PROGMEM = 8;
const int fouPinB PROGMEM = 9;*/
//interrupt pins
const int oneInt PROGMEM = 2;
const int twoInt PROGMEM = 3;
/*const int thrInt PROGMEM = 17;
const int fouInt PROGMEM = 3;*/

//message array for creating the serial message
String msg;
// Position indicators for each wheel, onePos being current to this second, old_ being last second's value
volatile int onePos = 0;
volatile int twoPos = 0;
/*volatile int thrPos = 0;
volatile int fouPos = 0;*/
// For comparison of values in the interrupts
unsigned int oneOld = 0;
unsigned int oneNew = 0;
unsigned int twoOld = 0;
unsigned int twoNew = 0;
/*unsigned int thrOld = 0;
unsigned int thrNew = 0;
unsigned int fouOld = 0;
unsigned int fouNew = 0;*/
int QEM [16] = {0,-1,1,0,1,0,0,-1,-1,2,0,1,0,1,-1,0}; // Quadrature Encoder Matrix


void setup()
{
  // initialize serial:
  Serial.begin(9600);
  //Set encoder pins as inputs
  pinMode(onePinA, INPUT); 
  pinMode(onePinB, INPUT);
  pinMode(twoPinA, INPUT); 
  pinMode(twoPinB, INPUT);
  /*pinMode(thrPinA, INPUT); 
  pinMode(thrPinB, INPUT);
  pinMode(fouPinA, INPUT); 
  pinMode(fouPinB, INPUT);*/
  //Attach interrupts to encoder pins
  attachInterrupt(digitalPinToInterrupt(oneInt), encoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(twoInt), encoder2, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(thrInt), encoder3, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(fouInt), encoder4, CHANGE);
}

/* 
 *  Diameter of wheels = 9cm
 *  Circumference = 28.27cm
 *  1000 ticks/3 rotations = 333.3... ticks/rotation
 *  distance/tick = 0.84907mm/tick
 *  
 *  (onePos-oldOnePos) finds the number of ticks since the last loop (1 second)
 *  times that by distance/tick to find displacement in the last second. 
 *  divide that by 1 to get a velocity value in mm/sec.
 *  divide that by 1000 to get the value in m/s for publishing
 */

void loop(){
  //onePos = 32000;
  //twoPos = -31000;
  //sprintf(msg, "l%06dr%06dv", onePos, twoPos);   //= (String(onePos/*+thrPos)/2*/)+String("l")+String(twoPos/*+fouPos)/2*/)+String("r"));
  //Serial.println(onePos);
  msg = onePos + String("v") + twoPos;
  if (msg.length()<13){
    while (msg.length()!= 13){
      msg = msg + " ";
    }
  }
  Serial.print(msg + "\n");
    
    
  
  //Serial.println("Serial unavailable");
  delay(1000);
}
/*
 * Interrupts- repeated, only customised for each encoder to record values to the correct variables
 * 
 */
 // Interrupt on A changing state
void encoder1 () {
  oneOld = oneNew;
  oneNew = digitalRead (onePinA) * 2 + digitalRead (onePinB); // Convert binary input to decimal value
  onePos = onePos + QEM[oneOld * 4 + oneNew];
  //Serial.println(onePos);
}
void encoder2 () {
  twoOld = twoNew;
  twoNew = digitalRead (twoPinA) * 2 + digitalRead (twoPinB); // Convert binary input to decimal value
  twoPos = twoPos + QEM[twoOld * 4 + twoNew];
}/*
void encoder3 () {
  thrOld = thrNew;
  thrNew = digitalRead (thrPinA) * 2 + digitalRead (thrPinB); // Convert binary input to decimal value
  thrPos = thrPos + QEM[thrOld * 4 + thrNew];
}
void encoder4 () {
  fouOld = fouNew;
  fouNew = digitalRead (fouPinA) * 2 + digitalRead (fouPinB); // Convert binary input to decimal value
  fouPos = fouPos + QEM[fouOld * 4 + fouNew];
}*/
