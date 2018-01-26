/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   485���ԡ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./485/bsp_485.h"
#include "./485/485.h"
#include "./key/bsp_key.h"


//extern uint8_t receive_flag;
//extern uint8_t ucTemp;


static void _delay(__IO u32 nCount)
{

	for(; nCount != 0; nCount--);
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	char *pbuf;
	uint16_t len;
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
	
	Key_GPIO_Config();
	
  _485_Config();
  
	/* ����һ���ַ��� */
//	Usart_SendString( DEBUG_USART,"����һ��485���ջ���ʵ��\n");
//	printf("����һ��485���ջ���ʵ��\n");
	
  while(1)
	{	
		/*��һ�ΰ�������һ������*/
//		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
//		{
//     uint16_t i;
			
//			_485_TX_EN();
//			
//			for(i=0;i<=100;i++)
//      _485_SendByte(i);
//			
//			_delay(0xfff);
//			_485_RX_EN();
//			printf("\r\n��ʹ��485�������ݣ�\r\n");
//			
//		}else{
			
			pbuf=get_rebuff(&len);
			
		  if(len>=MingLingChangDu){
//			if(len>=2){

//			_485_DEBUG_ARRAY((uint8_t*)pbuf,len);
				MingLingChuLi((uint8_t *)pbuf,len);  //�����
				clean_rebuff();
//			}
		}
    

	}	
}



/*********************************************END OF FILE**********************/

