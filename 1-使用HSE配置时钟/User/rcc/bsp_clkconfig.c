#include "bsp_clkconfig.h"
#include "stm32f10x_rcc.h"

// ʹ��HSE����ϵͳʱ��
void HSE_SetSysClock(uint32_t pllmul)
{
    /*
    #define __IO volatile
    volatile ���߱�������
    �����������ֵ�����ڳ���֮�ⱻ�ı䣨����Ӳ���Ĵ���������Ҫ�Ż����Ķ�д��������
    Ȼ��ֱ����˼����������ͱ�־Ϊ����
    */
    __IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

    /*
    ��RCC��λ�ɳ�ʼ״̬
    Resets the RCC clock configuration to the default reset state.

    ��Ŀ	״̬˵��
    ϵͳʱ��Դ SYSCLK	ʹ�� HSI���ڲ����� RC ������8MHz��
    PLL	                �رգ�δ���ã�
    HSE	                �رգ��ⲿ����δ���ã�
    HSI	                ������Ĭ��ʱ��Դ��
    AHB ��Ƶ��	        SYSCLK / 1
    APB1 ��Ƶ��	        AHB / 1
    APB2 ��Ƶ��	        AHB / 1
    USB ��Ƶ��	        Ĭ��ֵ��ͨ��Ϊδ���ã�
    ʱ�Ӱ�ȫϵͳ CSS	�ر�
    ��������ʱ��	    �رգ�GPIO��USART��TIM ��δ���ã�
    */
   RCC_DeInit();

   /* 1������HSEʱ�� */
   RCC_HSEConfig(RCC_HSE_ON);

   /* 2���ȴ�HSEʱ���ȶ���ͨ����־λ�����ж� */
   HSEStartUpStatus = RCC_WaitForHSEStartUp();

   /* 3���������ȶ�֮������ִ�У����ñ�Ƶ���� */
   if(HSEStartUpStatus == SUCCESS)
   {
        /* AHB Ԥ��Ƶ��������Ϊ 1 ��Ƶ��HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* APB1 Ԥ��Ƶ��������Ϊ 1 ��Ƶ��HCLK = SYSCLK */
        RCC_PCLK1Config(RCC_HCLK_Div1);

        /* APB2 Ԥ��Ƶ��������Ϊ 2 ��Ƶ��HCLK = SYSCLK */
        RCC_PCLK2Config(RCC_HCLK_Div2);

        /* 
            �������໷ʱ����ԴΪHSE
            PLLCLK = 8MHz * pllmul RCC_PLLMul_x x�������ñ�Ƶ��
            pllmul ���﷽���ⲿ����
        */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);

        /* �������໷ */
        RCC_PLLCmd(ENABLE);

        /* �ȴ�PLL�ȶ� */
        while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY))
        {
        }
        /* �ȶ�֮���PLL���ó�ϵͳʱ�ӽ� PLL ʱ����Ϊϵͳʱ�ӣ�SYSCLK����Դ */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* ��ȡʱ���л�״̬��־λ�������Ƿ�ѡΪϵͳʱ�� */
        /* ���û����ɾͱ��������ѭ������ */
        while(RCC_GetSYSCLKSource() != 0x08){

        }
        
   }
   else{
        /* HSE����ʧ�ܵ�����£��û�������һЩ���� */
        while(1){

        }
   }
}



void HSI_SetSysClock(uint32_t pllmul)
{
	__IO uint32_t HSIStartUpStatus = 0;

    RCC_DeInit();
	RCC_HSICmd(ENABLE);
	

	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
	{
	}	

	HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;

  if (HSIStartUpStatus == RCC_CR_HSIRDY)
  {
 
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    RCC_PCLK1Config(RCC_HCLK_Div2);
	
    // �������໷ʱ��
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmul);
//------------------------------------------------------------------//

 
    RCC_PLLCmd(ENABLE);


    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { 
    while (1)
    {
    }
  }
}
