/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : adConv1.c
**     Project     : QLS111_S32K_X001
**     Processor   : S32K116_48
**     Component   : adc
**     Version     : Component SDK_S32K116_00, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K116_00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-07-21, 11:52, # CodeGen: 91
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file adConv1.c
** @version 01.00
*/
/*!
**  @addtogroup adConv1_module adConv1 module documentation
**  @{
*/

/* MODULE adConv1. */

#include "adConv1.h"

/*! adConv1 configuration structure */
const adc_converter_config_t adConv1_ConvConfig0 = {
  .clockDivide = ADC_CLK_DIVIDE_4,
  .sampleTime = 12U,
  .resolution = ADC_RESOLUTION_12BIT,
  .inputClock = ADC_CLK_ALT_1,
  .trigger = ADC_TRIGGER_HARDWARE,
  .pretriggerSel = ADC_PRETRIGGER_SEL_PDB,
  .triggerSel = ADC_TRIGGER_SEL_PDB,
  .dmaEnable = false,
  .voltageRef = ADC_VOLTAGEREF_VREF,
  .continuousConvEnable = false,
  .supplyMonitoringEnable = false,
};

const adc_chan_config_t adConv1_ChnConfig0 = {
  .interruptEnable = false,
  .channel = ADC_INPUTCHAN_EXT0,
};

const adc_chan_config_t adConv1_ChnConfig1 = {
  .interruptEnable = false,
  .channel = ADC_INPUTCHAN_EXT1,
};

const adc_chan_config_t adConv1_ChnConfig2 = {
  .interruptEnable = false,
  .channel = ADC_INPUTCHAN_EXT3,
};


/* END adConv1. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/

