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

short int C2_CALCON_RU8_XTEMP[10] = {-11,0,10,20,30,40,50,60,70,80};//从小到大
uint8_t C2_CALCON_RU8_YCON[10] = {0,40,80,100,112,120,128,140,180,220};//  concentration 10,15,20,25,28,30,32,35,45,55,从小到大，0.25%/bit
uint8_t calibrat_flag;
float C2_CALCON_TABLE[10][10]={{1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32},
							   {1400.0,1440.43,1480.51,1499.69,1511.91,1518.92,1525.9,1535.28,1576.07,1613.32}};//默认声速随温度升高数值增大

TABLE1_UNION C2_LEVEL_TABLE={0,{0,}};;


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
uint8_t ultrasonic_cal_concentration(float * velocity,short int temp)
{
    uint8_t  bg,ed,mid;
    uint8_t start=80; //0.25% unit 20%
    uint8_t end=160;//0.25% unit 40%
//    uint8_t step=8;//0.25% unit 2%
    uint8_t calcnt = 0;
    uint8_t i,con1,con2;
    static uint8_t ru8_concentration = 0;
    uint8_t p_temp=0,p_v=0;
    float v = * velocity;
    if ( v < 5.0)
    {
    	ru8_concentration = 255;
    	return ru8_concentration;
    }
    //找温度
    bg = 0 ;
    ed = TABLEX_ELEMENTS-1 ;
    mid = 0;
    if	(temp <= C2_CALCON_RU8_XTEMP[bg])
    {
    	p_temp = bg ;//ru8_concentration = 255;return ru8_concentration;
    	calcnt = 1;
    }
    else if(temp >= C2_CALCON_RU8_XTEMP[ed])
    {
    	p_temp = ed ;//ru8_concentration = 255;return ru8_concentration;
    	calcnt = 1;
    }
    else
    {
		while(bg < ed)
		{
			mid = (bg+ed)/2 ;
			if (temp == C2_CALCON_RU8_XTEMP[mid] )
			{
				p_temp = mid;
				calcnt = 1;
				break ;
			}

			if (temp <C2_CALCON_RU8_XTEMP[mid+1] && temp > C2_CALCON_RU8_XTEMP[mid])
			{
				p_temp = mid;
				calcnt = 2;
				break ;
			}

			if	(temp > C2_CALCON_RU8_XTEMP[mid])
				bg = mid ;
			else
				ed = mid ;
		}
    }
    if(bg > ed )
    {
    	ru8_concentration = 255;
    	return ru8_concentration;//what happens？
    }
    //找声速
    bg = 0 ;
    ed = TABLEX_ELEMENTS-1 ;
    mid = 0;
	if (1 == calcnt)
	{
		if	(v <= C2_CALCON_TABLE[p_temp][bg])
		{
			ru8_concentration = C2_CALCON_RU8_YCON[bg] ;
			return ru8_concentration;
		}
		else if(v >= C2_CALCON_TABLE[p_temp][ed])
		{
			ru8_concentration = C2_CALCON_RU8_YCON[ed] ;
			return ru8_concentration;
		}else
		{
			while(bg < ed)
			{
				mid = (bg+ed)/2 ;
				if (v == C2_CALCON_TABLE[p_temp][mid] )
				{
					p_v = mid;
					break ;
				}

				if (v <C2_CALCON_TABLE[p_temp][mid+1] && v > C2_CALCON_TABLE[p_temp][mid])
				{
					p_v = mid;
					break ;
				}
				if	(v > C2_CALCON_TABLE[p_temp][mid])
					bg = mid ;
				else
					ed = mid ;
			}
		}
		if(bg > ed )
	    {
	    	ru8_concentration = 255;
	    	return ru8_concentration;//what happens？
	    }else
			ru8_concentration = (((uint8_t )( v - C2_CALCON_TABLE[p_temp][p_v])) * 20);

			//ru8_concentration = C2_CALCON_RU8_YCON[p_v]+ (( v - C2_CALCON_TABLE[p_temp][p_v] ) * (C2_CALCON_RU8_YCON[p_v+1] - C2_CALCON_RU8_YCON[p_v])) / (C2_CALCON_TABLE[p_temp][p_v+1] - C2_CALCON_TABLE[p_temp][p_v]);
	}else if (2 == calcnt)
	{
		bg = 0 ;
		ed = TABLEX_ELEMENTS-1 ;
		if	( v <= C2_CALCON_TABLE[p_temp][bg] || v <= C2_CALCON_TABLE[p_temp+1][bg] )
		{
			ru8_concentration = C2_CALCON_RU8_YCON[bg] ;
			return ru8_concentration;
		}else if( v >= C2_CALCON_TABLE[p_temp][ed] || v >= C2_CALCON_TABLE[p_temp+1][ed] )
		{
			ru8_concentration = C2_CALCON_RU8_YCON[ed] ;
			return ru8_concentration;
		}else
		{
			while(bg < ed)
			{
				mid = (bg+ed)/2 ;
				if (v == C2_CALCON_TABLE[p_temp][mid] )
				{
					p_v = mid;
					break ;
				}

				if (v <C2_CALCON_TABLE[p_temp][mid+1] && v > C2_CALCON_TABLE[p_temp][mid])
				{
					p_v = mid;
					break ;
				}
				if	(v > C2_CALCON_TABLE[p_temp][mid])
					bg = mid ;
				else
					ed = mid ;
			}
		}
		if(bg > ed )
	    {
	    	ru8_concentration = 255;
	    	return ru8_concentration;//what happens？
	    }else
			con1 = C2_CALCON_RU8_YCON[p_v]+ \
					(( v - C2_CALCON_TABLE[p_temp][p_v] ) * (C2_CALCON_RU8_YCON[p_v+1] - C2_CALCON_RU8_YCON[p_v])) / (C2_CALCON_TABLE[p_temp][p_v+1] - C2_CALCON_TABLE[p_temp][p_v]);
		bg = 0 ;
		ed = TABLEX_ELEMENTS-1 ;
		while(bg < ed)
		{
			mid = (bg+ed)/2 ;
			if (v == C2_CALCON_TABLE[p_temp+1][mid] )
			{
				p_v = mid;
				break ;
			}

			if (v <C2_CALCON_TABLE[p_temp+1][mid+1] && v > C2_CALCON_TABLE[p_temp+1][mid])
			{
				p_v = mid;
				break ;
			}
			if	(v > C2_CALCON_TABLE[p_temp+1][mid])
				bg = mid ;
			else
				ed = mid ;
		}
		if(bg > ed )
		{
			ru8_concentration = 255;
			return ru8_concentration;//what happens？
		}else
			con2 = C2_CALCON_RU8_YCON[p_v]+ \
					(( v - C2_CALCON_TABLE[p_temp+1][p_v] ) * (C2_CALCON_RU8_YCON[p_v+1] - C2_CALCON_RU8_YCON[p_v])) / (C2_CALCON_TABLE[p_temp+1][p_v+1] - C2_CALCON_TABLE[p_temp+1][p_v]);
			ru8_concentration = ((temp - C2_CALCON_RU8_XTEMP[p_temp]) * abs(con2 - con1)) / (C2_CALCON_RU8_XTEMP[p_temp+1] - C2_CALCON_RU8_XTEMP[p_temp] );
	}else
		ru8_concentration = 255;

    return ru8_concentration;// 1unit=0.25%
}
