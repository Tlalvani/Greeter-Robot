#include "Arduino.h"
#include <Servo.h>
#include <Robot.h>

Robot robot;

Timer startTimer(5000);

void setup()
{
  robot.begin();
  startTimer.resetTimer();
}

void loop()
{
  robot.startup();
  
  if (startTimer.getTimer() > startTimer.getTime())
  {
    robot.remoteControl();
  }
}
