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

<<<<<<< HEAD
    void neutral()
    {
        look(.5, .5, .5);
        mouth.goToMin();
    }

    void look(float vertical, float tilt, float rotate)
=======
    void look(float vertical, float tilt, float rotate) //Takes three values 0-1
>>>>>>> b3b92c916e007a8f9ce11e1ee879a9d69502d5d5
    {
        neck.look(vertical, tilt);
        headRot.scale_write(rotate, 0, 1);
    }

    void basicLook()
    {
        look(basicArray[23], basicArray[22], basicArray[21]);
        mouth.scale_write(basicArray[20], 0, 1);
    }
};
#endif