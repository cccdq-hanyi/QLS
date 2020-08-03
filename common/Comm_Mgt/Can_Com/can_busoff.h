#ifndef _can_busoff_h
#define _can_busoff_h

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef BusOff_Support
    //Bus Off Mgt
    extern uint8_t u8_node_BusStatus_Check(void);
    extern uint8_t u8_node_BusOff_Check(void);
    extern uint8_t u8_node_BusOff_Clear(void);
    extern uint8_t u8_node_BusOff_Resume(void);
    extern uint8_t u8_node_BusOff_Mgt(void);
#endif

    extern uint8_t u8_can_CANErr_Callback(uint8_t ErrCode);

#ifdef __cplusplus
}
#endif

#endif
