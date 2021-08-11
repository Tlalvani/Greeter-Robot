#!/usr/bin/env python
import firebase 
import faceRecognition
import speechRecognition
import rosPublisher
import helper

import rospy

fb = firebase.Firebase()
fr = faceRecognition.FaceRecognition(fb)
spr = speechRecognition.SpeechRecognition(fb)
rp = rosPublisher.RosPublisher(fb)

if __name__ == '__main__':
    try:
        while not rospy.is_shutdown():
            mode_val =  fb.mode()
            rp.publishMode(mode_val)
            if mode_val == "Listen":
                command_val = helper.extractKeywords(spr.listener())
                rp.publishCommand(command_val)
            elif mode_val == "Basic":
                basic_val = fb.basic()
                rp.publishBasic(basic_val) 
            elif mode_val == "Encode":
                fr.encodeImage()
            elif mode_val == "Recognize":
                talk_val = fr.recognize()
                print(talk_val)
                rp.publishTalk(talk_val)
            elif mode_val == "Command":
                command_val = helper.extractKeywords(fb.command())
                rp.publishCommand(command_val)   
    except rospy.ROSInterruptException:
        fr.closeOpenCv()
        pass

