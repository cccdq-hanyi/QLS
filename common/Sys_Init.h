/*
 * Sys_Init.h
 *
 *  Created on: 2018��1��18��
 *      Author: watter
 */

#ifndef SYS_INIT_H_
#define SYS_INIT_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "S32K116.h"
#include "typedef_all.h"
#include "HW_Driver\hw_abstract.h"
#include "Node_Mgt\node_interface.h"
#include "Comm_Mgt\comm_mgt.h"
#include "APP\task\App_Task_Mgt.h"

    extern void Sys_Init(void);

#ifdef __cplusplus
}
#endif
#endif /* SYS_INIT_H_ */
