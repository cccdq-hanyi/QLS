#include "node_para.h"

node_info_struct node_info;

const u8_Frame_Struct FrameTx[ecu_msg_tx_num] = {
	{Frame_Tx_1_ID, Frame_Tx_1_T, Frame_Tx_1_Len, Frame_Tx_1_Type},
	{Frame_Tx_2_ID, Frame_Tx_2_T, Frame_Tx_2_Len, Frame_Tx_2_Type},
};
/*
local data->default value and Substitute value
*/
static uint8_t u8_node_CANDB_Init(void)
{
	node_info.Frame_Tx_1_Temp.def = 0;
	node_info.Frame_Tx_1_Temp.subs = 0;
	node_info.Frame_Tx_1_Temp.subs_type = subs_last;
	node_info.Frame_Tx_1_Temp.min = 0;
	node_info.Frame_Tx_1_Temp.max = 255; //Offset = -40c

	node_info.Frame_Tx_1_Conc.def = 0;
	node_info.Frame_Tx_1_Conc.subs = 0;
	node_info.Frame_Tx_1_Conc.subs_type = subs_last;
	node_info.Frame_Tx_1_Conc.min = 0;
	node_info.Frame_Tx_1_Conc.max = 255;

	node_info.Frame_Tx_1_Temp_Pre.def = 0;
	node_info.Frame_Tx_1_Temp_Pre.subs = 0;
	node_info.Frame_Tx_1_Temp_Pre.subs_type = subs_last;
	node_info.Frame_Tx_1_Temp_Pre.min = 0;
	node_info.Frame_Tx_1_Temp_Pre.max = 31;

	node_info.Frame_Tx_1_Proper_Pre.def = 0;
	node_info.Frame_Tx_1_Proper_Pre.subs = 0;
	node_info.Frame_Tx_1_Proper_Pre.subs_type = subs_last;
	node_info.Frame_Tx_1_Proper_Pre.min = 0;
	node_info.Frame_Tx_1_Proper_Pre.max = 31;

	node_info.Frame_Tx_1_Property.def = 0;
	node_info.Frame_Tx_1_Property.subs = 0;
	node_info.Frame_Tx_1_Property.subs_type = subs_last;
	node_info.Frame_Tx_1_Property.min = 0;
	node_info.Frame_Tx_1_Property.max = 15;

	node_info.Frame_Tx_2_Tank_Lev.def = 0;
	node_info.Frame_Tx_2_Tank_Lev.subs = 0;
	node_info.Frame_Tx_2_Tank_Lev.subs_type = subs_last;
	node_info.Frame_Tx_2_Tank_Lev.min = 0;
	node_info.Frame_Tx_2_Tank_Lev.max = 255;

	node_info.Frame_Tx_2_Tank_Temp.def = 0;
	node_info.Frame_Tx_2_Tank_Temp.subs = 0;
	node_info.Frame_Tx_2_Tank_Temp.subs_type = subs_last;
	node_info.Frame_Tx_2_Tank_Temp.min = 0;
	node_info.Frame_Tx_2_Tank_Temp.max = 255;

	node_info.Frame_Tx_2_Tank_Lev2.def = 0;
	node_info.Frame_Tx_2_Tank_Lev2.subs = 1;
	node_info.Frame_Tx_2_Tank_Lev2.subs_type = subs_last;
	node_info.Frame_Tx_2_Tank_Lev2.min = 0;
	node_info.Frame_Tx_2_Tank_Lev2.max = 0xFFFF;

	node_info.Frame_Tx_2_Tank_Lev_Pre.def = 0;
	node_info.Frame_Tx_2_Tank_Lev_Pre.subs = 1;
	node_info.Frame_Tx_2_Tank_Lev_Pre.subs_type = subs_last;
	node_info.Frame_Tx_2_Tank_Lev_Pre.min = 0;
	node_info.Frame_Tx_2_Tank_Lev_Pre.max = 31;

	node_info.Frame_Tx_2_Tank_Temp_Pre.def = 0;
	node_info.Frame_Tx_2_Tank_Temp_Pre.subs = 0;
	node_info.Frame_Tx_2_Tank_Temp_Pre.subs_type = subs_last;
	node_info.Frame_Tx_2_Tank_Temp_Pre.min = 0;
	node_info.Frame_Tx_2_Tank_Temp_Pre.max = 31;
	return 0;
}
static uint8_t u8_node_SigInfo_Init(void)
{
	(void)u8_node_CANDB_Init();
	return 0;
}
/*
local data->Lost communication data
*/
static uint8_t u8_node_Comm_init(void)
{
//tx msg init
#if (ecu_msg_tx_num > 0)
	uint8_t i, j;
	for (i = 0; i < ecu_msg_tx_num; i++)
	{
		node_info.msg_tx_ecu[i].ID = FrameTx[i].id;
		node_info.msg_tx_ecu[i].T = FrameTx[i].period;
		node_info.msg_tx_ecu[i].Len = FrameTx[i].len;
		node_info.msg_tx_ecu[i].Msg_Type = FrameTx[i].type;
		node_info.msg_tx_ecu[i].Status = node_msg_init;
		node_info.msg_tx_ecu[i].Timer = 0;
		node_info.msg_tx_ecu[i].Counter = 0;
		for (j = 0; j < 8; j++)
		{
			node_info.msg_tx_ecu[i].Buffer.Data[j] = 0xFF;
		}
	}
#endif
	//enabe tx and rx
	node_info.comm_status = (comm_norm_tx_en | comm_norm_rx_en);
	node_info.u8_Dcomm_status = (comm_norm_tx_en | comm_norm_rx_en);
	return 0;
}

/*
local data->Bus Off data
*/
static uint8_t u8_node_BusOff_Init(void)
{
#ifdef BusOff_Support
	(void)memset(&node_info.busoff_Info, 0, sizeof(node_info.busoff_Info));
	node_info.busoff_Info.u8_State = Bus_Online;
#endif
	return 0;
}
/*
local data->Under/Over voltage data
*/
static uint8_t u8_node_VoltMgt_Init(void)
{
#ifdef Voltage_Support
	(void)memset(&node_info.volt_info, 0, sizeof(node_info.volt_info));
	node_info.volt_info.u8_Flag_CommResume = 1;
	node_info.volt_info.u8_Flag_NormResume = 1;
#endif
	return 0;
}

uint8_t u8_node_ParaInit(void)
{
	(void)memset(&node_info, 0, sizeof(node_info));
	(void)u8_node_SigInfo_Init();
	(void)u8_node_Comm_init();
	(void)u8_node_BusOff_Init();
	(void)u8_node_VoltMgt_Init();
	return 0;
}
