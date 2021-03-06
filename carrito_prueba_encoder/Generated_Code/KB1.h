/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : KB1.h
**     Project     : carrito_prueba_encoder
**     Processor   : MCF51AC256ACLK
**     Component   : KBI
**     Version     : Component 01.096, Driver 01.25, CPU db: 3.00.065
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-06-19, 18:28, # CodeGen: 1
**     Abstract    :
**         This component "KBI" implements the Freescale Keyboard 
**         Interrupt Module (KBI/KBD) which allows to catch events 
**         on selected external pins. These pins share one KBI/KBD 
**         interrupt which can be caused by events on the pins.
**     Settings    :
**         Keyboard                    : KBI 
**         Used pins           
**         Pin 0                       : PTG0_KBI1P0
**         Pin 1                       : PTG2_KBI1P2
**         Pin 2                       : PTG1_KBI1P1
**         Pin 3                       : PTD2_KBI1P5_AD1P10_ACMP1O
**         Pin 4                       : PTD3_KBI1P6_AD1P11
**         Pin 5                       : PTG3_KBI1P3_AD1P18
**         Pin 6                       : PTG4_KBI1P4_AD1P19
**         Pin 7                       : PTD7_KBI1P7_AD1P15
**         Pull resistor               : off
**         Generate interrupt on       : falling
**         Interrupt service           : Enabled
**         Interrupt                   : Vkeyboard
**         Interrupt Priority          : 240
**         Enable in init. code        : Yes
**         Events enabled in init.     : Yes
**     Contents    :
**         GetVal  - byte KB1_GetVal(void);
**         SetEdge - byte KB1_SetEdge(byte edge);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file KB1.h
** @version 01.25
** @brief
**         This component "KBI" implements the Freescale Keyboard 
**         Interrupt Module (KBI/KBD) which allows to catch events 
**         on selected external pins. These pins share one KBI/KBD 
**         interrupt which can be caused by events on the pins.
*/         
/*!
**  @addtogroup KB1_module KB1 module documentation
**  @{
*/         

#ifndef __KB1
#define __KB1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE KB1. */

#include "Cpu.h"

/* PUBLISHED CONSTANTS for using together with GetVal method  */
#define KB1_NUM_PIN0          0x01U /* Mask of Pin0 */
#define KB1_NUM_PIN1          0x02U /* Mask of Pin1 */
#define KB1_NUM_PIN2          0x04U /* Mask of Pin2 */
#define KB1_NUM_PIN3          0x08U /* Mask of Pin3 */
#define KB1_NUM_PIN4          0x10U /* Mask of Pin4 */
#define KB1_NUM_PIN5          0x20U /* Mask of Pin5 */
#define KB1_NUM_PIN6          0x40U /* Mask of Pin6 */
#define KB1_NUM_PIN7          0x80U /* Mask of Pin7 */

/* PUBLISHED CONSTANTS for enabled pins */
#define KB1_PIN_SIGNAL0       0x01U  /* Mask of Pin0*/
#define KB1_PIN_SIGNAL1       0x04U  /* Mask of Pin1*/
#define KB1_PIN_SIGNAL2       0x02U  /* Mask of Pin2*/
#define KB1_PIN_SIGNAL3       0x04U  /* Mask of Pin3*/
#define KB1_PIN_SIGNAL4       0x08U  /* Mask of Pin4*/
#define KB1_PIN_SIGNAL5       0x08U  /* Mask of Pin5*/
#define KB1_PIN_SIGNAL6       0x10U  /* Mask of Pin6*/
#define KB1_PIN_SIGNAL7       0x80U  /* Mask of Pin7*/

/* Deprecated */
#define PinSignal0            0x01U
#define PinSignal1            0x02U
#define PinSignal2            0x04U
#define PinSignal3            0x08U
#define PinSignal4            0x10U
#define PinSignal5            0x20U
#define PinSignal6            0x40U
#define PinSignal7            0x80U


void KB1_Init(void);
/*
** ===================================================================
**     Method      :  KB1_Init (component KBI)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

__interrupt void KB1_Interrupt(void);
/*
** ===================================================================
**     Method      :  KB1_Interrupt (component KBI)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

byte KB1_GetVal(void);

/*
** ===================================================================
**     Method      :  KB1_GetVal (component KBI)
**     Description :
**         Returns the value of pins
**     Parameters  : None
**     Returns     :
**         ---             - The value of associated pins (bits ordered
**                           according to the component list of pins)
** ===================================================================
*/

byte KB1_SetEdge(byte edge);
/*
** ===================================================================
**     Method      :  KB1_SetEdge (component KBI)
**     Description :
**         Sets the sensitive edge. If all selected pins don't have the
**         same edge setting possibility, the method allows to set only
**         those edges that are common (possible to set for all
**         selected pins).
**     Parameters  :
**         NAME            - DESCRIPTION
**         edge            - Edge type:
**                           0 - falling edge
**                           1 - rising edge
**                           2 - both edges
**                           3 - low level
**                           4 - high level
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_RANGE - Value is out of range
** ===================================================================
*/


/* END KB1. */

#endif /* ifndef __KB1 */
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
