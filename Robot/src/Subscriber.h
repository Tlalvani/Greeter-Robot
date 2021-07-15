#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <ros.h>
#include <std_msgs/String.h>

class Subscriber
{

private:
    ros::NodeHandle nh;

    std_msgs::String str_msg;
    ros::Publisher tts("tssOut", &str_msg);

public:
    Subscriber() {}
    void init()
    {
        nh.initNode();
        nh.advertise(tts);
    }

    void sendCom(String command)
    {
        str_msg.data = command;
        tts.publish(&str_msg);
        nh.spinOnce();
    }
};
#endif