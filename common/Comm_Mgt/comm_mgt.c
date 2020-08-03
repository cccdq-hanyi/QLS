#include "comm_mgt.h"

uint8_t u8_comm_init(void)
{
	u8_int_Init();
	u8_cancomm_Init();
	return 0;
}

uint8_t u8_comm_task(void)
{
	static uint16_t timerCnt;
	timerCnt += comm_task_period;
	if (0 == (timerCnt % int_task_period))
	{
		u8_int_task();
		timerCnt = 0;
	}
	return 0;
}
//call by application layer
uint8_t u8_comm_MsgStatus_Get(uint32_t id)
{
#if (ecu_msg_rx_num > 0)
	pmsg_struct Pmsg = &(node_info.msg_rx_ecu[0]);
	switch (id)
	{
	case (Frame_Rx_1_ID):
		Pmsg = &(node_info.msg_rx_ecu[0]);
		break;
	default:
		return 0;
		break;
	}
	if (node_msg_timeout == Pmsg->Status)
	{
		return 1;
	}
#endif
	return 0;
}
uint8_t u8_comm_TxRx_Set(uint8_t type)
{
	node_info.comm_status = type;
	return 0;
}
uint8_t u8_comm_TxRx_Get(void)
{
	return node_info.comm_status;
}
uint8_t u8_comm_TxReset(void)
{
	uint8_t i = 0;
	pmsg_struct Pmsg;
	for (i = 0; i < ecu_msg_tx_num; i++)
	{
		Pmsg = &(node_info.msg_tx_ecu[i]);
		//time set
		Pmsg->Timer = Pmsg->T; //when set T, the frame would be txed next period
	}
	return 0;
}
uint8_t u8_comm_TxAfterT(uint16_t timeDelay)
{
	uint8_t i = 0;
	pmsg_struct Pmsg;
	for (i = 0; i < ecu_msg_tx_num; i++)
	{
		//msg type check
		Pmsg = &(node_info.msg_tx_ecu[i]);
		//time set
		timeDelay = (timeDelay % Pmsg->T);
		Pmsg->Timer = Pmsg->T - timeDelay;
	}
	return 0;
}
