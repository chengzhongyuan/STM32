#ifndef __KEY_H
#define __KEY_H

#define KEY_ON	1
#define KEY_OFF	0
#include "stm32f10x.h"
void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif __KEY_H
