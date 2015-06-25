/* ###################################################################
**     Filename    : Events.c
**     Project     : carrito_com_def
**     Processor   : MCF51AC256ACLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-05-06, 17:38, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "time.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
struct{
		byte header;
		byte data1;
		byte data2;
		byte data3;
		byte data4;
		byte data5;
		byte data6;
		byte data7;
		byte data8;
}trama; 

extern struct{
		byte ref1;
		byte ref2;
		byte ref3;
		byte ref4;
		byte duty1;
		byte duty2;
		byte duty3;
		byte duty4;
}motores; 
  
extern byte estado; 
extern byte activo;
word received;
word contador = 0;
word longitud;  
word n =0;
/*
** ===================================================================
**     Event       :  AS2_OnFullRxBuf (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS2_OnFullRxBuf(void)
{
  //word received;
  AS2_RecvBlock((byte*)&trama, sizeof(trama), &received);
  AS2_ClearRxBuf();

  if (trama.header == 0x2F) /*Verificacion de la trama*/
  {
	  motores.ref1 = trama.data1;
	  motores.ref2 = trama.data2;
	  motores.ref3 = trama.data3;
	  motores.ref4 = trama.data4;
	  motores.duty1 = trama.data5;
	  motores.duty2 = trama.data6;
	  motores.duty3 = trama.data7;
	  motores.duty4 = trama.data8;
	  estado = 0;
  }
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
	estado = 1; /*Iniciar mediciones*/	
}

/*
** ===================================================================
**     Event       :  KB1_OnInterrupt (module Events)
**
**     Component   :  KB1 [KBI]
**     Description :
**         This event is called when the active signal edge/level
**         occurs. This event is enabled only if <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void KB1_OnInterrupt(void)
{
	contador = contador + 1; 
}

/* END Events */

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
