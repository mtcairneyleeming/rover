#!/usr/bin/env python

import serial
import time
import rospy
from geometry_msgs.msg import Twist
serial = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)


