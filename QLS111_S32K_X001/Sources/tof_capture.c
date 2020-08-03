/**===========================================================================*/
/* FILE		: tof_capture.c                                                            */
/*============================================================================*/
/* DESCRIPTION :                                                          */
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
/*    V0.1       2020/07/31         Initial Version              Cdq          */
/*============================================================================*/
#include "common.h"
#include "tof_capture.h"
#include "tdc1000.h"
//#include "flexTimer_ic1.h"


static uint16_t ru16_tdc_start = 0,ru16_tdc_stop = 0,ru16_tdc_pulse = 0;
static uint16_t OverflowCnt = 0;

uint32_t ru16_tof_Lv[100];//低压计算平均值数组
uint32_t ru16_tof_Hv[100];//高压计算平均值数组
static ftm_state_t ftm1StateStruct;
uint8_t tof_ready = 0;
bool start_cap = false;
volatile	uint8_t SelCh1 = 0;
bool tof_AvgValid_Lv = false,tof_AvgValid_Hv = false;//average tof data is ready
volatile uint32_t ru32_tof_avg_Lv = 0,ru32_tof_avg_Hv = 0;//average tof data
volatile float transLength = DISTANCE;
uint8_t tof_cnt_Lv = 0,tof_cnt_Hv = 0;// tof data array counter

/***************************************************************************************************
 * Function: OverFlow_FTM0_CH0_7_IRQ
 * Discription: OverFlow_FTM0_CH0_7 interrupt handler
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void OverFlow_FTM0_CH0_7_IRQ(void)
{
	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_FLAG);
	OverflowCnt++;
	return ;
}

/***************************************************************************************************
 * Function: tof_capture_TofCap
 * Discription: record capture tof data to array
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void tof_capture_TofCap(ic_event_t event, void *userData)
{
	ru16_tdc_pulse = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1, 0);
    if (SelCh1)
    {
    	ru16_tof_Lv[tof_cnt_Lv % 100] = ru16_tdc_pulse;
    	tof_cnt_Lv++;
    }else
    {
    	ru16_tof_Hv[tof_cnt_Hv % 100] = ru16_tdc_pulse;
    	tof_cnt_Hv++;
    }
//    realt = get_realtime();
    tof_ready = 1;
}

/***************************************************************************************************
 * Function: StartCap
 * Discription: start capture
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void StartCap(ic_event_t event, void *userData)
{
//    uint8_t channel = flexTimer_ic1_InputCaptureChannelConfig[0].hwChannelId;
//    ru16_tdc_start = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1, channel);
//    FTM_DRV_EnableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
    OverflowCnt = 0;
}
/***************************************************************************************************
 * Function: StopCap
 * Discription: stop capture
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void StopCap(ic_event_t event, void *userData)
{
//    uint8_t channel = flexTimer_ic1_InputCaptureChannelConfig[1].hwChannelId;
    FTM_DRV_DisableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
    ru16_tdc_start = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1, 0);
    ru16_tdc_stop = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1, 1);
    ru16_tdc_pulse = (ru16_tdc_start > ru16_tdc_stop) ?  (65536 + ru16_tdc_stop - ru16_tdc_start) : (ru16_tdc_stop - ru16_tdc_start);
    if (SelCh1)
    {
    	ru16_tof_Lv[tof_cnt_Lv % 100] = ru16_tdc_pulse;
    	tof_cnt_Lv++;
    }else
    {
    	ru16_tof_Hv[tof_cnt_Hv % 100] = ru16_tdc_pulse;
    	tof_cnt_Hv++;
    }
//    realt = get_realtime();
    tof_ready = 1;
}
/***************************************************************************************************
 * Function: ftm0_Init
 * Discription: ftm0 initiate
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void ftm0_Init(void)
{
    uint32_t frequency;
    FTM_DRV_Init(INST_FLEXTIMER_IC1, &flexTimer_ic1_InitConfig, &ftm1StateStruct);
    /* Setup input capture for FTM 0 channel 0  - PTD15,channel 1 - PTD16 */
    FTM_DRV_InitInputCapture(INST_FLEXTIMER_IC1, &flexTimer_ic1_InputCaptureConfig);
