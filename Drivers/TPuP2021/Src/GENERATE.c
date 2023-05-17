/*
 * GENERATE.c
 *
 *  Created on: 27 oct. 2021
 *      Author: Sami Asfary Ensea
 */
#include "stm32f7xx_hal.h"

void GENE_TogglePin(){
	int ODR = GPIOA->ODR;
	if(((ODR>>8)&1) == 1){
		GPIOA->ODR &= ~(0x1<<8);
	}else{
		GPIOA->ODR |= (0x1<<8);
	}
}

void GENE_SetFreqPin(int f){
	f =(int) 10000/(2*f);
	TIM5->ARR = f;
	TIM5->CNT = 0;
}
