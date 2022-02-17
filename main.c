//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Puls.h"
#include "Led.h"
#include "Arduino.h"
#include "Servo.h"
#include "clock.h"

int main(void){ 

	SwInit();
	LedInit();
	pllInit(0,10,0);
	
	ServoMotoreInit();
	ServoMotoreTestInit();
	
	vTaskStartScheduler();
}

