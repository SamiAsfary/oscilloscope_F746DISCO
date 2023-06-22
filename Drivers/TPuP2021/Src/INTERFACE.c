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
#include "FreeRTOS.h"
#include "main.h"

char str[] = "AZERTY";
uint8_t lastFrameCompleted = 0;
uint8_t value[500];
extern SemaphoreHandle_t sem_display;

void clearPlot(){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(0, 90, 300, 272);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawHLine(0, 89, 300);
	BSP_LCD_DrawVLine(300, 89, 272);
}

void newpoint(uint16_t adc_result, uint16_t time){

	int current_value =  (adc_result*110/255);
	current_value = - current_value;
	current_value += 241;



	value[time] = (uint8_t) (current_value);

	if(time == 300){
		lastFrameCompleted = 0;
	}else if(time >= 499){
		lastFrameCompleted = 1;
	}

	/*int value =  (Tension*110/4095);
	value = - value;
	value += 241;
	Tension = value;
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawVLine(temps, 90, 272);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawVLine(temps+1, 89, 272);
	if(temps == 0){
		BSP_LCD_Clear(LCD_COLOR_WHITE);
	}*/
	/*
	if(Tension > oltTension){
		BSP_LCD_DrawVLine(temps, oltTension, Tension-oltTension);
	}else if(Tension < oltTension){
		BSP_LCD_DrawVLine(temps, Tension, oltTension-Tension);
	}else{
		BSP_LCD_DrawPixel(temps, Tension, LCD_COLOR_BLACK);
	}
	oltTension = Tension;*/
}

void task_display(){
	uint32_t min, max;
	uint8_t status;
	uint16_t i;
	uint8_t edge;
	uint16_t period;
	uint64_t mean;
	while(1){
		//vTaskDelay(10);
		xSemaphoreTake(sem_display,portMAX_DELAY);
		clearPlot();
		BSP_LCD_DrawPixel(0, value[lastFrameCompleted*200], LCD_COLOR_BLACK);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		for(i = lastFrameCompleted*200+1; i < lastFrameCompleted*200 + 300; i++){
			if(value[i] > value[i-1]){
				BSP_LCD_DrawVLine(i-lastFrameCompleted*200, value[i-1], value[i]-value[i-1]);
			}else if(value[i] < value[i-1]){
				BSP_LCD_DrawVLine(i-lastFrameCompleted*200, value[i], value[i-1]-value[i]);
			}else{
				BSP_LCD_DrawPixel(i-lastFrameCompleted*200, value[i], LCD_COLOR_BLACK);
			}
		}
		/*
		if (g_frameset == 1) {
					g_frameset = 0;
					min = 4096;
					max = 0;
					for (i = 0; i < 300; i++) {
						value[i] = g_value[i];
						if (min > value[i]) {
							min = value[i];
						}
						if (max < value[i]) {
							max = value[i];
						}
					}
					if (value[0] > ((min + max) / 2)) {
						status = 1;
					} else {
						status = 0;
					}
					edge = 0;
					i = 0;
					while (edge < 3 && i < 300) {
						if (value[i] < ((min + max) / 2) && status == 1) {
							status = 0;
							switch (edge) {
							case 0:
								period = i;
								break;
							case 2:
								period = i - period;
								break;
							default:
								break;
							}
							edge++;
						} else if (value[i] > ((min + max) / 2) && status == 0) {
							status = 1;
							switch (edge) {
							case 0:
								period = i;
								break;
							case 2:
								period = i - period;
								break;
							default:
								break;
							}
							edge++;
						}
						if (edge > 0) {
							mean += value[i];
						}
					}
					mean = mean / period;
					sprintf(bufStr, "period:%d", period);
					BSP_LCD_DisplayStringAt(0, 0, (uint8_t*) bufStr, LEFT_MODE);
				}*/
	}
}



