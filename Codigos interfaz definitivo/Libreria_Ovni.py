#!/usr/bin/env python
import math
import pygame

############################################################################
'''DEFINICION DE CONSTANTES'''
BLACK    = (   0,   0,   0)
WHITE    = ( 255, 255, 255)
GREEN    = (16, 96, 34)
GREEN1   = (128, 193, 143)
GREEN2   = (80, 161, 98)
GREEN3   = (43, 128, 62)
RED      = (85, 07, 00)
RED1     = (212, 116, 106)
RED2     = (170, 67, 57)
GRAY     = (47, 47, 47)
GRAY1     = (90, 90, 90)

LATERAL = 60
SUPERIOR1 = 65
ANCHO1 = 268
ALTO1 = 215
SUPERIOR2 = 315
ANCHO2 = 330
ALTO2 = 365

ANCHO = 1220
ALTO = 750
CENTRO = (((ANCHO - LATERAL - ANCHO2)/2) + ANCHO2 + LATERAL, ALTO/2 + 40)
RADIO = 220

LADO_ARROW = 80

Rrueda = 0.025
Rrobot = 0.145
PI = math.pi
perimetro_rueda = 0.157
constante_encoder = 1000/31 #Relacion entre un segundo y el tiempo que dura el conteo de pulsos por canal del encoder

Offset1 = 2064
Offset2 = 2054
Offset3 = 2065
Offset4 = 2055

giro_izquierda = [47,False, False, False, False, 0, 0, 0, 0]
giro_derecha = [47,True, True, True, True, 255, 255, 255, 255]
stop = [47,False, False, False, False, 255, 255, 255, 255]
############################################################################

############################################################################
V = [-math.sin(PI/4), math.cos(PI/4), Rrobot*math.cos(PI/4),
     -math.sin(3*PI/4), math.cos(3*PI/4), Rrobot*math.cos(3*PI/4),
     -math.sin(5*PI/4), math.cos(5*PI/4), Rrobot*math.cos(5*PI/4),
     -math.sin(7*PI/4), math.cos(7*PI/4), Rrobot*math.cos(7*PI/4)]

J2 = [Rrueda, 0, 0, 0,
      0, Rrueda, 0, 0,
      0, 0, Rrueda, 0,
      0, 0, 0, Rrueda]

size = (ANCHO, ALTO)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Mi Joystick")
############################################################################

############################################################################
'''Calcula la distancia del puntero respecto al centro del circulo'''
def longitud(pos_x, pos_y):
  x = (pos_x - CENTRO[0])*1.0
  y = (pos_y - CENTRO[1])*1.0
  dist = math.pow(x,2) + math.pow(y,2)
  dist = math.sqrt(dist)
  if dist > RADIO:
    flag = False
  elif dist <= RADIO:
    flag = True
  return flag
############################################################################

############################################################################
'''Identifica en que cuadrante se encuentra la flecha'''
def cuadrante(pos_x, pos_y):
  cuadrante = 0
  if pos_x <= CENTRO[0] and pos_y <= (CENTRO[1]-1):
    cuadrante = 1
  elif pos_x < (CENTRO[0]) and pos_y >= CENTRO[1]:
    cuadrante = 2
  elif pos_x >= CENTRO[0] and pos_y >= (CENTRO[1]+1):
    cuadrante = 3
  elif pos_x >= (CENTRO[0]+1) and pos_y <= CENTRO[1]:
    cuadrante = 4
  elif pos_x == CENTRO[0] and pos_y == CENTRO[1]:  #Esto salva el caso cuando el mouse presiona sobre el centro
    cuadrante = 4
  return cuadrante
############################################################################

############################################################################
'''Devuelve a que distancia del centro se encuentra la flecha 
y el angulo en que se encuentra pero sin considerar el cuadrante 
si es en radianes'''
def distancia(pos_x,pos_y,quad):
  x = (pos_x - CENTRO[0])*1.0
  y = (pos_y - CENTRO[1])*1.0
  if y == 0.0:
    if x <= 0.0:
      thita_rad = math.pi/2
      angulo = 90
    else:
      thita_rad = 1.5*math.pi
      angulo = 270
  else:
    thita_rad = math.atan(x/y)
    thita_rad = math.fabs(thita_rad)
    if quad == 1: #Primer Cuadrante
      thita_rad = thita_rad
    elif quad == 2:   #Segundo Cuadrante
      thita_rad = math.pi - thita_rad
    elif quad == 3:   #Tercer Cuadrante
      thita_rad = math.pi + thita_rad
    else:  #Cuarto Cuadrante
      thita_rad = (2 * math.pi) - thita_rad
    angulo = math.degrees(thita_rad)
  return (thita_rad, angulo)
