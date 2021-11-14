#include "hcsr.h"
#include "delay.h"

int N=0;
float distance=0;
void My_CSB_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//GPIO初始化，定时器初始化，初始化外部中断
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//PB6-Trig(输入)所以PB6是输出模式 PB7-Echo(输出)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//Trig
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//Echo
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //下拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//溢出时间tim=(arr+1)*(psc+1)/72000000	50000*72/72000000=500ms
	TIM_TimeBaseStructure.TIM_Period = 49999;
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_Cmd(TIM2, ENABLE);
}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
	     N += 1;		   
	}
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除中断标志位
}

int count=0;
float Distance(void)
{
	  GPIO_ResetBits(GPIOB, GPIO_Pin_6);//预先拉低Trig引脚
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		delay_us(20);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);//发出10us的脉冲
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0);	//等待信号发出，信号发出，计数器置0,信号发出，变为高电平，引脚置1
		//N=0;
		TIM2->CNT=0;//us级别读取
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 1); //等待信号接受，信号发出过程中，引脚一直置位1 
		count=TIM2->CNT;
		//count=N;
		//单位cm
		//v = 340m/s = 34000cm/s = 34000cm/10^6us = 0.034cm/us
		//s = vt/2 = t*0.034/2 = t*0.017 ≈ t/58	
		distance=(float)count/58;					
		return distance;
}
