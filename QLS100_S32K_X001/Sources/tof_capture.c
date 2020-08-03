/**===========================================================================*/
/* FILE		: tof_capture.c                                                   */
/*============================================================================*/
/* DESCRIPTION :                                                         */
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
#include <tof_capture.h>
#include "common.h"
volatile float transLength = DISTANCE;
//#include "tdc1000.h"
//#include "flexTimer_ic1.h"
//static uint16_t ru16_tdc_start = 0,ru16_tdc_stop = 0,ru16_tdc_pulse = 0;
//static uint16_t OverflowCnt = 0;
//
//uint32_t ru16_tof_Lv[100];//ตอัน
//uint32_t ru16_tof_Hv[100];//ธ฿ัน
//static ftm_state_t ftm1StateStruct;
//uint8_t tof_ready = 0;
//bool start_cap = false;
//volatile	uint8_t SelCh1 = 0;
//uint8_t tof_AvgValid_Lv = false,tof_AvgValid_Hv = false;
//volatile uint32_t tof_avg_Lv = 0,tof_avg_Hv = 0;
//uint8_t tof_cnt_Lv = 0,tof_cnt_Hv = 0;
//void OverFlow_FTM0_CH0_7_IRQ(void)
//{
//	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_FLAG);
//	OverflowCnt++;
//	return ;
//}
//void StartCap(ic_event_t event, void *userData)
//{
////    uint8_t channel = flexTimer_ic1_InputCaptureChannelConfig[0].hwChannelId;
////    ru16_tdc_start = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1, channel);
////    FTM_DRV_EnableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
//    OverflowCnt = 0;
//}
//void StopCap(ic_event_t event, void *userData)
//{
//	static float realt=0.0;
////    uint8_t channel = flexTimer_ic1_InputCaptureChannelConfig[1].hwChannelId;
//    FTM_DRV_DisableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
//    ru16_tdc_start = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1, 0);
//    ru16_tdc_stop = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1, 1);
//    ru16_tdc_pulse = (ru16_tdc_start > ru16_tdc_stop) ?  (65536 + ru16_tdc_stop - ru16_tdc_start) : (ru16_tdc_stop - ru16_tdc_start);
//    if (SelCh1)
//    {
//    	ru16_tof_Lv[tof_cnt_Lv % 100] = ru16_tdc_pulse;
//    	tof_cnt_Lv++;
//    }else
//    {
//    	ru16_tof_Hv[tof_cnt_Hv % 100] = ru16_tdc_pulse;
//    	tof_cnt_Hv++;
//    }
////    realt = get_realtime();
//    tof_ready = 1;
//}
//
//void ftm0_Init(void)
//{
//    uint32_t frequency;
//    FTM_DRV_Init(INST_FLEXTIMER_IC1, &flexTimer_ic1_InitConfig, &ftm1StateStruct);
//    /* Setup input capture for FTM 0 channel 0  - PTD15,channel 1 - PTD16 */
//    FTM_DRV_InitInputCapture(INST_FLEXTIMER_IC1, &flexTimer_ic1_InputCaptureConfig);
////    INT_SYS_SetPriority(12, 4);
////    //interrupt register
//////    IRQn_Type FTM0CapIRQ = FTM0_Ovf_Reload_IRQn;
//////    INT_SYS_InstallHandler(FTM0CapIRQ, &OverFlow_FTM0_CH0_7_IRQ, (isr_t*) 0);
//////    FTM_DRV_DisableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
////    INT_SYS_SetPriority(14, 8);
////	FTM_DRV_EnableInterrupts(INST_FLEXTIMER_IC1,FTM_TIME_OVER_FLOW_INT_ENABLE);
//    /* Get the FTM1 frequency to calculate
//     * the frequency of the measured signal.
//     */
//    frequency = FTM_DRV_GetFrequency(INST_FLEXTIMER_IC1);
//}
//
//float get_realtime(void)
//{
//	float realtime;
//    realtime = ru16_tdc_pulse * ((float) CAP_TIMETICK);
//}
//
//uint8_t get_LvAvgTof(void)
//{
//	uint8_t i = 0;
//	uint32_t tof_sum = 0;
//	uint8_t ef = tdc1000_read_errflg();
//
//	if ( 0 != ef )
//	{
//		tdc1000_clear_errflg();
//	}
//	if (tof_cnt_Lv >=100)
//	{
//		tof_cnt_Lv = 0;
//		tof_AvgValid_Lv = 1;
//	}
//	if ( tof_AvgValid_Lv )
//	{
//		for (i=0;i<100; i++)
//		{
//			tof_sum = tof_sum + ru16_tof_Lv[i];
//		}
//		tof_avg_Lv = tof_sum / 100;
//	}
//	return tof_AvgValid_Lv;
//}
//
//uint8_t get_HvAvgTof(void)
//{
//	uint8_t i = 0;
//	uint32_t tof_sum = 0;
//	if (tof_cnt_Hv >=100)
//	{
//		tof_cnt_Hv = 0;
//		tof_AvgValid_Hv = 1;
//	}
//	if ( tof_AvgValid_Hv )
//	{
//		for (i=0;i<100; i++)
//		{
//			tof_sum = tof_sum + ru16_tof_Hv[i];
//		}
//		tof_avg_Hv = tof_sum / 100;
//	}
//
//	return tof_AvgValid_Hv;
//}

/***************************************************************************************************
 * Function: tof_capture_Get_AvgVelocity
 * Discription: get average sonic velocity by tof
 * Param :us concentration tof time unit us Microseconds.
 * Return:average sonic velocity unit m/s
 * Note:
 ***************************************************************************************************/
float tof_capture_Get_AvgVelocity(float us)
{
	float rf32_velocity = 0.0;
	if ( us != 0)
		rf32_velocity =  transLength * 2.0 / us * 1000000;
	return rf32_velocity;
}


/***************************************************************************************************
 * Function: tof_capture_TofCntToUs
 * Discription: turn pulse width count of tof to microsecond
 * Param :us concentration tof time unit us Microseconds.
 * Return:tof time unit microsecond
 * Note:
 ***************************************************************************************************/
float tof_capture_TofCntToUs(uint32_t tofcnt)
{
	float rf32_us = 0.0;
	rf32_us = CAP_TIMETICK * tofcnt * 1000000;// unit us
	return rf32_us;
}
