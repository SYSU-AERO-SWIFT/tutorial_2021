#ifndef __ADC_H
#define __ADC_H	 
#include "sys.h"


void My_ADC1_Init(void);//��ʼ��
u16 Get_Adc1(void);	//��ȡ��ֵ 	
u16 Get_Adc2(void) ;
u16 Get_Adc3(void);
u16 Get_Adc4(void);
u16 Get_Adc1_Average(u8 times);
u16 Get_Adc2_Average(u8 times);
u16 Get_Adc3_Average(u8 times);
u16 Get_Adc4_Average(u8 times);
	
#endif