#include "App_Task_Mgt.h"
#include "..\..\RTE\RTE_interface.h"
#include <string.h>
#include "common.h"
//task mgt
extern float rf_Velocity;
//--------------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------------
static uint8_t u8_task_Write_CanSigs(void)
{
//	uint8_t val = 0;
//	uint8_t can_concen,can_temp;
//	u8_rte_Write_PGN64923_SPN3515(sendresults.members.ru8_temp_ultrasonic);//temp_con 1¡£C/bit -40¡£C offset
//	u8_rte_Write_PGN64923_SPN3516(sendresults.members.ru8_concentration);//concen 0.25%/bit 0% offset
//	u8_rte_Write_PGN64923_SPN3519(val);//FMI
//	u8_rte_Write_PGN64923_SPN3520(val);//FMI
//	u8_rte_Write_PGN64923_SPN3521(val);//catalyst reagent type
//	u8_rte_Write_PGN65110_SPN1761(val);//not used?
//	u8_rte_Write_PGN65110_SPN3031(sendresults.members.ru8_temp_ultrasonic);//temp_con
//	u8_rte_Write_PGN65110_SPN3517(sendresults.members.ru16_level);//level 0.1mm/bit 0 offset
//	u8_rte_Write_PGN65110_SPN3532(val);//FMI
//	u8_rte_Write_PGN65110_SPN4365(val);//FMI
	uint8_t senddata[8];
	uint8_t *vp=(uint8_t *)&rf_Velocity;
	senddata[0] = sendresults.members.ru8_temp_ultrasonic;
	senddata[1] = sendresults.members.ru8_concentration;
	senddata[2] = sendresults.members.ru16_level & 0xff;
	senddata[3] = sendresults.members.ru16_level >> 8;
	senddata[4] = *vp++;
	senddata[5] = *vp++;
	senddata[6] = *vp++;
	senddata[7] = *vp;
	u8_int_Write_PGN64923_message(senddata,sizeof(senddata));
	return 0;
}

//--------------------------------------------------------------------------------------------------
//call by back server T=1ms																			|
//--------------------------------------------------------------------------------------------------
uint8_t u8_task_AppMgt_1ms(void)
{
	if (0 != u8_rte_ReadTxMsgState())
	{
		(void)u8_task_Write_CanSigs();
	}
	return 0;
}

uint8_t u8_task_AppInit(void)
{
	return 0;
}
