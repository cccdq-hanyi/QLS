/*
 * tof_capture.h
 *
 *  Created on: 2020年6月2日
 *      Author: ganying
 */

#ifndef TOF_CAPTURE_H_
#define TOF_CAPTURE_H_

//#include "common.h"
#define DISTANCE 0.030 //meter,挡板到晶体距离
#define CAP_CLOCK 48000000
#define CAP_TIMETICK ((float) 21381.264558904 )//ps
#define CAP_TIMEOUT 200U //200us
extern uint8_t tof_ready;
extern void StartCap(ic_event_t event, void *userData);
extern void StopCap(ic_event_t event, void *userData);
extern void ftm0_Init(void);
extern float tof_capture_get_realtimelv(void);
extern float tof_capture_get_realtimehv(void);
extern uint8_t tof_capture_get_LvAvgTof(void);
extern uint8_t tof_capture_get_HvAvgTof(void);
extern float tof_capture_get_AvgVelocity(float us);
extern float tof_capture_TofCntToUs(uint32_t tofcnt);
extern volatile	uint8_t SelCh1; //channel 1
extern volatile uint32_t ru32_tof_avg_Lv,ru32_tof_avg_Hv;

#endif /* TOF_CAPTURE_H_ */