############################################################################

############################################################################
'''Te devuelve la ubicacion de la distancia maxima permitida 
dependiendo del cuadrante en que se encuentra'''
def frente(angulo,quad):
  coord_x = math.sin(angulo)
  coord_y = math.cos(angulo)
  modulo_x = abs(int(round(RADIO * coord_x)))
  modulo_y = abs(int(round(RADIO * coord_y)))
  if quad == 1:
    rx = CENTRO[0] - modulo_x
    ry = CENTRO[1] - modulo_y
  elif quad == 2:
    rx = CENTRO[0] - modulo_x
    ry = CENTRO[1] + modulo_y  
  elif quad == 3:
    rx = CENTRO[0] + modulo_x
    ry = CENTRO[1] + modulo_y
  elif quad == 4:
    rx = CENTRO[0] + modulo_x
    ry = CENTRO[1] - modulo_y
  return(rx,ry,coord_x,coord_y)
############################################################################

############################################################################
'''Devuelve la velocidad lineal de cada motor'''
def velocidad_ruedas(vx,vy,rw,theta):
  v_ruedas = [0, 0, 0, 0]
  seno = math.sin(theta)
  coseno = math.cos(theta)
  matriz = [(vx*coseno + vy*seno), (-vx*seno+vy*coseno), rw]
  constante_encoder
  v_ruedas[0] = Rrueda*math.fsum([V[0]*matriz[0], V[1]*matriz[1], V[2]*matriz[2]])
  v_ruedas[1] = Rrueda*math.fsum([V[3]*matriz[0], V[4]*matriz[1], V[5]*matriz[2]])
  v_ruedas[2] = Rrueda*math.fsum([V[6]*matriz[0], V[7]*matriz[1], V[8]*matriz[2]])
  v_ruedas[3] = Rrueda*math.fsum([V[9]*matriz[0], V[10]*matriz[1], V[11]*matriz[2]])
  return v_ruedas
############################################################################

############################################################################
'''Determina el sentido de rotacion de los motores. Una salida en False indica 
que rota en sentido positivo'''
def referencia_ruedas(v_matriz):
  v_ref = [0, 0, 0, 0]
  for x in range (0, 4):
    if v_matriz[x] >= 0:
      v_ref[x] = False 
    else:
      v_ref[x] = True
  return v_ref
############################################################################

############################################################################
'''Traduce la magnitud de la velocidad a byte'''
def acondicionamiento_ruedas(v_matriz):
  v_byte = [(v * 255)/0.028 for v in v_matriz]
  return v_byte
############################################################################

############################################################################
'''Redondea la velocidad en byte'''
def redondeo (v_matriz):
  v_1 = [0, 0, 0, 0]
  for x in range(0,4):
    v_1[x] = int(round(math.fabs(v_matriz[x])))
  return v_1
############################################################################

############################################################################
def logica(v_ref, v_duty):
  v_2 = [0, 0, 0, 0]
  for x in range(0,4):
    if v_ref[x] == False:
      v_2[x] = 255 - v_duty[x]
    else:
      v_2[x] = v_duty[x]
  return v_2
############################################################################

############################################################################
'''Metodo: Determina  si el mouse esta sobre las figuras de las flechas para cruzar'''    
def cruce(posx, posy):
  if (posy >= CENTRO[1] - LADO_ARROW/2) and (posy <= CENTRO[1] + LADO_ARROW/2):
    if (posx >= (CENTRO[0]-RADIO-150)) and (posx <= CENTRO[0]-RADIO-(150-LADO_ARROW)):
      giro = 0
    elif (posx >= CENTRO[0]+RADIO+(150-LADO_ARROW)) and (posx <= CENTRO[0]+RADIO+150):
      giro = 1
    else:
      giro = 2
  else:
    giro = 2
  return (giro)
############################################################################

