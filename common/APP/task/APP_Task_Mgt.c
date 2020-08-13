#include "App_Task_Mgt.h"
#include "..\..\RTE\RTE_interface.h"
#include <string.h>
#include "common.h"
//task mgt

//--------------------------------------------------------------------------------------------------
//																									|
//--------------------------------------------------------------------------------------------------
static uint8_t u8_task_Write_CanSigs(void)
{
	uint8_t val = 0;
	uint8_t can_concen,can_temp;
	u8_rte_Write_PGN64923_SPN3515(sendresults.members.ru8_temp_ultrasonic);//temp_con 1¡£C/bit -40¡£C offset
	u8_rte_Write_PGN64923_SPN3516(sendresults.members.ru8_concentration);//concen 0.25%/bit 0% offset
	u8_rte_Write_PGN64923_SPN3519(val);//FMI
	u8_rte_Write_PGN64923_SPN3520(val);//FMI
	u8_rte_Write_PGN64923_SPN3521(val);//catalyst reagent type
	u8_rte_Write_PGN65110_SPN1761(val);//not used?
	u8_rte_Write_PGN65110_SPN3031(sendresults.members.ru8_temp_ultrasonic);//temp_con
	u8_rte_Write_PGN65110_SPN3517(sendresults.members.ru16_level);//level 0.1mm/bit 0 offset
	u8_rte_Write_PGN65110_SPN3532(val);//FMI
	u8_rte_Write_PGN65110_SPN4365(val);//FMI
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
