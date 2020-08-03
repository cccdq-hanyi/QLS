#ifndef typedef_all_h
#define typedef_all_h   
#include <stdint.h>
/******************************************************************************
 * These defines allow for easier porting to other compilers. 
 ******************************************************************************/
/*
#ifndef	 uint8_t
typedef unsigned char   uint8_t;
#endif
#ifndef	 uint16_t
typedef unsigned int    uint16_t;
#endif
#ifndef	 uint32_t
typedef unsigned long   uint32_t;
#endif
#ifndef  int8_t
//typedef char            int8_t;
#endif
#ifndef	int16_t
//typedef int             int16_t;
#endif
#ifndef int32_t
//typedef long            int32_t;
#endif
 */

/******************************************************************************
 * Boolean values
 ******************************************************************************/
#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif
/*****************************************************************************/
typedef void (*func_v_v)(void);


#endif        
