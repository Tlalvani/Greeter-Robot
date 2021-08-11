#!/usr/bin/env python
import firebase 
import speaker
import speechRecognition
import faceRecognition
import helper
import ros

import rospy

fb = firebase.Firebase()
spr = speechRecognition.SpeechRecognition(fb)
fr = faceRecognition.FaceRecognition(fb)
rp = rosPublisher.RosPublisher()

if __name__ == '__main__':
    try:
        while not rospy.is_shutdown():
            # try:            
                mode_val =  fb.mode()
                rp.publishMode(mode_val)
                if mode_val == "Listen":
                    command_val = helper.extractKeywords(spr.listener())
                    rp.publishCommand(command_val, fb)
                elif mode_val == "Basic":
                    basic_val = fb.basic()
                    rp.publishBasic(basic_val) 
                elif mode_val == "Encode":
                    fr.encode()
                elif mode_val == "Recognize":
                    rp.publishTalk(fr.recognize())
                elif mode_val == "Command":
                    command_val = helper.extractKeywords(fb.command())
                    rp.publishCommand(command_val, fb)                
            # except KeyboardInterrupt:
            #     fr.closeOpenCv()
            #     break
    except rospy.ROSInterruptException:
        fr.closeOpenCv()
        pass

