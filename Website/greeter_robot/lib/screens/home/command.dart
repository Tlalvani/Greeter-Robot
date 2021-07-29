import 'package:flutter/material.dart';
import 'package:greeter_robot/services/authFB.dart';
import 'package:greeter_robot/services/db.dart';
import 'package:flutter/services.dart';


class Command extends StatelessWidget {
  String command = "";
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Write Command"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Column(
            children: <Widget>[
              Padding(
                padding: EdgeInsets.only(top: 20),
              ),
              new TextFormField(
                decoration: new InputDecoration(
                  labelText: "Enter Command",
                  fillColor: Colors.white,
                  border: new OutlineInputBorder(
                    borderRadius: new BorderRadius.circular(25.0),
                    borderSide: new BorderSide(
                    ),
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
                  command = val;
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
                  AuthService().setCommand(command);
                },
              ),
            ]
        ),
      ),
    );
  }
}

