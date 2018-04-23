/***********************************************

����: hmc5883l.c
����: ��������
��ַ��http://qiuyangdz.taobao.com
����: 2013/03/15
�汾��v1.0
����: hmc5883l��ʼ�������ݶ�ȡ
˵������ȡ����ش�ԭʼ����
*************************************************/
#include "stm32f10x.h"
#include "hmc5883l.h"
#include "iic.h"

#define HMC5883L_ADDR       0x3c    // AD0 = 0 ʱ��ַ
#define CONFIG_REGA         0x00
#define CONFIG_REGB         0x01	
#define MODE_REG            0x02
#define HMC5883L_BURST_ADDR 0x03	         	     
/*************************************************

���ƣ�hmc5883l_init(void)
���ܣ�hmc5883l��ʼ��
�����������
�����������
����ֵ����
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

���ƣ�hmc5883l_get_data(s16 *mx, s16 *my, s16 *mz)
���ܣ�hmc5883l���ݶ�ȡ
���������
  	s16 *mx ����ָ�� 
	s16 *my
	s16 *mz  
���������hmc5883l����ԭʼ����
����ֵ����
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
