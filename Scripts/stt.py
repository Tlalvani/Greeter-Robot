#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from pocketsphinx import LiveSpeech


def stt():
	
    pub = rospy.Publisher('sttOut', String, queue_size=10)
    rospy.init_node('stt', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        speech = LiveSpeech(lm=False,kws='words.list')
        for phrase in speech:
	    	print(str(phrase))
        	pub.publish(str(phrase))
        rate.sleep()

if __name__ == '__main__':
    try:
        stt()
    except rospy.ROSInterruptException:
        pass
