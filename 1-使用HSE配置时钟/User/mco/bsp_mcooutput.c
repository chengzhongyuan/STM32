#include "bsp_mcooutput.h"
#include "stm32f10x_rcc.h"

/*
 * 初始化MCO引脚PA8
 */
void MCO_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
