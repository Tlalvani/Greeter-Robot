#!/bin/bash
roscore  & python Github/GreeterRobot/Scripts/tts.py & source /opt/ros/melodic/setup.bash; rosrun rosserial_python serial_node.py /dev/ttyACM0 & python Github/GreeterRobot/Scripts/stt.py