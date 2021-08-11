#!/usr/bin/env python
import os
import datetime
import requests

from firebase_admin import credentials
import firebase_admin
from google.cloud import firestore, storage


class Firebase():       
    folderpath = "/home/george/Github/GreeterRobot/Scripts/"
    path = folderpath + "key.json"
    os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = path
    cred = credentials.Certificate(path)
    app = firebase_admin.initialize_app(cred)
    db = firestore.Client()
    prev_mode =''
    old_basic_list =[]

    """
    Takes the mode from firebase and prints to terminal if it changed
    """
    
    def mode(self):
        mode_val = self.db.collection(u'Misc').document(u'Mode').get().to_dict()["Mode"]
        
        if self.prev_mode != '' and self.prev_mode != mode_val:
            print("Mode switched to "+ mode_val)
        self.prev_mode = mode_val
        
        return mode_val

    def command(self):
        command_val = self.db.collection(u'Misc').document(u'Command').get().to_dict()["Command"] # gets command from firebase
        self.db.collection(u'Misc').document(u'Command').set({u'Command':''}, merge= True) # sets command to nothing to reset
        return command_val

    def basic(self):
        basic_ref = self.db.collection(u'Basic')
        basic_list = [] 
        basic_string = ""
        for doc in basic_ref.stream(): # loops through every document in the Basic Collection
            temp_key =[]
            for key,value in doc.to_dict().items(): # loops through every key in the document
                temp_key.append(key)
            temp_key.sort() # sorts it becuase it mixes the order
            for i in range(len(temp_key)):
                basic_list.append(doc.to_dict()[temp_key[i]]) # appends the values to the list
        if len(self.old_basic_list) ==0:
            self.old_basic_list =basic_list
        else:
            for i in range(len(basic_list)):
                if basic_list[i] != self.old_basic_list[i]:
                    basic_string +=  str(i) + ',' + basic_list[i] + ',;'
        self.old_basic_list = basic_list

        return(basic_string)


    def changeMode(self, string): # helper function 
        mode_ref = self.db.collection(u'Misc').document(u'Mode')
        mode_ref.set({u'Mode':string},merge=True)

    def downloadImage(self): # downloads the current users image and then returns the fullname
        client = storage.Client()
        bucket = client.bucket("greeterrobot.appspot.com")
        # Get name from firebase
        uid = self.getUidFromMode()
        fname = self.db.collection(u'Users').document(uid).get().to_dict()['First Name']
        lname = self.db.collection(u'Users').document(uid).get().to_dict()['Last Name']
        fullname = fname+' ' + lname
        blob = bucket.blob("Images/"+uid)
        url = blob.generate_signed_url(datetime.timedelta(seconds=300), method='GET')
        self.imagepath = self.folderpath +"AllImages/"+uid+".jpg"
        with open(self.imagepath, "wb") as file_obj:
            file_obj.write(requests.get(url).content)
            file_obj.close()
        return fullname

    def deleteImage(self):
        os.remove(self.filepath)
    
    def getUidFromMode(self):
        return self.db.collection(u'Misc').document(u'Mode').get().to_dict()['uid']
