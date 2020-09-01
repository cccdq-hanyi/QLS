#include "Int_interface.h"

//COMMON INTERFACE

uint8_t u8_int_Write_PGN64923_message(uint8_t *data,uint8_t len)
{
	msg_struct *Pmsg;
	uint8_t writelen = len > 8 ? 8 : len;
	uint8_t i;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_1];
	for (i=0;i<len;i++)
	{
		Pmsg->Buffer.Data[i] = data[i];
	}
	return 0;
}

uint8_t u8_int_Write_PGN65110_message(uint8_t *data,uint8_t len)
{
	msg_struct *Pmsg;
	uint8_t writelen = len > 8 ? 8 : len;
	uint8_t i;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_2];
	for (i=0;i<len;i++)
	{
		Pmsg->Buffer.Data[i] = data[i];
	}
	return 0;
}
//read normal msg ----------------------------------------------------------------------------------
//write normal msg ---------------------------------------------------------------------------------
uint8_t u8_int_Write_PGN64923_SPN3515(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_1];
	Pmsg->Buffer.Sigs1.temperature2 = val;
	return 0;
}
uint8_t u8_int_Write_PGN64923_SPN3516(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_1];
	Pmsg->Buffer.Sigs1.concentration = val;
	return 0;
}
uint8_t u8_int_Write_PGN64923_SPN3519(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_1];
	Pmsg->Buffer.Sigs1.temperature2_pre = 0xE0 | (val & 0x1F);
	return 0;
}
uint8_t u8_int_Write_PGN64923_SPN3520(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_1];
	Pmsg->Buffer.Sigs1.properties_pre = 0xE0 | (val & 0x1F);
	return 0;
}
uint8_t u8_int_Write_PGN64923_SPN3521(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_1];
	Pmsg->Buffer.Sigs1.properties = 0xF0 | (val & 0xF);
	return 0;
}
/**
 * range:0-100, bit/0.4
 * */
