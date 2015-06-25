/* ###################################################################
**     Filename    : main.c
**     Project     : carrito_prueba_encoder
**     Processor   : MCF51AC256ACLK
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-06-19, 17:49, # CodeGen: 0
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
#include "KB1.h"
#include "FC321.h"
#include "AS2.h"
#include "Bit1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
  char cabecera = 0xFF;
  char cola = '\n';
  word sent;
  byte overcurrent = FALSE;
  word clock_inicial;
  word clock_actual;
  extern word contador;
  
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

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;){
	  FC321_Reset();	  
	  /* ENCODER 1 CANAL A*/
	  Bit1_PutVal(TRUE);
	  contador = 0;
	  FC321_GetTimeMS(&clock_inicial);
	  clock_actual = clock_inicial;
	  KBIPE = 0x01;
	  while (clock_actual <= clock_inicial+3000)
	  {
	  		FC321_GetTimeMS(&clock_actual);
	  }
	  KBIPE = 0;
	  sensores.A1 = contador;
	  		  
	  /* ENCODER 1 CANAL B*/
	  Bit1_PutVal(FALSE);
	  contador = 0;
	  FC321_GetTimeMS(&clock_inicial);
	  clock_actual = clock_inicial;
	  KBIPE = 0x04; 
	  while (clock_actual <= clock_inicial+3000)
	  {	  	  
	  		FC321_GetTimeMS(&clock_actual);
	  }
	  KBIPE = 0;
	  sensores.B1 = contador;
	  		  
	  /* ENCODER 2 CANAL A*/
	  Bit1_PutVal(TRUE);
	  contador = 0;
	  FC321_GetTimeMS(&clock_inicial);
	  clock_actual = clock_inicial;
	  KBIPE = 0x02; 
	  while (clock_actual <= clock_inicial+3000)
	  { 		  	  
	  		FC321_GetTimeMS(&clock_actual);
	  }
	   KBIPE = 0;
	   sensores.A2 = contador;
	  		  
	   /* ENCODER 2 CANAL B*/
	   Bit1_PutVal(FALSE);
	   contador = 0;
	   FC321_GetTimeMS(&clock_inicial);
	   clock_actual = clock_inicial;
	   KBIPE = 0x40; 
	   while (clock_actual <= clock_inicial+3000)
	   {  	  
	  		 FC321_GetTimeMS(&clock_actual);
	   }
	   sensores.B2 = contador;
	  		  
	   /*ENCODER 3 CANAL A*/
	   Bit1_PutVal(TRUE);
	   contador = 0;
	   FC321_GetTimeMS(&clock_inicial);
	   clock_actual = clock_inicial;
  	   KBIPE = 0x08; 
	   while (clock_actual <= clock_inicial+3000)
	   {  	  
	  		 FC321_GetTimeMS(&clock_actual);
	   }
	   sensores.A3 = contador;
	  		  
	   /* ENCODER 3 CANAL B*/
	   Bit1_PutVal(FALSE);
	   contador = 0;
	   FC321_GetTimeMS(&clock_inicial);
   	   clock_actual = clock_inicial;
	   KBIPE = 0x20; 
  	   while (clock_actual <= clock_inicial+3000)
	   {  	  
	    	 FC321_GetTimeMS(&clock_actual);
	   }
	   sensores.B3 = contador;
	  		  
	   /* ENCODER 4 CANAL A*/
	   Bit1_PutVal(TRUE);
	   contador = 0;
  	   FC321_GetTimeMS(&clock_inicial);
  	   clock_actual = clock_inicial;
       KBIPE = 0x10; 
	   while (clock_actual <= clock_inicial+3000)
	   {  	  
	  		 FC321_GetTimeMS(&clock_actual);
	   }
	   sensores.A4 = contador;
	   		  
	   /* ENCODER 4 CANAL B*/
	   Bit1_PutVal(FALSE);
  	   contador = 0;
	   FC321_GetTimeMS(&clock_inicial);
	   clock_actual = clock_inicial;
	   KBIPE = 0x80; 
	   while (clock_actual <= clock_inicial+3000)
	   {  	  
	  		 FC321_GetTimeMS(&clock_actual);
	   }
	   sensores.B4 = contador;
	   
	   AS2_SendChar(cabecera);
	   AS2_SendBlock((byte*)&sensores, sizeof(sensores), &sent);
	   AS2_SendChar(overcurrent);
	   AS2_SendChar(cola);
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
