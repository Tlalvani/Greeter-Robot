#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <ros.h>
#include <std_msgs/String.h>
class Subscriber
{

private:
    ros::NodeHandle nh;

    std_msgs::String tts_msg;
    String stt_msg;
    ros::Publisher tts;
    ros::Subscriber<std_msgs::String, Subscriber> stt;

public:
    
    Subscriber():tts("ttsOut", &tts_msg), stt("sttOut", &Subscriber::sttCallback, this) {
        
    }
    void init()
    {
        nh.getHardware()->setBaud(115200);
        nh.initNode();
        nh.advertise(tts);
        nh.subscribe(stt);
    }
    void sendCom(char command[100])
    {
        tts_msg.data = command;
        tts.publish(&tts_msg);
        nh.spinOnce();
    }
    void sttCallback(const std_msgs::String &out){
        stt_msg = out.data;
    }

    void takeCom(){
        if(stt_msg == "Hello")
            sendCom("Hello, I am George");
        // if(stt_msg == "Handshake")
    }
};
#endif