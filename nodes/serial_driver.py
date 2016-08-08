#!/usr/bin/env python

import serial
import time
import rospy
from std_msgs.msg import Float32

def driver():
	global ser
	ser = serial.Serial('/dev/arduino_motor', 9600) # uses udev rule
	# wait for the serial connection to initialise
	time.sleep(2)
	print("waited")
	# init the node
	rospy.init_node('serial_driver', anonymous=True)
	print("node initialised")
	# subscribe to rmotor_cmd and lmotor_cmd to transmit to motor
	rospy.Subscriber("lmotor_cmd", Float32, lmotor_callback)
	rospy.Subscriber("rmotor_cmd", Float32, rmotor_callback)
	print("subscribed successfully")

	#keep node running
	rospy.spin()

def lmotor_callback(data):
	ser.write(str(int(data.data))+"l")
	rospy.loginfo("lmotor_callback run")
def rmotor_callback(data):
	ser.write(str(int(data.data))+"r")
	print("rmotor_callback run")

if __name__ == "__main__":
		driver()
