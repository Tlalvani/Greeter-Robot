import 'package:cloud_firestore/cloud_firestore.dart';

class DbService{


  final String uid;
  DbService({this.uid});
  final CollectionReference Basic = FirebaseFirestore.instance.collection('Basic');
  final CollectionReference Misc = FirebaseFirestore.instance.collection('Misc');
  Future updateRightArm(List<String> input) async{
    return await Basic.doc('rightArm').set({
      'bicepExt': input[0],
      'bicepRot': input[1],
      'shouldExt': input[2],
      'shouldRot': input[3],
    });
  }

  Future updateLeftArm(List<String> input) async{
    return await Basic.doc('leftArm').set({
      'bicepExt': input[0],
      'bicepRot': input[1],
      'shouldExt': input[2],
      'shouldRot': input[3],
    });
  }

  Future updateRightHand(List<String> input) async{
    return await Basic.doc('rightHand').set({
      'Thumb': input[0],
      'Index': input[1],
      'Middle': input[2],
      'Ring': input[3],
      'Pinky': input[4],
      'Wrist': input[5],
    });
  }

  Future updateLeftHand(List<String> input) async{
    return await Basic.doc('leftHand').set({
      'Thumb': input[0],
      'Index': input[1],
      'Middle': input[2],
      'Ring': input[3],
      'Pinky': input[4],
      'Wrist': input[5],
    });
  }

  Future updateNeck(List<String> input) async{
    return await Basic.doc('neck').set({
      //TODO when neck code gets written
    });
  }

  Future updateCommand(String input) async{
    return await Misc.doc('Command').set({
      'Command': input,
    });
  }

  Future updateMode(String input) async{
    return await Misc.doc('Mode').set({
      'Mode': input,
    });
  }

}

