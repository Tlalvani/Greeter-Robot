import 'package:flutter/material.dart';
import 'package:greeter_robot/services/authFB.dart';
import 'package:greeter_robot/services/db.dart';
import 'package:flutter/services.dart';


class Mode extends StatefulWidget {

  @override
  const Mode({Key key}) : super(key: key);
  ModeState createState() => ModeState();
}

class ModeState extends State<Mode> {
  String _mode;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Select Mode"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Column(children: <Widget>[
          Padding(
            padding: EdgeInsets.only(top: 20),
          ),

          DropdownButton<String>(
            focusColor:Colors.white,
            value: _mode,
            //elevation: 5,
            style: TextStyle(color: Colors.white),
            iconEnabledColor:Colors.black,
            items: <String>[
              'Basic',
              'Listen',
              'Parrot',
            ].map<DropdownMenuItem<String>>((String value) {
              return DropdownMenuItem<String>(
                value: value,
                child: Text(value,style:TextStyle(color:Colors.black),),
              );
            }).toList(),
            hint:Text(
              "Please choose a mode",
              style: TextStyle(
                  color: Colors.black,
                  fontSize: 14,
                  fontWeight: FontWeight.w500),
            ),
            onChanged: (String value) {
              setState(() {
                _mode= value;
              });
            },
          ),
          Padding(
            padding: EdgeInsets.only(top: 15),
          ),
          ElevatedButton(
            //TODO Add mode read and write
            child: Text('Select'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              AuthService().setMode(_mode);
            },
          ),
        ]),
      ),
    );
  }
}
