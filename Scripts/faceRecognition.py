#!/usr/bin/env python

import datetime
import os

from imutils import paths
import face_recognition
import pickle
import cv2

class FaceRecognition():
    #OpenCV Face Recognition
    cascPathface = os.path.dirname(cv2.__file__) + "/data/haarcascade_frontalface_alt2.xml"
        # load the harcaascade in the cascade classifier
    faceCascade = cv2.CascadeClassifier(cascPathface)
        # load the known faces and embeddings saved in encoded dictionary file
    try:
        data = pickle.loads(open('allface_enc', "rb").read())
    except FileNotFoundError:
        print("Making new encoding")
        data = {"encodings": [], "names": []}

    def __init__(self, fb):
        self.fb = fb

    def encodeImage(self):
        print("Encoding")
        name = self.fb.downloadImage()
        print(name)
        try:
            self.data = pickle.loads(open('allface_enc', "rb").read())
        except FileNotFoundError:
            print("Making new encoding")
            self.data = {"encodings": [], "names": []}
        knownEncodings = self.data["encodings"]
        knownNames = self.data["names"]
        # load the input image and convert it from BGR (OpenCV ordering) to dlib ordering (RGB)
        imagepath, _ = self.fb.getImagePath()
        image = cv2.imread(imagepath)
        rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # Use Face_recognition to locate faces
        boxes = face_recognition.face_locations(rgb,model='hog')
        # compute the facial embedding for the face
        encodings = face_recognition.face_encodings(rgb, boxes)
        # loop over the encodings
        for encoding in encodings:
            knownEncodings.append(encoding)
            knownNames.append(name)
        
        # save encodings along with their names in dictionary data
        self.data = {"encodings": knownEncodings, "names": knownNames}
        # use pickle to save data into a file for later use
        f = open("allface_enc", "wb")
        f.write(pickle.dumps(self.data))
        f.close()
        print("Encoded")
        self.fb.deleteImage()
        self.fb.changeMode("Listen")



    def recognize(self):
        print("Streaming started")
        self.data = pickle.loads(open('allface_enc', "rb").read())
        print("Names: ",self.data['names'])
        self.video_capture = cv2.VideoCapture(-1)
        process_this_frame = True
        mode_out = self.fb.mode()
        count = 0
        out =''
        while (mode_out == "Recognize"):
            try:
                # grab the frame from the threaded video stream
                ret, frame = self.video_capture.read()
                small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
                rgb_small_frame = small_frame[:, :, ::-1]
                
                if count %5 ==0:
                    print("Processing frame " + str(count))
                if process_this_frame:
                    # Find all the faces and face encodings in the current frame of video
                    face_locations = face_recognition.face_locations(rgb_small_frame)
                    face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
                    for face_encoding in face_encodings:
                        # See if the face is a match for the known face(s)
                        matches = face_recognition.compare_faces(self.data["encodings"], face_encoding)
                        name = "Unknown"

                        # # If a match was found in known_face_encodings, just use the first one.
                        if True in matches:
                            #Find positions at which we get True and store them
                            matchedIdxs = [i for (i, b) in enumerate(matches) if b]
                            for i in matchedIdxs:

                                #Check the names at respective indexes we stored in matchedIdxs
                                name = self.data["names"][i]
                                print(name)
                                out = "Hi " + name
                                self.fb.changeMode("Command")

                process_this_frame = not process_this_frame
                mode_out = self.fb.mode()
                count +=1
                
            except KeyboardInterrupt:
                self.closeOpenCv()
                print("Camera closed by Keyboard Interrupt")
                break

        self.closeOpenCv()
        print("Camera closed by switching modes")
        return out
         
    def closeOpenCv(self): #void function to close the camera so that you dont have to unplug it after stopping terminal

        self.video_capture.release()
        cv2.destroyAllWindows()