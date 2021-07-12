#include "Arduino.h"
#include <Servo.h>
#include <Hand.h>

Servo pinky, ring, middle, index, thumb; // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; // variable to store the servo position

Hand LeftHand = Hand(
    Finger(23, 0, 0, 110, 100),//thumb, yellow analog
    Finger(25, 1, 0, 110, 50),
    Finger(27, 2, 0, 90, 300),
    Finger(29, 3, 0, 90, 100),
    Finger(31, 4, 0, 90, 300) //grey analog
  );

Hand RightHand = Hand(
    Finger(37, 8, 0, 90, 100),//thumb, yellow analog
    Finger(39, 9, 0, 90, 100),
    Finger(41, 10, 0, 90, 100),
    Finger(43, 11, 0, 90, 100),
    Finger(45, 12, 0, 90, 100) //grey analog
  );

  //Joint leftWrist(7,0,180);
  //Joint leftBicep(8,130,170);

//Joint test = Joint(31,0,90);
Servo test;
void setup()
{
  Serial.begin(9600);
  LeftHand.begin();
  RightHand.begin();
  //test.begin();
  //test.attach(3);
}

void loop()
{

  //LeftHand.fixed(175);
  //test.write(30);
  //LeftHand.fixed(0);
  
  //Serial.println(LeftHand.ring.sensorRead());

  //delay(500);
  //LeftHand.readSensor();
 //LeftHand.close();
  //RightHand.fixed(0);
  RightHand.spinspin(0,80);
// LeftHand.spinspin(0,80);

 

  /*
  if(indexValue > thresh)
    Serial.println("Index Touched");
  if(middleValue > thresh)
    Serial.println("Middle Touched");
  if(ringValue > thresh)
    Serial.println("Ring Touched");
  if(pinkyValue > thresh)
    Serial.println("Pinky Touched");
  */
  /* int sensorValue = analogRead(A0);
  if(sensorValue > 300){
    Serial.print("TOUCHED ");
    Serial.println(sensorValue);
  }
  else
    Serial.println(sensorValue);
  delay(500);
 */
 
}
