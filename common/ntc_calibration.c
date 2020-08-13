/**===========================================================================*/
/* FILE		: ntc_calibration.c                                               */
/*============================================================================*/
/* DESCRIPTION :  QLS100                                                        */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) 2019 by Hanyi                                                */
/* ALL RIGHTS RESERVED                                                        */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |            Change             |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*    V0.1       2020/07/31         Initial Version              Cdq   */
/*============================================================================*/

#include <ntc_calibration.h>
#include "stdlib.h"
NTC_TABLE ntc_liquid={0,
//	{//R18=R20=200K
//			38865,35146,31267,27381,23636,20150,17002,14231,11843,9818,8122,
//			6714,5554,4600,3818,3177,2652,2221,1867,1574,1333,1132,965,826,
//			710,612,529,459,400,349,306,269,237,209,186,165,147,131,118,106,95,86,77
//	},
	{4050,4035,4015,3990,3958,3919,3871,3812,3742,3659,3563,3453 ,3329,3192,3042,2881,2713,2538,2360,2183,
				2008,1838,1675,1521,1377,1243,1120,1007,905,812,729,655,588,528,475,428,385,348,314,284,
				257,233,212},
	{-55,-50,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,
			100,105,110,115,120,125,130,135,140,145,150,155
	}
};

/***************************************************************************************************
 * Function: ntc_calibration_cal_temp
 * Discription: calibrate temperature by ntc resistor
 * Param : addata  AD sample  value
 * Return: rf32_temperature   unit c
 * Note:data element of  AD table is sorted from large to small
 ***************************************************************************************************/
short int ntc_calibration_cal_temp(uint16_t addata)
{
    uint8_t  bg,ed,mid;


    float max_temp=250;

    float rf32_temperature = 0.0;
    short int ri16_temperature = 0;
    bg = 0 ;
    ed = sizeof(ntc_liquid.ADValue)/2-1 ;
    if	(addata >= ntc_liquid.ADValue[bg])
    	return ntc_liquid.temp[bg] ;
    else if(addata <= ntc_liquid.ADValue[ed])
    	return ntc_liquid.temp[ed] ;
    while(bg < ed)
    {
    	mid = (bg+ed)/2 ;
    	if (addata == ntc_liquid.ADValue[mid] )
    		break ;
    	if (addata >ntc_liquid.ADValue[mid+1] && addata < ntc_liquid.ADValue[mid])
    		break ;
        if	(addata < ntc_liquid.ADValue[mid])
        	bg = mid ;
        else
        	ed = mid ;
    }
    if(bg > ed )
    	return -100;//what happens？
//    return ntc_liquid.temp[mid];// 粗算
//    rf32_temperature = ntc_liquid.temp[mid]+((float)(abs(ntc_liquid.ADValue[mid]-addata))/(ntc_liquid.ADValue[mid]-ntc_liquid.ADValue[mid+1]))*step;//精算 AD 越小，温度越高
    rf32_temperature = ntc_liquid.temp[mid]+((float)(abs(ntc_liquid.ADValue[mid]-addata))/(ntc_liquid.ADValue[mid+1]-ntc_liquid.ADValue[mid]))
    		 * (ntc_liquid.temp[mid]-ntc_liquid.temp[mid+1]);//精算 AD 越小，温度越高
    rf32_temperature = (rf32_temperature >= max_temp) ? max_temp : rf32_temperature;
    ri16_temperature = rf32_temperature + 0.5 ;
    return ri16_temperature;
}


