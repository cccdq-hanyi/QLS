#ifndef _SPI_H
#define _SPI_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "S32K116.h"
#include "..\typedef_all.h"
#include "..\Node_Mgt\node_para.h"

extern uint8_t u8_SpiInit(void);
extern uint8_t u8_SpiTransfer(const uint16_t * sendBuffer, uint16_t * receiveBuffer, uint16_t transferByteCount);


#ifdef __cplusplus
}
#endif

#endif
