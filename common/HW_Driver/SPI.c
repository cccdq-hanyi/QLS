#include "SPI.h"

/* -----------------------------------------------------------------------------
 * SPI Init
 * ---------------------------------------------------------------------------*/
static void PortIOInit_SPI(void) 
{
	PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock for PORTB */
	PORTB->PCR[2] |= PORT_PCR_MUX(3); /* Port B2: MUX = ALT3, LPSPI0_SCK */
	PORTB->PCR[2] |= PORT_PCR_PS(0);	//Internal pulldown resistor is enabled
	PORTB->PCR[2] |= PORT_PCR_PE(1);//Internal pullup or pulldown resistor is enabled

	PORTB->PCR[3] |= PORT_PCR_MUX(3); /* Port B3: MUX = ALT3, LPSPI0_SIN */
	PORTB->PCR[4] |= PORT_PCR_MUX(3); /* Port B4: MUX = ALT3, LPSPI0_SOUT */
	PORTB->PCR[4] |= PORT_PCR_DSE(0); /* Low drive strength is configured */
	PORTB->PCR[5] |= PORT_PCR_MUX(4); /* Port B5: MUX = ALT3, LPSPI0_PCS3 */
	PORTB->PCR[5] |= PORT_PCR_DSE(0); /* Low drive strength is configured */
}
static void LPSPI0_init_master(void) 
{
//	PCC->PCCn[PCC_LPSPI0_INDEX] = 0; /* Disable clocks to modify PCS ( default) */
//	PCC->PCCn[PCC_LPSPI0_INDEX] = PCC_PCCn_PCS(0b011); /* Clock Src = 3 (FIRCDIV2_CLK) */
//	PCC->PCCn[PCC_LPSPI0_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clk to LPIT0 regs */
#ifdef FIRC_48M_Support
	PCC->PCCn[PCC_LPSPI0_INDEX] = 0xC2000000; /* 0xC2000000,Enable clk to LPSPI0 regs, Clock Src = 3 (FIRCDIV2_CLK) */
#else
	PCC->PCCn[PCC_LPSPI0_INDEX] = 0xC1000000; /* 0xC2000000,Enable clk to LPSPI0 regs, Clock Src = 1 (SIRCDIV2_CLK) */
#endif
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

	LPSPI0->CR = LPSPI0->CR & (~(LPSPI_CR_MEN_MASK));	//disable spi
	LPSPI0->CCR = 0x0409080A; 	/* Clock dividers based on prescaled func'l clk of 100 nsec */
								/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) */
								/* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) */
								/* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) */
								/* SCKDIV=10: SCK divider =10+2 = 12 (1 usec: 1 MHz baud rate) */
	(LPSPI0->CR) |= (uint32_t) 1U << LPSPI_CR_MEN_SHIFT;	//enable spi

//	LPSPI0->FCR = 0x00000003; /* RXWATER=0: Rx flags set when Rx FIFO >0 */
	/* TXWATER=3: Tx flags set when Tx FIFO <= 3 */
	LPSPI0->TCR = 0x4000000F; 	/* Transmit cmd: PCS3, 16 bits, prescale func'l clk by 4, etc*/
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

	LPSPI0->CR = 0x00000001; 	/* Enable module for operation */
								/* DBGEN=1: module enabled in debug mode */
								/* DOZEN=0: module enabled in Doze mode */
								/* RST=0: Master logic not reset */
								/* MEN=1: Module is enabled */
}
uint8_t u8_SpiInit(void)
{
	PortIOInit_SPI();
	LPSPI0_init_master();
	return 0;
}





static void LPSPI0_transmit_16bits(uint16_t send) 
{
	while ((LPSPI0->SR & LPSPI_SR_TDF_MASK) >> LPSPI_SR_TDF_SHIFT == 0)
		;
	/* Wait for Tx FIFO available */
	LPSPI0->TDR = send; /* Transmit data */
	LPSPI0->SR |= LPSPI_SR_TDF_MASK; /* Clear TDF flag */
}
static uint16_t LPSPI0_receive_16bits(void) 
{
	uint16_t recieve = 0;

	while ((LPSPI0->SR & LPSPI_SR_RDF_MASK) >> LPSPI_SR_RDF_SHIFT == 0)
		;
	/* Wait at least one RxFIFO entry */
	recieve = LPSPI0->RDR; /* Read received data */
	LPSPI0->SR |= LPSPI_SR_RDF_MASK; /* Clear RDF flag */
	return recieve; /* Return received data */
}
static void LPSPI0_transmite_receive_16bits(const uint16_t* dataT, uint16_t* dataR, uint16_t transferByteCount)
{
	uint16_t i = 0;
	for (i = 0; i < transferByteCount; i++) {
		LPSPI0_transmit_16bits(dataT[i]); /* Transmit */
		dataR[i] = LPSPI0_receive_16bits(); /* Read result */
	}
}
uint8_t u8_SpiTransfer(const uint16_t * sendBuffer, uint16_t * receiveBuffer, uint16_t transferByteCount) 
{
	LPSPI0_transmite_receive_16bits(sendBuffer, receiveBuffer, transferByteCount);
	return 0;
}
