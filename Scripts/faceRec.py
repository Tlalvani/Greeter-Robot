from imutils import paths
import face_recognition
import pickle
import cv2
import os
 
#get paths of each file in folder named Images
#Images here contains my data(folders of various persons)

# loop over the image paths

def encodeFace(imagePath, name):

    try:
        data = pickle.loads(open('allface_enc', "rb").read())
    except FileNotFoundError:
        print("Making new encoding")
        data = {"encodings": [], "names": []}
    knownEncodings = data["encodings"]
    knownNames = data["names"]
    # load the input image and convert it from BGR (OpenCV ordering)
    # to dlib ordering (RGB)
    image = cv2.imread(imagePath)
    rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    #Use Face_recognition to locate faces
    boxes = face_recognition.face_locations(rgb,model='hog')
    # compute the facial embedding for the face
    encodings = face_recognition.face_encodings(rgb, boxes)
    # loop over the encodings
    for encoding in encodings:
        knownEncodings.append(encoding)
        knownNames.append(name)
    
    #save emcodings along with their names in dictionary data
    data = {"encodings": knownEncodings, "names": knownNames}
    #use pickle to save data into a file for later use
    f = open("allface_enc", "wb")
    f.write(pickle.dumps(data))
    f.close()
    print("Encoded")