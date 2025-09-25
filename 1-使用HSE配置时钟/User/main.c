#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_clkconfig.h"

#define SOFT_DELAY Delay(0x0FFFFF);

void Delay(__IO u32 nCount); 

int main(void)
{	
	/* LED 端口初始化 */
	LED_GPIO_Config();	 
	KEY_GPIO_Config();
	LED1(OFF);
	LED2(OFF);
	LED3(OFF);

	while (1)
	{
		// if(Key_Scan(GPIOC,GPIO_Pin_13) == KEY_ON)
		// {
		// 	LED3_TOGGLE;
		// 	// LED3(ON);
		// }
		HSE_SetSysClock(RCC_PLLMul_2);
		LED3(ON);
		Delay(0x0FFFFF);
		LED3(OFF);
		Delay(0x0FFFFF);

	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
