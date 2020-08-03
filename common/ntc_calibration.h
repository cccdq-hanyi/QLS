/*
 * NTC_calibration.h
 *
 *  Created on: 2020Äê4ÔÂ16ÈÕ
 *      Author: ganying
 */
#include <stdint.h>
#ifndef SOURCES_NTC_CALIBRATION_H_
#define SOURCES_NTC_CALIBRATION_H_

typedef struct _NTC_TABLE{
	uint8_t calibrat_flag;
	uint16_t ADValue[43];
	int temp[43];
}NTC_TABLE;




extern float ntc_calibration_cal_temp(uint16_t addata);

#endif /* SOURCES_NTC_CALIBRATION_H_ */
