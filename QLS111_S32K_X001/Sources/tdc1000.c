/**===========================================================================*/
/* FILE		: tdc1000.c                                                            */
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
/*    V0.1       2020/07/31         Initial Version              Cdq   */
/*============================================================================*/
//#include "pins_driver.h"
#include "common.h"
#include "tdc1000.h"
//#include "tof_capture.h"



void delay(volatile int cycles)
{
  /* Delay function - do nothing for a number of cycles */
  while(cycles--);
}

/***************************************************************************************************
 * Function: tdc1000_Write_TDC
 * Discription: write data to tdc1000 through spi interface
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void tdc1000_Write_TDC(uint8_t addr, uint8_t data)
{
	uint8_t spiDataSend[2];
	uint8_t spiDataReceive[2];
	uint8_t ret = 0;
	spiDataSend[1] = WRITE_CMD_MASK | (0x0F & addr);
	spiDataSend[0] = data;
	ret = LPSPI_DRV_MasterTransferBlocking (LPSPICOM1, spiDataSend, spiDataReceive, 2 , SPICOMM_TIMEOUT);

	return ;
}


/***************************************************************************************************
 * Function: tdc1000_Read_TDC
 * Discription: read data from tdc1000 through spi interface
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
uint8_t tdc1000_Read_TDC(uint8_t addr)
{
	uint8_t spiDataSend[2];
	uint8_t spiDataReceive[2];
	uint8_t ret = 0;
	spiDataSend[1] = READ_CMD_MASK & (0x0F & addr);
	spiDataSend[0] = 0;
	ret = LPSPI_DRV_MasterTransferBlocking(LPSPICOM1, spiDataSend, spiDataReceive, 2, SPICOMM_TIMEOUT);
	if ( ret == STATUS_SUCCESS)
		return spiDataReceive[0];
	else
		return 0;

}

/***************************************************************************************************
 * Function: tdc1000_Reg_Init
 * Discription: Initialize tdc1000 registers
 * Param :
 * Return:
 * Note:  π”√channel 1
 ***************************************************************************************************/
void tdc1000_Reg_Init(void)
{
	tdc1000_Write_TDC(REG_CONFIG0,0x44); 	// bit 7-4:Frequency Divide by 32
											// bit 3-0:4 pulses
	tdc1000_Write_TDC(REG_CONFIG1,0x41);	// bit 7-6:reserve
											// bit 5-3:1 measurement cycle
											// bit 2-0:1 event (1 STOP pulse output)
	tdc1000_Write_TDC(REG_CONFIG2,0x04);	// bit 7:Common-mode voltage reference control:0h: Internal
											// bit 6:AFE measurement type:0h: Time-of-flight measurement (default)
											// bit 5:TX burst damping:0h: Disable damping (default)
											// bit 4: Automatic channel swap in Mode 2 :0h: Disable automatic channel swap
											// bit 3:External channel select by CHSEL pin:0h: Disable external channel select (default).
											// bit 2:Active TX/RX channel pair:1h:	channel 2
											// bit 1-0:Time-of-flight measurement mode:0h:Mode 0
//	tdc1000_Write_TDC(REG_CONFIG3,0x0C);	// bit 3:1h: Enable power blanking
	tdc1000_Write_TDC(REG_CONFIG3,0x0E);	// bit 3:1h: Enable power blanking
											// bit 2-0:4h: -220 mV
	tdc1000_Write_TDC(REG_CONFIG4,0x5F);	// bit 6:1h: Receive multi echo
											// bit 5-0:1Fh:TX 180°„ pulse shift position 31 (default)
	tdc1000_Write_TDC(REG_TOF1,0xE0);		// bit7-5: PGA gain 21dB
//	tdc1000_Write_TDC(REG_TOF1,0xA0);		// bit7-5: PGA gain 15dB
											// bit4: PGA active
											// bit3: LNA active
											// bit2: LNA Capacitive feedback
											// bit1-0: TIMING_REG[9:8]
	tdc1000_Write_TDC(REG_TOF0,0x1E);		// TIMING_REG[7:0] // wait listen time = (TIMING_REG-30)*8*T0
	tdc1000_Write_TDC(REG_ERROR_FLAG,0x01);	// reset errors flags
	tdc1000_Write_TDC(REG_TIMEOUT,0x27);
	//tdc1000_Write_TDC(REG_TIMEOUT,0x23);	//bit 5-3:Short time-of-flight blanking period :4h:128*T0
											//bit 1-0:3h:Echo listening window timeout 1024*T0
	tdc1000_Write_TDC(REG_CLOCK_RATE,0x01);	//bit 1-0:Receiver auto-zero period:1h:128 * T0

	return;
}

