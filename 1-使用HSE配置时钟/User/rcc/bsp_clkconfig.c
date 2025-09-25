#include "bsp_clkconfig.h"
#include "stm32f10x_rcc.h"

// 使用HSE配置系统时钟
void HSE_SetSysClock(uint32_t pllmul)
{
    /*
    #define __IO volatile
    volatile 告诉编译器：
    “这个变量的值可能在程序之外被改变（比如硬件寄存器），不要优化它的读写操作。”
    然后分别定义了计数器变量和标志为变量
    */
    __IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

    /*
    把RCC复位成初始状态
    Resets the RCC clock configuration to the default reset state.

    项目	状态说明
    系统时钟源 SYSCLK	使用 HSI（内部高速 RC 振荡器，8MHz）
    PLL	                关闭（未启用）
    HSE	                关闭（外部晶振未启用）
    HSI	                开启（默认时钟源）
    AHB 分频器	        SYSCLK / 1
    APB1 分频器	        AHB / 1
    APB2 分频器	        AHB / 1
    USB 分频器	        默认值（通常为未配置）
    时钟安全系统 CSS	关闭
    所有外设时钟	    关闭（GPIO、USART、TIM 等未启用）
    */
   RCC_DeInit();

   /* 1、开启HSE时钟 */
   RCC_HSEConfig(RCC_HSE_ON);

   /* 2、等待HSE时钟稳定，通过标志位进行判断 */
   HSEStartUpStatus = RCC_WaitForHSEStartUp();

   /* 3、当程序稳定之后向下执行，设置倍频因子 */
   if(HSEStartUpStatus == SUCCESS)
   {
        /* AHB 预分频因子设置为 1 分频，HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* APB1 预分频因子设置为 1 分频，HCLK = SYSCLK */
        RCC_PCLK1Config(RCC_HCLK_Div1);

        /* APB2 预分频因子设置为 2 分频，HCLK = SYSCLK */
        RCC_PCLK2Config(RCC_HCLK_Div2);

        /* 
            设置锁相环时钟来源为HSE
            PLLCLK = 8MHz * pllmul RCC_PLLMul_x x代表设置倍频数
            pllmul 这里方便外部调节
        */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);

        /* 开启锁相环 */
        RCC_PLLCmd(ENABLE);

        /* 等待PLL稳定 */
        while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY))
        {
        }
        /* 稳定之后把PLL配置成系统时钟将 PLL 时钟作为系统时钟（SYSCLK）来源 */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* 读取时钟切换状态标志位，看看是否被选为系统时钟 */
        /* 如果没有完成就被困在这个循环里面 */
        while(RCC_GetSYSCLKSource() != 0x08){

        }
        
   }
   else{
        /* HSE开启失败的情况下，用户可以做一些配置 */
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
	
    // 配置锁相环时钟
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
