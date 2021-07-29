#!/usr/bin/env python
import rospy
from std_msgs.msg import String

import pyttsx3

#speaker engine
engine = pyttsx3.init()
engine.setProperty('voice', 'english-us')
   

def speakerCallback(data):
    
    if data.data !="":
        rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
        engine.say(data.data)
        engine.runAndWait()
    
def speakerListener():

    rospy.init_node('Speaker', anonymous=True)

    rospy.Subscriber("/speaker", String, speakerCallback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':

    engine.say("Hi I am george jetson")
    engine.runAndWait()

    print("Subscriber started")
    speakerListener()
    