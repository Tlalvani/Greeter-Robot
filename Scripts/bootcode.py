#!/usr/bin/env python
import rospy
from std_msgs.msg import String

import subprocess
state = False

def callback(data):
    if data.data !="":
        print(state)
        if data.data == '0' and state :
            pro.terminate()
            state = False
        elif data.data =='1' and not state:
            pro = subprocess.Popen("sudo bash ./Github/GreeterRobot/Scripts/start.sh",  
                    shell=True) 
            state = True
        else:
            print('Elses1')
    else:
        print("else")
                
def power():

    rospy.init_node('bootcode', anonymous=True)

    rospy.Subscriber("power", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    print('bootcode.py started')
    power()