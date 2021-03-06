# Python and Shell Scripts

## Linux Scripts
**This code runs on boot by hitting alt+f2 and clicking gnome-session-properties**
- bootcode.sh runs necessary ros commands and runs bootcode.py
  - gnome-terminal -- bash -c "/home/george/Github/GreeterRobot/Scripts/bootcode.sh; exec bash"
- swapfile.sh creates a swapfile on our usbdrive
  -  https://github.com/JetsonHacksNano/installSwapfile
  -  gnome-terminal -- bash -c "/home/george/Github/GreeterRobot/Scripts/swapfile.sh; exec bash"
## Python Scripts
There are a combo of executable python scripts which utilize python classes
### Executable Scripts
- bootcode.py: Manages publisher and subscriber by shutting them down when the power is off
- publisher.py: Manages python classes and runs them all depending on the mode from firebase
- subscriber.py: Solely runs the speaker node
### Custom Classes
- rosPublisher: publishes information to arduino using ros
- faceRecognition: using opencv to encode the persons face and then recognize using the allface_enc file
- speechRecognition: using google speech recognition
- firebase: accesses import data in firestore and file storage 
### Extra Files
- helper: contains helper code for extracting the keywords from commands 
- allface_enc: a byte file that contains the dictionary for each persons encoding, created by faceRecognition
- key.json: firebase authentication
