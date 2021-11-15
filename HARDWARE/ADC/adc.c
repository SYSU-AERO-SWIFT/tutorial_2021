#include "adc.h"
#include "delay.h"

void My_ADC1_Init(void)
{	
	
	ADC_InitTypeDef ADC_InitStructure;//����ADC��ʼ���ṹ�����
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);       
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//ʹ��ADC1ʱ��
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 ;                    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;      
	GPIO_Init(GPIOA, &GPIO_InitStructure);//PA5
	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//ADCת�������ڵ���ģʽ���������͵���
	ADC_InitStructure.ADC_NbrOfChannel = 1;//˳����й���ת����ADCͨ������Ŀ������ADC�ɼ�ͨ�������޸ģ�
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //ʧ��ɨ��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���������ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ת�������Ҷ���
	ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

	ADC_Cmd(ADC1, ENABLE);//ʹ��ADC1
	//У׼
	ADC_ResetCalibration(ADC1); //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
	ADC_StartCalibration(ADC1);//��ʼADC1У׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���

}



u16 Get_Adc1(void)   
{
//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��	  			    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5);//ADC1ѡ���ŵ�x,����˳��y,����ʱ��n������
		//У׼
	ADC_ResetCalibration(ADC1); //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
	ADC_StartCalibration(ADC1);//��ʼADC1У׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����

}

u16 Get_Adc2(void)   
{
	
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��	  			    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);//ADC1ѡ���ŵ�x,����˳��y,����ʱ��n������
	//У׼
	ADC_ResetCalibration(ADC1); //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
	ADC_StartCalibration(ADC1);//��ʼADC1У׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
    return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����

}

u16 Get_Adc3(void)
{
	
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��	  			    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);//ADC1ѡ���ŵ�x,����˳��y,����ʱ��n������
	//У׼
	ADC_ResetCalibration(ADC1); //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
	ADC_StartCalibration(ADC1);//��ʼADC1У׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����

}	
u16 Get_Adc4(void) 
{
	
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��	  			    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5);//ADC1ѡ���ŵ�x,����˳��y,����ʱ��n������
	//У׼
	ADC_ResetCalibration(ADC1); //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
	ADC_StartCalibration(ADC1);//��ʼADC1У׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc1_Average(u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc1();
    }
    return temp_val/times;
}    

u16 Get_Adc2_Average(u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc2();
    }
    return temp_val/times;
}  

u16 Get_Adc3_Average(u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc3();
    }
    return temp_val/times;
}  

u16 Get_Adc4_Average(u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc4();
    }
    return temp_val/times;
}  
