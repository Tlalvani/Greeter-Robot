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
 
known_face_names = [
    "Parker Sell",
    "Tej Lalvani"
]

print("Streaming started")
video_capture = cv2.VideoCapture(-1)
process_this_frame = True
try:
    while True:
        # grab the frame from the threaded video stream
        ret, frame = video_capture.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
        rgb_small_frame = small_frame[:, :, ::-1]
        #faces = faceCascade.detectMultiScale(gray, scaleFactor=1.1,minNeighbors=5,minSize=(60, 60),flags=cv2.CASCADE_SCALE_IMAGE)
     
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

        #for (top, right, bottom, left), name in zip(face_locations, face_names):
        #    print('Test')            
# Scale back up face locations since the frame we detected in was scaled to 1/4 size
        #    top *= 4
        #    right *= 4
        #    bottom *= 4
        #    left *= 4

            # Draw a box around the face
        #    cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)

            # Draw a label with a name below the face
        #    cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
            #font = cv2.FONT_HERSHEY_DUPLEX
        #    cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)

        # Display the resulting image
        #cv2.imshow('Video', frame)
except KeyboardInterrupt:
    video_capture.release()
    cv2.destroyAllWindows()
    pass


