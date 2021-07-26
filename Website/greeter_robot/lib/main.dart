import 'package:greeter_robot/services/authFB.dart';
import 'package:flutter/material.dart';
import 'package:greeter_robot/screens/wrapper.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:provider/provider.dart';
import'package:greeter_robot/models/user.dart';
import 'package:greeter_robot/screens/home/home.dart';
import 'package:greeter_robot/screens/home/basic.dart';
import 'package:greeter_robot/screens/home/command.dart';
import 'package:greeter_robot/screens/home/mode.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return StreamProvider<AUser>.value(
      value: AuthService().user,
      child:MaterialApp(

        routes: {
          '/': (context) => Wrapper(),
          '/basic': (context) => Basic(),
          '/command': (context) => Command(),
          '/mode': (context) => Mode(),
          '/rightarm': (context) =>RightArm(),
          '/leftarm': (context) => LeftArm(),
          '/lefthand': (context) => LeftHand(),
          '/righthand': (context) => RightHand(),
          '/neck': (context) => Neck(),


        },
      ),
    );
  }
}

