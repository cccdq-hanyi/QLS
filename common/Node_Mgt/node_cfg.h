#ifndef _node_cfg_h
#define _node_cfg_h
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * task schdule define
 * */
#define node_task_period (1) //Reserved
#define int_task_period (1)
#define comm_task_period (1)
//tx normal msg
#define ecu_msg_tx_num (2)
//rx normal msg
#define ecu_msg_rx_num (0)
//PGN64923
#define Frame_Tx_1_ID (0x18FD9BA3) //(P<<24)|(PGN<<8)|SA=(6<<24)|(0xFD9B<<8)|0xA3
#define Frame_Tx_1_T (1000)
#define Frame_Tx_1_Len (8)
#define Frame_Tx_1_Type (Msg_Period)
//PGN65110
#define Frame_Tx_2_ID (0x18FE56A3) //(P<<24)|(PGN<<8)|SA=(6<<24)|(0xFE56<<8)|0xA3
#define Frame_Tx_2_T (1000)
#define Frame_Tx_2_Len (8)
#define Frame_Tx_2_Type (Msg_Period)

//Node Info Mgt
#define _CAN_Ch (0)             //fixed
#define _CAN_Speed (250)        //K
#define _CAN_ClockSpeed (8)    //M
#define _CAN_ClockSource (0)    //Outside
//#define _CAN_ClockSource (1)    //SYS_CLK
#define _CAN_SamplePoint (8125) //81.25%

/**
 * Function Define
 * */
#define comm_user_rx
#define comm_user_tx


#ifdef __cplusplus
}
#endif

#endif