//    INT_SYS_SetPriority(12, 4);
//    //interrupt register
//    IRQn_Type FTM0CapIRQ = FTM0_Ovf_Reload_IRQn;
//    INT_SYS_InstallHandler(FTM0CapIRQ, &OverFlow_FTM0_CH0_7_IRQ, (isr_t*) 0);
//    FTM_DRV_DisableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
//    INT_SYS_SetPriority(14, 8);
//	FTM_DRV_EnableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
    /* Get the FTM1 frequency to calculate
     * the frequency of the measured signal.
     */
    frequency = FTM_DRV_GetFrequency(INST_FLEXTIMER_IC1);
}
/***************************************************************************************************
 * Function: tof_capture_get_realtimelv
 * Discription: get tof of low voltage channel
 * Param :
 * Return: real time of tof  uinit us
* Note:
 ***************************************************************************************************/
float tof_capture_get_realtimelv(void)
{
	float realtime;
	uint32_t sumpulse = 0;
	uint16_t avergepulse = 0;
	uint8_t i = 0;
	for (i=0;i<100;i++)
		sumpulse += ru16_tof_Lv[i];
	avergepulse = sumpulse / 100;
    realtime = avergepulse * ((float) CAP_TIMETICK);
    return realtime;
}
/***************************************************************************************************
 * Function: tof_capture_get_realtimehv
 * Discription: get tof of high voltage channel
 * Param :
 * Return: real time of tof  uinit us
* Note:
 ***************************************************************************************************/
float tof_capture_get_realtimehv(void)
{
	float realtime;
	uint32_t sumpulse = 0;
	uint16_t avergepulse = 0;
	uint8_t i = 0;
	for (i=0;i<100;i++)
		sumpulse += ru16_tof_Hv[i];
	avergepulse = sumpulse / 100;
    realtime = avergepulse * ((float) CAP_TIMETICK);
    return realtime;
}
/***************************************************************************************************
 * Function: tof_capture_get_LvAvgTof
 * Discription: caculate average 100 tof data of low voltage channel
 * Param :
 * Return: average tof  uinit tick
* Note:
 ***************************************************************************************************/
uint8_t tof_capture_get_LvAvgTof(void)
{
	uint8_t i = 0;
	uint32_t tof_sum = 0;
	uint8_t ef = tdc1000_read_errflg();

	if ( 0 != ef )
	{
		tdc1000_clear_errflg();
	}
	if (tof_cnt_Lv >=100)
	{
		tof_cnt_Lv = 0;
		tof_AvgValid_Lv = true;
	}
	if ( tof_AvgValid_Lv )
	{
		for (i=0;i<100; i++)
		{
			tof_sum = tof_sum + ru16_tof_Lv[i];
		}
		ru32_tof_avg_Lv = tof_sum / 100;
	}
	return tof_AvgValid_Lv;
}
/***************************************************************************************************
 * Function: tof_capture_get_HvAvgTof
 * Discription: caculate average 100 tof data of high voltage channel
 * Param :
 * Return: average tof  uinit tick
* Note:
 ***************************************************************************************************/
uint8_t tof_capture_get_HvAvgTof(void)
{
	uint8_t i = 0;
	uint32_t tof_sum = 0;
	if (tof_cnt_Hv >=100)
	{
		tof_cnt_Hv = 0;
		tof_AvgValid_Hv = true;
	}
	if ( tof_AvgValid_Hv )
	{
		for (i=0;i<100; i++)
		{
			tof_sum = tof_sum + ru16_tof_Hv[i];
		}
		ru32_tof_avg_Hv = tof_sum / 100;
	}

	return tof_AvgValid_Hv;
}

//float get_AvgVelocity(uint32_t tof_avg)
//{
//	float velocity = 0.0;
// 	velocity =  DISTANCE * 2.0 / (CAP_TIMETICK * tof_avg ) ;
//	return velocity;
//}

/***************************************************************************************************
 * Function: tof_capture_get_AvgVelocity
 * Discription: caculate sonic velocityby
 * Param :
 * Return: average tof  uinit tick
* Note:
 ***************************************************************************************************/
float tof_capture_get_AvgVelocity(float us)
{
	float velocity = 0.0;
 	velocity =  transLength * 2.0 / us * 1000000;
	return velocity;
}

/***************************************************************************************************
 * Function: tof_capture_TofCntToUs
 * Discription: turn tof tick data to us
 * Param :
 * Return: tof  uinit us
* Note:
 ***************************************************************************************************/
float tof_capture_TofCntToUs(uint32_t tofcnt)
{
	float us = 0.0;
	us = CAP_TIMETICK * tofcnt * 1000000;// unit us
	return us;
}

