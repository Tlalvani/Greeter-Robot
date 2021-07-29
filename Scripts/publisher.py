#!/usr/bin/env python
import requests
import rospy
from std_msgs.msg import String
import speech_recognition as sr
import time

from firebase_admin import credentials
import firebase_admin
from google.cloud import firestore, storage
import datetime
import os
import faceRec
import face_recognition
import pickle
import cv2

#Listen 
r = sr.Recognizer()
m = sr.Microphone()

#Firebase
folderpath = "/home/george/Github/GreeterRobot/Scripts/"
path = folderpath + "key.json"
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = path
cred = credentials.Certificate(path)
app = firebase_admin.initialize_app(cred)
db = firestore.Client()


#Ros
pubBasic = rospy.Publisher('sendBasicCom', String, queue_size=10)
pubMode = rospy.Publisher('sendMode',String, queue_size=10)
pubTalk = rospy.Publisher('/speaker', String, queue_size=10)
pubCommand = rospy.Publisher('/sendCom', String, queue_size=10)
rospy.init_node('Subscriber', anonymous=True)
rate = rospy.Rate(1) # 1hz

#OpenCV Face Recognition
cascPathface = os.path.dirname(cv2.__file__) + "/data/haarcascade_frontalface_alt2.xml"
    # load the harcaascade in the cascade classifier
faceCascade = cv2.CascadeClassifier(cascPathface)
    # load the known faces and embeddings saved in encoded dictionary file
data = pickle.loads(open('allface_enc', "rb").read())
 



def listener():
    with m as source: r.adjust_for_ambient_noise(source)
    print("Set minimum energy threshold to {}".format(r.energy_threshold))
    mode_out = mode()
    while mode_out == "Listen":
        try:
            print("Say something!")
            pubCommand.publish('')
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
                
                publishCommands(out)
            except sr.UnknownValueError:
                print("Oops! Didn't catch that")
            except sr.RequestError as e:
                print("Uh oh! Couldn't request results from Google Speech Recognition service; {0}".format(e))
            rate.sleep()
            mode_out = mode()
        except KeyboardInterrupt:
            pass
        

# helper function to extract keywords and publish keyword             
def publishCommands(string):

    string = string.replace("Hi-5", 'high five')
    string = string.replace("-", ' ')
    print(string)
    diction = ['hello',"handshake", 'high five' , 'bye','hold','throw']

    for i in range(len(diction)):
        if diction[i] in string:
            pubCommand.publish(diction[i])
            time.sleep(1.1)
            break

def changeMode(string):
    mode_ref = db.collection(u'Misc').document(u'Mode')
    mode_ref.set({u'Mode':string},merge=True)

# to retrieve from Firebase
def getCommand():
    command_val = db.collection(u'Misc').document(u'Command').get().to_dict()["Command"]
    publishCommands(command_val)


def basic():
    basic_ref = db.collection(u'Basic')
    basic_list = [] 
    for doc in basic_ref.stream():
        temp_key =[]
        temp_val = []
        for key,value in doc.to_dict().items():
            temp_key.append(key)
        temp_key.sort() 
        print(temp_key)
        for i in range(len(temp_key)):
            basic_list.append(doc.to_dict()[temp_key[i]])
    pubBasic.publish(",".join(basic_list))

def mode():
    mode_val = db.collection(u'Misc').document(u'Mode').get().to_dict()["Mode"]
    pubMode.publish(mode_val)
    return mode_val

def encodeImage():
    client = storage.Client()
    bucket = client.bucket("greeterrobot.appspot.com")
    # Get name from firebase
    uid = db.collection(u'Misc').document(u'Mode').get().to_dict()['uid']
    fname = db.collection(u'Users').document(uid).get().to_dict()['First Name']
    lname = db.collection(u'Users').document(uid).get().to_dict()['Last Name']
    fullname = fname+' ' + lname
    blob = bucket.blob("Images/"+uid)
    url = blob.generate_signed_url(datetime.timedelta(seconds=300), method='GET')
    imagepath = folderpath +"AllImages/"+uid+".jpg"
    with open(imagepath, "wb") as file_obj:
        file_obj.write(requests.get(url).content)
        file_obj.close()
    print(imagepath, fullname)
    faceRec.encodeFace(imagepath, fullname)
    os.remove(imagepath)
    changeMode("Listen")


def recognize():
    print("Streaming started")
    video_capture = cv2.VideoCapture(-1)
    process_this_frame = True
    mode_out = mode()
    stop = False
    count = 0
    while (mode_out == "Recognize") and not stop:
        try:
            # grab the frame from the threaded video stream
            ret, frame = video_capture.read()
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
            rgb_small_frame = small_frame[:, :, ::-1]
            #faces = faceCascade.detectMultiScale(gray, scaleFactor=1.1,minNeighbors=5,minSize=(60, 60),flags=cv2.CASCADE_SCALE_IMAGE)
            if count %20 ==0:
                print("Processing frame " + str(count))
            if process_this_frame:
                # Find all the faces and face encodings in the current frame of video
                face_locations = face_recognition.face_locations(rgb_small_frame)
                face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
                for face_encoding in face_encodings:
                    # See if the face is a match for the known face(s)
                    matches = face_recognition.compare_faces(data["encodings"], face_encoding)
                    name = "Unknown"

                    # # If a match was found in known_face_encodings, just use the first one.
                    if True in matches:
                        #Find positions at which we get True and store them
                        matchedIdxs = [i for (i, b) in enumerate(matches) if b]
                        for i in matchedIdxs:

                            #Check the names at respective indexes we stored in matchedIdxs
                            name = data["names"][i]
                            print(name)
                            uid = db.collection(u'Misc').document(u'Mode').get().to_dict()['uid']
                            gesture = db.collection(u'Users').document(uid).get().to_dict()['Gesture']
                            if gesture != '':
                                print("No Gesture")
                                pubCommand.publish(publishCommands(gesture))
                            pubTalk.publish("Hi " + name)
                            changeMode("Listen")
                            
                            stop = True


        

            process_this_frame = not process_this_frame
            mode_out = mode()
            count +=1
            
        except KeyboardInterrupt:
            video_capture.release()
            cv2.destroyAllWindows()
            print("Camera closed by Keyboard Interrupt")
            break

    video_capture.release()
    cv2.destroyAllWindows()
    print("Camera closed by switching modes")
    
    
         

if __name__ == '__main__':
    try:
        print('Publisher started')
        count = 0
        while not rospy.is_shutdown():
            try:
                mode_out = mode()
                if count %20 == 0:
                    print(mode_out)
                if mode_out == "Listen":
                    listener()
                elif mode_out == "Basic":
                    basic()
                elif mode_out == "Encode":
                    encodeImage()
                elif mode_out == "Recognize":
                    recognize()
                elif mode_out == "Command":
                    getCommand()
                count +=1
            except KeyboardInterrupt:
                print("Caught one")
                mode_out = mode()
                if mode_out == "Recognize":
                    print(mode_out)
                    video_capture.release()
                    cv2.destroyAllWindows()
                break
    except rospy.ROSInterruptException:
        print("Caught two")
        mode_out = mode()
        if mode_out == "Recognize":
            print(mode_out)
            video_capture.release()
            cv2.destroyAllWindows()
        pass
