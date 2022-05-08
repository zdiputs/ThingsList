/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Buttuon1_Pin GPIO_PIN_0
#define Buttuon1_GPIO_Port GPIOB
#define Buttuon2_Pin GPIO_PIN_1
#define Buttuon2_GPIO_Port GPIOB
#define Buttuon3_Pin GPIO_PIN_2
#define Buttuon3_GPIO_Port GPIOB
#define SPIready_Pin GPIO_PIN_12
#define SPIready_GPIO_Port GPIOB
#define SPICS_Pin GPIO_PIN_15
#define SPICS_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
//stm32f401ccu6 256kbytes flash 64kbytes ram
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_4   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_5  +  GetSectorSize(ADDR_FLASH_SECTOR_5) -1 /* End @ of user Flash area : sector start address + sector size -1 */
void MenuCtrl(void);
void keyScan(void);
void OLED_Init(void);
void OLED_CLS(void);
void MenuInit(void);
#define SUMC	100
extern unsigned short AdcValue[2];
extern unsigned short AdDataOrig[SUMC][2];
#define ADCPause     HAL_ADC_Stop(&hadc1)
#define ADCContinue  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&AdDataOrig,SUMC*2)
extern UART_HandleTypeDef huart1;
extern void ThingsL_erRunSequence(void);
extern unsigned int Menu1Ms;
extern unsigned char Menu1Sec;
 
void SuperRunSequence(void);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
