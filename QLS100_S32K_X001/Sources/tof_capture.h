/*
 * tof_capture.h
 *
 *  Created on: 2020Äê6ÔÂ2ÈÕ
 *      Author: ganying
 */

#ifndef SOURCES_TOF_CAPTURE_H_
#define SOURCES_TOF_CAPTURE_H_

#include "common.h"
#define DISTANCE 0.030 //meter
#define CAP_CLOCK 48000000
#define CAP_TIMETICK ((float) 1/48000000)
//#define CAP_TIMEOUT 200U //200us
//extern uint8_t tof_ready;
//extern void StartCap(ic_event_t event, void *userData);
//extern void StopCap(ic_event_t event, void *userData);
//extern void ftm0_Init(void);
//extern float get_realtime(void);
//extern uint8_t get_LvAvgTof(void);
//extern uint8_t get_HvAvgTof(void);
extern float tof_capture_Get_AvgVelocity(float us);
extern float tof_capture_TofCntToUs(uint32_t tofcnt);
//extern volatile uint8_t SelCh1; //channel 1
//extern volatile uint32_t tof_avg_Lv,tof_avg_Hv;

#endif /* SOURCES_TOF_CAPTURE_H_ */
