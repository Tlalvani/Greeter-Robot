#include "Arduino.h"
#include <Servo.h>
#include <Robot.h>
#include <Timer.h>

Robot robot;

Timer startTimer(5000);
Timer spinTimer(1000);

void setup()
{
  //Serial.begin(9600);

  robot.begin();
  //lefthand.begin();
  startTimer.resetTimer();
  robot.sub.init();
  //robot.rightArm.shouldExt.begin();
}

void loop()
{

  //lefthand.close();

  robot.startup();

  if (startTimer.getTimer() > startTimer.getTime())
  {

    if (spinTimer.getTimer() > spinTimer.getTime())
    {
      robot.listen();
      robot.sub.nh.spinOnce();
      spinTimer.resetTimer();
    }
  }
}
