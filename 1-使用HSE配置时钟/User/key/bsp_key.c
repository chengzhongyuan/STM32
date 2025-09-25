#include "bsp_key.h"  
void KEY_GPIO_Config(void)
{
    // ����Ҫ�����Ž��г�ʼ��,�����������óɸ�������ģʽ
    // ѡ��PC13���ţ���������ʱ�ߵ�ƽ
    GPIO_InitTypeDef GPIO_InitStructure;
    // ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**�������±��ú�
*��������Ϊ�ߵ�ƽ������KEY_ON=1��KEY_OFF=0
*����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0��KEY_OFF=1����
*/
#define KEY_ON 1
#define KEY_OFF 0

/**
*@brief����Ƿ��а�������
*@param GPIOx:����Ķ˿�,x�����ǣ�A...G��
*@param GPIO_PIN:����Ķ˿�λ��������GPIO_PIN_x��x������0...15��
*@retval������״̬
* @arg KEY_ON:��������
* @arg KEY_OFF:����û����
*/

/*
    GPIO_TypeDef* GPIOx ������һ�� GPIO �˿ڵļĴ����ṹ��ָ��
*/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    // ��ⰴ���Ƿ���
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    {
        // �ȴ������ͷ�
        while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON);
        return KEY_ON;
    }
    else
        return KEY_OFF;
}

