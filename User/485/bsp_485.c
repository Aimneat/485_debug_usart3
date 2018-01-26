/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author 
  * @version V1.0
  * @date    
  * @brief   485驱动
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */ 
  
#include "./485/bsp_485.h"


//1.初始化485使用到的串口
//2.编写TX_RX引脚控制输出
//3.编写中断服务函数
//4.编写收发测试

//注意！！ 控制TX_RX_EN引脚状态切换后，一定要加延时


//作业：参考本例子，编写485通讯驱动。试验一下把切换状态中的延时取消，观察现象


 static void Delay(__IO u32 nCount); 


/// 配置USART接收中断
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = _485_INT_IRQ; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/*
 * 函数名：_485_Config
 * 描述  ：USART GPIO 配置,工作模式配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void _485_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART clock */
	RCC_AHB1PeriphClockCmd(_485_USART_RX_GPIO_CLK|_485_USART_TX_GPIO_CLK|_485_RE_GPIO_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(_485_USART_CLK, ENABLE); 

	
	  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(_485_USART_RX_GPIO_PORT,_485_USART_RX_SOURCE, _485_USART_RX_AF);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(_485_USART_TX_GPIO_PORT,_485_USART_TX_SOURCE,_485_USART_TX_AF);

	
	/* USART GPIO config */
   /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = _485_USART_TX_PIN  ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(_485_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = _485_USART_RX_PIN;
  GPIO_Init(_485_USART_RX_GPIO_PORT, &GPIO_InitStructure);

  
  /* 485收发控制管脚 */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin = _485_RE_PIN  ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(_485_RE_GPIO_PORT, &GPIO_InitStructure);
	  
	/* USART mode config */
	USART_InitStructure.USART_BaudRate = _485_USART_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(_485_USART, &USART_InitStructure); 
  USART_Cmd(_485_USART, ENABLE);
	
	NVIC_Configuration();
	/* 使能串口接收中断 */
	USART_ITConfig(_485_USART, USART_IT_RXNE, ENABLE);
	
	GPIO_ResetBits(_485_RE_GPIO_PORT,_485_RE_PIN); //默认进入接收模式
}



/***************** 发送一个字符  **********************/
//使用单字节数据发送前要使能发送引脚，发送后要使能接收引脚。
void _485_SendByte(  uint8_t ch )
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(_485_USART,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(_485_USART, USART_FLAG_TXE) == RESET);	
	
}
/*****************  发送指定长度的字符串 **********************/
void _485_SendStr_length( uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;

	  _485_TX_EN()	;//	使能发送数据	
    while(k < strlen)
    {
        _485_SendByte( *(str + k) );
        k++;
    } 
		
	/*加短暂延时，保证485发送数据完毕*/
//	Delay(0xFFF);
		
	_485_RX_EN()	;//	使能接收数据
}


/*****************  发送字符串 **********************/
void _485_SendString( uint8_t *str)
{
	unsigned int k=0;
	
	  _485_TX_EN()	;//	使能发送数据
	
	while(*(str + k)!='\0')
	{
			_485_SendByte(  *(str + k) );
			k++;
	}
	printf("\n");
	
//	do
//	{
//			_485_SendByte(  *(str + k) );
////				printf("%c",*(str+k));
//			k++;
//	}while(*(str + k)!='\0');
//	printf("\n");
	/*加短暂延时，保证485发送数据完毕*/
			Delay(0xfFF);
			_485_RX_EN()	;//	使能接收数据
		

}



//中断缓存串口数据
#define UART_BUFF_SIZE      1024
volatile    uint16_t uart_p = 0;
uint8_t     uart_buff[UART_BUFF_SIZE];

void bsp_485_IRQHandler(void)
{
    if(uart_p<UART_BUFF_SIZE)
    {
        if(USART_GetITStatus(_485_USART, USART_IT_RXNE) != RESET)
        {
            uart_buff[uart_p] = USART_ReceiveData(_485_USART);
            uart_p++;
						
						USART_ClearITPendingBit(_485_USART, USART_IT_RXNE);
        }
    }
		else
		{
			USART_ClearITPendingBit(_485_USART, USART_IT_RXNE);
//			clean_rebuff();       
		}
}



//获取接收到的数据和长度
char *get_rebuff(uint16_t *len) 
{
    *len = uart_p;
    return (char *)&uart_buff;
}

//清空缓冲区
void clean_rebuff(void) 
{

    uint16_t i=UART_BUFF_SIZE+1;
    uart_p = 0;
	  while(i)
		uart_buff[--i]=0;

}

///重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
//	  _485_TX_EN();
		/* 发送一个字节数据到串口DEBUG_USART */
		USART_SendData(_485_USART, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(_485_USART, USART_FLAG_TXE) == RESET);
	
//	  _485_RX_EN_NODelay();
		return (ch);
}

/////重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
//{
//		/* 等待串口输入数据 */
//		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

//		return (int)USART_ReceiveData(DEBUG_USART);
//}

static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/
