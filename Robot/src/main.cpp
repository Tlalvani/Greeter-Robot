#include "Arduino.h"
#include <Servo.h>
#include <Robot.h>
#include <Timer.h>


Robot robot;
String input = "";
bool started = false;
Timer startTimer(5000);
Timer readSensor(1000);
Subscriber sub;
void setup()
{
  Serial.begin(115200);

  robot.begin();
  //lefthand.begin();
  startTimer.resetTimer();
  sub.init();
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
   
    robot.rightArm.moveArm(.5,.5,0,.5);
    robot.rightArm.hand.fixed(80);
    robot.rightArm.wrist.write(0);
    delay(2000);
    robot.rightArm.wrist.write(170);
    robot.rightArm.hand.fixed(80);
    delay(5000);
    
  }

  // if (readSensor.getTimer() > readSensor.getTime())
  // {
  //   robot.leftArm.hand.readSensor();
  //   readSensor.resetTimer();
  // }
}
