/*
 * LED.h
 *
 *  Created on: 27 oct. 2021
 *      Author: Sami Asfary Ensea
 */

#ifndef TPUP2021_INC_LED_H_
#define TPUP2021_INC_LED_H_

void LED_InitGreen();
void LED_DispGreen();
void LED_TimEnable();
void LED_SetFreqGreen(int f);

extern int LED_NbTimes;

#endif /* TPUP2021_INC_LED_H_ */
