/* ###################################################################
**     Filename    : main.c
**     Project     : carrito_com_def
**     Processor   : MCF51AC256ACLK
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-05-06, 17:38, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PWM1.h"
#include "PWM2.h"
#include "PWM3.h"
#include "PWM4.h"
#include "Ref1.h"
#include "Ref2.h"
#include "Ref3.h"
#include "Ref4.h"
#include "En1.h"
#include "En2.h"
#include "En3.h"
#include "En4.h"
#include "AS2.h"
#include "AD1.h"
#include "KB1.h"
#include "FC321.h"
#include "Bit1.h"
#include "TI1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "time.h"
#include "stdlib.h"
/* User includes (#include below this line is not maintained by Processor Expert) */




  struct{
		byte ref1;
		byte ref2;
		byte ref3;
		byte ref4;
		byte duty1;
		byte duty2;
		byte duty3;
		byte duty4;
  }motores = {FALSE,FALSE,FALSE,FALSE,255,255,255,255};  
  
  struct{
	  word I1;
	  word I2;
  	  word I3;
   	  word I4;
  	  word A1;
  	  word B1;
  	  word A2;
  	  word B2;
  	  word A3;
  	  word B3;
  	  word A4;
  	  word B4;
  }sensores = {0,0,0,0,0,0,0,0,0,0,0,0}; 

  
  byte estado = 0; 
  char cabecera = 0xFF;
  char cola = '\n';
  word sent;
  word clock_inicial;
  word clock_actual;
  word clock_prueba;
  extern word contador;
  byte activo = TRUE;
  byte overcurrent = FALSE;
 

void main(void)
{
  /* Write your local variable definition here */
  
  estado = 0; /*Estado Inicial*/
  
  
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  //KBIPE = 0; /*Deshabilita KBI*/
  
  for(;;){
	  
	  switch(estado)
	  {
	  case 0: /*Movimiento*/
		  KBIPE = 0;
		  En1_PutVal(activo); /*Habilita los motores*/
		  En2_PutVal(activo);
		  En3_PutVal(activo);
		  En4_PutVal(activo);
		  Ref1_PutVal(motores.ref1);
		  Ref2_PutVal(motores.ref2);
		  Ref3_PutVal(motores.ref3);
		  Ref4_PutVal(motores.ref4);	  
		  PWM1_SetRatio8(motores.duty1);
		  PWM2_SetRatio8(motores.duty2);
		  PWM3_SetRatio8(motores.duty3);
		  PWM4_SetRatio8(motores.duty4);
		  break;
		  
	  case 1: /*Lectura de Sensores*/
		  FC321_Reset();
		  
		  /* ENCODER 1 CANAL A*/
		  contador = 0;
		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x01;
		  while (clock_actual <= clock_inicial+30 && estado == 1)
		  {
			  
			  FC321_GetTimeMS(&clock_actual);
		  }
		  KBIPE = 0;
		  sensores.A1 = contador;
		  
		  /* ENCODER 1 CANAL B*/
		  contador = 0;
		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x04; 
		  while (clock_actual <= clock_inicial+30 && estado == 1)
		  {
		  	  
		  	  FC321_GetTimeMS(&clock_actual);
		  }
		  KBIPE = 0;
		  sensores.B1 = contador;
		  
		  /* ENCODER 2 CANAL A*/
		  contador = 0;
		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x02; 
 		  while (clock_actual <= clock_inicial+30 && estado == 1)
 		  { 		  	  
		  	  FC321_GetTimeMS(&clock_actual);
		  }
 		  KBIPE = 0;
 		  sensores.A2 = contador;
		  
		  /* ENCODER 2 CANAL B*/
		  contador = 0;
   		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x40; 
		  while (clock_actual <= clock_inicial+30 && estado == 1)
		  {  	  
			  FC321_GetTimeMS(&clock_actual);
		  }
		  sensores.B2 = contador;
		  
		  /*ENCODER 3 CANAL A*/
		  contador = 0;
		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x08; 
		  while (clock_actual <= clock_inicial+30 && estado == 1)
		  {  	  
		  	  FC321_GetTimeMS(&clock_actual);
		  }
		  sensores.A3 = contador;
		  
		  /* ENCODER 3 CANAL B*/
		  contador = 0;
		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x20; 
		  while (clock_actual <= clock_inicial+30 && estado == 1)
		  {  	  
		  	  FC321_GetTimeMS(&clock_actual);
		  }
		  sensores.B3 = contador;
		  
		  /* ENCODER 4 CANAL A*/
		  contador = 0;
		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x10; 
		  while (clock_actual <= clock_inicial+30 && estado == 1)
		  {  	  
		  	  FC321_GetTimeMS(&clock_actual);
		  }
		  sensores.A4 = contador;
 		  
		  /* ENCODER 4 CANAL B*/
		  FC321_GetTimeMS(&clock_prueba);
		  contador = 0;
		  FC321_GetTimeMS(&clock_inicial);
		  clock_actual = clock_inicial;
		  KBIPE = 0x80; 
		  while (clock_actual <= clock_inicial+30 && estado == 1)
		  {  	  
		  	  FC321_GetTimeMS(&clock_actual);
		  }
		  sensores.B4 = contador;
		  
		  if (estado == 1)
		  {
			  AD1_MeasureChan(TRUE,0);
			  AD1_MeasureChan(TRUE,1);
			  AD1_MeasureChan(TRUE,2);
			  AD1_MeasureChan(TRUE,3);
			  AD1_GetChanValue(0,&sensores.I1);
		  	  AD1_GetChanValue(1,&sensores.I2);
		  	  AD1_GetChanValue(2,&sensores.I3);
		  	  AD1_GetChanValue(3,&sensores.I4);
			  
			  if (sensores.I1 >= 0x85B || sensores.I2 >= 0x85B || sensores.I3 >= 0x85B || sensores.I4 >= 0x85B)
			  {
				  if (overcurrent == TRUE)
				  {
					  estado = 2;
				  }
				  else
				  {
					  estado = 0;
				  }
				  overcurrent = TRUE; 
			  }
			  else
			  {
				  overcurrent = FALSE;
				  estado = 0;
			  }
			  AS2_SendChar(cabecera);
			  AS2_SendBlock((byte*)&sensores, sizeof(sensores), &sent);
			  AS2_SendChar(overcurrent);
			  AS2_SendChar(cola);
		  }
		  break;
		  
	  case 2:
		  activo = FALSE;
		  Bit1_PutVal(TRUE);
		  estado = 0;
		  break;
	  }
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
