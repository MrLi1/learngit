/***********************************************

标题: hmc5883l.c
作者: 秋阳电子
网址：http://qiuyangdz.taobao.com
日期: 2013/03/15
版本：v1.0
功能: hmc5883l初始化及数据读取
说明：读取三轴地磁原始数据
*************************************************/
#include "stm32f10x.h"
#include "hmc5883l.h"
#include "iic.h"

#define HMC5883L_ADDR       0x3c    // AD0 = 0 时地址
#define CONFIG_REGA         0x00
#define CONFIG_REGB         0x01	
#define MODE_REG            0x02
#define HMC5883L_BURST_ADDR 0x03	         	     
/*************************************************

名称：hmc5883l_init(void)
功能：hmc5883l初始化
输入参数：无
输出参数：无
返回值：无
**************************************************/
void hmc5883l_init(void)
{
  u8 data_buf;

  /* 8 samples averaged, 75Hz frequency, no artificial bias */
  data_buf = 0x78;
  iic_rw(&data_buf, 1, CONFIG_REGA, HMC5883L_ADDR, WRITE);
  
  /* +-4.7Gau */
  data_buf = 0xa0;
  iic_rw(&data_buf, 1, CONFIG_REGB, HMC5883L_ADDR, WRITE);

  /* continuos measurement mode */
  data_buf = 0x00;
  iic_rw(&data_buf, 1, MODE_REG,HMC5883L_ADDR, WRITE);
}
/*************************************************

名称：hmc5883l_get_data(s16 *mx, s16 *my, s16 *mz)
功能：hmc5883l数据读取
输入参数：
  	s16 *mx 变量指针 
	s16 *my
	s16 *mz  
输出参数：hmc5883l三轴原始数据
返回值：无
**************************************************/
void hmc5883l_get_data(s16 *mx, s16 *my, s16 *mz)
{
  u8 data_buf[6];

  iic_rw(&data_buf[0], 6, HMC5883L_BURST_ADDR, HMC5883L_ADDR, READ);
  *mx = data_buf[0] * 0x100 + data_buf[1];
  *my = data_buf[4] * 0x100 + data_buf[5];
  *mz = data_buf[2] * 0x100 + data_buf[3];
}
/***************************END OF FILE**********************************************************************/
