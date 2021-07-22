from firebase_admin import credentials
import firebase_admin
from google.cloud import firestore
import os
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "./key.json"


cred = credentials.Certificate("./key.json")
firebase_admin.initialize_app(cred)
db = firestore.Client()
# Add a new document

doc_ref = db.collection(u'Basic').document(u'leftArm')
doc_ref.set({
    u'bicepExt': u'0',
    u'bicepRot': u'0',
    u'shouldExt': u'0',
    u'shouldRot': u'0',
})

doc_ref = db.collection(u'Basic').document(u'rightArm')
doc_ref.set({
    u'bicepExt': u'0',
    u'bicepRot': u'0',
    u'shouldExt': u'0',
    u'shouldRot': u'0',
})

doc_ref = db.collection(u'Basic').document(u'leftHand')
doc_ref.set({
    u'Thumb': u'0',
    u'Index': u'0',
    u'Middle': u'0',
    u'Ring': u'0',
    u'Pinky': u'0',
})

doc_ref = db.collection(u'Basic').document(u'rightHand')
doc_ref.set({
    u'Thumb': u'0',
    u'Index': u'0',
    u'Middle': u'0',
    u'Ring': u'0',
    u'Pinky': u'0',
})
