#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2014, Grupo de Mecatronica USB.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Revision $Id$

## Demoqe128 Accelerometer and Potentiometer aquisition

import rospy
import sys, getopt
import serial
import struct
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Int32MultiArray
from std_msgs.msg import UInt16

Datos = bytearray(9)
flag = 0

def callback(data):
    global Datos
    global flag
    Datos[0] = data.data[0]
    Datos[1] = data.data[1]
    Datos[2] = data.data[2]
    Datos[3] = data.data[3]
    Datos[4] = data.data[4]
    Datos[5] = data.data[5]
    Datos[6] = data.data[6]
    Datos[7] = data.data[7]
    Datos[8] = data.data[8]
    flag = 1

def usage():
  print "                                           "
  print "Usage:"
  print "rosrun demoqe128 serial_pot_accel.py -p <SerialPort>"
  print "                                           "

def ros_serial_demoqe128():
    global Datos
    global flag
    Port = '/dev/ttyUSB0'
    try:
        opts, args = getopt.getopt(sys.argv[1:], "p:")
    except getopt.GetoptError as err:
        # print help information and exit:
        print(str(err))
        usage()
        sys.exit(2)

    for o, a in opts:
        if o == "-p":
            Port = a
        else:
            assert False, "Unhandled option"

    try:
        #ser = serial.Serial(Port, 38400)
	ser = serial.Serial(Port, 9600, timeout=0)
    except serial.SerialException:
        print("No connection to the device could be established")
        usage()
        sys.exit(2)

    pub_ovni = rospy.Publisher('/ovni_sensores', Float32MultiArray)
    rospy.Subscriber('/cmd_motores', Int32MultiArray, callback) #comando con vel motores
    rospy.init_node('serial', anonymous=False)
    #rospy.init_node('serial_pot', anonymous=False)
    r = rospy.Rate(10) # 10hz
    
    while not rospy.is_shutdown():
        if flag:
            ser.write(Datos)
            flag = 0
	
	#while ser.inWaiting() > 26:
	while ser.inWaiting() > 27:
	    enc = ser.read(1)
	    if ord(enc) == 255:
		datain = ser.read(25)
		eol = ser.read(1)
		if ord(eol) == 10:
		    power = enc + datain + eol
		    serial_in = struct.unpack('>BHHHHHHHHHHHHb',power[0:-1])
            	    msg_ovni = Float32MultiArray(None, serial_in[0:])
	    	    #if (serial_in[0] + 2**8 == 255):
		    if (serial_in[0]== 255):
            		pub_ovni.publish(msg_ovni)
		else:
		    datain = ser.read(1)
		    print 'Crap!'
        r.sleep()
        
if __name__ == '__main__':
    try:
        ros_serial_demoqe128()
    except rospy.ROSInterruptException: pass
