/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define	BUTTON_PRESSED		0
#define	BUTTON_UNPRESSED	1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Segment_Cathode_Code[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
//*********************************
void Clear_Data_Segment1(){
	for(uint8_t i = 0; i<8; i++){
		HAL_GPIO_WritePin(DATA1_GPIO_Port,DATA1_Pin,(0xff<<i)&0x80);
		HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(LAT_GPIO_Port,LAT_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LAT_GPIO_Port,LAT_Pin,GPIO_PIN_SET);
}
void Write_Data_Segment1(uint8_t number){   //write data into 74hc595 then 74hc595 will push data to segment
	if((number <= 9) && (number >= 0)){
		for(uint8_t i = 0; i<8; i++){
			HAL_GPIO_WritePin(DATA1_GPIO_Port,DATA1_Pin,(Segment_Cathode_Code[number]<<i)&0x80);
			HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET);
		}
		HAL_GPIO_WritePin(LAT_GPIO_Port,LAT_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LAT_GPIO_Port,LAT_Pin,GPIO_PIN_SET);
	}
}
void Turn_On_Segment1(uint8_t pos){
	if(pos == 1){	// Turn on LED 1 and turn off LED 2
		HAL_GPIO_WritePin(B1_GPIO_Port,B1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);
	}
	else if(pos == 2){ // Turn on LED 2 and turn off LED 1
		HAL_GPIO_WritePin(B1_GPIO_Port,B1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_SET);
	}
}

void Display_Number_Segment1(uint8_t number){
	if((number >= 0) && (number <= 99)){
		Write_Data_Segment1(number / 10);
		Turn_On_Segment1(1);
		HAL_Delay(4);
		Clear_Data_Segment1();
		Write_Data_Segment1(number % 10);
		Turn_On_Segment1(2);
		HAL_Delay(4);
		Clear_Data_Segment1();
	}
}
//************************************
void Clear_Data_Segment2(){
	for(uint8_t i = 0; i<8; i++){
		HAL_GPIO_WritePin(DATA2_GPIO_Port,DATA2_Pin,(0xff<<i)&0x80);
		HAL_GPIO_WritePin(CLK2_GPIO_Port,CLK2_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CLK2_GPIO_Port,CLK2_Pin,GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(LAT2_GPIO_Port,LAT2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LAT2_GPIO_Port,LAT2_Pin,GPIO_PIN_SET);
}
void Write_Data_Segment2(uint8_t number){   //write data into 74hc595 then 74hc595 will push data to segment
	if((number <= 9) && (number >= 0)){
		for(uint8_t i = 0; i<8; i++){
			HAL_GPIO_WritePin(DATA2_GPIO_Port,DATA2_Pin,(Segment_Cathode_Code[number]<<i)&0x80);
			HAL_GPIO_WritePin(CLK2_GPIO_Port,CLK2_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CLK2_GPIO_Port,CLK2_Pin,GPIO_PIN_SET);
		}
		HAL_GPIO_WritePin(LAT2_GPIO_Port,LAT2_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LAT2_GPIO_Port,LAT2_Pin,GPIO_PIN_SET);
	}
}
void Turn_On_Segment2(uint8_t pos){
	if(pos == 1){	// Turn on LED 1 and turn off LED 2
		HAL_GPIO_WritePin(B3_GPIO_Port,B3_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(B4_GPIO_Port,B4_Pin,GPIO_PIN_RESET);
	}
	else if(pos == 2){ // Turn on LED 2 and turn off LED 1
		HAL_GPIO_WritePin(B3_GPIO_Port,B3_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B4_GPIO_Port,B4_Pin,GPIO_PIN_SET);
	}
}
void Display_Number_Segment2(uint8_t number){
	if((number >= 0) && (number <= 99)){
		Write_Data_Segment2(number / 10);
		Turn_On_Segment2(1);
		HAL_Delay(4);
		Clear_Data_Segment2();
		Write_Data_Segment2(number % 10);
		Turn_On_Segment2(2);
		HAL_Delay(4);
		Clear_Data_Segment2();
	}
}
//**************************************
uint8_t hour = 00; // loi so 1 va 4
uint8_t min = 55;
void Display_Time(uint8_t* hour, uint8_t* min){
	Display_Number_Segment1(*hour);
	Display_Number_Segment2(*min);
}
//******************************
uint8_t button_value = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == CHANGE_MODE_Pin){
		if((button_value <2) && (button_value >= 1))	button_value++;
		else																					button_value = 1;	
		
		if(button_value == 1){
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,0);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
		}
		else if(button_value == 2){
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
		}
	}
	
	if(GPIO_Pin == INCREASE_Pin){
		if(button_value == 1){
			if((min < 59) && (min >= 0))		min++;
			else if(min == 59)							min = 0;
		}
		else if(button_value == 2){
			if((hour < 24) && (hour >= 0))	hour++;
			else if(hour == 24)							hour = 0;
		}
	}
	
	else if(GPIO_Pin == DECREASE_Pin){
		if(button_value == 1){
			if((min <= 59) && (min > 0))		min--;
			else if(min == 0)								min = 59;
		}
		else if(button_value == 2){
			if((hour <= 24) && (hour > 0))	hour--;
			else if(hour == 0)							hour = 24;
		}
	}
}
//************************************************
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
	uint8_t sys_state1 = 0;
	uint8_t sys_state2 = 0;
	uint8_t sec = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		Display_Time(&hour,&min);
		if((HAL_GPIO_ReadPin(RUN_GPIO_Port,RUN_Pin) == BUTTON_PRESSED) && sys_state1 == 0)		sys_state1 = 1;
		if(sys_state1 == 1)	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
		while(sys_state1 == 1){
			for(uint8_t i = 0; i < 36; i++){
				Display_Time(&hour,&min);
			}
			if(sec < 59)	sec++;
			else if((sec == 59) && (min < 59)){
				sec = 0;
				min++;
			}
			else if((sec == 59) && (min == 59) && (hour < 24)){
				sec = 0;
				min = 0;
				hour++;
			}
			else if((sec == 59) && (min == 59) && (hour == 24)){
				sec = 0;
				min = 0;
				hour = 0;
			}
			if((HAL_GPIO_ReadPin(STOP_GPIO_Port,STOP_Pin) == BUTTON_PRESSED) && sys_state2 == 0)		sys_state2 = 1;
			if(sys_state2 == 1)	break;
		}
		HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,0);
		sys_state1 = 0;
		sys_state2 = 0;
//		Display_Number_Segment1(00);
		
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CLK_Pin|LAT_Pin|DATA1_Pin|B1_Pin
                          |B2_Pin|CLK2_Pin|LAT2_Pin|DATA2_Pin
                          |B3_Pin|B4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED4_Pin|LED5_Pin|LED1_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CLK_Pin LAT_Pin DATA1_Pin B1_Pin
                           B2_Pin CLK2_Pin LAT2_Pin DATA2_Pin
                           B3_Pin B4_Pin */
  GPIO_InitStruct.Pin = CLK_Pin|LAT_Pin|DATA1_Pin|B1_Pin
                          |B2_Pin|CLK2_Pin|LAT2_Pin|DATA2_Pin
                          |B3_Pin|B4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : STOP_Pin RUN_Pin */
  GPIO_InitStruct.Pin = STOP_Pin|RUN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED4_Pin LED5_Pin LED1_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED4_Pin|LED5_Pin|LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : INCREASE_Pin DECREASE_Pin CHANGE_MODE_Pin */
  GPIO_InitStruct.Pin = INCREASE_Pin|DECREASE_Pin|CHANGE_MODE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
