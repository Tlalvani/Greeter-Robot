#!/usr/bin/env python
import rospy
from std_msgs.msg import String

# importing the pyttsx library
import pyttsx3
  
# initialisation of library
engine = pyttsx3.init()
engine.setProperty('voice', 'english-us')
   

def callback(data):
    
    if data.data !="":
        rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
        engine.say(data.data)
        engine.runAndWait()
    
def listener():

    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("listen", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':

    engine.say("Hi I am george jetson")
    print("tts started")
    #engine.say(data.data)
    engine.runAndWait()
    listener()
    