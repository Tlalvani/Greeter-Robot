#include "Arduino.h"
#include <Servo.h>
#include <Robot.h>

Robot robot;

Timer startTimer(5000);
Timer spinTimer(1000);

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

    if (spinTimer.getTimer() > spinTimer.getTime())
    {
      robot.listen();
      robot.sub.nh.spinOnce();
      spinTimer.resetTimer();
    }
  }
}
