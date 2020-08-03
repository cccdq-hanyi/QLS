#include "..\..\Node_Mgt\node_interface.h"
#include "..\comm_mgt.h"
#include "..\..\HW_Driver\hw_abstract.h"

#ifdef BusOff_Support
//Bus Off Mgt
uint8_t u8_node_BusStatus_Check(void)
{
	busoff_struct *BusOffT;
	BusOffT = &(node_info.busoff_Info);
	return BusOffT->u8_State;
}
uint8_t u8_node_BusOff_Check(void)
{
	busoff_struct *BusOffT;
	BusOffT = &(node_info.busoff_Info);
	return (1 == BusOffT->u8_Flag) ? Bus_Offline : Bus_Online;
}
//call by application layer
uint8_t u8_node_BusOff_Clear(void)
{
	busoff_struct *BusOffT;
	BusOffT = &(node_info.busoff_Info);
	BusOffT->u8_Flag = 0;
	BusOffT->u8_Flag_History = 0;
	BusOffT->u8_cL1ToL2 = 0;
	return 0;
}
/*
	use for tx one frame after bus off.
*/
uint8_t u8_node_BusOff_Resume(void)
{
	pmsg_struct Pmsg;
	//vbat low, no frame aollowed to tx
	if (0 != u8_node_VbatStatus_Check(Voltage_Comm_Status))
		return 0;
	//local sleep, no frame aollowed to tx
	if ((0 == (node_info.comm_status & comm_norm_tx_en)))
		return 0;
	//check if no frame tx
	if (0 == ecu_msg_tx_num)
		return 0;
	//tx only one frame at once
	Pmsg = &(node_info.msg_tx_ecu[0]);
	Pmsg->Timer = 0;
	//update tx status
	Pmsg->Status = node_msg_txing;
	return u8_cancomm_TxDirect(Pmsg->ID, Pmsg->Data, Pmsg->Len);
}
/**
* @brief update bus off state
* @author ihr
* @param[in] void
* @return busoff state
* @retval uint8
*/
//call by system back server in highest priority
uint8_t u8_node_BusOff_Mgt(void)
{
	busoff_struct *BusOffT;
	BusOffT = &(node_info.busoff_Info);
	if (Bus_Online == BusOffT->u8_State)
		return Bus_Online;
	if (Bus_Offline == BusOffT->u8_State)
	{
		//use for bus off recovery communication
		BusOffT->u16_Cnt_MsgMonitor = 0;
		BusOffT->u8_Flag_MsgMonitor = 1;
		if (BusOffT->u8_cL1ToL2 <= BusOff_cL1ToL2_Max)
		{
			if (BusOffT->u16_Cnt < BusOff_L1_Timer_Recover)
			{
				BusOffT->u16_Cnt++;
			}
			else
			{
				BusOffT->u16_Cnt = 0;
				BusOffT->u8_WaitRecover = 0;
			}
		}
		else
		{
			BusOffT->u8_Flag = 1;
			BusOffT->u8_Flag_History = 0;
			if (BusOffT->u16_Cnt < BusOff_L2_Timer_Recover)
			{
				BusOffT->u16_Cnt++;
			}
			else
			{
				BusOffT->u16_Cnt = 0;
				BusOffT->u8_WaitRecover = 0;
			}
		}
	}
	else
	{
		BusOffT->u8_cL1ToL2 = 0;
		BusOffT->u16_Cnt = 0;
		BusOffT->u8_WaitRecover = 0;
		if (BusOffT->u16_Cnt_MsgMonitor < BusOff_MsgMonitor)
		{
			BusOffT->u16_Cnt_MsgMonitor++;
			BusOffT->u8_State = Bus_Resume;
		}
		else
		{
			if (1 == BusOffT->u8_Flag)
			{
				BusOffT->u8_Flag = 0;
				BusOffT->u8_Flag_History = 1;
			}
			BusOffT->u8_Flag_MsgMonitor = 0;
			BusOffT->u8_State = Bus_Online;
		}
	}
	return (BusOffT->u8_State);
}

/**
* @brief recovery from bus off
* @author ihr
* @param[in] void
* @return void
*/
//call by CAN ERR CALLBACK
uint8_t u8_busoff_Cnt2 = 0;
static void v_node_BusOff_Recovery(void)
{
	uint8_t ERR_Status;
	busoff_struct *BusOffT;

	BusOffT = &(node_info.busoff_Info);
	//get the last one tx msg锛� cancel required by geely network management
	// (void)u8_cancomm_GetLastTxFrame(&BusOff_frame_id, BusOff_frame_data, &BusOff_frame_len);
resume_recovery:
	u8_busoff_Cnt2++;
	//clear tx queue, done by Init
	//reset bus off state, done by Init
	BusOffT->u8_State = Bus_Offline;
	BusOffT->u8_WaitRecover = 1;
	BusOffT->u8_cL1ToL2++;
	u8_hw_isr_disable();
	// (void)u8_cancomm_Init();//without reset tx buffer
	(void)u8_cancomm_Init(); //reset tx buffer
	u8_hw_isr_enable();
	//State change in api interrupt
	while (1 == BusOffT->u8_WaitRecover)
	{
		u8_hw_wtd_reset();
	}
	(void)u8_node_TxAppReset();
	//u8_cancomm_TxCall
	//cancel tx last frame, required by geely network management
	// ERR_Status = u8_hw_CAN_Tx(BusOff_frame_id, BusOff_frame_data, BusOff_frame_len);
	//tx one app frame after bus off resume
	ERR_Status = u8_node_BusOff_Resume();
	if (0 != ERR_Status)
	{
		goto resume_recovery;
	}
}
#endif

uint8_t u8_can_CANErr_Callback(uint8_t ErrCode)
{
#ifdef BusOff_Support
	if ((ErrCode & BUSOFF) == BUSOFF)
	{
		v_node_BusOff_Recovery();
	}
/* CLEAR flags */
//done by hardware driver
#endif
	return 0;
}
