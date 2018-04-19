#ifndef TIMER__
#define TIMER__

#include "stm32f10x.h"

extern uint8_t  loop200HzFlag,loop100HzFlag,loop50HzFlag,loop10HzFlag;

//�δ�ʱ����ʼ��
//config��ϵͳռ���ˣ���init
void SysTick_Init(void);

//��ȡ��ǰʱ�䣬us��ms
uint32_t micros(void);
uint32_t millis(void);

//��ʱ��ռ��CPU����ʱ
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
	


#endif


