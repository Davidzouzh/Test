

#include "ttp229.h"
#include "myiic.h"
#include "stdio.h"



/**************************实现函数********************************************
*函数原型:		uint8_t TTP229_ReadData(void)
*功　　能:	    读取ttp229的按键数据

返回   按键值

		1	2 	3	4	左/上警	右/退水
		5	6	7	8
		9	10	11	12
		0	确定
		
		确定=0xf0
		左/上警=0xf1
		右/退水=0xf2
		
		无按键=0xff
		
*******************************************************************************/ 
uint16_t TTP229_ReadData(void)		//i2c读取
{
	uint16_t data;
	
	IIC_Start();						//产生一个起始条件
	IIC_Write_Byte(TTP229_READ_ADDR);	//发送目标设备读地址	
	IIC_Wait_Ack();						//发送ACK
	data = (uint16_t)IIC_Read_Byte(1)<<8 | (uint16_t)IIC_Read_Byte(0);		//第一字节ACK，第二字节NACK
    IIC_Stop();							//产生一个停止条件
	
	return data;
}


