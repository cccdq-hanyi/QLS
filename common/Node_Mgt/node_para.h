#ifndef _node_mbd_para_h
#define _node_mbd_para_h
#ifdef __cplusplus
extern "C"
{
#endif
#include <string.h>
#include "typedef_all.h"
#include "node_cfg.h"

#define subs_fixed (1)
#define subs_last (2)
#define Msg_Period (1)
#define Msg_Event (2)
#define Msg_PE (3)
#define node_msg_init (0)
#define node_msg_txing (1)
#define node_msg_txed (2)
#define node_msg_rxed (3)
#define node_msg_timeout (4)
#define comm_norm_tx_en (0x01)
#define comm_norm_rx_en (0x10)
	//Sig Mgt
	typedef struct
	{
		uint8_t subs_type;
		uint8_t def;
		uint8_t subs;
		uint8_t max;
		uint8_t min;
		uint8_t value;
	} u8_SigInfo_Struct;
	typedef struct
	{
		uint8_t subs_type;
		uint16_t def;
		uint16_t subs;
		uint16_t max;
		uint16_t min;
		uint16_t value;
	} u16_SigInfo_Struct;
	typedef struct
	{
		uint8_t subs_type;
		uint32_t def;
		uint32_t subs;
		uint32_t max;
		uint32_t min;
		uint16_t value;
	} u32_SigInfo_Struct;
	//CAN MSG
	typedef struct
	{
		uint32_t id;
		uint16_t period;
		uint8_t len;
		uint8_t type;
	} u8_Frame_Struct;
	enum ecu_msg_tx_name
	{
		Frame_Tx_1 = 0,
		Frame_Tx_2 = 1,
	};
	//Mesg Mgt
	typedef struct
	{
		/* data */
		uint8_t temperature2;
		uint8_t concentration;
		uint8_t reserve;
		uint8_t temperature2_pre;
		uint8_t properties_pre;
		uint8_t properties;
		uint8_t reserve2[2];
	} Signal1;
	typedef struct
	{
		/* data */
		uint8_t tank_level;
		uint8_t tank_temperature;
		uint16_t tank_level2;
		uint8_t tank_level_pre;
		uint8_t tank1_temperature_pre;
		uint8_t reserve2[2];
	} Signal2;
	typedef union {
		/* data */
		uint8_t Data[8];
		Signal1 Sigs1;
		Signal2 Sigs2;
	} MsgBuffer;
	typedef struct
	{
		uint32_t ID;
		uint16_t T;
		uint16_t Timer; //use for tx/rx period or timeout check
		uint8_t Msg_Type;
		uint8_t Counter;
		uint8_t Status;
		//use for rx set, 0->init, 1->rx, 2->timeout
		//use for tx set, 0->init, 1->tx
		uint8_t Len;
		uint8_t ComErr;
		uint8_t Event_tx_num;
		MsgBuffer Buffer;
	} msg_struct, *pmsg_struct;
//Bus Off Mgt
#ifdef BusOff_Support
#define BUSOFF (0x0C)
#define BusOff_cL1ToL2_Max (10)
#define BusOff_L2_Timer_Recover (1000)
#define BusOff_L1_Timer_Recover (100)
#define BusOff_MsgMonitor (1000)
#define Bus_Offline (0)
#define Bus_Resume (1)
#define Bus_Online (2)
	typedef struct
	{
		uint8_t u8_cL1ToL2;
		uint8_t u8_WaitRecover;
		uint8_t u8_State; //0->Bus_Offline, 1->Bus_Resume, 2->Bus_Online
		uint8_t u8_Flag;
		uint8_t u8_Flag_History;
		uint8_t u8_Flag_MsgMonitor;
		uint16_t u16_Cnt;
		uint16_t u16_Cnt_MsgMonitor;
	} busoff_struct;
#endif

//Voltage Mgt
#ifdef Voltage_Support
#define Voltage_Diag_Status (0)
#define Voltage_Norm_Status (1)
#define Voltage_Comm_Status (2)
#define Voltage_Diag_TimeStatus (3)
#define Voltage_Comm_Max (996)		   //26.5V
#define Voltage_Comm_MaxRecover (959)  //25.5
#define Voltage_Diag_Max (600)		   //16V
#define Voltage_Diag_Min (335)		   //9V
#define Voltage_Norm_High (600)		   //16V
#define Voltage_Norm_HighRecover (562) //15V
#define Voltage_Norm_LowRecover (370)  //10V
#define Voltage_Norm_Low (335)		   //9.0V
#define Voltage_Comm_MinRecover (260)  //7V
#define Voltage_Comm_Min (240)		   //6.5V
#define Voltage_Err_T (100)			   //100*5=500ms
	typedef struct
	{
		uint16_t u16_Cnt_BeyondCommMax;  //26.5
		uint16_t u16_Cnt_CommResume;	 //25.5-7.0
		uint16_t u16_Cnt_BeyondDiagMax;  //18
		uint16_t u16_Cnt_BeyondNormHigh; //16
		uint16_t u16_Cnt_Normal;		 //15-10
		uint16_t u16_Cnt_BelowNormLow;   //9
		uint16_t u16_Cnt_BelowDiagMin;   //8
		uint16_t u16_Cnt_BelowCommMin;   //6
		uint8_t u8_Flag_CommBelow;
		uint8_t u8_Flag_CommBeyond;
		uint8_t u8_Flag_CommResume;
		uint8_t u8_Flag_DiagBelow;
		uint8_t u8_Flag_DiagBeyond;
		uint8_t u8_Flag_NormResume;
		uint8_t u8_Flag_NormBelow;
		uint8_t u8_Flag_NormBeyond;
	} volt_struct;
#endif

	typedef struct
	{
		uint8_t run_status;
		uint8_t comm_status;
		uint8_t u8_Dcomm_status;
//local data->Bus Off data
#ifdef BusOff_Support
		busoff_struct busoff_Info;
#endif
//local data->Under/Over voltage data
#ifdef Voltage_Support
		volt_struct volt_info;
#endif
		//local data->default value and Substitute value
		//PGN64923
		u8_SigInfo_Struct Frame_Tx_1_Temp;		 //SPN3515
		u8_SigInfo_Struct Frame_Tx_1_Conc;		 //SPN3516
		u8_SigInfo_Struct Frame_Tx_1_Temp_Pre;   //SPN3519
		u8_SigInfo_Struct Frame_Tx_1_Proper_Pre; //SPN3520
		u8_SigInfo_Struct Frame_Tx_1_Property;   //SPN3521
		//PGN65110
		u8_SigInfo_Struct Frame_Tx_2_Tank_Lev;		//SPN1761
		u8_SigInfo_Struct Frame_Tx_2_Tank_Temp;		//SPN3031
		u16_SigInfo_Struct Frame_Tx_2_Tank_Lev2;	//SPN3517
		u8_SigInfo_Struct Frame_Tx_2_Tank_Lev_Pre;  //SPN3532
		u8_SigInfo_Struct Frame_Tx_2_Tank_Temp_Pre; //SPN4365
#if (ecu_msg_tx_num > 0)
		msg_struct msg_tx_ecu[ecu_msg_tx_num];
#endif
#if (ecu_msg_rx_num > 0)
		msg_struct msg_rx_ecu[ecu_msg_rx_num];
#endif
	} node_info_struct;

	extern node_info_struct node_info;

#ifdef __cplusplus
}
#endif
#endif
