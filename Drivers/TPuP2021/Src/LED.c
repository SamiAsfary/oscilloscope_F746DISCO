/*
 * LED.c
 *
 *  Created on: 27 oct. 2021
 *      Author: Sami Asfary Ensea
 */
#include "stm32f746xx.h"
#include "LED.h"

int LED_NbTimes=0;

void LED_InitGreen(){
	int *pt = (int*) 0xE0042008;
	    *pt |= (1<<4);
}

void LED_DispGreen(int i){
	if(i==0){
		GPIOI->ODR &= 0xFFFFFFFD;
	}else{
		GPIOI->ODR |= 0x2;
	}
}

void LED_SetFreqGreen(int f){

	if(f != 0){
		TIM2->ARR = 10000/f;
		TIM2->CNT = 0;
	}


}

