/*
 * CAN.c
 *
 *  Created on: 2017锟斤拷12锟斤拷21锟斤拷
 *      Author: Palmer
 */
#include "CAN.h"
#include "..\Comm_Mgt\Can_Com\can_com.h"
#include "common.h"
#define CAN_Choose (((CAN_Type *)CAN_Addr))
#define MSG_BUF_SIZE (4) /* Msg Buffer Size. (CAN 2.0AB: 2 hdr +  2 data= 4 words) */
#define ErrCode 1
// #define StdFrameTxSupport
// #define StdFrameRxSupport
const FunType_Frame _rxFunc = u8_cancomm_RxCallback;
const FunType_Frame _txOKFunc = u8_cancomm_TxOKCallback;
const FunType_Error errorFunc = u8_cancomm_ErrCallback;
uint32_t CAN_Addr = CAN0_BASE;
canInit_Struct InitStruct;
uint32_t TxId;
uint32_t RxID;				   /* Received message ID */
uint32_t RxLENGTH;			   /* Recieved message number of data bytes */
uint32_t RxDATA[2];			   /* Received message data (2 words) */
volatile uint32_t RxCODE;	  /* Received message buffer code */
volatile uint32_t RxTIMESTAMP; /* Received message time */

static void InitNVIC(voidh)
{

	S32_NVIC->ICPR[0] = 1 << (CAN0_ORed_0_31_MB_IRQn % 32); /* IRQ81 CAN0 channel: clear any pending IRQ */
	S32_NVIC->ISER[0] = 1 << (CAN0_ORed_0_31_MB_IRQn % 32); /* IRQ81 CAN0 channel: enable IRQ */
	S32_NVIC->IPR[CAN0_ORed_0_31_MB_IRQn % 4] = 0xA0;		/* IRQ81 CAN0 channel: priority 10 of 0-15 */

	S32_NVIC->ICPR[0] = 1 << (CAN0_ORed_Err_Wakeup_IRQn % 32); /* IRQ79 CAN0 channel: clear any pending IRQ */
	S32_NVIC->ISER[0] = 1 << (CAN0_ORed_Err_Wakeup_IRQn % 32); /* IRQ79 CAN0 channel: enable IRQ */
	S32_NVIC->IPR[CAN0_ORed_Err_Wakeup_IRQn % 4] = 0x90;	   /* IRQ79 CAN0 channel: priority 10 of 0-15 */
}

uint8_t CAN_Tx_Call_X(uint32_t id, uint8_t *data, uint8_t len, uint8_t u8_IsExtendId)
{
	uint8_t i;
	if (len > 8)
		return ErrCode;
	if (data == NULL)
		return ErrCode;
	TxId = id;
	//while((CAN_Choose->ESR1&CAN_ESR1_TX_MASK) != 0){} //wait transmit end
	CAN_Choose->IFLAG1 = 0x00000001; /* Clear CAN 0 MB 0 flag without clearing others*/
	if (u8_IsExtendId)
	{
		CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 0] = 0x09600000; //Bit21-IDE
	}
#ifdef StdFrameTxSupport
	else
	{
		CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 0] = 0x09400000; //Bit21-IDE
	}
#endif
	CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 2] = 0;
	CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 3] = 0;
	for (i = 0; i < len; i++)
	{
		if (i < 4)
		{
			CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 2] |= (*(data + i) << ((3 - i) << 3)); /* MB0 word 2: data word 0 */
		}
		else
		{
			CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 3] |= (*(data + i) << ((7 - i) << 3)); /* MB0 word 3: data word 1 */
		}
	}
	if (u8_IsExtendId)
	{
		CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 1] = id;										  /* MB0 word 1: Tx msg with ID */
		CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 0] = 0x0C600000 | (len << CAN_WMBn_CS_DLC_SHIFT); /* MB0 word 0: */
																							  /* EDL,BRS,ESI=0: CANFD not used */
																							  /* CODE=0xC: Activate msg buf to transmit */
																							  /* IDE=1: Ext ID */
																							  /* SRR=1 Tx frame (not req'd for std ID) */
																							  /* RTR = 0: data, not remote tx request frame*/
																							  /* DLC = ? bytes */
	}
#ifdef StdFrameTxSupport
	else
	{
		CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 1] = id << 18; /* MB0 word 1: Tx msg with ID */
		CAN_Choose->RAMn[0 * MSG_BUF_SIZE + 0] = 0x0C400000 | (len << CAN_WMBn_CS_DLC_SHIFT);
	}
