#include "myiic.h"
#include "timer.h"
#include "math.h"


#define IIC_SDA(a)			(a)?GPIO_SetBits(GPIOA,GPIO_Pin_4):GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define IIC_SCLK(a)			(a)?GPIO_SetBits(GPIOA,GPIO_Pin_5):GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define IIC_READ_SDA()		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)

#define IIC_SDA_IN()		{GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=0x00080000;}
#define IIC_SDA_OUT()		{GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=0x00030000;}




//IIC开始信号
void IIC_Start(void)
{
	IIC_SDA_OUT();
	IIC_SDA(1);
	IIC_SCLK(1);
 	IIC_SDA(0);//START:when CLK is high,DATA change form high to low
	IIC_SCLK(0);//钳住I2C总线，准备发送或接收数据
}

//IIC结束信号
void IIC_Stop(void)
{
	IIC_SDA_OUT();
	IIC_SCLK(0);
	IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
	IIC_SCLK(1);	
	IIC_SDA(1);//发送I2C总线结束信号

}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t iicErrCnt=0;
	
	IIC_SDA_IN();
	IIC_SDA(1);
	IIC_SCLK(1);
	while(IIC_READ_SDA())
	{
		iicErrCnt++;
		if(iicErrCnt>2)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCLK(0);
	return 0;  
} 

//产生ACK应答
void IIC_Ack(void)
{
	IIC_SDA_OUT();
	IIC_SCLK(0);
	IIC_SDA(0);
	IIC_SCLK(1);
	IIC_SCLK(0);
}

//不产生ACK应答   
void IIC_NAck(void)
{
	IIC_SDA_OUT();
	IIC_SCLK(0);
	IIC_SDA(1);
	IIC_SCLK(1);
	IIC_SCLK(0);
}

//IIC发送一个字节
void IIC_Write_Byte(uint8_t txd)
{                        
    uint8_t mask;
	
	IIC_SDA_OUT();	
    IIC_SCLK(0);
	for(mask=0x80; mask!=0; mask>>=1)
    {
		if((txd & mask) == 0)
		{
			IIC_SDA(0);
		}
		else
		{
			IIC_SDA(1);
		}
		IIC_SCLK(1);
		IIC_SCLK(0);		
    }	 
} 
 
//读1个字节，
//ack=1，发送ACK，
//ack=0，发送nACK  
uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t mask,dat;
	
	IIC_SDA_IN();//SDA设置为输入
    for(mask=0x80,dat=0; mask!=0; mask>>=1)
	{
		IIC_SCLK(1);
		if(IIC_READ_SDA() == 0)
			dat &= ~mask;
		else
			dat |= mask;
		IIC_SCLK(0);
	}					 
    if (!ack)
        IIC_NAck();		//发送nACK
    else
        IIC_Ack();		//发送ACK   
    return dat;
}




void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}



