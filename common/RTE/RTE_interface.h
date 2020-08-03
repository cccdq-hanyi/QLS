#ifndef _RTE_interface_h
#define _RTE_interface_h
#ifdef __cplusplus
extern "C"
{
#endif

#include "typedef_all.h"
#include "..\Node_Mgt\node_interface.h"
#include "..\Comm_Mgt\Int_Mgt\Int_interface.h"

//-------------------------------------------------------------------------------
//CAN Network																	|
//-------------------------------------------------------------------------------
//write normal msg
#define u8_rte_Write_PGN64923_SPN3515 u8_int_Write_PGN64923_SPN3515
#define u8_rte_Write_PGN64923_SPN3516 u8_int_Write_PGN64923_SPN3516
#define u8_rte_Write_PGN64923_SPN3519 u8_int_Write_PGN64923_SPN3519
#define u8_rte_Write_PGN64923_SPN3520 u8_int_Write_PGN64923_SPN3520
#define u8_rte_Write_PGN64923_SPN3521 u8_int_Write_PGN64923_SPN3521
#define u8_rte_Write_PGN65110_SPN1761 u8_int_Write_PGN65110_SPN1761
#define u8_rte_Write_PGN65110_SPN3031 u8_int_Write_PGN65110_SPN3031
#define u8_rte_Write_PGN65110_SPN3517 u8_int_Write_PGN65110_SPN3517
#define u8_rte_Write_PGN65110_SPN3532 u8_int_Write_PGN65110_SPN3532
#define u8_rte_Write_PGN65110_SPN4365 u8_int_Write_PGN65110_SPN4365
//INT interface
#define u8_rte_ReadTxMsgState u8_int_ReadTxMsgState
    //Node Interface

#ifdef __cplusplus
}
#endif
#endif
