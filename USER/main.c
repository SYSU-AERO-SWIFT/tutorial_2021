#include "stm32f10x.h"
#include "delay.h"
//#include "led.h"
//#include "myus.h"
//#include "hongw.h"
//#include "hcsr.h"
#include "pwm.h"
#include "adc.h"
#include "OLED.h"
#include "exti.h" 
#include "usart.h"
#include "timer.h"
#include "usart3.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"


extern dataPoint_t currentDataPoint;
int flag_study_motion=0;     
int flag_repeat_motion=0;
bool flag_remote_control=false;
int move_count=0;
int i=0;

float duty_cycle1;
float duty_cycle2;
float duty_cycle3;
float duty_cycle4;

u16 V1_in;
u16 V2_in;
u16 V3_in;
u16 V4_in;
u16 V_temp;

uint32_t angle1;
uint32_t angle2;
uint32_t angle3;
uint32_t angle4;

//�ĸ��������ڼ�¼�ĸ������״̬
u16 record1[100];
u16 record2[100];
u16 record3[100];
u16 record4[100];


u16 compare1,compare2,compare3,compare4;

void control(void);           //�ú���ʵ�ֵ�λ�����ƻ�е���˶�
void study_motion(void);      //�ú���ʵ��ѧϰ����
void repeat_motion(void);     //�ú���ʵ�ָ��ֶ���
void hardware_init(void);
void Gizwits_Init(void);

 int main(void)
 {	
	 //����Ӳ����ʼ��
	 hardware_init();
	 //������Э�飬ESP8266�Լ�����3��ʼ��
	  Gizwits_Init();
	 printf("��ʼ�����\r\n");
     while(1)
	{	
		if(flag_repeat_motion==0 && flag_study_motion==0 && !flag_remote_control )
		{			
		    control();
		}
		if(flag_repeat_motion==0 && flag_study_motion==1 && !flag_remote_control)
		{
			study_motion();
		}
		if(flag_repeat_motion==1 && flag_study_motion==0 && !flag_remote_control)
		{
			repeat_motion();
		}
		if(flag_remote_control)
		{
			userHandle();
			gizwitsHandle( (dataPoint_t*) &currentDataPoint); //Э�鴦���ϱ��ýṹ��
		}
	}
 }
 
 void control(void)
 {
		 //���Ƶ�һ�����
		V_temp=Get_Adc1_Average(100);
		if( abs(V_temp-V1_in)>200 )
		{
			V1_in=V_temp;
			//USART_SendData(USART1,V1_in);
			duty_cycle1=(float) V1_in/4096;
			compare1=(u16) ((duty_cycle1*2+0.5)/20*20000);
			//�õ���PWMģʽ1
			compare1=20000-compare1;
			TIM_SetCompare1(TIM3,compare1);   //500/20000=0.5/20
		}
        
		
		//���Ƶڶ������
		V_temp=Get_Adc2_Average(100);
		//USART_SendData(USART1,V2_in);
		if( abs(V_temp-V2_in)>200 )
		{
			V2_in=V_temp;
			duty_cycle2=(float) V2_in/4096;
			compare2=(u16) ((duty_cycle2*2+0.5)/20*20000);
			compare2=20000-compare2;
			TIM_SetCompare2(TIM3,compare2);   //500/20000=0.5/20
		}
		
		
		//���Ƶ��������
		V_temp=Get_Adc3_Average(100);
		//USART_SendData(USART1,V3_in);
		if( abs(V_temp-V3_in)>200 )
		{
			V3_in=V_temp;
			duty_cycle3=(float) V3_in/4096;
			compare3=(u16) ((duty_cycle3*2+0.5)/20*20000);
			compare3=20000-compare3;
			TIM_SetCompare3(TIM3,compare3);   //500/20000=0.5/20
		}
		
		
		//���Ƶ��ĸ����
		V_temp=Get_Adc4_Average(200);
		//USART_SendData(USART1,V4_in);
		if( abs(V_temp-V4_in)>100 )
		{
			V4_in=V_temp;
			duty_cycle4=(float) V4_in/4096;
			compare4=(u16) ((duty_cycle4*1+0.5)/20*20000);
			compare4=20000-compare4;
			TIM_SetCompare4(TIM3,compare4);   //500/20000=0.5/20
		}
		
		//��ʾ��һ�������״̬
		OLED_ShowString(1,1,"base:");
		angle1=(float) V1_in/4096*180;
		OLED_ShowNum(1,7,angle1,3);
		//��ʾ�ڶ��������״̬
		OLED_ShowString(2,1,"joint1:");
		angle2=(float) V2_in/4096*180;
		OLED_ShowNum(2,9,angle2,3);
		
		//��ʾ�����������״̬
		OLED_ShowString(3,1,"joint2:");
		angle3=(float) V3_in/4096*180;
		OLED_ShowNum(3,9,angle3,3);
		
		//��ʾ���ĸ������״̬

		OLED_ShowString(4,1,"claw:");
		angle4=V4_in/4096*180;
		if(V4_in>3048)
		{
			
			OLED_ShowString(4,6,"release!");
		}
		else
		{

			OLED_ShowString(4,6,"catch!");
			OLED_ShowString(4,12,"   ");  
		}
		//delay_ms(100);
	
 }
 