/***************************************************************************************************
 * Function: tdc1000_Init
 * Discription:  tdc1000 initiate
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
uint8_t tdc1000_Init(void)
{
	uint8_t reg0 = 0;
	uint8_t reg1 = 0;
	uint8_t ret = 1;
	PINS_DRV_SetPins( DO_TDC_EN_PORT, 1 <<	DO_TDC_EN );
	PINS_DRV_SetPins( DO_TDC_RESET_PORT, 	1 << DO_TDC_RESET );

	PINS_DRV_ClearPins(	DO_TDC_TRIGGER_PORT, 	1 << DO_TDC_TRIGGER );
	PINS_DRV_ClearPins(	DO_TDC_RESET_PORT, 	1 << DO_TDC_RESET );

	tdc1000_Reg_Init();

	//test tdc1000
	reg0 = tdc1000_Read_TDC( REG_CONFIG1 );
	reg1 = tdc1000_Read_TDC( REG_CONFIG4 );
	if ((reg0 != 0x40) && (reg1 != 0x5F))
		ret = 0; //error
	return ret;
}

/***************************************************************************************************
 * Function: tdc1000_Trig_Ch_Hv
 * Discription:  trigger tdc1000 high voltage channel
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void tdc1000_Trig_Ch_Hv(void)
{
	if ( 0 )
		return;
	tdc1000_clear_errflg();
	tdc1000_Write_TDC(REG_CONFIG2,0x00);
	PINS_DRV_SetPins( DO_HV_PWR_EN_PORT, 1 <<	DO_HV_PWR_EN );
	delay(2U);
	PINS_DRV_SetPins( DO_TDC_TRIGGER_PORT, 1 <<	DO_TDC_TRIGGER );
	//delay(1U);
	PINS_DRV_ClearPins( DO_TDC_TRIGGER_PORT, 1 <<	DO_TDC_TRIGGER );
	delay(10U);
	PINS_DRV_ClearPins( DO_HV_PWR_EN_PORT, 1 <<	DO_HV_PWR_EN );
	return;
}

/***************************************************************************************************
 * Function: tdc1000_Trig_Ch_Lv
 * Discription:  trigger tdc1000 low voltage channel
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void tdc1000_Trig_Ch_Lv(void)
{
	tdc1000_clear_errflg();
	tdc1000_Write_TDC(REG_CONFIG2,0x04);
	PINS_DRV_SetPins( DO_TDC_TRIGGER_PORT, 1 <<	DO_TDC_TRIGGER );
	//delay(1U);
	PINS_DRV_ClearPins( DO_TDC_TRIGGER_PORT, 1 <<	DO_TDC_TRIGGER );

	return;
}

/***************************************************************************************************
 * Function: tdc1000_read_errflg
 * Discription:  read tdc1000 error flag
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
uint8_t tdc1000_read_errflg(void)
{
	return tdc1000_Read_TDC(REG_ERROR_FLAG);
}

/***************************************************************************************************
 * Function: tdc1000_read_errflg
 * Discription:  clear  tdc1000  error flag
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void tdc1000_clear_errflg(void)
{
	tdc1000_Write_TDC(REG_ERROR_FLAG,0x01);
}
