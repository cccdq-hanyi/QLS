/*
 * CAN_Comm.h
 *
 *  Created on: Jul 10, 2019
 *      Author: nxa07657
 */

#ifndef CAN_COMM_H_
#define CAN_COMM_H_

#include "Cpu.h"

#define RX_MAX_BUF_NUM 2

#define TX_MAILBOX	(1UL)      /*MB0 is used for CAN message transmit*/
#define TX_MSG_ID	(0x111UL)  /*TX message ID = 0x111*/

#define RX_MAILBOX	(0UL)      /*MB0 is used for CAN message receive*/
#define RX_MSG_ID	(0x222UL)  /*receive only ID = 0x222*/

#define Set_CANEN() PINS_DRV_SetPins(PTD, 1<<5)
#define Set_CANSTB() PINS_DRV_ClearPins(PTC, 1<<5)


void CAN_Comm_Init(void);
void CAN_Transmit(uint32_t id, uint8_t* Data,uint8_t Length);

extern can_message_t Rx_CAN_Msg_Buffer[RX_MAX_BUF_NUM];
extern uint32_t CAN_RxComplete_Flag;
extern uint8_t Rx_CAN_Msg_Buffer_Index;


#endif /* CAN_COMM_H_ */
