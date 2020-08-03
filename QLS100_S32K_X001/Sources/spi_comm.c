/**===========================================================================*/
/* FILE		: spi_comm.c                                                             */
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
#include "spi_comm.h"
#include "lpspiCom1.h"
#include "common.h"


qls_results results;

/***************************************************************************************************
 * Function: spi_comm_Spi_Init
 * Discription: spi interface Initialize
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
void spi_comm_Spi_Init(void)
{
	uint8_t ret=0;
    /* Initialize LPSPI0 */
    ret = LPSPI_DRV_SlaveInit(LPSPICOM1, &lpspiCom1State, &lpspiCom1_SlaveConfig0);
    return;
}



/***************************************************************************************************
 * Function: spi_comm_Spi_Transfer
 * Discription: spi communicate ,get spi data from e703.15,use slave mode,e703.15 send tof data
 * 				every second
 * Param :
 * Return:
 * Note:
 ***************************************************************************************************/
uint8_t spi_comm_Spi_Transfer(void)
{
	uint8_t ru8_spi_comm_received = 0;
	uint8_t rs8_spiDataSend[sizeof(qls_results_members)];
    uint8_t rs8_spiDataReceive[sizeof(qls_results_members)];
	uint8_t ret = 0;
	memset(rs8_spiDataReceive,0x0,sizeof(rs8_spiDataReceive));
	rs8_spiDataSend[0] = 0x55;
	ret = LPSPI_DRV_SlaveTransferBlocking(LPSPICOM1, rs8_spiDataSend, rs8_spiDataReceive, SPI_BUFFER_SIZE, SPICOMM_TIMEOUT);
	if ((rs8_spiDataReceive[0] == 0xA5) && (rs8_spiDataReceive[1] == 0x5A))//±¨ÎÄÍ·0xA5¡¢0x5A
	{

		uint16_t tmp_ultrasonic,tmp_concentration;
		uint64_t tmp_level,tmp_concen;
		results.members.status = (rs8_spiDataReceive[3] << 8) + rs8_spiDataReceive[2];
		results.members.temp_ultrasonic = (rs8_spiDataReceive[5] << 8) + rs8_spiDataReceive[4];
		results.members.temp_environment = (rs8_spiDataReceive[7] << 8) + rs8_spiDataReceive[6];
		results.members.tof_concentration = (rs8_spiDataReceive[15] << 56) + (rs8_spiDataReceive[14] << 48) +
											(rs8_spiDataReceive[13] << 40) + (rs8_spiDataReceive[12] << 32) +
											(rs8_spiDataReceive[11] << 24) + (rs8_spiDataReceive[10] << 16) +
											(rs8_spiDataReceive[9] << 8) + rs8_spiDataReceive[8];
		results.members.tof_level = (rs8_spiDataReceive[23] << 56) + (rs8_spiDataReceive[22] << 48) +
									(rs8_spiDataReceive[21] << 40) + (rs8_spiDataReceive[20] << 32) +
									(rs8_spiDataReceive[19] << 24) + (rs8_spiDataReceive[18] << 16) +
									(rs8_spiDataReceive[17] << 8) + rs8_spiDataReceive[16];
		ru8_spi_comm_received = 1;
	}
	return ru8_spi_comm_received;
}

