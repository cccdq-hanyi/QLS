/*
 * Sys_Init.c
 *
 *  Created on: 2018��1��18��
 *      Author: watter
 */
#include "Sys_Init.h"

//Clock Init -------------------------------------------------------------------
void SOSC_init_8MHz(void)
{
	SCG->SOSCDIV = 0x00000101; /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
	SCG->SOSCCFG = 0x00000034; /* Range=3: Medium freq (SOSC betw 1MHz-8MHz)*/
	/* HGO=0:   Config xtal osc for low power */
	/* EREFS=1: Input is external XTAL */
	while (SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK)
		;					   /* Ensure SOSCCSR unlocked */
	SCG->SOSCCSR = 0x00000001; /* LK=0:          SOSCCSR can be written */
	/* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled */
	/* SOSCCM=0:      OSC CLK monitor disabled */
	/* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
	/* SOSCLPEN=0:    Sys OSC disabled in VLP modes */
	/* SOSCSTEN=0:    Sys OSC disabled in Stop modes */
	/* SOSCEN=1:      Enable oscillator */
	while (!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK))
		; /* Wait for sys OSC clk valid */
}
void SIRC_Init_8MHz(void)
{
	SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV1(1)	/* SIRCDIV1 = 1: divide by 1 (8MHz)*/
				   | SCG_SIRCDIV_SIRCDIV2(1); /* SIRCDIV2 = 1: divide by 1 (8MHz)*/
	SCG->SIRCCFG = SCG_SIRCCFG_RANGE(1);	  /* Range = 1: 8MHz */

	while (SCG->SIRCCSR & SCG_SIRCCSR_LK_MASK)
		;									/* Ensure FIRCCSR unlocked */
	SCG->SIRCCSR = SCG_SIRCCSR_SIRCSEL(0)   /* SIRCSEL = 1:  Slow IRC is not the system clock source */
				   | SCG_SIRCCSR_SIRCVLD(1) /* SIRCVLD = 1:  Slow IRC is enabled and output clock is valid */
				   | SCG_SIRCCSR_LK(0)		/* LK = 0:  SIRCCSR can be written */
				   | SCG_SIRCCSR_SIRCEN(1); /* FIRCEN = 1:  Slow IRC is enabled */

	while (!(SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK))
		; /* Wait for output clock valid */
}

void FIRC_Init_48MHz(void)
{
	SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV1(2)	/* FIRCDIV1 = 2: divide by 2 (24MHz)*/
				   | SCG_FIRCDIV_FIRCDIV2(2); /* FIRCDIV2 = 2: divide by 2 (24MHz)*/
	SCG->FIRCCFG = SCG_FIRCCFG_RANGE(0);	  /* Range = 0: 48MHz */

	while (SCG->FIRCCSR & SCG_FIRCCSR_LK_MASK)
		;									   /* Ensure FIRCCSR unlocked */
	SCG->FIRCCSR = SCG_FIRCCSR_FIRCSEL(1)	  /* FIRCSEL = 1:  Fast IRC is the system clock source */
				   | SCG_FIRCCSR_FIRCVLD(1)	/* FIRCVLD = 1:  Fast IRC is enabled and output clock is valid */
				   | SCG_FIRCCSR_LK(0)		   /* LK = 0:  FIRCCSR can be written */
				   | SCG_FIRCCSR_FIRCREGOFF(0) /* FIRCREGOFF = 0:  Fast IRC Regulator is enabled */
				   | SCG_FIRCCSR_FIRCEN(1);	/* FIRCEN = 1:  Fast IRC is enabled */

	while (!(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK))
		; /* Wait for output clock valid */
}

void SYS_CLK_Init_FIRC(void)
{
	SCG->RCCR = SCG_RCCR_SCS(3)		   /* FIRC as clock source */
				| SCG_RCCR_DIVCORE(0)  /* DIVCORE= 1, Core clock = 48 MHz */
				| SCG_RCCR_DIVBUS(1)   /* DIVBUS = 2, bus clock = 24 MHz */
				| SCG_RCCR_DIVSLOW(1); /* DIVSLOW = 2, SCG slow, flash clock= 24 MHz */
	if ((SCG->CSR & SCG_CSR_SCS_MASK >> SCG_CSR_SCS_SHIFT) != 3)
	{
	} /* Waiting for SYS_CLK = FIRE_CLK */
}
void v_task_MgtCallback(void)
{
	;
}
//System Init ------------------------------------------------------------------
void Sys_Init(void)
{
	u8_comm_init(); //include u8_cancomm_Init, u8_int_Init
	//init basic
	u8_task_AppInit();
	u8_node_ParaInit();
	//timer init
#ifdef QLS_111
	PINS_DRV_ClearPins(	DO_CAN_STB_PORT, 	1 << DO_CAN_STB );//QLS_111:CAN_STB pull_down;
#endif
	(void)u8_hw_Timer_Init(v_task_MgtCallback);
	//last
	(void)u8_hw_wtd_Init();
	(void)u8_hw_wtd_reset();
}
