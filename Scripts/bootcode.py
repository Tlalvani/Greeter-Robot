#!/usr/bin/env python
import rospy
from std_msgs.msg import String

import subprocess
import sys

state = False

def callback(data):
    global state, pid1, pid2
    
    
    if data.data == '0' and state :
        pid1.terminate()
        pid2.terminate()
        state = False
        print("FALSE")
    elif data.data =='1' and not state:
        pid1 = subprocess.Popen([sys.executable, "/home/george/Github/GreeterRobot/Scripts/subscriber.py"])
        pid2 = subprocess.Popen([sys.executable, "/home/george/Github/GreeterRobot/Scripts/publisher.py"])
        state = True
        print("TRUE")
                
def power():

    rospy.init_node('bootcode', anonymous=True)

    rospy.Subscriber("power", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    print('bootcode.py started')
    power()