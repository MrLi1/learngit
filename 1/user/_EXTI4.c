#include "_EXTI4.h"
#include "stm32f10x_exti.h"
#include "stm32f10x.h"
/**-------------------------------------------------------
  * @������ NVIC_GroupConfig
  * @����   ����NVIC�ж����ȼ����麯��.
  *         Ĭ������Ϊ1���ر�ʾ�����ȼ�, 3���ر�ʾ�����ȼ�
  *         �û����Ը�����Ҫ�޸�
  * @����   ��
  * @����ֵ ��
***------------------------------------------------------*/
void NVIC_GroupConfig(void)
{
  /* ����NVIC�ж����ȼ�����:
     - 2���ر�ʾ�����ȼ�  �����ȼ��Ϸ�ȡֵΪ 0��1��2��3 
     - 2���ر�ʾ�����ȼ�  �����ȼ��Ϸ�ȡֵΪ 0��1��2��3
     - ��ֵԽ�����ȼ�Խ�ߣ�ȡֵ�����Ϸ���Χʱȡ��bitλ */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
/*==================================================================================
    NVIC_PriorityGroup   |  �����ȼ���Χ  |  �����ȼ���Χ  |   ����
  ==================================================================================
   NVIC_PriorityGroup_0  |      0         |      0-15      |   0 ���ر�ʾ�����ȼ�
                         |                |                |   4 ���ر�ʾ�����ȼ� 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |      0-1       |      0-7       |   1 ���ر�ʾ�����ȼ�
                         |                |                |   3 ���ر�ʾ�����ȼ� 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_2  |      0-3       |      0-3       |   2 ���ر�ʾ�����ȼ�
                         |                |                |   2 ���ر�ʾ�����ȼ� 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_3  |      0-7       |      0-1       |   3 ���ر�ʾ�����ȼ�
                         |                |                |   1 ���ر�ʾ�����ȼ� 
  ----------------------------------------------------------------------------------
   NVIC_PriorityGroup_4  |      0-15      |      0         |   4 ���ر�ʾ�����ȼ�
                         |                |                |   0 ���ر�ʾ�����ȼ�   
  ==================================================================================*/
}




void EXTIX_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	/* ����AFIO��ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* ��PB13 ��Ӧ�Ĺܽ����ӵ��ڲ��ж��� */    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource13);

    /* ��PB7 ����Ϊ�ж�ģʽ���½��ش����ж� */    
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;			   //�ж���
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		 //�ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½��ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* ��PB7 ���ж����ȼ�����Ϊ��� */  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);				 //����NVIC_InitStructure��ָ���Ĳ�����ʼ������NVIC

}

