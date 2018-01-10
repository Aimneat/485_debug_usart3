/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   485测试。
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	char *pbuf;
	uint16_t len;
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  Debug_USART_Config();
	
	Key_GPIO_Config();
	
  _485_Config();
  
	/* 发送一个字符串 */
//	Usart_SendString( DEBUG_USART,"这是一个485接收回显实验\n");
//	printf("这是一个485接收回显实验\n");
	
  while(1)
	{	
		/*按一次按键发送一次数据*/
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
//			printf("\r\n已使用485发送数据！\r\n");
//			
//		}else{
			
			pbuf=get_rebuff(&len);
			
		  if(len>=MingLingChangDu){
//			if(len>=2){

//			_485_DEBUG_ARRAY((uint8_t*)pbuf,len);
				MingLingChuLi((uint8_t *)pbuf,len);  //命令处理
				clean_rebuff();
//			}
		}
    

	}	
}



/*********************************************END OF FILE**********************/

