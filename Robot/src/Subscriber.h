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
        nh.advertise(power);
        nh.subscribe(listener);
        nh.subscribe(mode);
        nh.subscribe(basic);
    }

    void speak(String command) //publisher method
    {
        speaker_msg.data = command.c_str();
        speaker.publish(&speaker_msg);
    }

    void powerCheck() //publisher method used to launch startup files on power flick
    {
        int analogthresh = 400;
        if (analogRead(A15) > analogthresh)
        {
            nh.loginfo(("Power On: " + String(analogRead(A15), 10)).c_str());
            power_msg.data = "1";
        }
        else
            power_msg.data = "0";
        power.publish(&power_msg);
    }

    void listenerCallback(const std_msgs::String &outL) //subscriber callback that stores Listen data in the listener_msg
    {
        nh.loginfo("LCall");
        listener_msg = outL.data;
    }

    String getSpeechCom() //retrieves data
    {
        return listener_msg;
    }

    void modeCallback(const std_msgs::String &outM) //subscriber callback that stores Mode data in the mode_msg
    {
        nh.loginfo("MCall");
        mode_msg = outM.data;
    }

    String getMode() //retrieves data
    {
        return mode_msg;
    }

    void basicCallback(const std_msgs::String &outB) //subscriber callback that stores Basic data in the basic_msg
    {
        nh.loginfo("BCall");
        basic_msg = outB.data;
        String temp = "";
        int count = 0;
        parseString(basic_msg); //calls parseString method to update the global array containing the basic data points
    }

    String getBasic() //retrieves data
    {
        return basic_msg;
    }

    void parsePair(String str) //Parses string of form 0,0 //called by parseString
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
};
#endif