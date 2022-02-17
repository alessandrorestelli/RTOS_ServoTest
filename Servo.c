//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"                     	// ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Servo.h"
#include "Led.h"
#include "Arduino.h"

EventGroupHandle_t xServo;

void ServoMotoreInit(void){
	
	/*Inizializzazione pin servo(PE11) in alternate function 
	per generare un segnale PWM che piloterà il servomotore*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE11_1;
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL11_Msk;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL11_0;

	//Inizializzazione timer del pin PE11
	TIM1_CH2_PWM(1551);
	
	//Creazione task per pilotare servomotore
	xServo=xEventGroupCreate();	
	
	xTaskCreate(vTaskSmistaDx, 
	"Task 4 (Smista destra)",    
	50, 
	NULL,  
	1,     
	NULL); 
	xTaskCreate(vTaskSmistaSx,
	"Task 5 (Smista sinistra)",    
	50,   
	NULL, 
	1,     
	NULL);
}

void ServoMotoreTestInit(void){
	
	//Creazione task per test servomotore
	xTaskCreate(vTaskPA0, 
		"Task 10 (PA0 check)",  
		50,   
		NULL, 
		1,     
		NULL); 
	xTaskCreate(vTaskPA1, 
		"Task 11 (PA1 check)",    
		50,  
		NULL,  
		1,     
		NULL); 
}

void vTaskSmistaDx(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_SMISTADX;
	while(1){
		xEventGroupWaitBits(xServo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);
		LedRossoToggle();
		TIM1->CCR2 = 2500;	//Sposta a 0°
		vTaskDelay(700);
		TIM1->CCR2 = 800;	//Sposta a 150°
		vTaskDelay(700);
		TIM1->CCR2 = 1500;	//Sposta a 0°
	}
}

void vTaskSmistaSx(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_SMISTASX;
	while(1){
		xEventGroupWaitBits(xServo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);
		LedVerdeToggle();
		TIM1->CCR2=800;	//Sposta a 0°
		vTaskDelay(700);
		TIM1->CCR2 = 2500;	//Sposta a 150°
		vTaskDelay(700);
		TIM1->CCR2 = 1500;	//Sposta a 0°
	}
}

void vTaskPA0(void * pvParameters){
	while(1){
		//Lettura pulsante sinistro 
		while(!digitalRead(PA0));
		while(digitalRead(PA0)){;}
			//Modifica event group per richiamare task smista
			xEventGroupSetBits(xServo, EVENT_SMISTASX);
		}	
}

void vTaskPA1(void * pvParameters){
	while(1){
		//Lettura pulsante sinistro 
		while(!digitalRead(PA1));
		while(digitalRead(PA1)){;}
			xEventGroupSetBits(xServo, EVENT_SMISTADX);
		}	
}

