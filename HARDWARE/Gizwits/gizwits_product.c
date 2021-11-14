/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "usart3.h"
#include "PWM.h"

extern uint32_t angle1;
extern uint32_t angle2;
extern uint32_t angle3;
extern uint32_t angle4;

extern u16 compare1;
extern u16 compare2;
extern u16 compare3;
extern u16 compare4;


static uint32_t timerMsCount;

/** Current datapoint */
dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {


      case EVENT_steer1:
        currentDataPoint.valuesteer1 = dataPointPtr->valuesteer1;
        GIZWITS_LOG("Evt:EVENT_steer1 %d\n",currentDataPoint.valuesteer1);
        //user handle
	    compare1= ((((float) (currentDataPoint.valuesteer1)) /180)*2+0.5)/20*20000;
	    compare1=20000-compare1;
		TIM_SetCompare1(TIM3,compare1);
        break;
      case EVENT_steer2:
        currentDataPoint.valuesteer2 = dataPointPtr->valuesteer2;
        GIZWITS_LOG("Evt:EVENT_steer2 %d\n",currentDataPoint.valuesteer2);
        //user handle
	  	compare2= ((((float) (currentDataPoint.valuesteer2)) /180)*2+0.5)/20*20000;
	    compare2=20000-compare2;
		TIM_SetCompare2(TIM3,compare2);
        break;
      case EVENT_steer3:
        currentDataPoint.valuesteer3 = dataPointPtr->valuesteer3;
        GIZWITS_LOG("Evt:EVENT_steer3 %d\n",currentDataPoint.valuesteer3);
        //user handle
	  	    compare3= ((((float) (currentDataPoint.valuesteer3)) /180)*2+0.5)/20*20000;
	    compare3=20000-compare3;
		TIM_SetCompare3(TIM3,compare3);
        break;
      case EVENT_steer4:
        currentDataPoint.valuesteer4 = dataPointPtr->valuesteer4;
        GIZWITS_LOG("Evt:EVENT_steer4 %d\n",currentDataPoint.valuesteer4);
        //user handle
	  	    compare4= ((((float) (currentDataPoint.valuesteer4)) /180)*2+0.5)/20*20000;
	    compare4=20000-compare4;
		TIM_SetCompare4(TIM3,compare4);
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valuestate1 = ;//Add Sensor Data Collection
    currentDataPoint.valuestate2 = ;//Add Sensor Data Collection
    currentDataPoint.valuestate3 = ;//Add Sensor Data Collection
    currentDataPoint.valuestate4 = ;//Add Sensor Data Collection
    */
	currentDataPoint.valuestate1= angle1;
	currentDataPoint.valuestate2= angle2;
	currentDataPoint.valuestate3= angle3;
	currentDataPoint.valuestate4= angle4;
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valuesteer1 = ;
      currentDataPoint.valuesteer2 = ;
      currentDataPoint.valuesteer3 = ;
      currentDataPoint.valuesteer4 = ;
      currentDataPoint.valuestate1 = ;
      currentDataPoint.valuestate2 = ;
      currentDataPoint.valuestate3 = ;
      currentDataPoint.valuestate4 = ;
    */

}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
	__set_FAULTMASK(1);
    NVIC_SystemReset();
}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function ，For Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief uartWrite

* Serial write operation, send data to the WiFi module

* @param buf      : Data address
* @param len       : Data length
*
* @return : Not 0,Serial send success;
*           -1，Input Param Illegal
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }
    
    #ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);
    }
    GIZWITS_LOG("\n");
    #endif

    for(i=0; i<len; i++)
    {
        //USART_SendData(UART, buf[i]);//STM32 test demo
        //Serial port to achieve the function, the buf[i] sent to the module
		USART_SendData(USART3, buf[i]);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
        if(i >=2 && buf[i] == 0xFF)
        {
           USART_SendData(USART3, 0x55);
           while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
			//Serial port to achieve the function, the 0x55 sent to the module
          //USART_SendData(UART, 0x55);//STM32 test demo
        }
    }


    
    return len;
}






