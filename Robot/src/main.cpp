#include "Arduino.h"
#include <Servo.h>
#include <Robot.h>
#include <Timer.h>
#include <Subscriber.h>

Robot robot;
String input = "";
bool started = false;
Timer startTimer(5000);
Timer readSensor(1000);
Subscriber sub;
void setup()
{
  Serial.begin(9600);

  robot.neck.begin();
  //lefthand.begin();
  startTimer.resetTimer();

  //robot.rightArm.shouldExt.begin();
}

void loop()
{

  // while (Serial.available())
  // {

  //   char temp = Serial.read();
  //   Serial.print(temp);
  //   //Serial.println("hi");
  //   if (temp == '\n')
  //   {
  //     if (input == "d")
  //     {
  //     }
  //     else if (input == "e")
  //     {
  //     }
  //     else if (input == "g")
  //     {
  //     }
  //     else if (input == "h")
  //     {
  //     }
  //     else if (input == "z")
  //     {
  //     }
  //     input = "";
  //   }
  //   else
  //     input += temp;
  // }

  //lefthand.close();
  robot.startup(started);

  if (startTimer.getTimer() > startTimer.getTime())
  {

    // robot.leftArm.shakeHand();
    // robot.rightArm.shakeHand();
    // delay(5000);
    // robot.leftArm.hand.fixed(50);
    // robot.rightArm.hand.fixed(50);
    // robot.leftArm.bicepExt.goToMax();
    // delay(5000);

    robot.neck.goToMax();
    delay(5000);
    robot.neck.goToMin();
    delay(5000);
  }

  // if (readSensor.getTimer() > readSensor.getTime())
  // {
  //   robot.leftArm.hand.readSensor();
  //   readSensor.resetTimer();
  // }
}
