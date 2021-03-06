import rospy
from std_msgs.msg import String
import time

class RosPublisher():
    #Ros
    pubBasic = rospy.Publisher('sendBasicCom', String, queue_size=10)
    pubMode = rospy.Publisher('sendMode',String, queue_size=10)
    pubCommand = rospy.Publisher('/sendCom', String, queue_size=10)
    pubTalk = rospy.Publisher('/speaker', String, queue_size=10)
    rospy.init_node('publisher', anonymous=True)
    rate = rospy.Rate(1) # 1hz

    def __init__(self, fb):
        self.fb = fb

    def publishBasic(self, basic_val):
        if basic_val != '':
            self.pubBasic.publish(basic_val)
        self.rate.sleep()

    def publishMode(self, mode_val):
        self.pubMode.publish(mode_val)
        self.rate.sleep()
    
    def publishCommand(self, command_val):
        if command_val == "recognize":
            self.fb.changeMode("Recognize")
        else:
            self.pubCommand.publish(command_val)
        time.sleep(1) # so that arduino doesnt subscribe to the topic twice
        self.rate.sleep()
        self.pubCommand.publish('') # resets topic
    
    def publishTalk(self, talk_val):
        self.pubTalk.publish(talk_val)
    
    

        
