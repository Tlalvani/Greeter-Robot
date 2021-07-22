#ifndef HAND
#define HAND
#include <Finger.h>
#include <Global.h>
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

    void moveHand(int t, int i, int m, int r, int p)
    {
        thumb.write(scale(t, thumb.getMin(), thumb.getMax()));
        index.write(scale(i, index.getMin(), index.getMax()));
        middle.write(scale(m, middle.getMin(), middle.getMax()));
        ring.write(scale(r, ring.getMin(), ring.getMax()));
        pinky.write(scale(p, pinky.getMin(), pinky.getMax()));
    }
};
#endif