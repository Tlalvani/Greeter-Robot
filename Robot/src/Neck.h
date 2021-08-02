#ifndef NECK
#define NECK
#include <Joint.h>

class Neck
{

private:
public:
    Joint front;
    Joint left;
    Joint right;
    Neck() {}
    Neck(Joint front, Joint left, Joint right)
    {
        this->front = front;
        this->left = left;
        this->right = right;
    }

    //Left and Right balance at 50
    void begin()
    {
        front.begin();
        left.begin();
        right.begin();
    }

    void goToMin()
    {
        front.goToMin();
        left.write(50);
        right.write(50);
    }

    void goToMax()
    {
        front.goToMax();
        left.goToMax();
        right.goToMax();
    }

    void look(float vertical, float tilt) //Takes two values that are 0-1
    {
        front.scale_write(vertical, 0, 1);
        left.scale_write(tilt, 0, 1); //Left and Right are scaled opposite so they move in sync
        right.scale_write(tilt, 1, 0);
    }
};
#endif