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

  String getUID(){
    final User userA = _auth.currentUser;
    final uidA = userA.uid;
    return uidA;
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

  Future registerAccount(String email, String password, String firstName, String lastName) async {
    try {
      UserCredential result = await _auth.createUserWithEmailAndPassword(
          email: email, password: password);
      User user = result.user;
      await DbService(uid: user.uid).updateUser(firstName, lastName);
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

  Future setRightArm(List<RefWrapper> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateArm(input, 'rightArm');
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setLeftArm(List<RefWrapper> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateArm(input, 'leftArm');
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setRightHand(List<RefWrapper> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateHand(input, 'rightHand');
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setLeftHand(List<RefWrapper> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateHand(input, 'leftHand');
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }

  Future setHead(List<RefWrapper> input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateHead(input);
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

  Future setGesture(String input) async {
    try {
      final User userA = _auth.currentUser;
      final uidA = userA.uid;

      await DbService(uid: uidA).updateGesture(input);
      return userFirebase(userA);
    } catch (error) {
      print(error.toString());
      return null;
    }
  }
}
