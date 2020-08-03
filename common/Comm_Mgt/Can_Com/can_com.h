#ifndef _can_com_mgt_h
#define _can_com_mgt_h
#ifdef __cplusplus
extern "C"
{
#endif

#include "..\..\typedef_all.h"
#include "..\..\Node_Mgt\node_para.h"
#include "..\..\HW_Driver\hw_abstract.h"
#include "..\Int_Mgt\Int_interface.h"
#include "can_busoff.h"
    typedef uint8_t (*u8_cancomm_frame_func)(uint32_t id, uint8_t *data, uint8_t len);
    typedef uint8_t (*u8_cancomm_err_func)(uint8_t errorCode);

//frame status define
#define frame_idel (0)
#define frame_txing (1)
#define frame_txed (2)
#define frame_rxed (3)
#define frame_disc (4)
//for 1ms 4frames at most
#define queue_max (4)
    typedef struct
    {
        uint8_t len;
        uint8_t type;
        uint8_t set; //0->idel, 1->tx, 2->rx
        uint32_t id;
        uint8_t data[8];
    } comm_frame_struct;

    typedef struct
    {
        uint8_t size;
        uint8_t head;
        uint8_t tail;
        comm_frame_struct queue[queue_max];
    } comm_queue_struct;

    extern uint8_t u8_cancomm_Init(void);
    extern uint8_t u8_cancomm_DeInit(void);
    extern uint8_t u8_cancomm_GetLastTxFrame(uint32_t *id, uint8_t *data, uint8_t *len);
    extern uint8_t u8_cancomm_RxCallback(uint32_t id, uint8_t data[], uint8_t len);
    extern uint8_t u8_cancomm_TxOKCallback(uint32_t id, uint8_t data[], uint8_t len);
    extern uint8_t u8_cancomm_ErrCallback(uint8_t errorCode);
    extern uint8_t u8_cancomm_TxCall(uint32_t id, uint8_t *data, uint8_t len);
    extern uint8_t u8_cancomm_TxOneFrame(void);
    extern uint8_t u8_cancomm_TxDirect(uint32_t id, uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif
#endif
