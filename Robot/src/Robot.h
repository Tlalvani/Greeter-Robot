#ifndef ROBOT
#define ROBOT
#include <Arm.h>
#include <Head.h>
#include <Subscriber.h>

class Robot
{

private:
    Timer spinTimer = Timer(1000);
    bool started = false;
    Hand lefthand = Hand(
        Finger(23, 0, 0, 110, 100), //thumb, yellow analog
        Finger(25, 1, 0, 110, 50),
        Finger(27, 2, 0, 90, 300),
        Finger(29, 3, 0, 90, 100),
        Finger(31, 4, 0, 90, 300) //grey analog
    );
    Joint leftWrist = Joint(33, 0, 180);
    Joint leftBicepExt = Joint(35, 110, 160);
    Joint leftBicepRot = Joint(36, 0, 180);
    Joint leftShouldExt = Joint(38, 0, 55);
    Joint leftShouldRot = Joint(40, 0, 180);

    Hand righthand = Hand(
        Finger(37, 8, 0, 90, 300), //thumb, yellow analog, black digital, red finger sensor wire
        Finger(39, 9, 0, 90, 30),  //black finger sensor wire
        Finger(41, 10, 0, 90, 150),
        Finger(43, 11, 0, 90, 300), //grey finger sensor wire
        Finger(45, 12, 0, 90, 10)   //grey analog, orange finger sensor wire
    );
    Joint rightWrist = Joint(47, 0, 180);
    Joint rightBicepExt = Joint(49, 10, 90);
    Joint rightBicepRot = Joint(42, 0, 180);
    Joint rightShouldExt = Joint(44, 0, 55);
    Joint rightShouldRot = Joint(46, 20, 180);

public:
    Subscriber sub;
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

    Head head = Head(
        neck,
        Joint(52, 0, 180), // neck and jaw move conjoined if only writing to one
        Joint(53, 0, 10));

    Robot() {}

    void begin()
    {
        leftArm.begin();
        rightArm.begin();
        neck.begin();
        sub.init();
    }

    void goToMin()
    {
        leftArm.goToMin();
        rightArm.goToMin();
        neck.goToMin();
    }

    void startup()
    {
        if (!started)
        {
            neck.goToMin();
            leftArm.neutral();
            rightArm.neutral();
            started = true;
        }
    }

    void listen()
    {

        String command = sub.getSpeechCom();
        //sub.nh.loginfo(command.c_str());
        if (command == "hello")
        {
            sub.nh.loginfo("Hello");
            sub.speak("Hi How are you");
        }
        else if (command == "high five")
        {
            rightArm.highFive();
            sub.speak("Let's do it!");
        }
        else if (command == "bye")
        {
            sub.speak("See you later");
            started = false;
        }
        else if (command == "hold")
        {
            sub.speak("Okay");
            rightArm.holdTimer.resetTimer();
            rightArm.throwBall(sub);
        }
    }
    void basic()
    {
        leftArm.basicMoveArm(true);
        rightArm.basicMoveArm(false);
    }

    void remoteControl() //Calls Listen and Basic
    {

        if (spinTimer.getTimer() > spinTimer.getTime())
        {
            sub.powerCheck();
            String mode = sub.getMode();
            if (mode == "Listen")
            {
                listen();
            }
            else if (mode == "Basic")
                basic();
            sub.nh.spinOnce();
            spinTimer.resetTimer();
        }
    }
};
#endif