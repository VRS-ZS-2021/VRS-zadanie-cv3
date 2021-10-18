/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "assignment.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
//void SystemClock_Config(void);
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
	  /*
	   *  DO NOT WRITE TO THE WHOLE REGISTER!!!
	   *  Write to the bits, that are meant for change.
	   *
	*/
  //Systick init
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);

	   /*
	   * TASK - configure MCU peripherals so that button state can be read and LED will blink.
	   * Button must be connected to the GPIO port A and its pin 3.
	   * LED must be connected to the GPIO port A and its pin 4.
	   *
	   * In header file "assignment.h" define macros for MCU registers access and LED blink application.
	   * Code in this file must use these macros for the peripherals setup.
	   * Code of the LED blink application is already given so just the macros used in the application must be defined.
	   */

  /* Enable clock for GPIO port A*/
  RCC_AHBENR_REG |= (uint32_t)(1 << 17);

  /* GPIOA pin 3 and 4 setup */

  //Pin A3 input mode
  GPIOA_MODER_REG &= ~(uint32_t)(0x3 << 6);

  //pin A4 output mode
  GPIOA_MODER_REG &= ~(uint32_t)(0x3 << 8);
  GPIOA_MODER_REG |= (uint32_t)(1 << 8);

  //pin A4 OTYPER mode push-pull
  GPIOA_OTYPER_REG &= ~(uint32_t)(1 << 4);

  //pin A4 OSPEEDR low speed
  GPIOA_OSPEEDR_REG &= ~(uint32_t)(0x3 << 8);

  //pin A4 no-pull
  GPIOA_PUPDR_REG &= ~(uint32_t)(0x3 << 8);
  //pin A3 pull-up
  GPIOA_PUPDR_REG &= ~(uint32_t)(0x3 << 6);
  GPIOA_PUPDR_REG |= (uint32_t)(1 << 6);

  int8_t actual_state = !(BUTTON_GET_STATE); //initial button state
  int8_t samples = 20;
  int8_t LED_state = 0; //initial LED state
  LED_OFF;
  EDGE_TYPE toggle_edge = RISE; //this type of edge will cause LED toggle
  while (1)
    {
	 EDGE_TYPE edge_type = edgeDetect(actual_state,samples); //read from edge detect function
  	 if(edge_type == toggle_edge) { //check rising edge - if yes, toggle LED state
  		 if(LED_state == 1){
  			 LED_OFF;
  			 LED_state = 0;
  		 } else {
  			LED_ON;
  			LED_state = 1;
  		 }
  	  }
  	 if(edge_type == RISE){
  		actual_state = 1;
  	 } else if(edge_type == FALL) {
  		actual_state = 0;
  	 }
    }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

EDGE_TYPE edgeDetect(uint8_t pin_state, uint8_t samples) {
	int detection = 0;
	while(1){
		int8_t actual_state = !(BUTTON_GET_STATE);
		if(((!actual_state) && (pin_state)) || ((actual_state) && (!pin_state))){
			detection++;
		}
		else{
			return NONE;
		}
		if(detection == samples){
			if (pin_state){
				return FALL;
			}
			else{
				return RISE;
			}
		}
	}


}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
