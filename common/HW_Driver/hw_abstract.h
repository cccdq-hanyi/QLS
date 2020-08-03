#ifndef _hw_abstract_h
#define _hw_abstract_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "..\typedef_all.h"
#include "S32K116.h"
#include "WatchDog.h"
#include "CAN.h"
#include "prj_gpio.h"
#include "..\Comm_Mgt\Can_Com\can_com.h"

    extern uint8_t task_1ms_OK;
    extern uint8_t task_5ms_OK;
    extern uint8_t task_100ms_OK;
    //ISR
    extern uint8_t u8_hw_ISRDisable(void);
    extern uint8_t u8_hw_ISREnable(void);
    //WTD
    extern void u8_hw_system_reset(void);
    extern uint8_t u8_hw_wtd_reset(void);
    extern uint8_t u8_hw_wtd_Init(void);
    //CAN
    extern uint8_t u8_hw_CAN_Init(void);
    extern uint8_t u8_hw_CAN_DeInit(void);
    extern uint8_t u8_hw_CAN_Send(uint32_t u32_id, uint8_t *u8_data, uint8_t u8_len);
    //TIMER
    extern uint8_t u8_hw_Timer_DeInit(void);
    extern uint8_t u8_hw_Timer_Init(func_v_v _func);
    extern uint8_t u8_hw_GetRandom(void);
    //SPI
    extern uint8_t u8_hw_SpiInit(void);
    extern uint8_t u8_hw_SpiTransfer(const uint16_t *sendBuffer, uint16_t *receiveBuffer, uint16_t transferByteCount);
//IO
#define v_hw_GPIO_Init v_GPIO_Init
#define u8_hw_GPIO_Read u8_GPIO_Read
#define v_hw_GPIO_Tranceiver_Disable v_GPIO_Tranceiver_Disable
#define v_hw_GPIO_Tranceiver_Enable v_GPIO_Tranceiver_Enable

#ifdef __cplusplus
}
#endif
#endif
