#include "prj_gpio.h"

#define IO_ISR_Enable
static void v_v_stuff(void)
{
	;
}
func_v_v v_func_local = v_v_stuff;
/* -----------------------------------------------------------------------------
 *GPIO Init
 *----------------------------------------------------------------------------*/
//static void v_GPIOA_Init(uint8_t u8_index, uint8_t u8_default)
//{
//	if (u8_index > 15)
//		return;
//	PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK; //Enable Clock
//	PTA->PDDR |= (1 << u8_index);					 //Set as output
//	PORTA->PCR[u8_index] = 0x00000100;				 //As GPIO
//	if (u8_default > 0)
//	{
//		PTA->PDOR |= (1 << u8_index); //Output High
//	}
//	else
//	{
//		PTA->PDOR &= ~(1 << u8_index); //Output Low
//	}
//}
void v_GPIO_Init(func_v_v _func)
{
	//CAN_WAKE->PTE8->output
	// PCC->PCCn[PCC_PORTE_INDEX]  |=  PCC_PCCn_CGC_MASK; //濞达綀鍎婚崗妤禩E缂佹棏鍨拌ぐ娑㈠籍閸洘瀵�
	// PTE->PDDR  |=  (1<<8);      //闂佹澘绉堕悿鍝朤E8濞戞捇缂氱欢顓㈠礄閾忚浼傞柛娆欐嫹
	// PORTE->PCR[8] = 0x00000100; //闂佹澘绉堕悿鍝朤E8濞戞挾鐦IO闁挎稑濂旂粭澶嬫媴鐠恒劍鏆忛柛蹇旀构缁剚寰勫鍥ㄦ殢闁告梻鍠曢崗锟�
	// PTE->PDOR &= ~(1<<8);       //PTE8閺夊牊鎸搁崵顓熸媴鎼达絾鏆╂鐑囨嫹
	//CAN_INH->PTD3->input
	PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK; //enable clock for port D
	PTD->PIDR &= ~(1 << 3);							 //PD3 Pin is configured for General Purpose Input
	PTD->PDDR &= ~(1 << 3);							 //set PTD3 as input port
	//clear flag first
	PORTD->ISFR = 0xFFFFFFFF;
	PORTD->PCR[3] = 0x00090102; //set PTD3 as GPIO闁挎冻鎷�
								//0x08->ISF flag and Interrupt when logic 0
								//0x09->interrupt on rising-edge
								//0x0A->interrupt on failing-edge
								//0x0B->interrupt on either-edge
								//0x0C->ISF flag and Interrupt when logic 1.
								//PS = 1, Internal pulldown
								//PE = 1, Internal pullup or pulldown resistor is enabled
	v_GPIO_Tranceiver_Enable();
#ifdef IO_ISR_Enable
	if ((void *)0 != _func)
	{
		v_func_local = _func;
	}
	//GPIO ISR set
	S32_NVIC->ICPR[0] = 1 << (PORT_IRQn % 32); //PORT_IRQn = 9u,< Port A, B, C, D and E pin detect interrupt
	S32_NVIC->ISER[0] = 1 << (PORT_IRQn % 32);
	S32_NVIC->IPR[PORT_IRQn % 4] = 0x1; //set isr priority
#endif
}
void PORT_IRQHandler(void)
{
	uint32_t u32_flag = 0;
	//IG1 Flag Clear
	u32_flag = PORTA->ISFR;
	PORTA->ISFR = u32_flag;
	//CAN_INH clear isr flag
	u32_flag = PORTD->ISFR;
	//clear current flag
	PORTD->ISFR = u32_flag;
	//system reset
	if ((void *)0 != v_func_local)
	{
		v_func_local();
	}
	return;
}
/**
 * GPIO Read
 * return:1-high, 0-low
 * */
uint8_t u8_GPIO_Read(uint8_t u8_type)
{
	uint8_t u8_result = 0;
	switch (u8_type)
	{
	case (0): //can_inh
		if (PTD->PDIR & (1 << 3))
		{
			u8_result = 1;
		}
		break;
	case (1): //IGN
		if (PTA->PDIR & (1 << 7))
		{
			u8_result = 1;
		}
		break;
	default:
		break;
	}
	return u8_result;
}
/**
 * INH1 Pull down/up ->PTB0
 * */
void v_GPIO_Tranceiver_Enable(void)
{
	PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK; //Enable Clock
	PTB->PDDR |= (1 << 0);							 //Set as output
	PORTB->PCR[0] = 0x00000100;						 //As GPIO
	PTB->PDOR |= (1 << 0);							 //Output High
}
void v_GPIO_Tranceiver_Disable(void)
{
	PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK; //Enable Clock
	PTB->PDDR |= (1 << 0);							 //Set as output
	PORTB->PCR[0] = 0x00000100;						 //As GPIO
	PTB->PDOR &= ~(1 << 0);							 //Output Low
}
