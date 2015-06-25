#!/usr/bin/env python
import rospy
import serial
import math
import pygame
import Libreria_Ovni as ovni

from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Int32MultiArray
from geometry_msgs.msg import Twist
from Libreria_Ovni import WHITE, size, RED, GRAY, CENTRO, screen, BLACK 
from Libreria_Ovni import giro_izquierda, giro_derecha, stop

from datetime import datetime
from copy import deepcopy

Datos = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0]
arreglo = [0,0,0,0,0,0,0,0,0]
rosdice = False


def callback(data):
    global Datos
    Datos = data.data

def roscallback(orden):
	global Ordene
	global rosdice
	Ordene = deepcopy(orden)
	'''rospy.loginfo("Received a /cmd_vel message!")
	rospy.loginfo("Linear Components: [%f, %f, %f]"%(orden.linear.x, orden.linear.y, orden.linear.z))
	rospy.loginfo("Angular Components: [%f, %f, %f]"%(orden.angular.x, orden.angular.y, orden.angular.z))'''
	rosdice = True

def ros_main():
    global Datos
    global rosdice
    global Ordene
    rospy.init_node('Main_Ovni', anonymous=False)
    rospy.Subscriber('/ovni_sensores', Float32MultiArray, callback)
    rospy.Subscriber('/cmd_vel', Twist, roscallback) #mensaje del tel
    pub_ovni = rospy.Publisher('/cmd_motores', Int32MultiArray)
    r = rospy.Rate(10) 

    flag = False
    vector_viejo = 0 
    deshabilitado = False
    evento = False
    stay = False

    pygame.init() 
    done = False   
    clock = pygame.time.Clock() 

    #while not rospy.is_shutdown():  
    while not done and not rospy.is_shutdown():
        for event in pygame.event.get(): 
       	    if event.type == pygame.QUIT: 
      	        done = True 
    	    elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RIGHT:
                    vector_micro = giro_derecha
		    evento = True
                    print vector_micro
                elif event.key == pygame.K_LEFT:
                    vector_micro = giro_izquierda
                    evento = True
		    print vector_micro
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_RIGHT or event.key == pygame.K_LEFT:
                    vector_micro = stop
                    print vector_micro 
		    evento = False ####
	    else:
		evento = False 	 

      	flag = pygame.mouse.get_pressed()
      	pos_mouse = pygame.mouse.get_pos()
      	status = ovni.longitud(pos_mouse[0],pos_mouse[1])
      	status_flecha = ovni.cruce(pos_mouse[0],pos_mouse[1])

	if flag[0] == True:
		if status == True:
			cuadrante = ovni.cuadrante(pos_mouse[0],pos_mouse[1])
			[ang_rad, angulo] = ovni.distancia(pos_mouse[0],pos_mouse[1],cuadrante) 
			[rx,ry,lon_x, lon_y] = ovni.frente(ang_rad,cuadrante)
			vel_ruedas = ovni.velocidad_ruedas(lon_y, lon_x,1,0)
			#print vel_ruedas
			ref_ruedas = ovni.referencia_ruedas(vel_ruedas) 
			vel_ruedas_byte = ovni.acondicionamiento_ruedas(vel_ruedas)
			vel_byte = ovni.redondeo(vel_ruedas_byte)
			vel_byte_logica = ovni.logica(ref_ruedas, vel_byte)
			ref_ruedas.extend(vel_byte_logica)
			vector_micro = [47]
			vector_micro.extend(ref_ruedas)
		elif status_flecha == 0:
				vector_micro = giro_izquierda
				status_cruce = 0
		elif status_flecha == 1: 
				vector_micro = giro_derecha
				status_cruce = 1
		else:
				status_cruce = 2
		rosdice = False

	#elif rosdice == True:
	elif rosdice == True and flag[0] == False:
		vel_ruedas = ovni.velocidad_ruedas(Ordene.linear.x,Ordene.angular.z,0,0)
		ref_ruedas = ovni.referencia_ruedas(vel_ruedas) 
		vel_ruedas_byte = ovni.acondicionamiento_ruedas(vel_ruedas)
		vel_byte = ovni.redondeo(vel_ruedas_byte)
		vel_byte_logica = ovni.logica(ref_ruedas, vel_byte)
		ref_ruedas.extend(vel_byte_logica)
		vector_micro = [47]
		vector_micro.extend(ref_ruedas)
		if Ordene.linear.x == 0.0 and Ordene.angular.z == 0.0:
			rosdice = False

	elif flag[0] == False and evento == False and rosdice == False:
		vector_micro = stop
		[rx,ry] = CENTRO
		status_cruce = 2
        
	if vector_micro != vector_viejo:
		msg_ovni = Int32MultiArray(None, vector_micro[0:])
		arreglo = map(hex,vector_micro)
		arreglo = str(arreglo).upper()
		print arreglo
		pub_ovni.publish(msg_ovni)
		vector_viejo = vector_micro
	screen.fill(GRAY)

	msg = ovni.Mensajes()
	msg.i1 = Datos[1]
	msg.i2 = Datos[2]
	msg.i3 = Datos[3]
	msg.i4 = Datos[4]
	msg.v1A = Datos[5]
	msg.v1B = Datos[6]
	msg.v2A = Datos[7]
	msg.v2B = Datos[8]
	msg.v3A = Datos[9]
	msg.v3B = Datos[10]
	msg.v4A = Datos[11]
	msg.v4B = Datos[12]
	msg.emergencia = Datos[13]

	msg.mensaje(msg.i1, msg.i2, msg.i3, msg.i4, msg.v1A, msg.v1B, msg.v2A, msg.v2B, msg.v3A, msg.v3B, msg.v4A, msg.v4B)	
	
        if (msg.emergencia == 1):
            emerg = True 
	    stay = True
        elif (msg.emergencia == 0 and stay == False):
            emerg = False  
	
        ovni.campo_movimiento(rx,ry,emerg, status_cruce)
        pygame.display.flip()
        pygame.display.update()
        clock.tick(60)
        r.sleep() 
    pygame.quit()
        


if __name__ == '__main__':
    try:
        ros_main()
    except rospy.ROSInterruptException: pass
