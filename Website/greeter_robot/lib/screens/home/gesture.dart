import 'package:flutter/material.dart';
import 'package:greeter_robot/services/authFB.dart';
import 'package:greeter_robot/services/db.dart';
import 'package:flutter/services.dart';

class Gesture extends StatefulWidget {
  @override
  const Gesture({Key key}) : super(key: key);

  GestureState createState() => GestureState();
}

class GestureState extends State<Gesture> {
  String gesture;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Select Gesture"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Column(children: <Widget>[
          Padding(
            padding: EdgeInsets.only(top: 20),
          ),
          new TextFormField(
            decoration: new InputDecoration(
              labelText: "Enter Gesture",
              fillColor: Colors.white,
              border: new OutlineInputBorder(
                borderRadius: new BorderRadius.circular(25.0),
                borderSide: new BorderSide(),
              ),
              //fillColor: Colors.green
            ),
            validator: (val) {
              return null;
            },
            keyboardType: TextInputType.emailAddress,
            style: new TextStyle(
              fontFamily: "Poppins",
            ),
            onChanged: (val) {
              gesture = val;
            },
          ),
          Padding(
            padding: EdgeInsets.only(top: 15),
          ),
          ElevatedButton(
            child: Text('Write'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              AuthService().setGesture(gesture);
            },
          ),
        ]),
      ),
    );
  }
}
