/*
 * canheader.h
 *
 *  Created on: 2020��7��15��
 *      Author: CDQ
 */

#ifndef CANHEADER_H_
#define CANHEADER_H_
/*
 * ����ʹ�ã�freemaster ʹ�õ�flexcan sdk�汾�ϸߣ��ɰ汾can pal �����������¶��壬
 * ��ͷ�ļ�Ϊ���������¶���
 * canheader.h ��Ҫ������can_pal1.c��
 */
typedef enum {
#if defined(CAN_INSTANCE_COUNT)
    CAN_INST_TYPE_FLEXCAN = 0u,
#endif /* defined(CAN_INSTANCE_COUNT) */
} can_inst_type_t;

#endif /* CANHEADER_H_ */
