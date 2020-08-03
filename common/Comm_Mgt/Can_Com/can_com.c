#include "can_com.h"


#ifdef comm_user_rx
    extern uint8_t u8_appl_dllcanRx(uint32_t id, uint8_t data[], uint8_t len);
#endif
#ifdef comm_user_tx
    extern uint8_t u8_appl_dllcanTxOk(uint32_t id, uint8_t data[], uint8_t len);
#endif
//static uint8_t u8_cancomm_frame_func_null(uint32_t id, uint8_t *data, uint8_t len)
//{
//    (void)id;
//    (void)len;
//    return data[0];
//}
//static uint8_t u8_cancomm_err_func_null(uint8_t errorCode)
//{
//    (void)errorCode;
//    return 0;
//}
const u8_cancomm_frame_func u8_cancomm_Int_TxCallback = u8_int_TxCallback;
const u8_cancomm_frame_func u8_cancomm_Int_RxCallback = u8_int_RxCallback;
const u8_cancomm_err_func u8_cancomm_Err_Callback = u8_can_CANErr_Callback;

comm_queue_struct comm_queue;
comm_frame_struct comm_frameTx;
comm_frame_struct comm_frameRx;
uint8_t u8_cancomm_ABTRQ = 0;

//internal interface
static uint8_t u8_cancomm_queueReset(void)
{
    comm_frameTx.set = 0;
    comm_frameRx.set = 0;
    comm_queue.size = 0;
    comm_queue.tail = 0;
    comm_queue.head = 0;
    return 0;
}
//public interface, event call by up layer
uint8_t u8_cancomm_Init(void)
{
    u8_cancomm_ABTRQ = 0;
    (void)u8_cancomm_queueReset();
    return u8_hw_CAN_Init();
}
uint8_t u8_cancomm_DeInit(void)
{
    return u8_hw_CAN_DeInit();
}
/**
 * get last send frame
 * */
uint8_t u8_cancomm_GetLastTxFrame(uint32_t *id, uint8_t *data, uint8_t *len)
{
    uint8_t i = 0;
    if (frame_idel == comm_frameTx.set)
    {
        return 2; //idel
    }
    *id = comm_frameTx.id;
    *len = comm_frameTx.len;
    for (i = 0; i < *len; i++)
    {
        data[i] = comm_frameTx.data[i];
    }
    return 0;
}
/**
 * callback interface
 * u8_cancomm_RxCallback: callback by dll layer when recived one frame
 * u8_cancomm_TxOKCallback: callback by dll layer when transmite one frame success
 * u8_cancomm_ErrCallback: callback by dll layer when dll error occur
 * */
//public interface, call by low layer when rx one valid frame
uint8_t u8_cancomm_RxCallback(uint32_t id, uint8_t data[], uint8_t len)
{
#if (ecu_msg_rx_num > 0)
    switch (id)
    {
    case (Frame_Rx_1_ID):
        if (node_info.comm_status & comm_norm_rx_en)
        {
            (void)u8_cancomm_Int_RxCallback(id, data, len);
        }
        break;
    default:
        break;
    }
#endif
#ifdef comm_user_rx
    u8_appl_dllcanRx(id, data, len);
#endif
    return 0;
}
//public interface, call by low layer when tx one framesuccess
uint8_t u8_cancomm_TxOKCallback(uint32_t id, uint8_t data[], uint8_t len)
{
#if (ecu_msg_tx_num > 0)
#ifdef BusOff_Support
    busoff_struct *BusOffT;
    BusOffT = &(node_info.busoff_Info);
    if (Bus_Offline == BusOffT->u8_State)
    {
        BusOffT->u8_State = Bus_Resume;
        BusOffT->u8_cL1ToL2 = 0;
    }
#endif
    comm_frameTx.set = frame_txed;
    if (u8_cancomm_ABTRQ)
    {
        u8_cancomm_ABTRQ = 0;
        return 0;
    }
    switch (id)
    {
    case (Frame_Tx_1_ID):
    case (Frame_Tx_2_ID):
        u8_cancomm_Int_TxCallback(id, data, len);
        break;
    default:
#ifdef comm_user_tx
        u8_appl_dllcanTxOk(id, data, len);
#endif
        break;
    }
#endif
    return 0;
}
//public interface, call by low layer when dll err occur
uint8_t u8_cancomm_ErrCallback(uint8_t errorCode)
{
    return u8_cancomm_Err_Callback(errorCode);
}
/**
 * frame transmite interface
 * u8_cancomm_TxCall: insert frame into queue, wait for transmite by back server
 * u8_cancomm_TxOneFrame: transmite one frame from queue, if there is no frame in queue, no frame would be send
 * u8_cancomm_TxDirect: transmite one frame directly, user should configure the data
 * */
