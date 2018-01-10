/**
  ******************************************************************************
  * @file    485.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   485应用
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
			 show_pressure("当前压力值为：");
		 }
	}
	else{
			  show("address error");
	}

}

void send_float(float x)
{
  send_bytes((unsigned char *)&x,sizeof(x));
}

void send_bytes(unsigned char *start,int len)
{
   int i;
	
		_485_TX_EN();
	 for(i=0;i<len;i++)
	 _485_SendByte(start[i]);
	
	 _delay(0xfff);
	 _485_RX_EN();
}

void show_pressure(char *str)
{
      _485_TX_EN();
	    puts(str);
			printf("%.3f Pa\n",f);
			_delay(0xfff);
	    _485_RX_EN();
}

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