############################################################################
class Mensajes():
  """docstring for Corriente"""
  def __init__(self):
    self.i1 = 0
    self.i2 = 0
    self.i3 = 0
    self.i4 = 0
    self.v1 = 0
    self.v2 = 0
    self.v3 = 0
    self.v4 = 0
    self.emergencia = 0

  def mensaje(self,v1,v2,v3,v4,v1A,v1B,v2A,v2B,v3A,v3B,v4A,v4B):
    A = 80
    B = 120
    C = 330

    if v1>= Offset1: 
    	vx1 = round((((v1*2.5)/Offset1)-2.5)/0.000185,2)
    elif v1 < Offset1:
	vx1 = 0
	
    if v2>= Offset2: 
    	vx2 = round((((v2*2.5)/Offset2)-2.5)/0.000185,2)
    elif v2 < Offset2:
	vx2 = 0

    if v3>= Offset3: 
    	vx3 = round((((v3*2.5)/Offset3)-2.5)/0.000185,2)
    elif v3 < Offset3:
	vx3 = 0

    if v4>= Offset4: 
    	vx4 = round((((v4*2.5)/Offset4)-2.5)/0.000185,2)
    elif v4 < Offset4:
	vx4 = 0
    
    v1A = round(v1A*constante_encoder*perimetro_rueda/360,4)
    v1B = round(v1B*constante_encoder*perimetro_rueda/360,4)
    v2A = round(v2A*constante_encoder*perimetro_rueda/360,4)
    v2B = round(v2B*constante_encoder*perimetro_rueda/360,4)
    v3A = round(v3A*constante_encoder*perimetro_rueda/360,4)
    v3B = round(v3B*constante_encoder*perimetro_rueda/360,4)
    v4A = round(v4A*constante_encoder*perimetro_rueda/360,4)
    v4B = round(v4B*constante_encoder*perimetro_rueda/360,4)

    color = WHITE
    font_titulo = pygame.font.SysFont(None, 70)
    font = pygame.font.SysFont(None, 25)
    text1 = font.render("Corriente1 (mA): "+str(vx1), True, color)
    text2 = font.render("Corriente2 (mA): "+str(vx2), True, color)
    text3 = font.render("Corriente3 (mA): "+str(vx3), True, color)
    text4 = font.render("Corriente4 (mA): "+str(vx4), True, color)
    text5 = font.render("Velocidad1_canalA (m/s): "+str(v1A), True, color)
    text6 = font.render("Velocidad1_canalB (m/s): "+str(v1B), True, color)
    text7 = font.render("Velocidad2_canalA (m/s): "+str(v2A), True, color)
    text8 = font.render("Velocidad2_canalB (m/s): "+str(v2B), True, color)
    text9 = font.render("Velocidad3_canalA (m/s): "+str(v3A), True, color)
    text10 = font.render("Velocidad3_canalB (m/s): "+str(v3B), True, color)
    text11 = font.render("Velocidad4_canalA (m/s): "+str(v4A), True, color)
    text12 = font.render("Velocidad4_canalB (m/s): "+str(v4B), True, color)
    text13 = font_titulo.render("Control OVNI BOT 2.7", True, RED2)
    text14 = font.render("CORRIENTE EN MOTORES", True, RED1)
    text15 = font.render("ENCODERS", True, RED1)
    text16 = font.render("Realizado por: Carolina Chang", True, WHITE)
    text17 = font.render("FUTBOT USB 2015", True, WHITE)
    text18 = font.render("Status", True, RED1)

    
    screen.blit(text1,(A,B))
    screen.blit(text2,(A,B + 40))
    screen.blit(text3,(A,B + 80))
    screen.blit(text4,(A,B + 120))
    screen.blit(text5,(A,C + 40))
    screen.blit(text6,(A,C + 80))
    screen.blit(text7,(A,C + 120))
    screen.blit(text8,(A,C + 160))
    screen.blit(text9,(A,C + 200))
    screen.blit(text10,(A,C + 240))
    screen.blit(text11,(A,C + 280))
    screen.blit(text12,(A,C + 320))
    screen.blit(text13, (575, 50))
    screen.blit(text14,(A,B - 40))
    screen.blit(text15,(A,C))
    screen.blit(text16,(950, 660))
    screen.blit(text17,(950, 690))
    screen.blit(text18,(1130, 250))
############################################################################

