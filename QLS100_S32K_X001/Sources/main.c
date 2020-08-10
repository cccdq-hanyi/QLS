/**===========================================================================*/
/* FILE		: main.c                                                            */
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

#define QLS_111		(1)
#define DO_CAN_STB_PORT	PTC
#define DO_CAN_STB		5U
volatile int exit_code = 0;

//#define CAN_Tx_Test (1)
#ifdef CAN_Tx_Test
uint8_t u8_canDataT[8] = {1, 2, 3, 4, 5, 6, 7, 8};
uint16_t u16_timerCnt = 0;
#endif


/*!
 \brief The main function for the project.
 \details The startup initialization sequence is the following:
 * - __start (startup asm routine)
 * - __init_hardware()
 * - main()
 *   - PE_low_level_init()
 *     - Common_Init()
 *     - Peripherals_Init()
 */

int main(void)
{
    /* Write your local variable definition here */
	/*** 测试临时变量 ***/
	static float rf_us_tof_level;
	static float rf_us_tof_concentra;
    static float rf_VBat = 0.0;
    static float rf_ult_temp = 0.0;
    static float rf_tmr_level = 0.0;
    static float rf_Velocity = 0.0,level = 0.0;
    static uint32_t r32u_tofcon = 0,r32u_toflevel = 0;

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
#ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT(); /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
#endif
    /*** End of Processor Expert internal initialization.                    ***/

    /* Initialize and configure clocks
     *     -   see clock manager component for details
     */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Initialize pins
     *    -   See PinSettings component for more info
     */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

//    /* Initialize LPSPI0 */
//    ret = LPSPI_DRV_SlaveInit(LPSPICOM1, &lpspiCom1State, &lpspiCom1_SlaveConfig0);

	Sys_Init();
	adsample_ADC_Init();
	spi_comm_Spi_Init();
//#ifdef QLS_111
//	PINS_DRV_ClearPins(	DO_CAN_STB_PORT, 	1 << DO_CAN_STB );//QLS_111:CAN_STB pull_down;
//#endif

    CAN_Comm_Init();
    FMSTR_Init();
    for(;;)
    {
		(void)u8_hw_wtd_reset();
    	FMSTR_Poll();

    	/**** spi_comm_Spi_Transfer,获得E703.15的TOF、温度数据 ******/
		if ( spi_comm_Spi_Transfer() )
		{
			runion_qls_results.members.ru8_temp_environment = ntc_calibration_cal_temp(results.members.temp_environment)+40;//spn 3515
			runion_qls_results.members.ru8_temp_ultrasonic = ntc_calibration_cal_temp(results.members.temp_ultrasonic)+40;//spn 3515
	/*    2020-7-21  close J1939 CAN function commented    */
//#ifdef CAN_Tx_Test
//				runion_qls_results.members.ru16_level--;
//				if ( runion_qls_results.members.ru16_level<=0 )
//				{
//					runion_qls_results.members.ru16_level = 65535;
//				}
//				runion_qls_results.members.ru8_concentration++;
//				if ( runion_qls_results.members.ru8_concentration>=255 )
//				{
//					runion_qls_results.members.ru8_concentration = 0;
//				}
//#else
//			rf_us_tof_level =  (float) results.members.tof_level / 1000000;
//			rf_us_tof_concentra =  (float) results.members.tof_concentration / 1000000;
//			sonic_velocity = get_AvgVelocity(rf_us_tof_concentra);
//        	tmp_ultrasonic = results.members.tof_level & 0xFFFF;
//        	runion_qls_results.members.ru16_level = cal_level(tmp_ultrasonic);
//        	tmp_concentration = results.members.tof_concentration & 0xFFFF;
//        	runion_qls_results.members.ru8_concentration = cal_concentration(tmp_concentration);
//#endif
		}

		/*** 1ms 检查刷新一次can通讯 ***/
		if (task_1ms_OK != 0)
		{
			task_1ms_OK = 0;
//			u8_task_AppMgt_1ms();
//			u8_comm_task(); //放在主循环周期不准，移到timer_1ms_isr()函数中运行

//#ifdef CAN_Tx_Test
//			u16_timerCnt++;
//			if ((u16_timerCnt >= 998))
//			{
//				u8_hw_CAN_Send(0x101, u8_canDataT, 8);
//				u16_timerCnt = 0;
//			}
//#endif
		}
		/*** 100ms计算一次 ***/
		if ( task_100ms_OK !=0 )
		{
			task_100ms_OK = 0;
			rf_us_tof_level =  (float) results.members.tof_level / 1000000;
			rf_us_tof_concentra =  (float) results.members.tof_concentration / 1000000;
			rf_Velocity = tof_capture_Get_AvgVelocity(rf_us_tof_concentra);
//			rf_VBat = adsample_Get_Voltage();
			rf_tmr_level = adsample_Get_TmrLevel();
			rf_ult_temp = adsample_Get_NTCTemp();
			adsample_Get_EnvirTemp();
		}
    }

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

/*!
 ** @}
 */

