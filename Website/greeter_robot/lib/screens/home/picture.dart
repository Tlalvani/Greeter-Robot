import 'package:flutter/material.dart';
import 'package:firebase_storage/firebase_storage.dart';
import 'dart:async';
import 'package:image_picker/image_picker.dart';
import 'package:greeter_robot/services/authFB.dart';

class Picture extends StatefulWidget {
  @override
  _PicState createState() => _PicState();
}

class _PicState extends State<Picture> {
  FirebaseStorage storage = FirebaseStorage.instance;
  PickedFile fileVar;
  bool uploaded=false;

  // Select and image from the gallery or take a picture with the camera
  // Then upload to Firebase Storage

  Future chooseImage() async {
    fileVar = await ImagePicker().getImage(
      source: ImageSource.gallery,
    );
  }

  uploadImageToStorage(PickedFile pickedFile) async {
    print(AuthService().getUID());
    Reference _reference =
        storage.ref().child('Images/').child(AuthService().getUID());
    await _reference
        .putData(
      await pickedFile.readAsBytes(),
      SettableMetadata(contentType: 'image/jpeg'),
    )
        .whenComplete(() async {
      await _reference.getDownloadURL().then((value) {
        uploaded = true;
        print(uploaded);
      });
    });
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Upload Picture'),
      ),
      body: Center(
        child: Column(
          children: [
            Padding(
              padding: EdgeInsets.only(top: 20),
            ),
            ElevatedButton(
              child: Text('Choose Picture'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                chooseImage();
              },
            ),
            Padding(
              padding: EdgeInsets.only(top: 20),
            ),
            ElevatedButton(
              child: Text('Upload'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                uploadImageToStorage(fileVar);
                uploaded = true;
              },
            ),
          ],
        ),
      ),
    );
  }
}
