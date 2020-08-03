#ifndef _comm_mgt_h
#define _comm_mgt_h
#ifdef __cplusplus
extern "C"
{
#endif

#include "typedef_all.h"
#include "..\Node_Mgt\node_para.h"
#include "..\HW_Driver\hw_abstract.h"
#include "..\Node_Mgt\node_interface.h"
#include "Int_Mgt\Int_interface.h"

    extern uint8_t u8_comm_init(void);
    extern uint8_t u8_comm_task(void);
    extern uint8_t u8_comm_MsgStatus_Get(uint32_t id);
    extern uint8_t u8_comm_TxRx_Set(uint8_t type);
    extern uint8_t u8_comm_TxRx_Get(void);
    extern uint8_t u8_comm_TxReset(void);
    extern uint8_t u8_comm_TxAfterT(uint16_t timeDelay);

#ifdef __cplusplus
}
#endif
#endif
