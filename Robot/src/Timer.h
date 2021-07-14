#ifndef TIMER
#define TIMER
#include "Arduino.h"

class Timer
{
private:
    unsigned long timer;
    int time;

public:
    Timer()
    {
        timer = millis();
        time = 0;
    }
    Timer(int time)
    {
        timer = millis();
        this->time = time;
    }

    void setTimer(int time)
    {
        timer = millis();
        this->time = time;
    }
    long getTimer()
    {
        return millis() - timer;
    }
    int getTime()
    {
        return time;
    }

    void resetTimer()
    {
        timer = millis();
    }
};

#endif