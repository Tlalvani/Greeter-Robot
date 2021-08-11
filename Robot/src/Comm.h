#ifndef COMM_H
#define COMM_H
#include "Arduino.h"
class Comm
{
private:
    String mode = "";
    String msg = "";
    String data = "";
    const byte numChars = 128;
    char receivedChars[128];

    boolean newData = false;

    void recvWithStartEndMarkers()
    {
        static boolean recvInProgress = false;
        static byte ndx = 0;
        char startMarker = '<';
        char endMarker = '>';
        char rc;

        while (Serial.available() > 0 && newData == false)
        {
            rc = Serial.read();

            if (recvInProgress == true)
            {
                if (rc != endMarker)
                {
                    receivedChars[ndx] = rc;
                    ndx++;
                    if (ndx >= numChars)
                    {
                        ndx = numChars - 1;
                    }
                }
                else
                {
                    receivedChars[ndx] = '\0'; // terminate the string
                    recvInProgress = false;
                    ndx = 0;
                    newData = true;
                }
            }

            else if (rc == startMarker)
            {
                recvInProgress = true;
            }
        }
    }

    void showNewData()
    {
        if (newData == true)
        {
            data = receivedChars;
            newData = false;
        }
    }

public:
    void getData()
    {
        recvWithStartEndMarkers();
        showNewData();

        if (data[0] == 'B')
        {
            mode = "Basic";
        }
        else if (data[0] == 'C')
        {
            mode = "Command";
        }
        else if (data[0] == 'L')
        {
            mode = "Listen";
        }
        else
        {
        }
        msg = data.substring(1);
        //Serial.println(mode);
        //Serial.print("Hi Raspberry Pi! You sent me: ");
        //Serial.println(data);
    }

    String getMode()
    {
        return mode;
    }

    String getMsg()
    {
        return msg;
    }

    void powerCheck() //Code used to launch startup files on power flick
    {
        String power = "";
        if (analogRead(A15) > 400)
        {
            power = "1";
        }
        else
            power = "0";
        Serial.println('P' + power);
        //nh.spinOnce(); // this was maybe reason it failed
    }

    void speak(String command)
    {
        Serial.println('C' + command);
        //nh.spinOnce(); // this was maybe reason it failed
    }

    void parseBasic()
    {
        String basicMsg = getMsg();
        Serial.println(getMsg());
        String temp = "";
        int count = 0;
        for (auto i : basicMsg) //Coverts string to array
        {
            if (i != ',') //Loop until ,
            {
                temp += i;
            }
            else
            {
                //basicArray are defined in global
                basicArray[count] = atof(temp.c_str()); //append temp to array

                //String out = String(basicArray[count], 2);

                count++;
                temp = "";
            }
        }
    }
};
#endif