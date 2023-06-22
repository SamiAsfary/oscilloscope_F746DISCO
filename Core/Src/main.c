/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "crc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include <stdio.h>
#include <string.h>
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "LED.h"
#include "INTERFACE.h"
#include "OBSERVE.h"
#include "GENERATE.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char bufStr[40];
int g_n = 0;
TS_StateTypeDef g_ts;
int boucle = 0;
uint32_t g_value[600];
volatile uint8_t g_frameset = 0;

SemaphoreHandle_t sem_display;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t value[300];
	uint32_t min, max;
	uint8_t status;
	uint16_t i;
	uint8_t edge;
	uint16_t period;
	uint64_t mean;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	int *pt = (int*) 0xE0042008;
	*pt |= (1 << 4);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	LED_InitGreen();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_ADC3_Init();
  MX_TIM7_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */
	BSP_SDRAM_Init();

	__HAL_RCC_CRC_CLK_ENABLE();

	BSP_TS_Init(480, 272);

	BSP_LCD_Init();

	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	BSP_LCD_DisplayOn();

	BSP_LCD_SelectLayer(0);

	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_LCD_DisplayStringAt(180,180,(uint8_t *) "Ca marche!!",LEFT_MODE);

	//HAL_TIM_Base_Start_IT(&htim2); // LED_blink
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // Currently Not Used
	HAL_TIM_Base_Start_IT(&htim4); // Detecting Touch on screen
	//HAL_TIM_Base_Start_IT(&htim5); // GENE_Toggle
	HAL_TIM_Base_Start_IT(&htim7); // start ADC
	//HAL_TIM_Base_Start_IT(&htim9); // Currently Not Used

	xTaskCreate(task_display, "tache affichage", 512, NULL , 1, NULL);

	sem_display = xSemaphoreCreateBinary();

	vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
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
		}

		//g_n++;

		//BSP_TS_GetState(&g_ts);
		/*
		 BSP_TS_GetState(&g_ts);
		 if(g_ts.touchDetected > 0){
		 if(g_ts.touchX[0] > 240){
		 LED_SetFreqGreen(1);
		 }else{
		 LED_SetFreqGreen(4);
		 }

		 }*/

		/*	      sprintf(bufStr,"X:%3d",g_ts.touchX[0]);
		 BSP_LCD_DisplayStringAt(20,20,(uint8_t *) bufStr,LEFT_MODE);
		 sprintf(bufStr,"Y:%3d",g_ts.touchY[0]);
		 BSP_LCD_DisplayStringAt(20,50,(uint8_t *) bufStr,LEFT_MODE);
		 */
		//LED_SetFreqGreen(freq);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
