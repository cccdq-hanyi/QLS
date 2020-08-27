/**===========================================================================*/
/* FILE		: tmr_level.c                                                    */
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
/*    V0.1       2020/08/11         Initial Version              Cdq   */
/*============================================================================*/
#include "common.h"
#include "tmr_level.h"
/***************** tmr 阻值液位对照表 ******************************************/
/*液位从低到高
 * AD采样电压单位：1bit = Vmax / 4096
 * 液位单位 :1bit = 0.1mm
 */
uint16_t C1_TMR_LEVEL[15] = {450,550,650,800,1000,1200,1400,1600,1800,2000,2200,2400,2600,2800,3050};
uint16_t C1_TMR_ADVAL[15] = {3048,2892,2680,2377,1908,1758,1598,1387,1154,1031,897,750,590,413,217};

/***************************************************************************************************
 * Function: tmr_level_cal
 * Discription: calibrate level by tmr resistor
 * Param : addata  AD sample  value
 * Return: rf32_temperature   unit mm
 * Note:data element of  AD table is sorted from large to small
 ***************************************************************************************************/
uint16_t tmr_level_cal(uint16_t addata)
{
    uint8_t  bg,ed,mid;
    bg = 0 ;
    uint16_t admaxval = 4096;
    uint16_t level_tmp = 0;
    ed = sizeof(C1_TMR_ADVAL)/2-1 ;
    if	(addata <= C1_TMR_ADVAL[ed])
    	return C1_TMR_LEVEL[ed] ;
    else if (addata >= C1_TMR_ADVAL[bg])
    	return  ((admaxval - addata)  * C1_TMR_LEVEL[bg]) / (admaxval - C1_TMR_ADVAL[bg])  ;
    while(bg < ed)
    {
    	mid = (bg+ed)/2 ;
    	if (addata == C1_TMR_ADVAL[mid] )
    		break ;
    	if (addata > C1_TMR_ADVAL[mid+1] && addata < C1_TMR_ADVAL[mid])
    		break ;
        if	(addata < C1_TMR_ADVAL[mid])
        	bg = mid ;
        else
        	ed = mid ;
    }
    if(bg > ed )
    	return 0;//what happens？
    return level_tmp = C1_TMR_LEVEL[mid] + \
    		((C1_TMR_ADVAL[mid] - addata) * (C1_TMR_LEVEL[mid] - C1_TMR_LEVEL[mid+1])) / (C1_TMR_ADVAL[mid] - C1_TMR_ADVAL[mid+1]);
        		 //AD 越小，液位越高
}

