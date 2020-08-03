/*
 * tdc1000.h
 *
 *  Created on: 2020Äê6ÔÂ1ÈÕ
 *      Author: ganying
 */
#include <stdint.h>
#ifndef TDC1000_H_
#define TDC1000_H_

//TDC_1000 configure
#define WRITE_CMD_MASK		0x40
#define READ_CMD_MASK		0x3F
#define REG_CONFIG0			0x00
#define REG_CONFIG1			0x01
#define REG_CONFIG2			0x02
#define REG_CONFIG3			0x03
#define REG_CONFIG4			0x04
#define REG_TOF1			0x05
#define REG_TOF0			0x06
#define REG_ERROR_FLAG		0x07
#define REG_TIMEOUT			0x08
#define REG_CLOCK_RATE		0x09


//TDC_1000 status
#define ERR_SIG_WEAK		0x04
#define ERR_NO_SIG			0x02
#define ERR_SIG_HIGH		0x01	//Writing a 1 to this field will reset all the error flags and reset the ERRB pin to high.


//TDC_1000_results

uint8_t tdc1000_Init(void);
void tdc1000_Trig_Ch_Hv(void);
void tdc1000_Trig_Ch_Lv(void);
uint8_t tdc1000_read_errflg(void);
void tdc1000_clear_errflg(void);
extern bool tof_AvgValid;
#endif /* TDC1000_H_ */
