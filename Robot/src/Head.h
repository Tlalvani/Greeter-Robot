#ifndef HEAD
#define HEAD
#include <Neck.h>

class Head
{

private:
public:
    Neck neck;
    Joint headRot;
    Joint mouth;

    Head() {}
    Head(Neck neck, Joint headRot, Joint mouth)
    {
        this->neck = neck;
        this->headRot = headRot;
        this->mouth = mouth;
    }

    void begin()
    {
        neck.begin();
        headRot.begin();
        mouth.begin();
    }

    void goToMin()
    {
        neck.goToMin();
        headRot.goToMin();
        mouth.goToMin();
    }

    void goToMax()
    {
        neck.goToMax();
        headRot.goToMax();
        mouth.goToMax();
    }
};
#endif