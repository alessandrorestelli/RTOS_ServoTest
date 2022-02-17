//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"                     	// ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>

#define PIN_SERVO PE12

#define EVENT_SMISTASX  					 1 << 4 // zero shift for bit0
#define EVENT_SMISTADX  		 			 1 << 5 // zero shift for bit0

void ServoMotoreInit(void);
void vTaskSmistaSx(void * pvParameters);
void vTaskSmistaDx(void * pvParameters);
void TIM1_CH2_PWM(int servo_Ton);

void ServoMotoreTestInit(void);
void vTaskPA0(void * pvParameters);  //test eventgroup ultrasuoni 
void vTaskPA1(void * pvParameters);  //test eventgroup ultrasuoni 
