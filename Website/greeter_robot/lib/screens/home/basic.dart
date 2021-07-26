import 'package:flutter/material.dart';
import 'package:greeter_robot/services/authFB.dart';
import 'package:greeter_robot/services/db.dart';
import 'package:flutter/services.dart';

double buttonDistance = 40;

class Basic extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Basic Control"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Column(children: <Widget>[
          Padding(
            padding: EdgeInsets.only(top: 20),
          ),
          ElevatedButton(
            child: Text('Left Arm'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/leftarm');
            },
          ),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          ElevatedButton(
            child: Text('Right Arm'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/rightarm');
            },
          ),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          ElevatedButton(
            child: Text('Left Hand'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/lefthand');
            },
          ),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          ElevatedButton(
            child: Text('Right Hand'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/righthand');
            },
          ),
          Padding(
            padding: EdgeInsets.only(top: buttonDistance),
          ),
          ElevatedButton(
            child: Text('Neck'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/neck');
            },
          ),
        ]),
      ),
    );
  }
}

String validate(var val){
  if (val.length == 0) {
    return "Please enter a value";
  } else if ((double.tryParse(val) is! double)) {
    return "Please enter a valid number";
  } else if (double.parse(val) > 1) {
    return "Please choose a value between 0 and 1";
  } else {
    return null;
  }
}
class RightArm extends StatelessWidget {
  var _formKey = GlobalKey<FormState>();

  List<String> moveArm = ['0', '0', '0', '0'];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Right Arm"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(
            children: <Widget>[
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Bicep Extension",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[0] = val;
                },
              ),
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Bicep Rotation",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[1] = val;
                },
              ),
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Shoulder Extension",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[2]= val;
                },
              ),
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Shoulder Rotation",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[3] = val;
                },
              ),
              Padding(
                padding: EdgeInsets.only(top: 15),
              ),
              ElevatedButton(
                child: Text('Move'),
                style: ElevatedButton.styleFrom(
                  // background color
                  primary: Colors.blue,
                  padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                  textStyle: TextStyle(fontSize: 20),
                ),
                onPressed: () {
                  if (_formKey.currentState.validate()) {
                    print('$moveArm[0]');
                    AuthService().setRightArm(moveArm);
                  }
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}

class LeftArm extends StatelessWidget {
  List<String> moveArm = ['0', '0', '0', '0'];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Left Arm"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(
            children: <Widget>[
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Bicep Extension",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[0] = val;
                },
              ),
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Bicep Rotation",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[1] = val;
                },
              ),
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Shoulder Extension",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[2] = val;
                },
              ),
              TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Shoulder Rotation",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveArm[3] = val;
                },
              ),
              Padding(
                padding: EdgeInsets.only(top: 15),
              ),
              ElevatedButton(
                child: Text('Move'),
                style: ElevatedButton.styleFrom(
                  // background color
                  primary: Colors.blue,
                  padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                  textStyle: TextStyle(fontSize: 20),
                ),
                onPressed: () {
                  if (_formKey.currentState.validate()) {
                    AuthService().setLeftArm(moveArm);
                  }
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}

class LeftHand extends StatelessWidget {
  List<String> moveHand = ['0', '0', '0', '0', '0', '0'];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Left Hand"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(children: <Widget>[
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Thumb",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[0] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Index",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[1] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Middle",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[2] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Ring",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[3] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Pinky",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[4] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Wrist",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[5] = val;
                }),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            ElevatedButton(
              child: Text('Move'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                if (_formKey.currentState.validate()) {
                  AuthService().setLeftHand(moveHand);
                }
              },
            ),
          ]),
        ),
      ),
    );
  }
}

class RightHand extends StatelessWidget {
  List<String> moveHand = ['0', '0', '0', '0', '0', '0'];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Right Hand"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Form(
          key: _formKey,
          child: Column(children: <Widget>[
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Thumb",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[0] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Index",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[1] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Middle",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[2] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Ring",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[3] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Pinky",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[4] = val;
                }),
            TextFormField(
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
                ],
                decoration: InputDecoration(
                  labelText: "Wrist",
                  hintText: "Enter a number 0-1",
                ),
                validator: (val) {
                  return validate(val);
                },
                onChanged: (val) {
                  moveHand[5] = val;
                }),
            Padding(
              padding: EdgeInsets.only(top: 15),
            ),
            ElevatedButton(
              child: Text('Move'),
              style: ElevatedButton.styleFrom(
                // background color
                primary: Colors.blue,
                padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
                textStyle: TextStyle(fontSize: 20),
              ),
              onPressed: () {
                if (_formKey.currentState.validate()) {
                  AuthService().setRightHand(moveHand);
                }
              },
            ),
          ]),
        ),
      ),
    );
  }
}

class Neck extends StatelessWidget {
  List<String> moveHand = ['0', '0', '0', '0', '0', '0'];
  var _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Right Hand"),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Column(children: <Widget>[
          Text("TODO"),
          Padding(
            padding: EdgeInsets.only(top: 15),
          ),
          ElevatedButton(
            child: Text('Move'),
            style: ElevatedButton.styleFrom(
              // background color
              primary: Colors.blue,
              padding: EdgeInsets.symmetric(horizontal: 30, vertical: 15),
              textStyle: TextStyle(fontSize: 20),
            ),
            onPressed: () {
              AuthService().setNeck(moveHand);
            },
          ),
        ]),
      ),
    );
  }
}
