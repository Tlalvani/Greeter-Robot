import 'package:flutter/material.dart';
import 'package:greeter_robot/services/authFB.dart';
import 'package:greeter_robot/services/db.dart';
import 'package:flutter/services.dart';


final AuthService _auth = AuthService();


class Home extends StatelessWidget {
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
            ElevatedButton(
              child: Text('Select Mode'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                Navigator.pushNamed(context, '/mode');
              },
            ),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            ElevatedButton(
              child: Text('Basic Control'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                Navigator.pushNamed(context, '/basic');
              },
            ),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            ElevatedButton(
              child: Text('Write Command'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                Navigator.pushNamed(context, '/command');
              },
            ),
          ]),
        ),
      ),
    );
  }
}



