#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <ros.h>
#include <std_msgs/String.h>
class Subscriber
{

private:
public:
    ros::NodeHandle nh;

    ros::Publisher speaker;
    std_msgs::String speaker_msg;

    ros::Publisher power;
    std_msgs::String power_msg;

    ros::Subscriber<std_msgs::String, Subscriber> listener;
    String listener_msg;

    ros::Subscriber<std_msgs::String, Subscriber> basic;
    String basic_msg;

    ros::Subscriber<std_msgs::String, Subscriber> mode;
    String mode_msg;

    //Callbacks should get called when ros topics update. Publishers update when .publish is called
    Subscriber() : speaker("/speaker", &speaker_msg), listener("/sendCom", &Subscriber::listenerCallback, this),
                   basic("/sendBasicCom", &Subscriber::basicCallback, this), power("/power", &power_msg), mode("/sendMode", &Subscriber::modeCallback, this)
    {
    }
    void init()
    {
        nh.getHardware()->setBaud(57600);
        nh.initNode();
        nh.advertise(speaker);
        nh.subscribe(listener);
        nh.subscribe(mode);
        nh.subscribe(basic);
        nh.advertise(power);
    }
    void speak(String command)
    {
        speaker_msg.data = command.c_str();
        speaker.publish(&speaker_msg);
        //nh.spinOnce(); // this was maybe reason it failed
    }
    void powerCheck() //Code used to launch startup files on power flick
    {
        if (analogRead(A15) > 400)
        {
            nh.loginfo(("Power On: " + String(analogRead(A15), 10)).c_str());
            power_msg.data = "1";
        }
        else
            power_msg.data = "0";
        power.publish(&power_msg);
        //nh.spinOnce(); // this was maybe reason it failed
    }
    void listenerCallback(const std_msgs::String &outL)
    {
        nh.loginfo("LCall");
        listener_msg = outL.data;
    }

    String getSpeechCom()
    {
        return listener_msg;
    }

    String getMode()
    {
        return mode_msg;
    }

    String getBasic()
    {
        return basic_msg;
    }

    void parsePair(String str) //Parses string of form 0,0
    {
        String substr;
        int index = 0;
        bool x = true;
        int indexVal;
        double valueVal;
        while (index != str.length())
        {

            if (str[index] != ',')
            {
                substr += str[index];
            }
            else if (x)
            {

                indexVal = substr.toInt();
                substr = "";
                x = false;
            }
            else
            {
                valueVal = substr.toDouble();
                substr = "";
            }
            index++;
        }
        basicArray[(indexVal)] = valueVal;
    }

    void parseString(String str) //Parses string from basic topic
    {

        int index = 0;
        String substr;
        while (index != str.length())
        {
            if (str[index] != ';')
            {
                substr += str[index];
                index++;
            }
            else
            {
                //cout << substr << endl;
                index++;
                parsePair(substr);
                substr = "";
            }
        }
    }

    void basicCallback(const std_msgs::String &outB)
    {
        nh.loginfo("BCall");
        basic_msg = outB.data;
        String temp = "";
        int count = 0;
        parseString(basic_msg);
    }

    void modeCallback(const std_msgs::String &outM)
    {
        nh.loginfo("MCall");
        mode_msg = outM.data;
    }
};
#endif