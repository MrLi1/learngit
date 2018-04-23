/***********************************************

标题: mian.c
作者: 秋阳电子
网址：http://qiuyangdz.taobao.com
日期: 2013/03/15
版本：v1.0
MDK-ARM 版本: v4.12
ST 库版本：v3.50  
功能: 周期更新欧拉角通过USB实时传输至PC
说明：
*************************************************/
#include "stm32f10x.h"
#include "iic.h"
#include "timer.h"
#include "mpu6050.h"
#include "hmc5883l.h"
#include "ahrs.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_istr.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_pwr.h"
#include "_EXTI4.h"
#include <math.h>

//#define USB

u8 flg_get_senor_data;
u8 flg_send_data;
u8 out[35]  ={0x5A,0x5A}; 
s16 gx, gy, gz, ax ,ay, az, mx, my, mz, temperature;
s16 gx_offset=-53, gy_offset=6, gz_offset=3, ax_offset=130, ay_offset=20, az_offset=-80, mx_offset=10,  my_offset=-20, mz_offset=-24;
float pitch, roll, yaw;
float f_gx, f_gy, f_gz;
s16 temp;
/******************************************************************************/
void delay(u32 count)
{
  for(; count != 0; count--);
}
/***************************************************************************/
int main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  u16 i;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_5);  // blue led


  delay(0x80000);
  NVIC_GroupConfig();
  EXTIX_Init();
  usart_init();				 
  iic_init();
  timer_init();
 
  mpu6050_init();
  hmc5883l_init();

  while (1)
  {
    if(flg_get_senor_data)
    {
      flg_get_senor_data = 0;

#ifdef USB
	  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	  NVIC_Init(&NVIC_InitStructure);
#endif	    
	 
      mpu6050_get_data(&gx, &gy, &gz, &ax, &ay, &az, &temperature);
      hmc5883l_get_data(&mx, &my ,&mz);

#ifdef USB
	  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure); 
#endif
     
	  gx -= gx_offset;
	  gy -= gy_offset;
	  gz -= gz_offset;
	  ax -= ax_offset;
	  ay -= ay_offset;
	  az -= az_offset;
	  mx -= mx_offset;
	  my -= my_offset;
	  mz -= mz_offset;
	   
      f_gx = gx * GYRO_SCALE;
	  f_gy = gy * GYRO_SCALE;
	  f_gz = gz * GYRO_SCALE;

	  get_euler_angle(f_gx, f_gy, f_gz, ax, ay, az, mx, my, mz, &pitch, &roll, &yaw);

//	  out[2] = (u8)(gx >> 8);
//	  out[3] = (u8)(gx);
//	  out[4] = (u8)(gy >> 8);
//	  out[5] = (u8)(gy);
//	  out[6] = (u8)(gz >> 8);
//	  out[7] = (u8)(gz);
	  out[2] = (u8)(ax >> 8);
	  out[3] = (u8)(ax);
	  out[4] = (u8)(ay >> 8);
	  out[5] = (u8)(ay);
	  out[6] = (u8)(az >> 8);
	  out[7] = (u8)(az);
//	  out[14] = (u8)(mx >> 8);
//	  out[15] = (u8)(mx);
//	  out[16] = (u8)(my >> 8);
//	  out[17] = (u8)(my);
//	  out[18] = (u8)(mz >> 8);
//	  out[19] = (u8)(mz);

	  temp = (s16)(pitch * 100);
	  out[8] = (u8)(temp >> 8);
	  out[9] = (u8)(temp);

	  temp = (s16)(roll * 100);
	  out[10] = (u8)(temp >> 8);
	  out[11] = (u8)(temp);

	  temp = (s16)(yaw * 100);
	  out[12] = (u8)(temp >> 8);
	  out[13] = (u8)(temp);

	  out[14]=0xA5;
	  out[15]=0xA5;
	 
	  if(1==flg_send_data)
	  {
	    flg_send_data=0;
		 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;;
  		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 		GPIO_Init(GPIOA, &GPIO_InitStructure); 
//#ifdef USB
//        USART_To_USB_Send_Data(&out[0], 26);
//#else 
	    for(i = 0; i < 16; i++)
	    {
	      USART_SendData(USART1, out[i]);
          while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
	    }

  		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 		GPIO_Init(GPIOA, &GPIO_InitStructure);
//#endif
       GPIOA->ODR ^= (1 << 5);
	  }	
	  	  
    }  // end if							   
  }  // end while
}
/*************************************************************************************************/
//void USB_LP_CAN1_RX0_IRQHandler(void)
//{
//  USB_Istr();
//}
/************************END OF FILE************************************************************/
