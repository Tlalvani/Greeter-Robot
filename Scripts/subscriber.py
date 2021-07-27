#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import speech_recognition as sr
import time

from firebase_admin import credentials
import firebase_admin
from google.cloud import firestore
import os

#Listen 
r = sr.Recognizer()
m = sr.Microphone()

#Firebase
path = "/home/george/Github/GreeterRobot/Scripts/key.json"
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = path
cred = credentials.Certificate(path)
firebase_admin.initialize_app(cred)
db = firestore.Client()

#Ros
pubBasic = rospy.Publisher('sendBasicCom', String, queue_size=10)
pubMode = rospy.Publisher('sendMode',String, queue_size=10)
pubListen = rospy.Publisher('/listener', String, queue_size=10)
rospy.init_node('Subscriber', anonymous=True)
rate = rospy.Rate(1) # 1hz

def listener():
    with m as source: r.adjust_for_ambient_noise(source)
    print("Set minimum energy threshold to {}".format(r.energy_threshold))
    mode_out = mode()
    while mode_out == "Listen":
        try:
            print("Say something!")
            pubListen.publish('')
            with m as source: audio = r.listen(source)
            print("Got it! Now to recognize it...")
            try:
                # recognize speech using Google Speech Recognition
                value = r.recognize_google(audio)
                out=''
                # we need some special handling here to correctly print unicode characters to standard output
                if str is bytes:  # this version of Python uses bytes for strings (Python 2)
                    out = (u"{}".format(value).encode("utf-8"))
                else:  # this version of Python uses unicode for strings (Python 3+)
                    out = ("{}".format(value))
                
                commands(out)
            except sr.UnknownValueError:
                print("Oops! Didn't catch that")
            except sr.RequestError as e:
                print("Uh oh! Couldn't request results from Google Speech Recognition service; {0}".format(e))
            rate.sleep()
            mode_out = mode()
        except KeyboardInterupt:
            pass
        

              
def commands(string):

    string = string.replace("Hi-5", 'high five')
    string = string.replace("-", ' ')
    print(string)
    diction = ['hello',"handshake", 'high five' , 'bye','hold','throw']

    for i in range(len(diction)):
        if diction[i] in string:
            pubListen.publish(diction[i])
            time.sleep(1.1)
            break


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
    return mode_val
         

if __name__ == '__main__':
    try:
        print('Subscriber started')
        while not rospy.is_shutdown():
            try:
                mode_out = mode()
                if mode_out == "Listen":
                    listener()
                elif mode_out == "Basic":
                    basic()
            except KeyboardInterupt:
                pass
    except rospy.ROSInterruptException:
        pass
