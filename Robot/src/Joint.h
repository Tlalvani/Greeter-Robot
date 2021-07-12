#ifndef JOINT
#define JOINT
#include <Servo.h>
#include "Arduino.h"

class Joint
{
private:
    Servo joint;
public:
    
    int servoPort=0;
    int min=0;
    int max=0;
    Joint() {
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
    
    void begin(){
        joint.attach(servoPort);
    }
    void write(int pos)
    {
        joint.write(pos);
    }
    void goToMin()
    {
        write(min);
    }
    void goToMax()
    {
        write(max);
    }
};
#endif