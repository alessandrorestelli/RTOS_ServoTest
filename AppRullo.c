#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "AppRullo.h"
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "timer.h"
#include "LCD.h"
#include "Arduino.h"
#include <stdio.h>
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups

void TIM2_CH1_InCapt_SM(void);
void TIM4_CH1_PWM(void);

//PA5
void TIM2_CH1_InCapt_SM(void){
	//abilitazione registri timer
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	
	//prescaler
	TIM2->PSC =80 - 1;
	
	//impostazione della direzione
	//00 output
	//01 input, CC1 su TI1
	//10 input, CC1 su TI2
	//11 CC2 slave
	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;
	
	//input filter   IC2F[3:0] 0 senza filtro
	TIM2->CCMR1 &= ~TIM_CCMR1_IC1F;
	
	//selezione fronti con CC2NP e CC2P
//	00 rising edge
//	01 falling edge
//	11 entrambi
	TIM2->CCER &= ~ (TIM_CCER_CC1P|TIM_CCER_CC1NP);
	TIM2->CCER |=  (TIM_CCER_CC1P);
	
	TIM2->SMCR &= ~TIM_SMCR_TS;
	TIM2->SMCR |= 4<<4;
	
	TIM2->SMCR &= ~TIM_SMCR_SMS;
	TIM2->SMCR |=4;
	
	
	//input prescaler selezione numero frionti per ogni transizione
	//0 tutti i fronti
	TIM2->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
	
	//abilitazione cattura su ch1
	TIM2->CCER |= TIM_CCER_CC1E;
	
	//abilitazione interrupt
	TIM2->DIER |= TIM_DIER_CC1IE;
	
	//abilitazione timer
	TIM2->CR1 |= TIM_CR1_CEN;
	
	//interrupt
	NVIC_SetPriority(TIM2_IRQn,1);
	NVIC_EnableIRQ(TIM2_IRQn);
}


//PB6
void TIM4_CH1_PWM(void){
	//abilitazione registri timer
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	
	//direzione UP
	TIM4->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM4->PSC =80 - 1;
	
	//impostazione periodo
	TIM4->ARR = 500000-1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM4->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM4->CCMR1 |=TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
//	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM4->CCMR1 |= TIM_CCMR1_OC1PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM4->CCER &= ~TIM_CCER_CC1P;
	
	//Abilitazione canale 1 complementare
	TIM4->CCER |= TIM_CCER_CC1E;
	
//	//abilitazione OCN1
//	TIM1->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM4->CCR1 = 13-1;
	
	//abilitazione timer1
	TIM4->CR1 |= TIM_CR1_CEN;
}


void ServoMotoreInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE11_1;
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL11_Msk;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL11_0;
	TIM1_CH2_PWM(1551);
}

void TriggerInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE6_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE6_1;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL6_Msk ;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_1;
}

void EchoInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5_Msk;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;
}

void MotoreInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODE14_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE14_1;
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL14_Msk;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL14_0;
}
