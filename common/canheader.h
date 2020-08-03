/*
 * canheader.h
 *
 *  Created on: 2020年7月15日
 *      Author: CDQ
 */

#ifndef CANHEADER_H_
#define CANHEADER_H_
/*
 * 特殊使用：freemaster 使用的flexcan sdk版本较高，旧版本can pal 驱动少了以下定义，
 * 本头文件为此增加以下定义
 * canheader.h 需要包含在can_pal1.c中
 */
typedef enum {
#if defined(CAN_INSTANCE_COUNT)
    CAN_INST_TYPE_FLEXCAN = 0u,
#endif /* defined(CAN_INSTANCE_COUNT) */
} can_inst_type_t;

#endif /* CANHEADER_H_ */
