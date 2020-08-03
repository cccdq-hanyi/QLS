/*
 * WatchDog.c
 *
 *  Created on: 2017Äê12ÔÂ20ÈÕ
 *      Author: Palmer
 */

#include "WatchDog.h"


uint8_t u8_wtd_Feed(void)
{
	WDOG->CNT = 0xB480A602;
	return 0;
}
//after init
void v_wtd_DeInit(void) 
{
	DISABLE_INTERRUPTS()
	;                 // disable global interrupt
	WDOG->CNT = 0xD928C520;             //unlockwatchdog
	WDOG->TOVAL = 0x0000FFFFU; /* Maximum timeout value */
	WDOG->CS &= ~WDOG_CS_EN_MASK;       //disable watchdog
	ENABLE_INTERRUPTS()
	;                   //enable globalinterrupt
}

uint8_t u8_wtd_Init(uint16_t Period)
{
	uint32_t CS=WDOG->CS;
	//LPO Clock 1KHz
	//SIM->LPOCLKS = SIM_LPOCLKS_LPOCLKSEL(3);


	CS &= ~(WDOG_CS_WIN_MASK | WDOG_CS_PRES_MASK | WDOG_CS_CLK_MASK | WDOG_CS_INT_MASK |
		            WDOG_CS_UPDATE_MASK | WDOG_CS_DBG_MASK | WDOG_CS_WAIT_MASK | WDOG_CS_STOP_MASK);
	CS |= WDOG_CS_WIN(0);
	CS |= WDOG_CS_PRES(0);
	CS |= WDOG_CS_CLK(0x10);
	CS |= WDOG_CS_INT(0);
	CS |= WDOG_CS_UPDATE(1);
	CS |= WDOG_CS_PRES(1);

	CS |= WDOG_CS_FLG_MASK;
	CS |= WDOG_CS_EN_MASK | WDOG_CS_CMD32EN_MASK;

	CS |= WDOG_CS_DBG(1);
	//CS |= WDOG_CS_TST(0x10);


	DISABLE_INTERRUPTS();
	if(WDOG->CS&WDOG_CS_CMD32EN_MASK)
		WDOG->CNT=0xD928C520;
	else
	{
		WDOG->CNT=0xC520;
		WDOG->CNT=0xD928;
	}
	while(!(((WDOG->CS & WDOG_CS_ULK_MASK) >> WDOG_CS_ULK_SHIFT) != 0U));

	WDOG->CS = CS;
	WDOG->TOVAL= ((uint32_t)Period)*31;

	while(((WDOG->CS & WDOG_CS_ULK_MASK) >> WDOG_CS_ULK_SHIFT) != 0U);
	ENABLE_INTERRUPTS();
	return 0;
}

void v_wtd_SysReset(void)
{
	S32_SCB ->AIRCR = S32_SCB_AIRCR_SYSRESETREQ_MASK|S32_SCB_AIRCR_VECTKEY(0x5FA);
	for(;;)
	{

	}
	//return 0;
}
