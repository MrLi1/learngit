#include "_EXTI4.h"
#include "stm32f10x_exti.h"
#include "stm32f10x.h"
/**-------------------------------------------------------
  * @函数名 NVIC_GroupConfig
  * @功能   配置NVIC中断优先级分组函数.
  *         默认配置为1比特表示主优先级, 3比特表示次优先级
  *         用户可以根据需要修改
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void NVIC_GroupConfig(void)
{
  /* 配置NVIC中断优先级分组:
     - 2比特表示主优先级  主优先级合法取值为 0、1、2、3 
     - 2比特表示次优先级  次优先级合法取值为 0、1、2、3
     - 数值越低优先级越高，取值超过合法范围时取低bit位 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
/*==================================================================================
    NVIC_PriorityGroup   |  主优先级范围  |  次优先级范围  |   描述
  ==================================================================================
   NVIC_PriorityGroup_0  |      0         |      0-15      |   0 比特表示主优先级
                         |                |                |   4 比特表示次优先级 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |      0-1       |      0-7       |   1 比特表示主优先级
                         |                |                |   3 比特表示次优先级 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_2  |      0-3       |      0-3       |   2 比特表示主优先级
                         |                |                |   2 比特表示次优先级 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_3  |      0-7       |      0-1       |   3 比特表示主优先级
                         |                |                |   1 比特表示次优先级 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_4  |      0-15      |      0         |   4 比特表示主优先级
                         |                |                |   0 比特表示次优先级   
  ==================================================================================*/
}




void EXTIX_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	/* 开启AFIO的时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* 将PB13 对应的管脚连接到内部中断线 */    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource13);

    /* 将PB7 配置为中断模式，下降沿触发中断 */    
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;			   //中断线
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		 //中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* 将PB7 的中断优先级配置为最低 */  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //抢占优先级为0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);				 //根据NVIC_InitStructure中指定的参数初始化外设NVIC

}

