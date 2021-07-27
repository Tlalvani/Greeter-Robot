#!/usr/bin/env python

from firebase_admin import credentials
import firebase_admin
from google.cloud import firestore
import os
import rospy
from std_msgs.msg import String
path = "/home/george/Github/GreeterRobot/Scripts/Firebase/key.json"
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = path

pubBasic = rospy.Publisher('sendBasicCom', String, queue_size=10)
pubMode = rospy.Publisher('sendMode',String, queue_size=10)
rospy.init_node('Firebase', anonymous=True)
rate = rospy.Rate(1) # 10hz

cred = credentials.Certificate(path)
firebase_admin.initialize_app(cred)
db = firestore.Client()

def all():
    while not rospy.is_shutdown():
        try:
            basic()
            mode()
        except KeyboardInterupt:
            pass

def basic():
    basic_ref = db.collection(u'Basic')
    basic_list = [] 
    for doc in basic_ref.stream():
        temp_key =[]
        temp_val = []
        for key,value in doc.to_dict().items():
            temp_key.append(key)
        temp_key.sort() 
        for i in range(len(temp_key)):
            basic_list.append(doc.to_dict()[temp_key[i]])
    pubBasic.publish(",".join(basic_list))

def mode():
    mode_val = db.collection(u'Misc').document(u'Mode').get().to_dict()["Mode"]
    pubMode.publish(mode_val)

if __name__ == '__main__':
    try:
        print("Firebase.py started")
        all()
    except rospy.ROSInterruptException:
        pass