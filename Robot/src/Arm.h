#ifndef ARM
#define ARM
#include <Hand.h>
#include <Global.h>
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
        //hand.goToMin();
        //hand.close();
        hand.fixed(0);
        moveArm(.75, .6, 0, .25);
        // bicepExt.write(140);
        // bicepRot.write(110);
        // shouldExt.write(0);
        // shouldRot.write(45);
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

    void neutral()
    {
        hand.goToMin();
        wrist.goToMin();
        bicepExt.write(170);
        bicepRot.write(90);
        shouldExt.write(0);
        shouldRot.write(0);
    }

    void moveArm(float bExten, float bRot, float sExten, float sRot)
    {

        // Serial.print("\nBicepExt ");
        // Serial.println(scale(bExten, bicepExt.getMin(), bicepExt.getMax()));

        // Serial.print("\nBicepRot ");
        // Serial.println(scale(bRot, bicepRot.getMin(), bicepRot.getMax()));

        // Serial.print("\nShouldExt ");
        // Serial.println(scale(sExten, shouldExt.getMin(), shouldExt.getMax()));

        // Serial.print("\nShouldRot ");
        // Serial.println(scale(sRot, shouldRot.getMin(), shouldRot.getMax()));

        // delay(10000);
        bicepExt.write(scale(bExten, bicepExt.getMin(), bicepExt.getMax()));
        bicepRot.write(scale(bRot, bicepRot.getMin(), bicepRot.getMax()));
        shouldExt.write(scale(sExten, shouldExt.getMin(), shouldExt.getMax()));
        shouldRot.write(scale(sRot, shouldRot.getMin(), shouldRot.getMax()));
    }
};
#endif