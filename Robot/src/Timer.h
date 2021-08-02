#ifndef TIMER
#define TIMER
#include "Arduino.h"

class Timer
{
private:
    unsigned long timer;
    int time;

public:
    Timer() //Default constructor which defaults to a 1 second timer
    {
        timer = millis();
        time = 1000;
    }
    Timer(int time) //Sets timer to be "time" seconds long
    {
        timer = millis();
        this->time = time;
    }

    void setTimer(int time) //Change delay of timer
    {
        timer = millis();
        this->time = time;
    }
    long getTimer() //Returns time passed since timer last reset
    {
        return millis() - timer;
    }
    int getTime() // Returns delay
    {
        return time;
    }

    void resetTimer() //Resets timer
    {
        timer = millis();
    }
};

#endif