import 'package:greeter_robot/services/db.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:greeter_robot/models/user.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

class AuthService {
  final FirebaseAuth _auth = FirebaseAuth.instance;

  AUser userFirebase(User user) {
    return user != null ? AUser(uid: user.uid) : null;
  }

  Stream<AUser> get user {
    return _auth.authStateChanges().map(userFirebase);
  }

  Future signInAnon() async {
    try {
      UserCredential result = await _auth.signInAnonymously();
      User user = result.user;
      return user;
    } catch (e) {
      print(e.toString());
      return null;
    }
  }

  Future signOut() async {
    try {
      return await _auth.signOut();
    } catch (e) {
      return null;
    }
  }

  Future registerAccount(String email, String password) async {
    try {
      UserCredential result = await _auth.createUserWithEmailAndPassword(
          email: email, password: password);
      User user = result.user;
      //await DbService(uid: user.uid).updateUser("0", "0");
      return userFirebase(user);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future signInAccount(String email, String password) async {
    try {
      UserCredential result = await _auth.signInWithEmailAndPassword(
          email: email, password: password);
      User user = result.user;
      return user;
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setRightArm(List<String> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateRightArm(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setLeftArm(List<String> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateLeftArm(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setRightHand(List<String> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateRightHand(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setLeftHand(List<String> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateLeftHand(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setNeck(List<String> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateNeck(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setCommand(String input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateCommand(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future getCommand() async {
    FirebaseFirestore.instance
        .collection('Misc')
        .get()
        .then((QuerySnapshot querySnapshot) {
      querySnapshot.docs.forEach((doc) {
        print(doc["Command"]);
      });
    });
  }

  Future setMode(String input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateMode(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }
}
