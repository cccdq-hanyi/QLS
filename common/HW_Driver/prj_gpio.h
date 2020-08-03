#ifndef _PRJ_GPIO_H
#define _PRJ_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "S32K116.h"
#include "..\typedef_all.h"

    extern void v_GPIO_Init(func_v_v _func);
    extern uint8_t u8_GPIO_Read(uint8_t u8_type);
    extern void v_GPIO_Tranceiver_Disable(void);
    extern void v_GPIO_Tranceiver_Enable(void);
#ifdef __cplusplus
}
#endif

#endif
