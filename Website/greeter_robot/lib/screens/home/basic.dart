import 'package:flutter/material.dart';
import 'package:greeter_robot/services/authFB.dart';
import 'package:greeter_robot/services/db.dart';
import 'package:flutter/services.dart';



class Basic extends StatelessWidget {
  ElevatedButton button(BuildContext context, String text, String path){
    return ElevatedButton(
      child: Text(text),
      style: ElevatedButton.styleFrom(
        // background color
        primary: Colors.blue,
        padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
        textStyle: TextStyle(fontSize: 20),
      ),
      onPressed: () {
        Navigator.pushNamed(context, path);
      },
    );
  }
  @override
  Widget build(BuildContext context) {
    const double buttonDistance = 40;
    return Scaffold(
      appBar: AppBar(
        title: Text("Basic Control"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Column(children: <Widget>[
          Padding(
            padding: EdgeInsets.only(top: 20),
          ),
          button(context, 'Left Arm', '/leftarm'),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          button(context, 'Right Arm', '/rightarm'),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          button(context, 'Left Hand', '/lefthand'),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          button(context, 'Right Hand', '/righthand'),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          button(context, 'Head', '/head'),
        ]),
      ),
    );
  }
}

TextFormField inputField(String label, RefWrapper value){
  return TextFormField(
    initialValue: value.getVal(),
    keyboardType: TextInputType.number,
    inputFormatters: <TextInputFormatter>[
      FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
    ],
    decoration: InputDecoration(
      labelText: label,
      hintText: "Enter a number 0-1",
    ),
    validator: (val) {
      return validate(val);
    },
    onChanged: (val) {
      alter(value, val);
    },
  );
}

String validate(var val){
  if (val.length == 0) {
    return "Please enter a value";
  } else if ((double.tryParse(val) is! double)) {
    return "Please enter a valid number";
  } else if (double.parse(val) > 1) {
    return "Please choose a value between 0 and 1";
  } else {
    return null;
  }
}

class RightArm extends StatelessWidget {
  var _formKey = GlobalKey<FormState>();

  List<RefWrapper> moveArm = [RefWrapper('1'), RefWrapper('.5'), RefWrapper('0'), RefWrapper('0')];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Right Arm"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(
            children: <Widget>[
              inputField("Bicep Extension", moveArm[0]),
              inputField("Bicep Rotation", moveArm[1]),
              inputField("Shoulder Extension", moveArm[2]),
              inputField("Shoulder Rotation", moveArm[3]),
              Padding(
                padding: EdgeInsets.only(top: 15),
              ),
              ElevatedButton(
                child: Text('Move'),
                style: ElevatedButton.styleFrom(
                  // background color
                  primary: Colors.blue,
                  padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                  textStyle: TextStyle(fontSize: 20),
                ),
                onPressed: () {
                  if (_formKey.currentState.validate()) {
                    AuthService().setRightArm(moveArm);
                  }
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}

class LeftArm extends StatelessWidget {
  List<RefWrapper> moveArm = [RefWrapper('1'), RefWrapper('.5'), RefWrapper('0'), RefWrapper('0')];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Left Arm"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(
            children: <Widget>[
              inputField("Bicep Extension", moveArm[0]),
              inputField("Bicep Rotation", moveArm[1]),
              inputField("Shoulder Extension", moveArm[2]),
              inputField("Shoulder Rotation", moveArm[3]),
              Padding(
                padding: EdgeInsets.only(top: 15),
              ),
              ElevatedButton(
                child: Text('Move'),
                style: ElevatedButton.styleFrom(
                  // background color
                  primary: Colors.blue,
                  padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                  textStyle: TextStyle(fontSize: 20),
                ),
                onPressed: () {
                  if (_formKey.currentState.validate()) {
                    AuthService().setLeftArm(moveArm);
                  }
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}

class LeftHand extends StatelessWidget {
  List<RefWrapper> moveHand = [RefWrapper('0'), RefWrapper('0'), RefWrapper('0'), RefWrapper('0'), RefWrapper('0'), RefWrapper('0')];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Left Hand"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(children: <Widget>[
            inputField("Thumb", moveHand[0]),
            inputField("Index", moveHand[1]),
            inputField("Middle", moveHand[2]),
            inputField("Ring", moveHand[3]),
            inputField("Pinky", moveHand[4]),
            inputField("Wrist", moveHand[5]),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            ElevatedButton(
              child: Text('Move'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                if (_formKey.currentState.validate()) {
                  AuthService().setLeftHand(moveHand);
                }
              },
            ),
          ]),
        ),
      ),
    );
  }
}

class RightHand extends StatelessWidget {
  List<RefWrapper> moveHand = [RefWrapper('0'), RefWrapper('0'), RefWrapper('0'), RefWrapper('0'), RefWrapper('0'), RefWrapper('0')];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Right Hand"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(children: <Widget>[
            inputField("Thumb", moveHand[0]),
            inputField("Index", moveHand[1]),
            inputField("Middle", moveHand[2]),
            inputField("Ring", moveHand[3]),
            inputField("Pinky", moveHand[4]),
            inputField("Wrist", moveHand[5]),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            ElevatedButton(
              child: Text('Move'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                if (_formKey.currentState.validate()) {
                  AuthService().setRightHand(moveHand);
                }
              },
            ),
          ]),
        ),
      ),
    );
  }
}

class Head extends StatelessWidget {
  List<RefWrapper> moveHead = [RefWrapper('.5'), RefWrapper('.5'), RefWrapper('.5'), RefWrapper('0')];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {

    return Scaffold(
      appBar: AppBar(
        title: Text("Head"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(children: <Widget>[
            inputField("Vertical", moveHead[0]),
            inputField("Tilt", moveHead[1]),
            inputField("Rotate", moveHead[2]),
            inputField("Jaw", moveHead[3]),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            ElevatedButton(
              child: Text('Move'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                if (_formKey.currentState.validate()) {
                  AuthService().setHead(moveHead);
                }
              },
            ),
          ]),
        ),
      ),
    );

  }
}
