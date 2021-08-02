#ifndef ARM
#define ARM
#include <Hand.h>
#include <Timer.h>
#include <Subscriber.h>
class Arm
{

private:

public:
    Hand hand;
    Joint wrist;
    Joint bicepExt;
    Joint bicepRot;
    Joint shouldExt;
    Joint shouldRot;

    //Used in throwBall method
    Timer holdTimer = Timer(3000);
    Timer throwTimer = Timer(1000);
    Timer commTimer = Timer(1000);

    Arm() {}
    Arm(Hand hand, Joint wrist, Joint bicepExt, Joint bicepRot, Joint shouldExt, Joint shouldRot)
    {
        this->hand = hand;
        this->wrist = wrist;
        this->bicepExt = bicepExt;
        this->bicepRot = bicepRot;
        this->shouldExt = shouldExt;
        this->shouldRot = shouldRot;
    }
    void begin()
    {
        hand.begin();
        wrist.begin();
        bicepExt.begin();
        bicepRot.begin();
        shouldExt.begin();
        shouldRot.begin();
    }
    void shakeHand()
    {
        wrist.goToMin();
        hand.fixed(0);
        moveArm(.75, .6, 0, .25);
    }

    void highFive()
    {
        moveArm(1, .5, 0, .7);
        wrist.write(180);
    }

    void throwBall(Subscriber &sub)
    {
        String comm = sub.getSpeechCom();
        moveArm(.7, .75, 0, .3);
        wrist.goToMin();
        hand.fixed(40);
        bool thrown = false;
        while (!thrown && comm != "bye")
        {

            if (holdTimer.getTimer() > holdTimer.getTime())
            {

                if (comm == "throw")
                {
                    moveArm(.3, .75, 0, .45);
                    if (throwTimer.getTimer() > throwTimer.getTime())
                    {
                        hand.fixed(0);
                        thrown = true;
                        sub.nh.loginfo("Thrown");
                    }
                }
                else //this runs first but only once since after the timer is done it will just run the if
                {
                    hand.close();
                    throwTimer.resetTimer();
                    sub.nh.loginfo("Holding");
                }
            }
            if (commTimer.getTimer() > commTimer.getTime())
            {
                comm = sub.getSpeechCom();
                sub.nh.spinOnce();
                commTimer.resetTimer();
            }
        }
    }
    void goToMin()
    {
        hand.goToMin();
        wrist.goToMin();
        bicepExt.goToMin();
        bicepRot.goToMin();
        shouldExt.goToMin();
        shouldRot.goToMin();
    }

    void neutral() //Moves arm to neutral position
    {
        hand.goToMin();
        wrist.goToMin();
        moveArm(1, .5, 0, 0);
    }

    void moveArm(float bExten, float bRot, float sExten, float sRot) //Takes four values 0-1 to write arm servos
    {
        bicepExt.scale_write(bExten, 0, 1);
        bicepRot.scale_write(bRot, 0, 1);
        shouldExt.scale_write(sExten, 0, 1);
        shouldRot.scale_write(sRot, 0, 1);
    }

    void basicMoveArm(bool left) //Used with basic control, pulls from basicArray which is defined in global
    {
        if (left)
        {
            moveArm(basicArray[0], basicArray[1], basicArray[2], basicArray[3]);
            wrist.scale_write(basicArray[9], 0, 1);
            hand.basicMoveHand(left);
        }
        else
        {
            moveArm(basicArray[10], basicArray[11], basicArray[12], basicArray[13]);
            wrist.scale_write(basicArray[19], 0, 1);
            hand.basicMoveHand(left);
        }
    }
};
#endif