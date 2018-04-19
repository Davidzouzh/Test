#ifndef __MYIIC__
#define __MYIIC__

#include "stm32f10x.h"


void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Write_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(uint8_t ack);

void IIC_Init(void);


#endif