############################################################################
'''Dibuda todo el joystick'''
#def campo_movimiento(rx,ry,emergencia, desh, giro):
def campo_movimiento(rx,ry,emergencia, giro):
  pygame.draw.circle(screen, GREEN1, CENTRO, RADIO+2,0) #Campo
  pygame.draw.circle(screen, GRAY1, CENTRO, RADIO-1, 0)
  pygame.draw.line(screen, GREEN2,[CENTRO[0]-RADIO, CENTRO[1]],[CENTRO[0]+RADIO, CENTRO[1]],5) #raya
  pygame.draw.line(screen, GREEN2,[CENTRO[0],CENTRO[1]-RADIO],[CENTRO[0],CENTRO[1]+RADIO],5) #raya
  pygame.draw.rect(screen, GREEN1, [LATERAL, SUPERIOR1, ANCHO1, ALTO1], 3)
  pygame.draw.rect(screen, GREEN1, [LATERAL, SUPERIOR2, ANCHO2, ALTO2], 3)
  pygame.draw.polygon(screen, GREEN3, [[CENTRO[0],CENTRO[1]-RADIO-30], [CENTRO[0]-10, CENTRO[1]-RADIO], [CENTRO[0]+10, CENTRO[1]-RADIO]], 0)
  pygame.draw.polygon(screen, GREEN2, [[CENTRO[0],CENTRO[1]+RADIO+30], [CENTRO[0]-10, CENTRO[1]+RADIO], [CENTRO[0]+10, CENTRO[1]+RADIO]], 0)
  pygame.draw.polygon(screen, GREEN2, [[CENTRO[0]-RADIO-30,CENTRO[1]], [CENTRO[0]-RADIO, CENTRO[1]-10], [CENTRO[0]-RADIO, CENTRO[1]+10]], 0)
  pygame.draw.polygon(screen, GREEN2, [[CENTRO[0]+RADIO+30,CENTRO[1]], [CENTRO[0]+RADIO, CENTRO[1]-10], [CENTRO[0]+RADIO, CENTRO[1]+10]], 0)
  pygame.draw.circle(screen, WHITE, [rx,ry], 60, 0)   #Palanca

  pygame.draw.rect(screen, GREEN1, [CENTRO[0]-RADIO-153, CENTRO[1]-(LADO_ARROW/2)-3, LADO_ARROW+7, LADO_ARROW+6], 0)
  pygame.draw.rect(screen, GREEN1, [CENTRO[0]+RADIO+(147- LADO_ARROW) , CENTRO[1]-(LADO_ARROW/2)-3, LADO_ARROW+6, LADO_ARROW+6], 0)
  pygame.draw.rect(screen, GRAY, [CENTRO[0]-RADIO-150, CENTRO[1]-(LADO_ARROW/2), LADO_ARROW, LADO_ARROW], 0)
  pygame.draw.rect(screen, GRAY, [CENTRO[0]+RADIO+(150- LADO_ARROW) , CENTRO[1]-(LADO_ARROW/2), LADO_ARROW, LADO_ARROW], 0)

  '''Flechas para girar'''
  if giro == 0:
    color1 = RED2
    color2 = GRAY1
  elif giro == 1:
    color1 = GRAY1
    color2 = RED2
  else:
    color1 = GRAY1
    color2 = GRAY1
  pygame.draw.polygon(screen, color1, [[CENTRO[0]-RADIO-150 ,CENTRO[1]], [CENTRO[0]-RADIO-(150-LADO_ARROW), CENTRO[1]-LADO_ARROW/2], [CENTRO[0]-RADIO-(150-LADO_ARROW), CENTRO[1]+LADO_ARROW/2]], 0)
  pygame.draw.polygon(screen, color2, [[CENTRO[0]+RADIO+(150-LADO_ARROW) ,CENTRO[1]-LADO_ARROW/2], [CENTRO[0]+RADIO+(150-LADO_ARROW), CENTRO[1]+LADO_ARROW/2], [CENTRO[0]+RADIO+150, CENTRO[1]]], 0)

  pygame.draw.circle(screen, GREEN1, [1160, 200], 44, 0)
  if emergencia == False:
    pygame.draw.circle(screen, GREEN, [1160, 200], 40, 0)   #Bombillo :
  elif emergencia == True: 
    pygame.draw.circle(screen, RED, [1160, 200], 40, 0)   #Bombillo
############################################################################
  






