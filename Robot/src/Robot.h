#ifndef ROBOT
#define ROBOT
#include <Arm.h>
#include <Neck.h>

class Robot
{

private:
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
        Finger(37, 8, 0, 90, 100), //thumb, yellow analog
        Finger(39, 9, 0, 90, 100),
        Finger(41, 10, 0, 90, 100),
        Finger(43, 11, 0, 90, 100),
        Finger(45, 12, 0, 90, 100) //grey analog
    );
    Joint rightWrist = Joint(47, 0, 180);
    Joint rightBicepExt = Joint(49, 150, 180);
    Joint rightBicepRot = Joint(42, 0, 180);
    Joint rightShouldExt = Joint(44, 0, 55);
    Joint rightShouldRot = Joint(46, 0, 180);

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
        Joint(34, 50, 60),
        Joint(48, 50, 60),
        Joint(50, 50, 60) //right neck orange digital
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
        }
    }
};
#endif