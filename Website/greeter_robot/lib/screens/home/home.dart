import 'package:flutter/material.dart';
import 'package:greeter_robot/services/authFB.dart';
import 'package:greeter_robot/services/db.dart';
import 'package:flutter/services.dart';


final AuthService _auth = AuthService();


class Home extends StatelessWidget {

  ElevatedButton option(BuildContext context, String label, String path){
    return ElevatedButton(
      child: Text(label),
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
    return Container(
      child: Scaffold(
        backgroundColor: Colors.white,
        appBar: AppBar(
          title: Text('George'),
          backgroundColor: Colors.blue,
          elevation: 0.0,
          actions: <Widget>[
            FlatButton.icon(
              icon: Icon(Icons.person),
              label: Text('Logout'),
              onPressed: () async {
                await _auth.signOut();
              },
            ),
          ],
        ),
        body: Center(
          child: Column(children: <Widget>[
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            option(context,"Select Mode","/mode"),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            option(context,"Basic Control","/basic"),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            option(context,"Write Command","/command"),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            option(context,"Take Picture","/picture"),

          ]),
        ),
      ),
    );
  }
}




