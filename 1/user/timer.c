/***********************************************

标题: timer.c
作者: 秋阳电子
网址：http://qiuyangdz.taobao.com
日期: 2013/03/15
版本：v1.0
功能: 定时器初及其中断初始化
说明：timer2外设的初始化
*************************************************/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "timer.h"
/*************************************************

名称：timer_init(void)
功能：timer3外设初始化（中断 定时时间）
输入参数：无
输出参数：无
返回值：  无
**************************************************/
void timer_init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 7200 - 1;    // 0.1ms
  TIM_TimeBaseStructure.TIM_Prescaler = 25 - 1;  // (Period + 1) * (Prescaler + 1) / 72M = 2.5ms
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);

  /* TIM IT enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

}
/***************************END OF FILE**********************************************************************/
