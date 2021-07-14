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

    void begin()
    {
        front.begin();
        left.begin();
        right.begin();
    }

    void goToMin()
    {
        front.goToMin();
        left.goToMin();
        right.goToMin();
    }
};
#endif