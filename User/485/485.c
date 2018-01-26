/**
  ******************************************************************************
  * @file    485.c
  * @author  
  * @version V1.0
  * @date    
  * @brief   485Ӧ��
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */ 
  
#include "./485/485.h"
#include "./485/bsp_485.h"
#include "string.h"
#include <stdbool.h>

float f=1;

static void _delay(__IO u32 nCount)
{

	for(; nCount != 0; nCount--);
}

/**
  * @brief  ����������Դ��ڷ���������
  * @param  array: ���յ�����
  * @param  num: ���յ�������ֽڳ���
  * @retval None
  */
void MingLingChuLi(uint8_t *array,uint16_t num)
{
  uint8_t* a= array;
	
	if(a[0]==0xf0)
	{
	   if(a[1]==0x01)
		 {			 
			send_float(f);
		 }
		 if(a[1]==0x02)
		 {
			 show_pressure("��ǰѹ��ֵΪ��");
		 }
	}
	else{
			  show("address error");
	}

}


/**
  * @brief  16���Ʒ��͸�����
  * @param  x: Ҫ���͵ĸ�����
  * @retval None
  */
void send_float(float x)
{
  send_bytes((unsigned char *)&x,sizeof(x));
}

/**
  * @brief  ��485�����ֽ�
  * @param  start: �������ݵ���ʼָ��
  * @param  len:�������ݵĳ���
  * @retval None
  */
void send_bytes(unsigned char *start,int len)
{
   int i;
	
		_485_TX_EN();
	 for(i=0;i<len;i++)
	 _485_SendByte(start[i]);
	
	 _delay(0xfff);
	 _485_RX_EN();
}

/**
  * @brief  485���ͽ�Ҫ��ӡ���ַ�����������
  * @param  str: Ҫ���͵��ַ���
  * @retval None
  */
void show_pressure(char *str)
{
      _485_TX_EN();
	    puts(str);
			printf("%.3f Pa\n",f);
			_delay(0xfff);
	    _485_RX_EN();
}

/**
  * @brief  485���ͽ�Ҫ��ӡ���ַ���
  * @param  str: Ҫ���͵��ַ���
  * @retval None
  */
void show(char *str)
{
      _485_TX_EN();
	    puts(str);
			_delay(0xfff);
	    _485_RX_EN(); 
}

//bool shuzuxiangdeng(uint8_t *array,uint8_t *mingling)
//{
//	uint16_t i;
//  uint8_t* a= array;
//	uint8_t* m=mingling;
//	
//	for(i=1;i<MingLingChangDu;i++)
//	{
//	  if(a[i]!=m[i])
//			break;
//	}
//	
//	return i==MingLingChangDu;
//}
/*********************************************END OF FILE**********************/
