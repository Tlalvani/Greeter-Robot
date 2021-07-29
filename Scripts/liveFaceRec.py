import face_recognition
import imutils
import pickle
import time
import cv2
import numpy as np

import os
names = []
#find path of xml file containing haarcascade file 
cascPathface = os.path.dirname(
 cv2.__file__) + "/data/haarcascade_frontalface_alt2.xml"
# load the harcaascade in the cascade classifier
faceCascade = cv2.CascadeClassifier(cascPathface)
# load the known faces and embeddings saved in last file
data = pickle.loads(open('newface_enc', "rb").read())
print(data)
known_face_names = [
    "Parker Sell",
    "Tej Lalvani"
]

print("Streaming started")
video_capture = cv2.VideoCapture(-1)
process_this_frame = True

def process():
    #print("Processing")
    global process_this_frame
    if process_this_frame:
            # Find all the faces and face encodings in the current frame of video
        face_locations = face_recognition.face_locations(rgb_small_frame)
        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)

        face_names = []
        for face_encoding in face_encodings:
            # See if the face is a match for the known face(s)
            matches = face_recognition.compare_faces(data["encodings"], face_encoding)
            name = "Unknown"

            # # If a match was found in known_face_encodings, just use the first one.
            if True in matches:
        #Find positions at which we get True and store them
                matchedIdxs = [i for (i, b) in enumerate(matches) if b]
                counts = {}
        # loop over the matched indexes and maintain a count for
        # each recognized face face
                for i in matchedIdxs:
            #Check the names at respective indexes we stored in matchedIdxs
                    name = data["names"][i]
            #increase count for the name we got
                    counts[name] = counts.get(name, 0) + 1
        #set name which has highest count
                name = max(counts, key=counts.get)
                print(name)
                
 
            # update the list of names
            names.append(name)

        process_this_frame = not process_this_frame

try:
    while True:
        # grab the frame from the threaded video stream
        ret, frame = video_capture.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
        rgb_small_frame = small_frame[:, :, ::-1]
        #faces = faceCascade.detectMultiScale(gray, scaleFactor=1.1,minNeighbors=5,minSize=(60, 60),flags=cv2.CASCADE_SCALE_IMAGE)
     
        process()
except KeyboardInterrupt:
    video_capture.release()
    cv2.destroyAllWindows()
    pass


