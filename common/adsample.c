/**===========================================================================*/
/* FILE		: adsample.c                                                      */
/*============================================================================*/
/* DESCRIPTION :  QLS100                                                        */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) 2019 by Hanyi                                                */
/* ALL RIGHTS RESERVED                                                        */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |            Change             |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*    V0.1       2020/07/31         Initial Version              Cdq   */
/*============================================================================*/
#include "S32K116.h"
#include "adConv1.h"
#include "pdly1.h"
#include "helper_functions.h"
#include "ntc_calibration.h"
#include "common.h"
#include "tmr_level.h"
/* Timeout for PDB in microseconds */
#define PDLY_TIMEOUT    1000000UL

#ifdef QLS_111
#define ADC_VREFH       4.0f
#else
#define ADC_VREFH       3.3f
#endif
#define ADC_VREFL       0.0f

//void PDB0_IRQHandler(void)
//{
//  /* Clear PDB instance Interrupt flag */
//  PDB_DRV_ClearTimerIntFlag(INST_PDLY1);
//
//}

/* Flag used to store if an ADC IRQ was executed */
volatile bool adcConvDone;
/* Variable to store value from ADC conversion */
volatile uint16_t adcRawValue;
volatile uint16_t adcMax;

/***************************************************************************************************
 * Function: adsample_ADC_IRQHandler
 * Discription: ADC interrupt handler
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void adsample_ADC_IRQHandler(void)
{
    /* Get channel result from ADC channel */
    ADC_DRV_GetChanResult(INST_ADCONV1, 0U, (uint16_t *)&adcRawValue);
    /* Set ADC conversion complete flag */
    adcConvDone = true;
//    FMSTR_Recorder();
    return;
}

/***************************************************************************************************
 * Function: adsample_ADC_Init
 * Discription: init ADC
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void adsample_ADC_Init(void)
{
    /* Write your local variable definition here */
    uint16_t delayValue = 6000;//0,100,5000

    /* Variables in which we store data from ADC */
//    uint16_t adcMax;
//    float adcValue;
    /* Get ADC max value from the resolution */
    if (adConv1_ConvConfig0.resolution == ADC_RESOLUTION_8BIT)
        adcMax = (uint16_t) (1 << 8);
    else if (adConv1_ConvConfig0.resolution == ADC_RESOLUTION_10BIT)
        adcMax = (uint16_t) (1 << 10);
    else
        adcMax = (uint16_t) (1 << 12);
    ADC_DRV_ConfigConverter(INST_ADCONV1, &adConv1_ConvConfig0);
    ADC_DRV_AutoCalibration(INST_ADCONV1);
    ADC_DRV_ConfigChan(INST_ADCONV1, 0UL, &adConv1_ChnConfig0);
    ADC_DRV_ConfigChan(INST_ADCONV1, 1UL, &adConv1_ChnConfig1);
    ADC_DRV_ConfigChan(INST_ADCONV1, 2UL, &adConv1_ChnConfig2);
    IRQn_Type adcIRQ = ADC0_IRQn;

    INT_SYS_InstallHandler(adcIRQ, &adsample_ADC_IRQHandler, (isr_t*) 0);

     /* Calculate the value needed for PDB instance
     * to generate an interrupt at a specified timeout.
     * If the value can not be reached, stop the application flow
     */
    if (!calculateIntValue(&pdly1_InitConfig0, PDLY_TIMEOUT, &delayValue))
    {
        /* Stop the application flow */
        while(1);//£¿£¿
    }
	/* PDB0 CH0 pre-trigger initialization */
    PDB_DRV_Init(INST_PDLY1, &pdly1_InitConfig0);
    PDB_DRV_Enable(INST_PDLY1);
    PDB_DRV_ConfigAdcPreTrigger(INST_PDLY1, 0UL, &pdly1_AdcTrigInitConfig0);
    PDB_DRV_ConfigAdcPreTrigger(INST_PDLY1, 0UL, &pdly1_AdcTrigInitConfig1);
    PDB_DRV_ConfigAdcPreTrigger(INST_PDLY1, 0UL, &pdly1_AdcTrigInitConfig2);

    PDB_DRV_SetTimerModulusValue(INST_PDLY1,6000);
	/* PDB0 CH0 pre-trigger0 delay set to DC-Bus Current in the beginning of the PWM cycle */
	PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDLY1, 0, 0, 0);
	/* PDB0 CH0 pre-trigger1 delay set to sense PhaseA stator current in the middle of the PWM cycle */
	PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDLY1, 0, 1, 2000);
	/* Mosfet temperature */
	PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDLY1, 0, 2, 4000);


