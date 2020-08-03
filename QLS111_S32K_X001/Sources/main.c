/**===========================================================================*/
/* FILE		: main.c                                                            */
/*============================================================================*/
/* DESCRIPTION :   QLS111                                                       */
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
#include "Cpu.h"
#include "tof_capture.h"
#if CPU_INIT_CONFIG
#include "Init_Config.h"
#endif

#include "Sys_Init.h"
/*******  2020-7-21  close J1939 CAN function commented   *******/
//#include "HW_Driver\hw_abstract.h"
//#include "Comm_Mgt\comm_mgt.h"
//#include "App_Task_Mgt.h"

/******   freemaster   *********/
#include "freemaster.h"
#include "freemaster_protocol.h"

volatile int exit_code = 0;
#define BUFFER_SIZE (16U)
#define TIMEOUT (200U)
#define DO_CAN_STB_PORT	PTC
#define DO_CAN_STB		5U
#define CAN_Tx_Test (1)
#ifdef CAN_Tx_Test
uint8_t u8_canDataT[8] = {1, 2, 3, 4, 5, 6, 7, 8};
uint16_t u16_timerCnt = 0;
#endif
/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
	/*** 测试临时变量 ***/
	static float rf32_us_tof_level;
	static float rf32_us_tof_concentra;
	static float rf32_VBat=0.0;
	static float rf32_ult_temp = 0.0;
	static float rf32_pcb_temp = 0.0;
	static float rf32_Velocity=0.0,level = 0.0;
	static uint32_t r32u_tofcon = 0,r32u_toflevel = 0;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	#ifdef PEX_RTOS_INIT
		PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
	#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
    /* Initialize and configure clocks
     *     -   see clock manager component for details
     */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Initialize pins
     *    -   See PinSettings component for more info
     */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
    spi_comm_Spi_Init();
    tdc1000_Init();
    ftm0_Init();
    adsample_ADC_Init();

    Sys_Init();
    CAN_Comm_Init();
    FMSTR_Init();
	for (;;)
	{
		(void)u8_hw_wtd_reset();
    	FMSTR_Poll();
		/*** 1ms 检查刷新一次can通讯 ***/
//		if (task_1ms_OK != 0)
//		{
//			task_1ms_OK = 0;
//			u8_task_AppMgt_1ms();
//			u8_comm_task();
//#ifdef CAN_Tx_Test
//			u16_timerCnt++;
//			if ((u16_timerCnt >= 998))
//			{
////				u8_hw_CAN_Send(0x101, u8_canDataT, 8);
//				u16_timerCnt = 0;
//				ru32_tofcon = (uint32_t) (get_realtimelv()+0.5);
//				ru32_toflevel = (uint32_t) get_realtimehv();
//			}
//#endif
//		}
		//  if (0 != task_5ms_OK)
		//  {
		//  	task_5ms_OK = 0;
		//  	u8_comm_task();
		//  }
    	/*    2020-7-21  J1939 CAN function commented    */
		/*** 100ms计算一次 ***/
		if ( 0 != task_100ms_OK )
		{
			task_100ms_OK = 0;
			if ( tof_capture_get_LvAvgTof() )
			{
				rf32_Velocity = tof_capture_get_AvgVelocity(tof_capture_TofCntToUs(ru32_tof_avg_Lv));
			}
	//		if ( get_HvAvgTof() )
	//		{
	//			get_AvgVelocity(tof_avg_Hv);
	//			//level = Velocity * tof_avg_Hv /2;
	//		}
			if (SelCh1)
			{
//				tdc1000_Trig_Ch_Hv();
			}else
			{
				tdc1000_Trig_Ch_Lv();
			}
			SelCh1 = 1 - SelCh1;
			rf32_VBat = adsample_Get_Voltage();
			rf32_pcb_temp = adsample_Get_EnvirTemp();
			rf32_ult_temp = adsample_Get_NTCTemp();
		}
	}
	/* to avoid the warning message for GHS and IAR: statement is unreachable*/
#if defined(__ghs__)
#pragma ghs nowarning 111
#endif
#if defined(__ICCARM__)
#pragma diag_suppress = Pe111
#endif
	return 0;
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

