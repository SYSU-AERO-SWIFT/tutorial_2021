#include "myus.h"
#include "pwm.h"
#include "led.h"
void My_US_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	//使能串口，GPIo
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//串口，GPIO的时钟使能
	//初始化GPIO
	//PA9-TX,PA10-RX
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	//初始化串口
	USART_InitStrue.USART_BaudRate=115200;//9600 115200 38400
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不使用硬件流
	USART_InitStrue.USART_Mode=USART_Mode_Rx |USART_Mode_Tx ;//RXTX都要
	USART_InitStrue.USART_Parity=USART_Parity_No;//不用奇偶校验
	USART_InitStrue.USART_StopBits=USART_StopBits_1;//停止位为1
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;//没有奇偶校验，8位
	USART_Init(USART1,&USART_InitStrue);
	
	USART_Cmd(USART1,ENABLE);//使能串口
	//开启中断 
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//ITConfig就是在什么情况下开启中断 接收缓存区非空
	//初始化中断
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);//中断初始化
}	

void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)
	{
		res=USART_ReceiveData(USART1);
	USART_SendData(USART1,res);
	}

}


