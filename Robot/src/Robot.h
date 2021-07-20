#ifndef ROBOT
#define ROBOT
#include <Arm.h>
#include <Neck.h>
#include <Subscriber.h>

class Robot
{

private:
    Subscriber sub;
    Hand lefthand = Hand(
        Finger(23, 0, 0, 110, 100), //thumb, yellow analog
        Finger(25, 1, 0, 110, 50),
        Finger(27, 2, 0, 90, 300),
        Finger(29, 3, 0, 90, 100),
        Finger(31, 4, 0, 90, 300) //grey analog
    );
    Joint leftWrist = Joint(33, 0, 180);
    Joint leftBicepExt = Joint(35, 110, 170);
    Joint leftBicepRot = Joint(36, 0, 180);
    Joint leftShouldExt = Joint(38, 0, 55);
    Joint leftShouldRot = Joint(40, 0, 180);

    Hand righthand = Hand(
        Finger(37, 8, 0, 90, 100), //thumb, yellow analog, black digital, red finger sensor wire
        Finger(39, 9, 0, 90, 100), //black finger sensor wire
        Finger(41, 10, 0, 90, 100),
        Finger(43, 11, 0, 90, 100), //grey finger sensor wire
        Finger(45, 12, 0, 90, 100)  //grey analog, orange finger sensor wire
    );
    Joint rightWrist = Joint(47, 0, 180);
    Joint rightBicepExt = Joint(49, 10, 100);
    Joint rightBicepRot = Joint(42, 0, 180);
    Joint rightShouldExt = Joint(44, 0, 55);
    Joint rightShouldRot = Joint(46, 20, 180);

public:
    Arm leftArm = Arm(
        lefthand,
        leftWrist,
        leftBicepExt,
        leftBicepRot,
        leftShouldExt,
        leftShouldRot);

    Arm rightArm = Arm(
        righthand,
        rightWrist,
        rightBicepExt,
        rightBicepRot,
        rightShouldExt,
        rightShouldRot);

    Neck neck = Neck(
        Joint(34, 40, 100),
        Joint(48, 10, 70),
        Joint(50, 10, 70) //right neck orange digital
    );

    Robot() {}

    void begin()
    {
        leftArm.begin();
        rightArm.begin();
        neck.begin();
    }

    void goToMin()
    {
        leftArm.goToMin();
        rightArm.goToMin();
        neck.goToMin();
    }

    void startup(bool &started)
    {
        if (!started)
        {
            neck.goToMin();
            leftArm.neutral();
            rightArm.neutral();
            started = true;
            Serial.println("Startup");
            //sub.sendCom("Startup");
        }
    }
};
#endif