uint8_t u8_int_Write_PGN65110_SPN1761(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_2];
	Pmsg->Buffer.Sigs2.tank_level = val;
	return 0;
}
uint8_t u8_int_Write_PGN65110_SPN3031(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_2];
	Pmsg->Buffer.Sigs2.tank_temperature = val;
	return 0;
}
uint8_t u8_int_Write_PGN65110_SPN3517(uint16_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_2];
	Pmsg->Buffer.Sigs2.tank_level2 = val;
	return 0;
}
uint8_t u8_int_Write_PGN65110_SPN3532(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_2];
	Pmsg->Buffer.Sigs2.tank_level_pre = 0xE0 | (val & 0x1F);
	return 0;
}
uint8_t u8_int_Write_PGN65110_SPN4365(uint8_t val)
{
	msg_struct *Pmsg;
	Pmsg = &node_info.msg_tx_ecu[Frame_Tx_2];
	Pmsg->Buffer.Sigs2.tank1_temperature_pre = 0xE0 | (val & 0x1F);
	return 0;
}
//INT interface---------------------------------------------------------------------------
uint8_t u8_int_ReadTxMsgState(void)
{
	return IntInfo.u8_msgStatus;
}
uint8_t u8_int_Init(void)
{
	IntInfo.u8_msgStatus = int_msg_init;
	return 0;
}
//call by system back server in highest priority
static uint8_t u8_int_FrameRx(void)
{
#if (ecu_msg_rx_num > 0)
	uint8_t i;
	pmsg_struct Pmsg;
//offline and resume check
#ifdef BusOff_Support
	if (Bus_Online != u8_node_BusStatus_Check())
		return 0;
#endif
	//comm enable check
	if (!(node_info.comm_status & comm_norm_rx_en))
		return 1;
	//rx msg timeout check
	for (i = 0; i < ecu_msg_rx_num; i++)
	{
		Pmsg = &(node_info.msg_rx_ecu[i]);
		Pmsg->Timer += int_task_period;
		if (Msg_Event == Pmsg->Msg_Type)
		{
			if (0 == Pmsg->Counter)
				continue;
			if (Pmsg->Timer > event_msg_timeout)
			{
				Pmsg->Counter = 0;
				Pmsg->Timer = 0;
			}
			continue;
		}
		if (Pmsg->T <= 50)
		{
			if (Pmsg->Timer >= 250)
			{
				Pmsg->Timer = 250;
				Pmsg->Status = node_msg_timeout;
			}
		}
		else
		{
			if (Pmsg->Timer >= 5 * Pmsg->T)
			{
				Pmsg->Timer = 5 * Pmsg->T;
				Pmsg->Status = node_msg_timeout;
			}
		}
	}
#endif
	return 0;
}
static uint8_t u8_int_FrameTx(void)
{
	uint8_t i = 0;
	pmsg_struct Pmsg;
#ifdef BusOff_Support
	busoff_struct *BusOffT;
	//can bus info update...
	BusOffT = &(node_info.busoff_Info);
	if (Bus_Offline == BusOffT->u8_State)
		return 4;
#endif
#ifdef Voltage_Support
	if (0 != u8_node_VbatStatus_Check(Voltage_Comm_Status))
		return 1;
#endif
	//avoid timer not true when disable tx
	if ((0 == (node_info.comm_status & comm_norm_tx_en)))
		return 2;
	//frame insert into dll queue
	for (i = 0; i < ecu_msg_tx_num; i++)
	{
		Pmsg = &(node_info.msg_tx_ecu[i]);
		//period update
		Pmsg->Timer += int_task_period;
		if (Pmsg->Timer >= Pmsg->T)
		{
			Pmsg->Timer = 0;
			//update tx status
			Pmsg->Status = node_msg_txing;
			(void)u8_cancomm_TxCall(Pmsg->ID, Pmsg->Buffer.Data, Pmsg->Len);
		}
	}
	(void)u8_cancomm_TxOneFrame();
	return 0;
}
uint8_t u8_int_task(void)
{
	uint8_t i, j;
	//init data set
	if ((int_msg_init == IntInfo.u8_msgStatus))
	{
		for (i = 0; i < ecu_msg_tx_num; i++)
		{
			for (j = 0; j < 8; j++)
			{
				node_info.msg_tx_ecu[i].Buffer.Data[j] = 0xFF; //default is 1, not avaliable or not request
			}
		}
	}
	//tx frame check
	u8_int_FrameTx();
	//rx frame check
	u8_int_FrameRx();
	return 0;
}
uint8_t u8_int_TxCallback(uint32_t id, uint8_t *data, uint8_t len)
{
	uint8_t i;
	switch (id)
	{
	case (Frame_Tx_1_ID):
		i = 0;
		break;
	case (Frame_Tx_2_ID):
		i = 1;
		break;
	default:
		return 0;
		break;
	}
	IntInfo.u8_msgStatus = int_msg_txed;
	node_info.msg_tx_ecu[i].Status = node_msg_txed;
	return 0;
}
uint8_t u8_int_RxCallback(uint32_t id, uint8_t *data, uint8_t len)
{
#if (ecu_msg_rx_num > 0)
	uint8_t j = 0;
	pmsg_struct Pmsg = &(node_info.msg_rx_ecu[0]);
	//valid can id check
	switch (id)
	{
	case (ACU_10_B_ID):
		Pmsg = &(node_info.msg_rx_ecu[ACU_10_B]);
		break;
	default:
		break;
	}
	for (j = 0; j < Pmsg->Len; j++)
	{
		Pmsg->Data[j] = data[j];
	}
	Pmsg->Timer = 0;
	if (Msg_Event == Pmsg->Msg_Type)
	{
		Pmsg->Counter++;
		if (Pmsg->Counter >= event_msg_valid_num)
		{
			Pmsg->Counter = 0;
			Pmsg->Status = node_msg_rxed;
		}
	}
	else
	{
		Pmsg->Status = node_msg_rxed;
	}
#endif
	return 0;
}
