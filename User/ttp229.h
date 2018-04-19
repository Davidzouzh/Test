#ifndef TTP229__
#define TTP229__

#include "stm32f10x.h"


#define TTP229_READ_ADDR  0xA1		//ttp229的i2c读地址，ttp229不响应写操作


uint16_t TTP229_ReadData(void);

#endif


