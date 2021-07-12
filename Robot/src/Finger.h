#ifndef FINGER
#define FINGER
#include <Joint.h>
#include "Arduino.h"

class Finger : public Joint
{
private:
    int analogPort;
    int thresh;
    int sensorValue;

    int pos = 0;
    unsigned long closeTimer = millis();
    unsigned long openTimer = millis();
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
        int openTime = 20;
        int closeTime = 0;
       Serial.println(sensorRead());

        if (millis() - closeTimer > closeTime)
        {
            if (pos <= max)
                pos++;
            write(pos); 
            closeTimer = millis();
        }
        


        if (sensorRead() > thresh)
        {
            while (pos > min && sensorRead() > thresh)
            {
                sensorRead();
                pos--;
                Serial.println(sensorRead());
                if (millis() - openTimer > openTime)
                {
                    write(pos);
                    openTimer = millis();
                }
            }
        }
        
    }
};
#endif