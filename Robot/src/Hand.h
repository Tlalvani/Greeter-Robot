#ifndef HAND
#define HAND
#include <Finger.h>
class Hand
{

private:
public:
    Finger thumb;
    Finger index;
    Finger middle;
    Finger ring;
    Finger pinky;
    Hand() {}
    Hand(Finger thumb, Finger index, Finger middle, Finger ring, Finger pinky)
    {
        this->thumb = thumb;
        this->index = index;
        this->middle = middle;
        this->ring = ring;
        this->pinky = pinky;
    }

    void begin()
    {
        thumb.begin();
        index.begin();
        middle.begin();
        ring.begin();
        pinky.begin();
    }
    void fixed(int pose)
    {
        pinky.write(pose);
        ring.write(pose);
        middle.write(pose);
        index.write(pose);
        thumb.write(pose);
    }
    void goToMin()
    {
        pinky.goToMin();
        ring.goToMin();
        middle.goToMin();
        index.goToMin();
        thumb.goToMin();
    }

    void spinspin(int min, int max)
    {
        int pos = 0;
        for (pos = min; pos <= max; pos += 1)
        { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            pinky.write(pos);
            ring.write(pos);
            middle.write(pos);
            index.write(pos);
            thumb.write(pos); // tell servo to go to position in variable 'pos'
            delay(30);        // waits 15ms for the servo to reach the position
        }
        for (pos = max; pos >= min; pos -= 1)
        { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            pinky.write(pos);
            ring.write(pos);
            middle.write(pos);
            index.write(pos);
            thumb.write(pos); // tell servo to go to position in variable 'pos'
            delay(30);        // waits 15ms for the servo to reach the position
        }
        delay(5000);
    }

    void readSensor()
    {
        Serial.print("Pinky: ");
        Serial.println(pinky.sensorRead());
        Serial.print("Ring: ");
        Serial.println(ring.sensorRead());
        Serial.print("Middle: ");
        Serial.println(middle.sensorRead());
        Serial.print("Index: ");
        Serial.println(index.sensorRead());
        Serial.print("Thumb: ");
        Serial.println(thumb.sensorRead());
        Serial.println("");
    }

    void close()
    {
        pinky.close();
        ring.close();
        middle.close();
        index.close();
        thumb.close();
    }

    void moveHand(int t, int i, int m, int r, int p) //Takes five values that are 0-1
    {
        thumb.scale_write(t, 0, 1);
        index.scale_write(i, 0, 1);
        middle.scale_write(m, 0, 1);
        ring.scale_write(r, 0, 1);
        pinky.scale_write(p, 0, 1);
    }

    void basicMoveHand(bool left)
    {
        if (left)
            moveHand(basicArray[8], basicArray[4], basicArray[5], basicArray[7], basicArray[6]);
        else
            moveHand(basicArray[18], basicArray[14], basicArray[1], basicArray[17], basicArray[16]);
    }
};
#endif