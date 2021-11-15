#include "led.h"
int flagtest=10;
void My_LED_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct;//配置GPIO的信息
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//开时钟总线
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//复用推挽
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;//13
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,  &GPIO_InitStruct);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);//set暗，reset亮
}
