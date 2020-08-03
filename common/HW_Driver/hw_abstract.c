#include "hw_abstract.h"

//ISR---------------------------------------------------------------------------
uint8_t u8_hw_ISRDisable(void)
{
	DISABLE_INTERRUPTS();
	return 0;
}
uint8_t u8_hw_ISREnable(void)
{
	ENABLE_INTERRUPTS();
	return 0;
}
//WTD---------------------------------------------------------------------------
void u8_hw_system_reset(void)
{
	v_wtd_SysReset();
}
uint8_t u8_hw_wtd_reset(void)
{
	return u8_wtd_Feed();
}
uint8_t u8_hw_wtd_Init(void)
{
	return u8_wtd_Init(256);
}
//CAN---------------------------------------------------------------------------
uint8_t u8_hw_CAN_DeInit(void)
{
	FLEXCAN_DRV_Deinit();
	return 0;
}
uint8_t u8_hw_CAN_Send(uint32_t u32_id, uint8_t *u8_data, uint8_t u8_len)
{
	return CAN_Tx_Call(u32_id, u8_data, u8_len); //cancel comment before release@watter.2019.03.06
}
uint8_t u8_hw_CAN_Init(void)
{
	J1939_CAN_Init();
	return 0;
}
//SPI---------------------------------------------------------------------------
void PortIOInit_SPI(void)
{
	PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock for PORTB */
	PORTB->PCR[2] |= PORT_PCR_MUX(3);				 /* Port B2: MUX = ALT3, LPSPI0_SCK */
	PORTB->PCR[2] |= PORT_PCR_PS(0);				 //Internal pulldown resistor is enabled
	PORTB->PCR[2] |= PORT_PCR_PE(1);				 //Internal pullup or pulldown resistor is enabled

	PORTB->PCR[3] |= PORT_PCR_MUX(3); /* Port B3: MUX = ALT3, LPSPI0_SIN */
	PORTB->PCR[4] |= PORT_PCR_MUX(3); /* Port B4: MUX = ALT3, LPSPI0_SOUT */
	PORTB->PCR[4] |= PORT_PCR_DSE(0); /* Low drive strength is configured */
	PORTB->PCR[5] |= PORT_PCR_MUX(4); /* Port B5: MUX = ALT3, LPSPI0_PCS3 */
	PORTB->PCR[5] |= PORT_PCR_DSE(0); /* Low drive strength is configured */
}
void LPSPI0_init_master(void)
{
	//	PCC->PCCn[PCC_LPSPI0_INDEX] = 0; /* Disable clocks to modify PCS ( default) */
	//	PCC->PCCn[PCC_LPSPI0_INDEX] = PCC_PCCn_PCS(0b011); /* Clock Src = 3 (FIRCDIV2_CLK) */
	//	PCC->PCCn[PCC_LPSPI0_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clk to LPIT0 regs */
	PCC->PCCn[PCC_LPSPI0_INDEX] = 0xC2000000; /* Enable clk to LPSPI0 regs, Clock Src = 3 (FIRCDIV2_CLK) */

	/* Software reset the internal logic */
	LPSPI0->CR = LPSPI_CR_RST_MASK;
	/* Now bring the LPSPI module out of reset and clear CR register */
	LPSPI0->CR = 0x00000000; /* Disable module for configuration */

	LPSPI0->CFGR1 = 0x00000003; /* Configurations: master mode*/
	/* PCSCFG=0: PCS[3:2] are enabled */
	/* OUTCFG=0: Output data retains last value when CS negated */
	/* PINCFG=0: SIN is input, SOUT is output */
	/* MATCFG=0: Match disabled */
	/* PCSPOL=0: PCS is active low */
	/* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full */
	/* AUTOPCS=0: does not apply for master mode */
	/* SAMPLE=1: input data sampled on delayed SCK edge */
	/* MASTER=1: Master mode */

	//	LPSPI0->IER = 0x00000000; /* Interrupts not used */
	//	LPSPI0->DER = 0x00000000; /* DMA not used */
	//	LPSPI0->CFGR0 = 0x00000000; /* Defaults: */
	/* RDM0=0: rec'd data to FIFO as normal */
	/* CIRFIFO=0; Circular FIFO is disabled */
	/* HRSEL, HRPOL, HREN=0: Host request disabled */

	LPSPI0->CR = LPSPI0->CR & (~(LPSPI_CR_MEN_MASK)); //disable spi
	LPSPI0->CCR = 0x0409084E;						  /* Clock dividers based on prescaled func'l clk of 100 nsec */
	/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) */
	/* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) */
	/* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) */
	/* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) */
	(LPSPI0->CR) |= (uint32_t)1U << LPSPI_CR_MEN_SHIFT; //enable spi

	//	LPSPI0->FCR = 0x00000003; /* RXWATER=0: Rx flags set when Rx FIFO >0 */
	/* TXWATER=3: Tx flags set when Tx FIFO <= 3 */
	LPSPI0->TCR = 0x4000000F; /* Transmit cmd: PCS3, 16 bits, prescale func'l clk by 4, etc*/
	/* CPOL=0: SCK inactive state is low */
	/* CPHA=1: Change data on SCK lead'g, capture on trail'g edge*/
	/* PRESCALE=0: Functional clock divided by 1 */
	/* PCS=0: Transfer using PCS0 */
	/* LSBF=0: Data is transfered MSB first */
	/* BYSW=0: Byte swap disabled */
	/* CONT, CONTC=0: Continuous transfer disabled */
	/* RXMSK=0: Normal transfer: rx data stored in rx FIFO */
	/* TXMSK=0: Normal transfer: data loaded from tx FIFO */
	/* WIDTH=0: Single bit transfer */
	/* FRAMESZ=15: # bits in frame = 15+1=16 */

	LPSPI0->CR = 0x00000001; /* Enable module for operation */
							 /* DBGEN=1: module enabled in debug mode */
							 /* DOZEN=0: module enabled in Doze mode */
							 /* RST=0: Master logic not reset */
							 /* MEN=1: Module is enabled */
}
void LPSPI0_transmit_16bits(uint16_t send)
{
	uint32_t i;
	i = 0;
	while ((LPSPI0->SR & LPSPI_SR_TDF_MASK) >> LPSPI_SR_TDF_SHIFT == 0)
	{
		i++;
		if (i > 0x1fffffff)
		{
			break;
		}
	}
	/* Wait for Tx FIFO available */
	LPSPI0->TDR = send;				 /* Transmit data */
	LPSPI0->SR |= LPSPI_SR_TDF_MASK; /* Clear TDF flag */
}
uint16_t LPSPI0_receive_16bits(void)
{
	uint16_t recieve = 0;
	uint32_t i = 0;
	i = 0;
	while ((LPSPI0->SR & LPSPI_SR_RDF_MASK) >> LPSPI_SR_RDF_SHIFT == 0)
	{
		i++;
		if (i > 0x1fffffff)
		{
			break;
		}
	}
	/* Wait at least one RxFIFO entry */
	recieve = LPSPI0->RDR;			 /* Read received data */
	LPSPI0->SR |= LPSPI_SR_RDF_MASK; /* Clear RDF flag */
	return recieve;					 /* Return received data */
}
uint8_t LPSPI0_transmite_receive_16bits(const uint16_t *dataT, uint16_t *dataR, uint16_t transferByteCount)
{
	uint16_t i = 0;
	uint16_t spi_result = 0; /* Result received SPI data from SBC */

	for (i = 0; i < transferByteCount; i++)
	{
		LPSPI0_transmit_16bits(dataT[i]);	 /* Transmit */
		spi_result = LPSPI0_receive_16bits(); /* Read result */
		dataR[i] = spi_result;				  /* Read result */
	}
	return 0;
}
uint8_t u8_hw_SpiInit(void)
{
	PortIOInit_SPI();
	LPSPI0_init_master();
	return 0;
}
uint8_t u8_hw_SpiTransfer(const uint16_t *sendBuffer, uint16_t *receiveBuffer,
						  uint16_t transferByteCount)
{
	LPSPI0_transmite_receive_16bits(sendBuffer, receiveBuffer,
									transferByteCount);
	return 0;
}
//PIT Timer---------------------------------------------------------------------
/* LPIT channel used */
#define LPIT_CHANNEL 0UL
#define LPIT_Channel_IRQn LPIT0_IRQn
uint8_t u8_timer_cnt = 0;
uint8_t task_1ms_OK = 0;
uint8_t task_5ms_OK = 0;
uint8_t task_100ms_OK = 0;
uint8_t task_100ms_Cnt = 0;
void timer_1ms_isr(void)
{
	static uint8_t u8_cnt = 0;
	task_1ms_OK = 1;
	u8_cnt++;
	if (0 == (u8_timer_cnt % 5))
	{
		task_5ms_OK = 1;
		u8_cnt = 0;
	}
	if (u8_timer_cnt >=100)
	{
		u8_timer_cnt = 0;
		task_100ms_OK = 1;
		task_100ms_Cnt++;
	}
}
static void v_v_stuff(void)
{
	;
}
func_v_v hw_BackServerISR_func = v_v_stuff;
static void NVIC_Init_IRQs(void)
{
	S32_NVIC->ICPR[0] = 1 << (20 % 32); /* IRQ20-LPIT: clr any pending IRQ*/
	S32_NVIC->ISER[0] = 1 << (20 % 32); /* IRQ20-LPIT: enable IRQ */
	S32_NVIC->IPR[5] = 0xA;				/* IRQ20-LPIT: priority 10 of 0-15*/
}
uint8_t u8_hw_Timer_DeInit(void)
{
	LPIT0->MCR &= ~LPIT_MCR_M_CEN_MASK;
	return 0;
}
uint8_t u8_hw_Timer_Init(func_v_v _func)
{
	if ((void *)0 != _func)
	{
		hw_BackServerISR_func = _func;
	}
	PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(0b011); /* Clock Src = 3 (FIRCDIV1_CLK) */
	PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK;  /* Enable clk to LPIT0 regs */
	LPIT0->MCR |= LPIT_MCR_M_CEN_MASK;				 /* DBG_EN-0: Timer chans stop in Debug mode */
	/* DOZE_EN=0: Timer chans are stopped in DOZE mode */
	/* SW_RST=0: SW reset does not reset timer chans, regs */
	/* M_CEN=1: enable module clk (allows writing other LPIT0 regs) */
	LPIT0->MIER |= LPIT_MIER_TIE0_MASK;				 /* TIE0=1: Timer Interrupt Enabled fot Chan 0 */
	LPIT0->TMR[0].TVAL = 24000U;					 /* Timeout period: 1k clocks */
	LPIT0->TMR[0].TCTRL |= LPIT_TMR_TCTRL_T_EN_MASK; /* T_EN=1: Timer channel is enabled */
	/* CHAIN=0: channel chaining is disabled */
	/* MODE=0: 32 periodic counter mode */
	/* TSOT=0: Timer decrements immediately based on restart */
	/* TSOI=0: Timer does not stop after timeout */
	/* TROT=0 Timer will not reload on trigger */
	/* TRG_SRC=0: External trigger source */
	/* TRG_SEL=0: Timer chan 0 trigger source is selected */
	NVIC_Init_IRQs();
	return 0;
}
void LPIT0_IRQHandler(void)
{
	u8_timer_cnt++;
	if ((void *)0 != hw_BackServerISR_func)
	{
		hw_BackServerISR_func();
	}
	timer_1ms_isr();
	LPIT0->MSR |= LPIT_MSR_TIF0_MASK; /* Clear LPIT0 timer flag 0 */
}

//General-----------------------------------------------------------------------
uint8_t u8_hw_GetRandom(void)
{
	return u8_timer_cnt;
}
