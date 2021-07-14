#include "Arduino.h"
#include <Servo.h>
#include <Robot.h>
#include <TImer.h>

Robot robot;
String input ="";
bool started = false;
Timer startTimer(5000);
Timer readSensor(1000);

void setup()
{
  Serial.begin(9600);

  robot.begin();
  //lefthand.begin();
  startTimer.resetTimer();

  //robot.rightArm.shouldExt.begin();
}

void loop()
{

  
  while (Serial.available())
  {

    char temp = Serial.read();
    Serial.print(temp);
    //Serial.println("hi");
    if (temp == '\n')
    {
      if (input == "d")
      {
      }
      else if (input == "e")
      {
      }
      else if (input == "g")
      {
      }
      else if (input == "h")
      {
      }
      else if (input == "z")
      {
      }
      input = "";
    }
    else
      input += temp;
  }
  //lefthand.close();
  robot.startup(started);

  if (startTimer.getTimer() > startTimer.getTime())
  {
    robot.leftArm.shakeHand();
    robot.rightArm.shakeHand();
    //robot.leftArm.bicepExt.goToMax();
  }

  // if (readSensor.getTimer() > readSensor.getTime())
  // {
  //   robot.leftArm.hand.readSensor();
  //   readSensor.resetTimer();
  // }
}
