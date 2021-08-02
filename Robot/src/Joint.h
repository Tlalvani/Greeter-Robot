#ifndef JOINT
#define JOINT
#include <Servo.h>
#include "Arduino.h"
#include <Global.h>

class Joint
{
private:
    Servo joint;

protected:
    int min = 0;
    int max = 0;

public:
    int servoPort = 0;

    Joint() //Default constructor, effectively null
    {
        servoPort = 98;
        min = 98;
        max = 98;
    }

    Joint(int servoPort, int min, int max) //Takes servo port min and max
    {
        this->servoPort = servoPort;
        this->min = min;
        this->max = max;
    }

    void begin()
    {
        joint.attach(servoPort);
    }

    void write(int pos) //Writes servo position such that it never exceeds min or max
    {
        joint.write(clip(pos, min, max));
    }

    void scale_write(float pos, float scaleMin, float scaleMax) //Scales pos between scaleMin and scaleMax. This is normally 0-1
    {
        write(scale(pos, getMin(), getMax(), scaleMin, scaleMax));
    }

    void goToMin()
    {
        write(min);
    }

    void goToMax()
    {
        write(max);
    }

    int getMin()
    {
        return min;
    }

    int getMax()
    {
        return max;
    }
};
#endif