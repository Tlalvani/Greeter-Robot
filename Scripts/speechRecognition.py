#!/usr/bin/env python
import speech_recognition as sr
import helper


class SpeechRecognition():
    r = sr.Recognizer()
    m = sr.Microphone()

    def __init__(self, fb):
        self.fb = fb

    def listener(self):
        with self.m as source: self.r.adjust_for_ambient_noise(source)
        print("Set minimum energy threshold to {}".format(self.r.energy_threshold))
        mode_out = self.fb.mode()
        while mode_out == "Listen":
            try:
                print("Say something!")
                with self.m as source: audio = self.r.listen(source)
                print("Got it! Now to recognize it...")
                try:
                    # recognize speech using Google Speech Recognition
                    value = self.r.recognize_google(audio)
                    out=''
                    # we need some special handling here to correctly print unicode characters to standard output
                    if str is bytes:  # this version of Python uses bytes for strings (Python 2)
                        out = (u"{}".format(value).encode("utf-8"))
                    else:  # this version of Python uses unicode for strings (Python 3+)
                        out = ("{}".format(value))
                    
                    helper.extractKeywords(out)
                except sr.UnknownValueError:
                    print("Oops! Didn't catch that")
                except sr.RequestError as e:
                    print("Uh oh! Couldn't request results from Google Speech Recognition service; {0}".format(e))
                
                mode_out = self.fb.mode()
            except KeyboardInterrupt:
                pass
        return ''