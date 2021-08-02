#include "Arduino.h"
#include <Servo.h>
#include <Robot.h>

Robot robot;

Timer startTimer(5000); //Delay between startup and actual motion
void setup()
{
  robot.begin();
  startTimer.resetTimer();
}

void loop()
{
  robot.startup();

  if (startTimer.getTimer() > startTimer.getTime()) //Waits until after start timer finishes to run this code
  {
    robot.remoteControl();
  }
}
