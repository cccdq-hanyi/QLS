/*
 * CAN.h
 *
 *  Created on: 2017��12��21��
 *      Author: Palmer
 */

#ifndef CAN_H_
#define CAN_H_

#include "S32K116.h" /* include peripheral declarations S32K144 */
#include "devassert.h"

#define BIT1ERR 1
#define BIT0ERR 2
#define ACKERR 3
#define CRCERR 4
#define FRMERR 5
#define STFERR 6

#define ReceiveDataFlag 0x00000030

#ifndef NULL
#define NULL 0
#endif

#define EnableCAN0 1
#define EnableCAN1 1
#define EnableCAN2 1


typedef enum
{
	CAN_100K = 100,
	CAN_125K = 125,
	CAN_250K = 250,
	CAN_500K = 500,
	CAN_1000K = 1000
} comm_spd_enum;

typedef enum
{
	clock_4M = 4,
	clock_8M = 8,
	clock_16M = 16,
	clock_25M = 25,
	clock_50M = 50
} clockspd_enum;

typedef struct
{
	comm_spd_enum comm_spd; //ͨ���ٶ�
	uint8_t CAN_ch;			//can ͨ��
	clockspd_enum clockspd; //ʱ���ٶȣ���λ M
	uint8_t clockSrc;		//ʱ��Դѡ�� 0���ⲿʱ�ӣ� 1���ڲ�ʱ��
	uint16_t SampPoint;		//�����㣬 0.01%���ȣ����� 80%=8000��
} canInit_Struct;

typedef uint8_t (*FunType_Frame)(uint32_t id, uint8_t *data, uint8_t len);
typedef uint8_t (*FunType_Error)(uint8_t ErrorCode);

extern uint8_t CAN_Tx_Call(uint32_t id, uint8_t *data, uint8_t len);
extern uint8_t J1939_CAN_Init(void);
extern void J1939_FLEXCAN_DRV_Deinit(void);

#endif /* CAN_H_ */
