import 'package:cloud_firestore/cloud_firestore.dart';

class RefWrapper {
  String value;

  RefWrapper(this.value);

  String getVal() {
    return value;
  }
}

void alter(RefWrapper data, String x){
  data.value = x;
}

class DbService {
  final String uid;

  DbService({this.uid});

  final CollectionReference Basic =
      FirebaseFirestore.instance.collection('Basic');
  final CollectionReference Misc =
      FirebaseFirestore.instance.collection('Misc');

  final CollectionReference Users =
  FirebaseFirestore.instance.collection('Users');

  String getUID(){
    return uid;
  }
  Future updateUser(String firstName, String lastName) async {
    return await Users.doc(uid).set({
      'First Name': firstName,
      'Last Name': lastName,
    });
  }

  Future updateArm(List<RefWrapper> input, String label) async {
    return await Basic.doc(label).set({
      'bicepExt': input[0].getVal(),
      'bicepRot': input[1].getVal(),
      'shouldExt': input[2].getVal(),
      'shouldRot': input[3].getVal(),
    });
  }


  Future updateHand(List<RefWrapper> input, String label) async {
    return await Basic.doc(label).set({
      'Thumb': input[0].getVal(),
      'Index': input[1].getVal(),
      'Middle': input[2].getVal(),
      'Ring': input[3].getVal(),
      'Pinky': input[4].getVal(),
      'Wrist': input[5].getVal(),
    });
  }


  Future updateHead(List<RefWrapper> input) async {
    return await Basic.doc('theHead').set({
      'Vertical': input[0].getVal(),
      'Tilt': input[1].getVal(),
      'Rotate': input[2].getVal(),
      'Jaw': input[3].getVal(),
    });
  }

  Future updateCommand(String input) async {
    return await Misc.doc('Command').set({
      'Command': input,
    });
  }

  Future updateMode(String input) async {
    return await Misc.doc('Mode').set({
      'Mode': input,
      'uid': uid,
    });
  }
}
