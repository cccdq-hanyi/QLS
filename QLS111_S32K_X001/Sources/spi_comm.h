/*
 * spi_comm.h
 *
 *  Created on: 2020Äê5ÔÂ29ÈÕ
 *      Author: ganying
 */

#include <stdint.h>
#include "lpspiCom1.h"
#ifndef SPI_COMM_H_
#define SPI_COMM_H_

#define SPICOMM_TIMEOUT (200U)




extern void spi_comm_Spi_Init(void);
extern void spi_comm_Receive(void *driverState, spi_event_t event, void *userData);

#endif /* SPI_COMM_H_ */
