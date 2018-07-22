/*
 * A0 -> Trig
 * A1 -> Echo
 * 
 * brown-> GND
 * red -> 5V
 * Orange -> Pin 3
 */

//Libraries
#include "Ultrasonic.h"
#include <Servo.h>

//Defines
#define PROXIMITY 10  //distance threshold in cm
#define DT 10        //Frequency
#define LOCK_TIME 1500 //delay after lock
#define ANGLE_MIN 40
#define ANGLE_MAX 140
#define SCAN_STEP 5

Ultrasonic ultrasonic(A0,A1);

int d;
int servoPin = 3;
int angle;
int i;
//int vector_size = (ANGLE_MAX - ANGLE_MIN) / SCAN_STEP +1;
//int scan_vec[vector_size];
int clockwise;
   
int d_fix(int d);

Servo servo;


//INITIALIZATION
void setup() {

randomSeed(analogRead(0));
servo.attach(servoPin);
d=200;
clockwise = 1;
angle=ANGLE_MIN;
servo.write(angle);
Serial.begin(9500);
}

//MAIN
void loop() {
while((d=d_fix(ultrasonic.distanceRead())) < PROXIMITY) //read distance
  delay(DT);

  if(clockwise !=0){
    if(angle >= ANGLE_MAX){
      clockwise = 0;
    }
    servo.write(angle += SCAN_STEP);
    delay(DT);
  }else{
    if(angle <= ANGLE_MIN){
      clockwise = 1; 
    }
    servo.write(angle -= SCAN_STEP);
    delay(DT);
  }
  
   Serial.print("Angle: ");
   Serial.print(angle);
   Serial.print(":: Distance: ");
   Serial.println(d);
}

//==FUNCTIONS==//

int d_fix(int d)
{
  if(d == 0)
  return 300;

  return d;
}



