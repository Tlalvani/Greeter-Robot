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


  Future updateNeck(List<RefWrapper> input) async {
    return await Basic.doc('neck').set({
      //TODO when neck code gets written
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
    });
  }
}