//internal interface, event call by current layer
static uint8_t u8_cancomm_FrameInsert(uint32_t id, uint8_t *data, uint8_t len)
{
    uint8_t pos, i;
    comm_frame_struct *frameP;
    comm_queue_struct *queueP;

    queueP = &comm_queue;
    if (queueP->size >= queue_max)
    {
        return 1; //bufferfull
    }
    if (len > 8)
    {
        return 2; //len beyond maxlen
    }
    pos = queueP->head;
    if (queueP->head >= queue_max)
    {
        queueP->head = 0;
    }
    frameP = &(queueP->queue[pos]);
    frameP->id = id;
    frameP->len = (uint8_t)len;
    for (i = 0; i < len; i++)
    {
        frameP->data[i] = data[i];
    }
    queueP->size++;
    queueP->head++;
    if (queueP->head >= queue_max)
    {
        queueP->head = 0;
    }
    return 0;
}
//public interface, event call by up layer
uint8_t u8_cancomm_TxCall(uint32_t id, uint8_t *data, uint8_t len)
{
    switch (id)
    {
    case (Frame_Tx_1_ID):
    case (Frame_Tx_2_ID):
        if (node_info.comm_status & comm_norm_tx_en)
        {
            return u8_cancomm_FrameInsert(id, data, len);
        }
        break;
    default:
        break;
    }
    return 0;
}
//public interface, period call by current layer or up layer
uint8_t u8_cancomm_TxOneFrame(void)
{
    static uint8_t tx_timer = 0;
    uint8_t pos, i;
    comm_frame_struct *frameP;
    comm_frame_struct *LframeP;
    comm_queue_struct *queueP;

    LframeP = &comm_frameTx;
    queueP = &comm_queue;
    //err check
    if (frame_txing == LframeP->set)
    {
        tx_timer++;
        if (tx_timer >= 3)
        {
            tx_timer = 0;
            // discard dll buffer data, avoid once bus resume, all tx buffer data transmit
            (void)u8_cancomm_queueReset();
            u8_cancomm_ABTRQ = 1;
            return 1; //tx error
        }
    }
    tx_timer = 0;
    //frame tx
    if (queueP->size > 0 && frame_txing != LframeP->set)
    {
        pos = queueP->tail;
        frameP = &(queueP->queue[pos]);
        LframeP->id = frameP->id;
        LframeP->len = frameP->len;
        for (i = 0; i < frameP->len; i++)
        {
            LframeP->data[i] = frameP->data[i];
        }
        if (0 == u8_hw_CAN_Send(frameP->id, frameP->data, frameP->len))
        {
            LframeP->set = frame_txing;
            queueP->size--;
            queueP->tail++;
        }
        else
        {
            return 1; //tx error
        }
        if (queueP->tail >= queue_max)
        {
            queueP->tail = 0;
        }
    }
    return 0;
}
//public interface, event/period call by current or up layer
//Direct Tx frame to can driver without check condition.
uint8_t u8_cancomm_TxDirect(uint32_t id, uint8_t *data, uint8_t len)
{
    return u8_hw_CAN_Send(id, data, len);
}
