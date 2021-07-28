from imutils import paths
import face_recognition
import pickle
import cv2
import os
 
#get paths of each file in folder named Images
#Images here contains my data(folders of various persons)
imagePaths = list(paths.list_images('Images'))
knownEncodings = []
knownNames = []
# loop over the image paths
def faceRec(imagepath):
    count = 0
    for (i, imagePath) in enumerate(imagePaths):
        # extract the person name from the image path
        name = imagePath.split(os.path.sep)[-2]
        print(name)
        # load the input image and convert it from BGR (OpenCV ordering)
        # to dlib ordering (RGB)
        print('i')
        image = cv2.imread(imagePath)
        print('r')
        rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        print('b')#Use Face_recognition to locate faces
        boxes = face_recognition.face_locations(rgb,model='hog')
        print('e')# compute the facial embedding for the face
        encodings = face_recognition.face_encodings(rgb, boxes)
        # loop over the encodings
        for encoding in encodings:
            print(count)
            knownEncodings.append(encoding)
            knownNames.append(name)
        count +=1
    #save emcodings along with their names in dictionary data
    data = {"encodings": knownEncodings, "names": knownNames}
    #use pickle to save data into a file for later use
    f = open("newface_enc", "wb")
    f.write(pickle.dumps(data))
    f.close()
    print("Encoded")
