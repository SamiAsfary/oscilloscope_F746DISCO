/*
 * INTERFACE.c
 *
 *  Created on: 27 oct. 2021
 *      Author: Sami Asfary Ensea
 */

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"

char str[80];
int oltTension = 0;

void newpoint(int Tension,int temps){
	int value =  (Tension*110/4095);
	value = - value;
	value += 241;
	Tension = value;
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawVLine(temps, 90, 272);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawVLine(temps+1, 89, 272);
	/*
	if(temps == 0){
		BSP_LCD_Clear(LCD_COLOR_WHITE);
	}*/
	if(Tension > oltTension){
		BSP_LCD_DrawVLine(temps, oltTension, Tension-oltTension);
	}else if(Tension < oltTension){
		BSP_LCD_DrawVLine(temps, Tension, oltTension-Tension);
	}else{
		BSP_LCD_DrawPixel(temps, Tension, LCD_COLOR_BLACK);
	}
	oltTension = Tension;
}




