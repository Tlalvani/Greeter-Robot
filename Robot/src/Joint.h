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

    Joint()
    {
        servoPort = 98;
        min = 98;
        max = 98;
    }

    Joint(int servoPort, int min, int max)
    {

        this->servoPort = servoPort;

        this->min = min;
        this->max = max;
        //joint.attach(servoPort);
    }

    void begin()
    {
        joint.attach(servoPort);
    }

    void write(int pos)
    {
        if (pos < min)
        {
            joint.write(min);
        }
        else if (pos > max)
        {
            joint.write(max);
        }
        else
        {
            joint.write(pos);
        }
    }

    void scale_write(float pos) //from 0 to 1
    {
        write(scale(pos, getMin(), getMax()));
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