#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <ros.h>
#include <std_msgs/String.h>
class Subscriber
{

private:
    ros::NodeHandle nh;

    std_msgs::String str_msg;
    ros::Publisher tts;

public:
    Subscriber():tts("ttsOut", &str_msg) {
        
    }
    void init()
    {
        nh.getHardware()->setBaud(115200);
        nh.initNode();
        nh.advertise(tts);
    }
    void sendCom(char command[100])
    {
        str_msg.data = command;
        tts.publish(&str_msg);
        nh.spinOnce();
    }
};
#endif