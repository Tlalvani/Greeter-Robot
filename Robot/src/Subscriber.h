#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64MultiArray.h>

#include <Joint.h> // for the global.h call since <global.h> can't be called twice

class Subscriber
{

private:
public:
    ros::NodeHandle nh;
    std_msgs::String tts_msg;
    String mode_msg;
    String stt_msg;
    String basic_msg;
    ros::Publisher tts;
    ros::Subscriber<std_msgs::String, Subscriber> mode;
    ros::Subscriber<std_msgs::String, Subscriber> stt;

    ros::Subscriber<std_msgs::String, Subscriber> basic;

    Subscriber() : tts("/listen", &tts_msg), mode("/sendMode", &Subscriber::modeCallback, this),
                   stt("/sendSpeechCom", &Subscriber::sttCallback, this), basic("/sendBasicCom", &Subscriber::basicCallback, this)
    {
    }
    void init()
    {
        nh.getHardware()->setBaud(57600);
        nh.initNode();
        nh.advertise(tts);
        nh.subscribe(stt);
        nh.subscribe(mode);
        nh.subscribe(basic);
    }
    void speak(String command)
    {
        tts_msg.data = command.c_str();
        tts.publish(&tts_msg);
        //nh.spinOnce(); // this was maybe reason it failed
    }
    void modeCallback(const std_msgs::String &out)
    {
        mode_msg = out.data;
    }
    void sttCallback(const std_msgs::String &out)
    {
        stt_msg = out.data;
    }
    void basicCallback(const std_msgs::String &out)
    {
        basic_msg = out.data;
        String temp = "";
        int count = 0;
        for (auto i : basic_msg)
        {
            if (i != ',')
            {
                temp += i;
            }
            else
            {

                basicArray[count] = atof(temp.c_str()); //basicArray are defined in global

                String out = String(basicArray[count], 2);
                // nh.loginfo(out.c_str());

                count++;
                temp = "";
            }
        }
    }
    String getMode()
    {
        return mode_msg;
    }
    String getSpeechCom()
    {
        return stt_msg;
    }
};
#endif