#endif
	return 0;
}
uint8_t CAN_Tx_Call(uint32_t id, uint8_t *data, uint8_t len)
{
	return CAN_Tx_Call_X(id, data, len, 1);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_Disable
 * Description   : Disable FlexCAN module.
 * This function will disable FlexCAN module.
 *
 * Implements : FLEXCAN_HAL_Disable_Activity
 *END**************************************************************************/
void FLEXCAN_HAL_Disable(CAN_Type *base)
{
	if ((void *)0 == base)
		return;
	/* To access the memory mapped registers */
	/* Entre disable mode (hard reset). */
	if (((base->MCR & CAN_MCR_MDIS_MASK) >> CAN_MCR_MDIS_SHIFT) == 0U)
	{
		/* Clock disable (module) */
		base->MCR = (base->MCR & ~CAN_MCR_MDIS_MASK) | CAN_MCR_MDIS(1U);
		/* Wait until disable mode acknowledged */
		while (((base->MCR & CAN_MCR_LPMACK_MASK) >> CAN_MCR_LPMACK_SHIFT) == 0U)
		{
		}
	}
}
///*FUNCTION**********************************************************************
// *
// * Function Name : INT_SYS_DisableIRQ
// * Description   : Disable individual interrupt for a specified IRQ
// * It  calls the system NVIC API to access the interrupt control register
// * and MSCM (if available) API for interrupt routing.
// * Implements INT_SYS_DisableIRQ_Activity
// *
// *END**************************************************************************/
//void INT_SYS_DisableIRQ(IRQn_Type irqNumber)
//{
//	/* Check IRQ number */
//	DEV_ASSERT(0 <= (int32_t)irqNumber);
//	DEV_ASSERT(irqNumber <= FEATURE_INTERRUPT_IRQ_MAX);
//
//	/* Disable interrupt */
//	S32_NVIC->ICER[((uint32_t)(irqNumber) >> 5U)] = (uint32_t)(1UL << ((uint32_t)(irqNumber) & (uint32_t)0x1FU));
//
//#if FEATURE_MSCM_HAS_INTERRUPT_ROUTER
//
//	/* Disable routing to current CPU */
//	uint16_t cpu_enable = (uint16_t)(1UL << (MSCM->CPXNUM));
//	MSCM->IRSPRC[irqNumber] &= (uint16_t) ~(cpu_enable);
//
//#endif /* FEATURE_MSCM_HAS_INTERRUPT_ROUTER */
//}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Deinit
 * Description   : Shutdown a FlexCAN module.
 * This function will disable all FlexCAN interrupts, and disable the FlexCAN.
 *
 * Implements    : FLEXCAN_DRV_Deinit_Activity
 *END**************************************************************************/
void J1939_FLEXCAN_DRV_Deinit(void)
{
	/* Disable FlexCAN interrupts.*/
	INT_SYS_DisableIRQ(CAN0_ORed_Err_Wakeup_IRQn);
	INT_SYS_DisableIRQ(CAN0_ORed_0_31_MB_IRQn);
	/* Disable FlexCAN.*/
	FLEXCAN_HAL_Disable(CAN0);
}
uint8_t J1939_CAN_Init(void)
{
	uint32_t i = 0, TimeQuanta = 0;
	canInit_Struct *clockSrc = &InitStruct;
	//can communication init
	clockSrc->CAN_ch = _CAN_Ch;
	clockSrc->SampPoint = _CAN_SamplePoint;
	clockSrc->clockSrc = _CAN_ClockSource;
	clockSrc->clockspd = _CAN_ClockSpeed;
	clockSrc->comm_spd = _CAN_Speed;
	if ((clockSrc->clockSrc != 0) && (clockSrc->clockSrc != 1))
		return ErrCode;
	if (clockSrc->SampPoint < 100)
		return ErrCode;
	PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock for PORTC */
	PORTC->PCR[3] |= PORT_PCR_MUX(3);				 /* Port C3: MUX = ALT3, CAN0_TX */
	PORTC->PCR[2] |= PORT_PCR_MUX(3);				 /* Port C2: MUX = ALT3, CAN0_RX */
	CAN_Addr = CAN0_BASE;
	PCC->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK; /* CGC=1: enable clock to FlexCAN0 */
	InitNVIC();
	CAN_Choose->MCR = 0xD890000F;
	CAN_Choose->CTRL1 = 0;
	CAN_Choose->MCR |= CAN_MCR_MDIS_MASK; /* MDIS=1: Disable module before selecting clock */
	CAN_Choose->CTRL1 = 0;
	if (clockSrc->clockSrc == 0)
		CAN_Choose->CTRL1 &= ~CAN_CTRL1_CLKSRC_MASK; /* CLKSRC=0: Clock Source = oscillator (8 MHz) */
	else
		CAN_Choose->CTRL1 |= CAN_CTRL1_CLKSRC_MASK;
	CAN_Choose->MCR &= ~CAN_MCR_MDIS_MASK; /* MDIS=0; Enable module config. (Sets FRZ, HALT)*/

	i = 0;
	while (!((CAN_Choose->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT))
	{
		i++;
		if (i > 0x2FFFFE)
			return ErrCode;
	}
	/* Good practice: wait for FRZACK=1 on freeze mode entry/exit */
	i = 1; //clock prescaler
	do
	{
		TimeQuanta = (clockSrc->clockspd * 1000) / clockSrc->comm_spd / i;
		i++;
		if (i > 256)
			return ErrCode;
	} while ((TimeQuanta < 8) || (TimeQuanta >= 20));
	//TimeQuanta = 16;//i=4
	CAN_Choose->CTRL1 |= CAN_CTRL1_PRESDIV(i - 2);

	i = TimeQuanta * clockSrc->SampPoint / 10000; //set propseg and pseg1
	if ((i - 3) % 2 != 0)
	{
		CAN_Choose->CTRL1 |= CAN_CTRL1_PROPSEG(((i - 2) / 2) + 1);
		CAN_Choose->CTRL1 |= CAN_CTRL1_PSEG1(((i - 2) / 2) - 2);
	}
	else
	{
		CAN_Choose->CTRL1 |= CAN_CTRL1_PROPSEG(((i - 1) / 2));
		CAN_Choose->CTRL1 |= CAN_CTRL1_PSEG1(((i - 1) / 2) - 2);
	}
	i = TimeQuanta - i; //set pseg2
	CAN_Choose->CTRL1 |= CAN_CTRL1_PSEG2(i - 1);
	//SWJ
	if ((i - 1) > 3)
		CAN_Choose->CTRL1 |= CAN_CTRL1_RJW(3);
	else
		CAN_Choose->CTRL1 |= CAN_CTRL1_RJW(i - 1);
	//single sampale point
	CAN_Choose->CTRL1 |= CAN_CTRL1_SMP(0);
	for (i = 0; i < (clockSrc->CAN_ch == 0 ? 128 : 64); i++)
	{							 /* CAN_Choose: clear 32 msg bufs x 4 words/msg buf = 128 words*/
		CAN_Choose->RAMn[i] = 0; /* Clear msg buf word */
	}
	for (i = 0; i < 16; i++)
	{									   /* In FRZ mode, init CAN0 16 msg buf filters */
		CAN_Choose->RXIMR[i] = 0xFFFFFFFF; /* Check all ID bits for incoming messages */
	}
	CAN_Choose->RXMGMASK = 0x00; /* Global acceptance mask: check all ID bits */
#ifdef StdFrameRxSupport
	//for std frame rx
	CAN_Choose->RAMn[4 * MSG_BUF_SIZE + 0] = 0x04000000; /* Msg Buf 4, word 0: Enable for reception */
														 /* EDL,BRS,ESI=0: CANFD not used */
														 /* CODE=4: MB set to RX inactive */
														 /* IDE=0: Standard ID */
														 /* SRR, RTR, TIME STAMP = 0: not applicable */
	CAN_Choose->RAMn[4 * MSG_BUF_SIZE + 1] = 0x14440000; /* Msg Buf 4, word 1: Standard ID = 0x111 */
#endif
	//for ext frame rx
	CAN_Choose->RAMn[5 * MSG_BUF_SIZE + 0] = 0x04200000; /* Msg Buf 5, word 0: Enable for reception */
														 /* EDL,BRS,ESI=0: CANFD not used */
														 /* CODE=4: MB set to RX inactive */
														 /* IDE=1: Extended ID*/
														 /* SRR, RTR, TIME STAMP = 0: not applicable */
	CAN_Choose->RAMn[5 * MSG_BUF_SIZE + 1] = 0x14440000; /* Msg Buf 5, word 1: Ext ID = 0x111x */

	CAN_Choose->MCR = 0x0000001F; /* Negate FlexCAN 1 halt state for 32 MBs */
	while ((CAN_Choose->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT)
	{
	}
	/* Good practice: wait for FRZACK to clear (not in freeze mode) */
	while ((CAN_Choose->MCR & CAN_MCR_NOTRDY_MASK) >> CAN_MCR_NOTRDY_SHIFT)
	{
	}
	/* Good practice: wait for NOTRDY to clear (module ready)  */
	CAN_Choose->CTRL1 |= CAN_CTRL1_ERRMSK(1); //enable error interrupt;
	CAN_Choose->MCR |= CAN_MCR_RFEN(0);		  //,disable FIFO enbale message buffer interrupt;
	CAN_Choose->IMASK1 = ((1 << 5) | 1);	  //enable buffer interrupt: Bit0-Tx(Ext/Std), Bit5-Ext Rx
#ifdef StdFrameRxSupport
	CAN_Choose->IMASK1 |= (1 << 4); //enable buffer interrupt: Bit-Std Rx
#endif
	return 0;
}
//为J1939定义
void CAN0_ORed_0_31_MB_IRQHandler()
{
	volatile uint32_t dummy = CAN0->IFLAG1;
	uint8_t u8_buf_Index = 0;
	uint32_t j;
	uint8_t _RXDATA[8] = {0};
	switch (dummy & ReceiveDataFlag)
	{
#ifdef StdFrameRxSupport
	case (0x10): //buffer 4 for std frame
		u8_buf_Index = 4;
		break;
#endif
	case (0x20): //buffer 5 for ext frame
		u8_buf_Index = 5;
		break;
	default:
		CAN0->IFLAG1 = dummy; //(0xFFFFFFFF - (0x01 << 4) - (0x01 << 5)); /* Clear CAN 0 MB  flag without clearing 4/5*/
		return;
		break;
	}
	RxCODE = (CAN0->RAMn[u8_buf_Index * MSG_BUF_SIZE + 0] & 0x07000000) >> 24; /* Read CODE field */
	if ((CAN0->RAMn[u8_buf_Index * MSG_BUF_SIZE + 0] & CAN_WMBn_CS_IDE_MASK) != 0)
	{
		RxID = CAN0->RAMn[u8_buf_Index * MSG_BUF_SIZE + 1];
	}
	else
		RxID = (CAN0->RAMn[u8_buf_Index * MSG_BUF_SIZE + 1] & CAN_WMBn_ID_ID_MASK) >> 18;
	RxLENGTH = (CAN0->RAMn[u8_buf_Index * MSG_BUF_SIZE + 0] & CAN_WMBn_CS_DLC_MASK) >> CAN_WMBn_CS_DLC_SHIFT;
	for (j = 0; j < 2; j++)
	{
		/* Read two words of data (8 bytes) */
		RxDATA[j] = CAN0->RAMn[u8_buf_Index * MSG_BUF_SIZE + 2 + j];
	}
	RxTIMESTAMP = (CAN0->RAMn[0 * MSG_BUF_SIZE + 0] & 0x000FFFF);
	dummy = CAN0->TIMER;				   /* Read TIMER to unlock message buffers */
	CAN0->IFLAG1 = (0x01 << u8_buf_Index); /* Clear CAN 0 MB 4/5 flag without clearing others*/
	for (j = 0; j < 4; j++)				   /* Transpose receive data */
	{
		_RXDATA[j] = (RxDATA[0] >> ((3 - j) << 3)) & 0xFF;
	}
	for (j = 0; j < 4; j++)
	{
		_RXDATA[4 + j] = (RxDATA[1] >> ((3 - j) << 3)) & 0xFF;
	}
	if (RxID == TxId) /*judge TX OR RX*/
	{
		if (_txOKFunc != NULL)
			_txOKFunc(RxID, _RXDATA, RxLENGTH);
	}
	else
	{
		if (_rxFunc != NULL)
			_rxFunc(RxID, _RXDATA, RxLENGTH);
	}
}
//为J1939定义
void CAN0_ORed_Err_Wakeup_IRQHandler()
{
	uint32_t dummy = CAN0->ESR1;
	if (errorFunc != NULL)
	{
		if (dummy & CAN_ESR1_STFERR_MASK)
		{
			errorFunc(STFERR);
		}
		else if (dummy & CAN_ESR1_FRMERR_MASK)
		{
			errorFunc(FRMERR);
		}
		else if (dummy & CAN_ESR1_CRCERR_MASK)
		{
			errorFunc(CRCERR);
		}
		else if (dummy & CAN_ESR1_ACKERR_MASK)
		{
			errorFunc(ACKERR);
		}
		else if (dummy & CAN_ESR1_BIT0ERR_MASK)
		{
			errorFunc(BIT0ERR);
		}
		else if (dummy & CAN_ESR1_BIT1ERR_MASK)
		{
			errorFunc(BIT1ERR);
		}
	}
	CAN0->ESR1 = 0x02; //clear interrupt flag
}
