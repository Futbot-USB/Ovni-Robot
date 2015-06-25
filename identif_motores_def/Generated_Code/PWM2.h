/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PWM2.h
**     Project     : identif_motores_def
**     Processor   : MCF51AC256ACLK
**     Component   : PWM
**     Version     : Component 02.240, Driver 01.28, CPU db: 3.00.065
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2015-05-06, 16:24, # CodeGen: 2
**     Abstract    :
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
**     Settings    :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       42            |  PTH0_FTM2CH2_AD1P20
**             ----------------------------------------------------
**
**         Timer name                  : FTM2 [16-bit]
**         Counter                     : FTM2CNT   [0xFFFF80C1]
**         Mode register               : FTM2SC    [0xFFFF80C0]
**         Run register                : FTM2SC    [0xFFFF80C0]
**         Prescaler                   : FTM2SC    [0xFFFF80C0]
**         Compare register            : FTM2C2V   [0xFFFF80CC]
**         Flip-flop register          : FTM2C2SC  [0xFFFF80CB]
**
**         User handling procedure     : not specified
**
**         Port name                   : PTH
**         Bit number (in port)        : 0
**         Bit mask of the port        : 0x0001
**         Port data register          : PTHD      [0xFFFF800E]
**         Port control register       : PTHDD     [0xFFFF800F]
**
**         Initialization:
**              Output level           : low
**              Timer                  : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 4194304 Hz
**           Initial value of            period     pulse width
**             Xtal ticks              : 33         33
**             microseconds            : 1000       1000
**             milliseconds            : 1          1
**             seconds (real)          : 0.000999927521 0.000999927521
**
**     Contents    :
**         SetRatio8 - byte PWM2_SetRatio8(byte Ratio);
**         SetDutyUS - byte PWM2_SetDutyUS(word Time);
**         SetDutyMS - byte PWM2_SetDutyMS(word Time);
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
** @file PWM2.h
** @version 01.28
** @brief
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
*/         
/*!
**  @addtogroup PWM2_module PWM2 module documentation
**  @{
*/         

#ifndef __PWM2
#define __PWM2

/* MODULE PWM2. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#define PWM2_PERIOD_VALUE              0x1061U /* Initial period value in ticks of the timer in high speed mode */
#define PWM2_PERIOD_VALUE_HIGH         0x1061U /* Period value in ticks of the timer in high speed mode */


byte PWM2_SetRatio8(byte Ratio);
/*
** ===================================================================
**     Method      :  PWM2_SetRatio8 (component PWM)
**     Description :
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as an 8-bit unsigned integer number. 0 - FF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         <Starting pulse width> property. 
**         Note: Calculated duty depends on the timer capabilities and
**         on the selected period.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ratio           - Ratio to set. 0 - 255 value is
**                           proportional to ratio 0 - 100%
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte PWM2_SetDutyUS(word Time);
/*
** ===================================================================
**     Method      :  PWM2_SetDutyUS (component PWM)
**     Description :
**         This method sets the new duty value of the output signal.
**         The duty is expressed in microseconds as a 16-bit
**         unsigned integer number.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Duty to set [in microseconds]
**                      (0 to 1000 us in high speed mode)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

byte PWM2_SetDutyMS(word Time);
/*
** ===================================================================
**     Method      :  PWM2_SetDutyMS (component PWM)
**     Description :
**         This method sets the new duty value of the output signal.
**         The duty is expressed in milliseconds as a 16-bit
**         unsigned integer number.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Duty to set [in milliseconds]
**                      (0 to 1 ms in high speed mode)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

void PWM2_Init(void);
/*
** ===================================================================
**     Method      :  PWM2_Init (component PWM)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


/* END PWM2. */

#endif /* ifndef __PWM2 */
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
