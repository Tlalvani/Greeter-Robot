#ifndef FINGER
#define FINGER
#include <Joint.h>
#include "Arduino.h"
#include <Timer.h>
class Finger : public Joint
{
private:
    int analogPort;
    int thresh;
    int sensorValue;

    int pos = 0;
    Timer closeTimer = Timer(0);
    Timer openTimer = Timer(20);

public:
    Finger()
    {
        servoPort = 99;
    }
    Finger(int sp, int ap, int min, int max, int t) : Joint(sp, min, max)
    {
        analogPort = ap;
        thresh = t;
        sensorValue = analogRead(analogPort);
    }

    int sensorRead()
    {
        sensorValue = analogRead(analogPort);
        return sensorValue;
    }

    void close()
    {
        Serial.println(sensorRead()); // not sure why it hecks it up without the print statements

        if (closeTimer.getTimer() > closeTimer.getTime())
        {
            if (pos <= max)
                pos++;
            write(pos);
            closeTimer.resetTimer();
        }

        if (sensorRead() > thresh)
        {
            while (pos > min && sensorRead() > thresh)
            {
                sensorRead();
                pos--;
                Serial.println(sensorRead());
                if (openTimer.getTimer() > openTimer.getTime())
                {
                    write(pos);
                    openTimer.resetTimer();
                }
            }
        }
    }
};
#endif