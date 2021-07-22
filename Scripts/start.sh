#!/bin/bash
roscore & source /opt/ros/melodic/setup.bash; rosrun rosserial_python serial_node.py /dev/ttyACM0 &gnome-terminal -- ./Github/GreeterRobot/Scripts/pystart.sh



