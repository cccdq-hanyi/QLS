#ifndef _int_para_h
#define _int_para_h
#ifdef __cplusplus
extern "C"
{
#endif

#include "typedef_all.h"
#include "..\..\Node_Mgt\node_para.h"

#define int_msg_init (0)
#define int_msg_txing (1)
#define int_msg_txed (2)
	//para define
	typedef struct
	{
		//local Information
		uint8_t u8_msgStatus; //0->Idel, 1->txing, 2->txed
		uint8_t u8_msgTxCnt;
	} IntInfo_Struct;

	extern IntInfo_Struct IntInfo;

#ifdef __cplusplus
}
#endif
#endif
