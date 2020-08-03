/*
 * common.h
 *
 *  Created on: 2020Äê6ÔÂ1ÈÕ
 *      Author: ganying
 */

#include "lpspiCom1.h"
#include "S32K116.h"
#include "spi_comm.h"
//#include "tof_capture.h"
#ifndef COMMON_H_
#define COMMON_H_


#define DIL_TDC_ERRB_PORT	PTE
#define DIL_TDC_ERRB		5U
#define DO_TDC_RESET_PORT	PTE
#define DO_TDC_RESET		8U
#define DO_TDC_EN_PORT		PTB
#define DO_TDC_EN			4U
#define DO_HV_PWR_EN_PORT		PTD
#define DO_HV_PWR_EN			5U
#define DO_TDC_TRIGGER_PORT		PTD
#define DO_TDC_TRIGGER			3U
#define DI_HV_STATUS_PORT		PTA
#define DI_HV_STATUS			11U
#define DO_HV_STATUS_DIS_PORT		PTA
#define DO_HV_STATUS_DIS			10U


#define QLS_111		(1)



typedef struct QLS_RESULTS_CAL_MEMBERS {
  uint8_t ru8_status;//t_results.members.status
  uint8_t ru8_temp_ultrasonic;//t_results.members.temperature_pt0
  uint8_t ru8_temp_environment;//t_results.members.temperature_pt1
  uint8_t ru8_concentration; //concen 0.25%/bit 0% offset
  uint16_t ru16_level;//level 0.1mm/bit 0 offset
  uint8_t ru8_level_perc; //tank level percent 0.4%/bit 0 offset
  uint8_t ru8_fmi_temp;//SPN 3519
  uint8_t ru8_fmi_concentration1;//SPN 3520
  uint8_t ru8_fmi_concentration2;//SPN 3521
  uint8_t ru8_fmi_level;//SPN 3532
  uint8_t ru8_fmi_voltage;//SPN 4365
} qls_results_cal_members;
typedef union QLS_RESULTS_CAL {
	qls_results_cal_members members;
  uint8_t rs8_candata[sizeof(qls_results_cal_members)];
} qls_results_cal;
qls_results_cal runion_qls_results;


qls_results_cal sendresults;
#endif /* COMMON_H_ */


