#!/usr/bin/env python

import serial
import time
import rospy

from std_msgs.msg import Int16

def driver():
	ser = serial.Serial('/dev/arduino_encoder', 9600) # uses udev rule
	time.sleep(4)
	# publish odometry messages for differentiaL_drive pid_velocity.py node
	l_pub = rospy.Publisher('lwheel', Int16, queue_size=1)
	r_pub = rospy.Publisher('rwheel', Int16, queue_size=1)
	# init the node
	rospy.init_node('encoder_driver', anonymous=True)
	rate = rospy.Rate(100) 
	ser.readline()
	while not rospy.is_shutdown():
		serial_data = ser.readline()
		serial_data.strip('\n')
		data = serial_data.split("v")
		left_data = data[0]
		print (data)
		#left_data.strip(' \t\n\r')
		try:
		    right_data = data[1]
		except Exception:
		    pass
                #right_data.strip()
		#rospy.loginfo("Left: %s" % left_data)
		#rospy.loginfo("Right: %s" % right_data)
		try:
                    l_pub.publish(int(left_data))
                except Exception:
		    pass
		try:
    		    r_pub.publish(int(right_data))
                except Exception:
		    pass
		print("left")
		print(left_data)
		print("right")
		print(right_data)
		#print(serial_data)
		rate.sleep()
if __name__ == "__main__":
	try: 
		driver()
	except rospy.ROSInterruptException:
		pass