//	/* enable PDB before LDOK */
//	PDB_DRV_Enable(INST_PDLY1);

    PDB_DRV_LoadValuesCmd(INST_PDLY1);
    PDB_DRV_SoftTriggerCmd(INST_PDLY1);

    /* Enable ADC 1 interrupt */
    INT_SYS_EnableIRQ(adcIRQ);
	/* Enable PDB0 interrupt */
//	INT_SYS_EnableIRQ(PDB0_IRQn);

}

/***************************************************************************************************
 * Function: adsample_Get_Voltage
 * Discription: get battery voltage
 * Param :
 * Return: voltage in unit V
 * Note:
 ***************************************************************************************************/
#ifdef QLS_111
float adsample_Get_Voltage(void)
{
    static float Voltage;
    uint16_t ADCValue = 0;
    ADC_DRV_GetChanResult(INST_ADCONV1, 0, &ADCValue);//PTA0
    Voltage = ((float) ADCValue / adcMax) * (ADC_VREFH - ADC_VREFL);
    return Voltage;
}
#else
float adsample_Get_Voltage(void)
{
    static float Voltage;
    uint16_t ADCValue = 0;
    ADC_DRV_GetChanResult(INST_ADCONV1, 1, &ADCValue);//PTA1
    Voltage = ((float) ADCValue / adcMax) * (ADC_VREFH - ADC_VREFL);
    return Voltage;
}
#endif

/***************************************************************************************************
 * Function: adsample_Get_TmrLevel
 * Discription: get level by tmr
 * Param :
 * Return: level in unit m
 * Note:
 ***************************************************************************************************/

uint16_t adsample_Get_TmrLevel(void)
{
    static uint16_t rf32_ltmr;
    uint16_t ADCValue = 0;
    ADC_DRV_GetChanResult(INST_ADCONV1, 1, &ADCValue);//PTA1
    rf32_ltmr = tmr_level_cal(ADCValue);

    return rf32_ltmr;
}

/***************************************************************************************************
 * Function: adsample_Get_EnvirTemp
 * Discription: get enviroment temperature
 * Param :
 * Return: temperature in unit c
 * Note:
 ***************************************************************************************************/
short int adsample_Get_EnvirTemp(void)
{
	uint16_t ADCValue = 0;
	ADC_DRV_GetChanResult(INST_ADCONV1, 2, &ADCValue);//PTA7
	static uint8_t rf32_pcb_temp;
	rf32_pcb_temp = ntc_calibration_cal_temp(ADCValue);
	return rf32_pcb_temp;
}

/***************************************************************************************************
 * Function: adsample_Get_NTCTemp
 * Discription: get urea temperature
 * Param :
 * Return: temperature in unit c
 * Note:
 ***************************************************************************************************/
#ifdef QLS_111
short int adsample_Get_NTCTemp(void)
{
	uint16_t ADCValue = 0;
	ADC_DRV_GetChanResult(INST_ADCONV1, 1, &ADCValue);//PTA1
	static short int ntctemp;
	ntctemp = ntc_calibration_cal_temp(ADCValue);
	return ntctemp;
}
#else
short int adsample_Get_NTCTemp(void)
{
	uint16_t ADCValue = 0;
	ADC_DRV_GetChanResult(INST_ADCONV1, 0, &ADCValue);//PTA0
	static uint8_t ntctemp;
	ntctemp = ntc_calibration_cal_temp(ADCValue);
	return ntctemp;
}
#endif
