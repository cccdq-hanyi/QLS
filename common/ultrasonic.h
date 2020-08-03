/*
 * ultrasonic.h
 *
 *  Created on: 2020Äê4ÔÂ22ÈÕ
 *      Author: ganying
 */
#include <stdint.h>
#ifndef SOURCES_ULTRASONIC_H_
#define SOURCES_ULTRASONIC_H_
#define TABLEX_ELEMENTS	10

//calibration table
typedef struct _SINGLE_TABLE_CACUL{
	uint8_t temperature;
	uint16_t ADValue[10];
}SINGLE_TABLE_CACUL;

typedef union _SINGLE_TABLE_UNION{
	SINGLE_TABLE_CACUL members;
	uint8_t databytes[sizeof(SINGLE_TABLE_CACUL)];
}SINGLE_TABLE_UNION;

typedef struct _TABLE1_CACUL{
	uint8_t calibrat_flag;
	uint8_t start;
	uint8_t end;
	uint8_t step;
	SINGLE_TABLE_CACUL table;
}TABLE1_CACUL;

typedef struct _TABLE10_CACUL{
	uint8_t calibrat_flag;
	uint8_t start;
	uint8_t end;
	uint8_t step;
	SINGLE_TABLE_CACUL table[10];
}TABLE10_CACUL;

typedef union _TABLE1_UNION{
	TABLE1_CACUL members;
	uint8_t databytes[sizeof(TABLE1_CACUL)];
}TABLE1_UNION;

typedef union _TABLE10_UNION{
	TABLE10_CACUL members;
	uint8_t databytes[sizeof(TABLE10_CACUL)];
}TABLE10_UNION;





#endif /* SOURCES_ULTRASONIC_H_ */
