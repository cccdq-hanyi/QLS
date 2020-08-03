/*
 * WatchDog.h
 *
 *  Created on: 2017Äê12ÔÂ20ÈÕ
 *      Author: Palmer
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_
#include <stdint.h>
#include "s32_core_cm0.h"
#include <S32K116.h>           /* include peripheral declarations S32K144 */

// extern void WDOG_disable (void);
extern uint8_t 	u8_wtd_Feed(void);
extern void 	v_wtd_DeInit(void);
extern uint8_t 	u8_wtd_Init(uint16_t Period);
extern void 	v_wtd_SysReset(void);

#endif /* WATCHDOG_H_ */
