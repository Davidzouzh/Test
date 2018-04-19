

#include "timer.h"
#include "usart.h"
#include "myiic.h"
#include "ttp229.h"



//主函数入口
int main(void)
{
	uint16_t i=0;
	SysTick_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	uart_init(9600);
	IIC_Init();
	
	printf("OK");
	
	while(1)
	{
		i=TTP229_ReadData();
		if(i!=0)
			printf("%d",i);
	}
	
	
}


