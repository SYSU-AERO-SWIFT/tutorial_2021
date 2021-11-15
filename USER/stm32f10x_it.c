/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "OLED.h"
#include "delay.h"
#include "gizwits_product.h"
extern int flag_study_motion;     
extern int flag_repeat_motion;
extern bool flag_remote_control;

 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void  EXTI3_IRQHandler(void)    //开始记录动作
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) 
	{
		delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0);  //松手检测
		delay_ms(10);
		flag_study_motion=1;
		flag_repeat_motion=0;
        //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line3);     
	}  
}

void EXTI15_10_IRQHandler(void) //开始复现动作
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) 
	{
		
		delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0);  //松手检测
		delay_ms(10);
		flag_study_motion=0;
		flag_repeat_motion=1;
	    //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line13);     
	}  
}

void  EXTI4_IRQHandler(void)    //开始学习动作
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(EXTI_Line4) != RESET) 
	{
		delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0);  //松手检测
		delay_ms(10);
		flag_study_motion=0;
		flag_repeat_motion=0;
		flag_remote_control=!flag_remote_control;
		gizwitsSetMode(WIFI_SOFTAP_MODE);
        printf("\r\nWIFI_SOFTAP_MODE\r\n") ; // 打印调试信息
        //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line4);     
	}  
}