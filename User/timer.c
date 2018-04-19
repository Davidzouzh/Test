

#include "timer.h"



volatile uint32_t sysTickUptime = 0;
volatile uint32_t usTicks = 0;


uint8_t  loop200HzFlag=0, loop100HzFlag=0, loop50HzFlag=0, loop10HzFlag=0;
volatile uint16_t loop200HzCnt=0, loop100HzCnt=0, loop50HzCnt=0, loop10HzCnt=0;

//�δ�ʱ��systick�ж�
void SysTick_Handler(void) 
{
	//1ms��1�����ڶ�ȡϵͳʱ�����ʱ
	sysTickUptime++;
	
	if(++loop200HzCnt*200 >= 1000)
	{
		loop200HzCnt=0;
		loop200HzFlag=1;
	}
	if(++loop100HzCnt*100 >= 1000)
	{
		loop100HzCnt=0;
		loop100HzFlag=1;
	}
	if(++loop50HzCnt*50 >= 1000)
	{
		loop50HzCnt=0;
		loop50HzFlag=1;
	}
	if(++loop10HzCnt*10 >= 1000)
	{
		loop10HzCnt=0;
		loop10HzFlag=1;
	}
	
}


//ϵͳsystick��ʼ��
//config��ϵͳռ���ˣ���init
void SysTick_Init(void)
{
		RCC_ClocksTypeDef clocks;
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8  

    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency/1000000;	//��ʼ��usTicks
	
		SysTick_Config(SystemCoreClock/1000);	//SysTick����ϵͳtick��ʱ������ʼ�����жϣ�1ms
}

// Return system uptime in microseconds (rollover in 70minutes)
//���� us
uint32_t micros(void)
{
    register uint32_t ms, cycle_cnt;
    do {
        ms = sysTickUptime;
        cycle_cnt = SysTick->VAL;
    } while (ms != sysTickUptime);
    return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

// Return system uptime in milliseconds (rollover in 49 days)
//���� ms
uint32_t millis(void)
{
    return sysTickUptime;
}

//��ʱus		    								   
void delay_us(uint32_t nus)
{
	uint32_t t0 = micros();
	while(micros() - t0 < nus);
}

//��ʱms
void delay_ms(uint32_t nms)
{
	uint32_t t0 = micros();
	while(micros() - t0 < nms * 1000);
}


