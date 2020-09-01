#ifndef _Int_interface_h
#define _Int_interface_h
#ifdef __cplusplus
extern "C"
{
#endif
#include "typedef_all.h"
#include "Int_para.h"
#include "..\Can_Com\can_com.h"
extern uint8_t u8_int_Write_PGN64923_message(uint8_t *data,uint8_t len);
    //CAN Network
    //write normal msg ---------------------------------------------------------------------------------
    extern uint8_t u8_int_Write_PGN64923_SPN3515(uint8_t val);
    extern uint8_t u8_int_Write_PGN64923_SPN3516(uint8_t val);
    extern uint8_t u8_int_Write_PGN64923_SPN3519(uint8_t val);
    extern uint8_t u8_int_Write_PGN64923_SPN3520(uint8_t val);
    extern uint8_t u8_int_Write_PGN64923_SPN3521(uint8_t val);
    extern uint8_t u8_int_Write_PGN65110_SPN1761(uint8_t val);
    extern uint8_t u8_int_Write_PGN65110_SPN3031(uint8_t val);
    extern uint8_t u8_int_Write_PGN65110_SPN3517(uint16_t val);
    extern uint8_t u8_int_Write_PGN65110_SPN3532(uint8_t val);
    extern uint8_t u8_int_Write_PGN65110_SPN4365(uint8_t val);
    //INT interface-------------------------------------------------------------------------------------
    extern uint8_t u8_int_ReadTxMsgState(void);
    extern uint8_t u8_int_Init(void);
    extern uint8_t u8_int_task(void);
    extern uint8_t u8_int_TxCallback(uint32_t id, uint8_t *data, uint8_t len);
    extern uint8_t u8_int_RxCallback(uint32_t id, uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif
#endif