void study_motion(void)
 {
	 move_count=0;
	 OLED_Clear();
     OLED_ShowString(2,1,"Record mode");
	while(flag_study_motion==1 && flag_repeat_motion==0 && move_count<1000)
	{
	 //���Ƶ�һ���������¼
		V_temp=Get_Adc1_Average(200);
		if( abs(V_temp-V1_in)>200 )
		{
			V1_in=V_temp;
			//USART_SendData(USART1,V1_in);
			duty_cycle1=(float) V1_in/4096;
			compare1=(u16) ((duty_cycle1*2+0.5)/20*20000);
			//�õ���PWMģʽ1
			compare1=20000-compare1;
			TIM_SetCompare1(TIM3,compare1);   //500/20000=0.5/20
		}
        record1[move_count]=compare1;
		
		//���Ƶڶ����������¼
		V_temp=Get_Adc2_Average(200);
		//USART_SendData(USART1,V2_in);
		if( abs(V_temp-V2_in)>200 )
		{
			V2_in=V_temp;
			duty_cycle2=(float) V2_in/4096;
			compare2=(u16) ((duty_cycle2*2+0.5)/20*20000);
			compare2=20000-compare2;
			TIM_SetCompare2(TIM3,compare2);   //500/20000=0.5/20
		}
		record2[move_count]=compare2;
		
		
		//���Ƶ������������¼
		V_temp=Get_Adc3_Average(100);
		//USART_SendData(USART1,V3_in);
		if( abs(V_temp-V3_in)>200 )
		{
			V3_in=V_temp;
			duty_cycle3=(float) V3_in/4096;
			compare3=(u16) ((duty_cycle3*2+0.5)/20*20000);
			compare3=20000-compare3;
			TIM_SetCompare3(TIM3,compare3);   //500/20000=0.5/20
		}
		record3[move_count]=compare3;
		
		//���Ƶ��ĸ��������¼
		V_temp=Get_Adc4_Average(200);
		//USART_SendData(USART1,V4_in);
		if( abs(V_temp-V4_in)>200 )
		{
			V4_in=V_temp;
			duty_cycle4=(float) V4_in/4096;
			compare4=(u16) ((duty_cycle4*1+0.5)/20*20000);
			compare4=20000-compare4;
			TIM_SetCompare4(TIM3,compare4);   //500/20000=0.5/20
		}
		record4[move_count]=compare4;
		
		delay_ms(100);
		move_count++;
	}
	OLED_Clear();
 }
// 
// 
 void repeat_motion(void)
 {
	 OLED_Clear();
     OLED_ShowString(2,1,"Repeatition mode");
	 TIM_SetCompare1(TIM3,record1[0]);
	 delay_ms(200);
	 TIM_SetCompare2(TIM3,record2[0]);
	 delay_ms(200);
	 TIM_SetCompare3(TIM3,record3[0]);
	 delay_ms(200);
	 TIM_SetCompare4(TIM3,record4[0]);
	 delay_ms(200);
     i=0;
	 while(i<move_count)
	 {
		 TIM_SetCompare1(TIM3,record1[i]);
		 TIM_SetCompare2(TIM3,record2[i]);
		 TIM_SetCompare3(TIM3,record3[i]);
		 TIM_SetCompare4(TIM3,record4[i]);
		 delay_ms(100);
		 i=i+1;
	 }
	 flag_repeat_motion=0;
	 flag_study_motion=0;
	 OLED_Clear();
 }

 void hardware_init(void)
 {
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
    //My_LED_Init();
	delay_init();
//	My_US_Init();
	//My_HW_Init();
	My_ADC1_Init();
	My_TIM3_Init(19999,71);//����Ϊ20ms  (arr+1)(psc+1)/Tclk=20000*72/72000000=20ms
	EXTI_Key_Config(); 
	uart_init(115200);
 }
 
void Gizwits_Init(void)
{
	TIM4_Int_Init(9,7199);
	usart3_init(9600);
	memset((uint8_t*)&currentDataPoint,0,sizeof(currentDataPoint));
	gizwitsInit();
}


