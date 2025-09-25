#include "bsp_key.h"  
void KEY_GPIO_Config(void)
{
    // 首先要对引脚进行初始化,按键引脚配置成浮空输入模式
    // 选择PC13引脚，按键按下时高电平
    GPIO_InitTypeDef GPIO_InitStructure;
    // 打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**按键按下标置宏
*按键按下为高电平，设置KEY_ON=1，KEY_OFF=0
*若按键按下为低电平，把宏设置成KEY_ON=0，KEY_OFF=1即可
*/
#define KEY_ON 1
#define KEY_OFF 0

/**
*@brief检测是否有按键按下
*@param GPIOx:具体的端口,x可以是（A...G）
*@param GPIO_PIN:具体的端口位，可以是GPIO_PIN_x（x可以是0...15）
*@retval按键的状态
* @arg KEY_ON:按键按下
* @arg KEY_OFF:按键没按下
*/

/*
    GPIO_TypeDef* GPIOx 它代表一个 GPIO 端口的寄存器结构体指针
*/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    // 检测按键是否按下
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    {
        // 等待按键释放
        while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON);
        return KEY_ON;
    }
    else
        return KEY_OFF;
}

