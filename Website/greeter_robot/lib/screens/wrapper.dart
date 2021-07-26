import 'package:flutter/material.dart';
import 'package:greeter_robot/screens/auth/Auth.dart';
import 'package:provider/provider.dart';
import 'package:greeter_robot/models/user.dart';
import 'package:greeter_robot/screens/home/home.dart';

class Wrapper extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    final user = Provider.of<AUser>(context);

    if(user == null){ //If not authenticated
      return Auth();
    }
    else{
      return Home();
    }
  }
}

    