#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <ros.h>
#include <std_msgs/String.h>
class Subscriber
{

private:
    

public:
    ros::NodeHandle nh;

    std_msgs::String tts_msg;
    String stt_msg;
    ros::Publisher tts;
    ros::Subscriber<std_msgs::String, Subscriber> stt;
    
    Subscriber():tts("/ttsOut", &tts_msg), stt("/sttOut", &Subscriber::sttCallback, this) {
        
    }
    void init()
    {
        nh.getHardware()->setBaud(57600);
        nh.initNode();
        nh.advertise(tts);
        nh.subscribe(stt);
    }
    void speak(String command)
    {
        tts_msg.data = command.c_str();
        tts.publish(&tts_msg);
        //nh.spinOnce(); // this was maybe reason it failed
    }
    void sttCallback(const std_msgs::String &out){
        stt_msg = out.data;
    }

    String getCom(){
        return stt_msg;
    }
};
#endif