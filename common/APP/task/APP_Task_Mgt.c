#include "App_Task_Mgt.h"
#include "..\..\RTE\RTE_interface.h"
#include <string.h>

//task mgt

//--------------------------------------------------------------------------------------------------
//																									|
//--------------------------------------------------------------------------------------------------
static uint8_t u8_task_Write_CanSigs(void)
{
	uint8_t val = 0;
	u8_rte_Write_PGN64923_SPN3515(val);
	u8_rte_Write_PGN64923_SPN3516(val);
	u8_rte_Write_PGN64923_SPN3519(val);
	u8_rte_Write_PGN64923_SPN3520(val);
	u8_rte_Write_PGN64923_SPN3521(val);
	u8_rte_Write_PGN65110_SPN1761(val);
	u8_rte_Write_PGN65110_SPN3031(val);
	u8_rte_Write_PGN65110_SPN3517(val);
	u8_rte_Write_PGN65110_SPN3532(val);
	u8_rte_Write_PGN65110_SPN4365(val);
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
