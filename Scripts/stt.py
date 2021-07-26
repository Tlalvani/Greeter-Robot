#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import speech_recognition as sr
import time

r = sr.Recognizer()
m = sr.Microphone()

pub = rospy.Publisher('sendSpeechCom', String, queue_size=10)
rospy.init_node('stt', anonymous=True)
rate = rospy.Rate(10) # 10hz

def stt():
    with m as source: r.adjust_for_ambient_noise(source)
    print("Set minimum energy threshold to {}".format(r.energy_threshold))
     
    while not rospy.is_shutdown():
        try:
            print("Say something!")
            pub.publish('')
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
        except KeyboardInterupt:
            pass

              
def commands(string):

    string = string.replace("Hi-5", 'high five')
    string = string.replace("-", ' ')
    print(string)
    diction = ['hello',"handshake", 'high five' , 'bye','hold','throw']

    for i in range(len(diction)):
        if diction[i] in string:
            pub.publish(diction[i])
            time.sleep(1.1)
            break

         

if __name__ == '__main__':
    try:
        print('stt.py started')
        stt()
    except rospy.ROSInterruptException:
        pass
