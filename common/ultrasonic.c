/**===========================================================================*/
/* FILE		: ultrasonic.c                                                    */
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
#include "common.h"
#include "ultrasonic.h"
#define TABLEX_ELEMENTS	10

int8_t rs8_x_temp[10] = {-20,-10,-5,0,5,10,15,20,30,45};//从小到大
float rf32_y_velocity[10] = {1500,1510,1520,1530,1540,1550,1560,1570,1580,1590};//从小到大
uint8_t calibrat_flag;
uint8_t C2_CALCON_TABLE[10][10]={0,};

TABLE1_UNION C2_LEVEL_TABLE={0,{0,}};;
TABLE10_UNION C2_CON_TABLE={0,{0,}};


/***************************************************************************************************
 * Function: ultrasonic_cal_level
 * Discription: Calibrate liquid level
 * Param : addata AD sample value
 * Return:  i16_level unit 0.1mm
 * Note: data element of  AD table is sorted from small to large
 ***************************************************************************************************/
uint16_t ultrasonic_cal_level(uint16_t addata)
{
    uint8_t  bg,ed,mid;
    uint16_t start=1500;//0.1mm unit
    uint16_t end=7000;//0.1mm unit
    uint16_t step=500;//0.1mm unit
    int i16_level;
    bg = 0 ;
    ed = sizeof(C2_LEVEL_TABLE.members.table.ADValue)/2-1 ;
    if	(addata <= C2_LEVEL_TABLE.members.table.ADValue[bg])
    	return start ;
    else if(addata >= C2_LEVEL_TABLE.members.table.ADValue[ed])
    	return end ;
    while(bg < ed)
    {
    	mid = (bg+ed)/2 ;
    	if (addata == C2_LEVEL_TABLE.members.table.ADValue[mid] )
    		break ;
    	if (addata <C2_LEVEL_TABLE.members.table.ADValue[mid+1] && addata > C2_LEVEL_TABLE.members.table.ADValue[mid])
    		break ;
        if	(addata > C2_LEVEL_TABLE.members.table.ADValue[mid])
        	bg = mid ;
        else
        	ed = mid ;
    }
    if(bg > ed )
    	return 0;//what happens？
    i16_level=start+((addata-C2_LEVEL_TABLE.members.table.ADValue[mid])/(C2_LEVEL_TABLE.members.table.ADValue[mid+1]-C2_LEVEL_TABLE.members.table.ADValue[mid]))*step;//精算
    return i16_level;// 1unit=0.1mm
}

/***************************************************************************************************
 * Function: ultrasonic_cal_concentration
 * Discription: calibrate concentration
 * Param : v  speed of sound,temp  liquid temperature
 * Return: uint8_t urea concentration   unit %
 * Note:
 ***************************************************************************************************/
uint8_t ultrasonic_cal_concentration(float v,uint8_t temp)
{
    uint8_t  bg,ed,mid;
    uint8_t start=80; //0.25% unit 20%
    uint8_t end=160;//0.25% unit 40%
//    uint8_t step=8;//0.25% unit 2%
    uint8_t  i;
    uint8_t ru8_concentration;
    uint8_t p_temp=0,p_v=0;
    //找温度
    bg = 0 ;
    ed = TABLEX_ELEMENTS-1 ;
    mid = 0;
    if	(temp <= rs8_x_temp[bg])
    	p_temp = bg ;
    else if(temp >= rs8_x_temp[ed])
    	p_temp = ed ;
    else
    {
		while(bg < ed)
		{
			mid = (bg+ed)/2 ;
			if (temp == rs8_x_temp[mid] )
			{
				p_temp = mid;
				break ;
			}

			if (temp <rs8_x_temp[mid+1] && temp > rs8_x_temp[mid])
			{
				p_temp = mid;
				break ;
			}

			if	(temp > rs8_x_temp[mid])
				bg = mid ;
			else
				ed = mid ;
		}
    }
    if(bg > ed ) p_temp = 0;//what happens？

    //找声速
    bg = 0 ;
    ed = TABLEX_ELEMENTS-1 ;
    mid = 0;

    if	(v <= rf32_y_velocity[bg])
    	p_v = bg ;
    else if(v >= rf32_y_velocity[ed])
    	p_v = ed ;
    else
    {
		while(bg < ed)
		{
			mid = (bg+ed)/2 ;
			if (v == rf32_y_velocity[mid] )
			{
				p_v = mid;
				break ;
			}

			if (v <rf32_y_velocity[mid+1] && v > rf32_y_velocity[mid])
			{
				p_v = mid;
				break ;
			}
			if	(v > rf32_y_velocity[mid])
				bg = mid ;
			else
				ed = mid ;
		}
    }
    if(bg > ed ) p_v = 0;//what happens？

//    ru8_concentration = C2_CALCON_TABLE[p_v][p_temp];
    ru8_concentration = C2_CALCON_TABLE[p_v][p_temp]+ \
    		( C2_CALCON_TABLE[p_v+1][p_temp+1] - C2_CALCON_TABLE[p_v][p_temp] ) * ( rf32_y_velocity[p_v+1] - rf32_y_velocity[p_v] ) / ( v - rf32_y_velocity[p_v] );////粗算,平面如何计算？
    return ru8_concentration;// 1unit=0.25%
	return 0;
}
