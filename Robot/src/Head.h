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

    void look(float vertical, float tilt, float rotate)
    {
        neck.look(vertical, tilt);
        headRot.scale_write(rotate, 0, 1);
    }
};
#endif