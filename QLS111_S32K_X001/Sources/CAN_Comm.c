/*
 * CAN_Comm.c
 *
 *  Created on: Jul 10, 2019
 *      Author: nxa07657
 */

#include "CAN_Comm.h"

can_message_t Rx_CAN_Msg_Buffer[RX_MAX_BUF_NUM];

/* the CAN message receive complete flag */
uint32_t CAN_RxComplete_Flag = 0;
/* the CAN message receive buffer index */
uint8_t Rx_CAN_Msg_Buffer_Index = 0;

/*
 * the FlexCAN hardware message buffer configuration
 * it is used for FlexCAN MB configure
 */
can_buff_config_t buffCfg =
{
	.enableFD = false,        /*disable CAN-FD, use classical CAN 2.0A/B*/
	.enableBRS = false,       /*disable bit rate switch for CAN-FD support*/
	.fdPadding = 0U,          /*disable CAN-FD padding feature*/
	.idType = CAN_MSG_ID_STD, /*ID type is 11-bit standard ID*/
	.isRemote = false         /*disable remote frame, use data frame*/
};

/*******************************************************************************
*
* Function:void CAN_ISR_Callback(uint32_t instance,can_event_t eventType,\
*                                uint32_t objIdx,void *driverState
*
* Description: the CAN TX/RX complete interrupt ISR callback for CAN_PAL component
*              sent
*
*******************************************************************************/
void CAN_ISR_Callback(uint32_t instance,can_event_t eventType,uint32_t objIdx,void *driverState)
{
	switch(eventType)
	{
		case CAN_EVENT_RX_COMPLETE:
			/* increase the CAN message buffer index */
			Rx_CAN_Msg_Buffer_Index++;

			if(Rx_CAN_Msg_Buffer_Index >= RX_MAX_BUF_NUM)
			{
				/* reset the CAN message buffer index */
				Rx_CAN_Msg_Buffer_Index = 0;
			}
			/* call the CAN_PAL receive API to receive new CAN message frame with new buffer */
//			CAN_Receive(&can_pal1_instance,RX_MAILBOX,&Rx_CAN_Msg_Buffer[Rx_CAN_Msg_Buffer_Index]);  //because of SDK version
			CAN_Receive(can_pal1_instance,RX_MAILBOX,&Rx_CAN_Msg_Buffer[Rx_CAN_Msg_Buffer_Index]);
			/* set the flag to notice application code */
			CAN_RxComplete_Flag = 1;

			break;

		case CAN_EVENT_TX_COMPLETE:
			break;

		default:
			break;
	}
}

/*******************************************************************************
*
* Function: void CAN_Comm_Init(void)
*
* Description: This function initializes the CAN communication
*              enable the CAN transceiver-TJA1043;
*              initialize the CAN_PAL driver with dedicated TX/RX MB
*              configure the CAN interrupt priority and install its interrupt ISR callback
*
*******************************************************************************/
void CAN_Comm_Init(void)
{
	/*set the used interrupt priority*/
	//INT_SYS_SetPriority(CAN0_ORed_0_15_MB_IRQn, 3);

	Set_CANSTB(); /*set high Standby pin to make TJA1043 work in normal mode*/

	/* initialize the FlexCAN PAL driver */
//	CAN_Init(&can_pal1_instance, &can_pal1_Config0);
//	/* configure the TX MB */
//	CAN_ConfigTxBuff(&can_pal1_instance, TX_MAILBOX, &buffCfg);
//	/* configure the RC MB */
//	CAN_ConfigRxBuff(&can_pal1_instance, RX_MAILBOX, &buffCfg, RX_MSG_ID);
//	/* install the interrupt ISR callback */
//	CAN_InstallEventCallback(&can_pal1_instance,(can_callback_t)CAN_ISR_Callback,NULL);
//	/* enable the CAN receive with fist user CAN message buffer */
//	CAN_Receive(&can_pal1_instance,RX_MAILBOX,&Rx_CAN_Msg_Buffer[0]);
	//由于不同版本的SDK，can_pal.h定义不同
	CAN_Init(can_pal1_instance, &can_pal1_Config0);
	/* configure the TX MB */
	CAN_ConfigTxBuff(can_pal1_instance, TX_MAILBOX, &buffCfg);
	/* configure the RC MB */
	CAN_ConfigRxBuff(can_pal1_instance, RX_MAILBOX, &buffCfg, RX_MSG_ID);
	/* install the interrupt ISR callback */
	CAN_InstallEventCallback(can_pal1_instance,(can_callback_t)CAN_ISR_Callback,NULL);
	/* enable the CAN receive with fist user CAN message buffer */
	CAN_Receive(can_pal1_instance,RX_MAILBOX,&Rx_CAN_Msg_Buffer[0]);
}

/*******************************************************************************
*
* Function: void CAN_Transmit(uint32_t id, uint8_t* Data,uint8_t Length)
*
* Description: This function sends the a classical CAN message with id and *Data as input buffer with Length(Byte)
*
*******************************************************************************/
void CAN_Transmit(uint32_t id, uint8_t* Data,uint8_t Length)
{
	can_message_t can_message;

	uint8_t i;

	can_message.cs = 0;         /*set the Code and Status*/
	can_message.id = id;        /*set message ID*/
	can_message.length = Length;/*set the data length*/

	/* copy the message data to CAN message structure for transmit */
	for(i=0;i<Length;i++)
	{
		can_message.data[i] = Data[i];
	}

	/*sent message*/
//	CAN_Send(&can_pal1_instance,TX_MAILBOX,&can_message);//because of SDK version
	CAN_Send(can_pal1_instance,TX_MAILBOX,&can_message);
}
