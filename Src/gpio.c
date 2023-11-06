/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, L1_Pin|L2_Pin|L3_Pin|L4_Pin
                          |L5_Pin|L6_Pin|L7_Pin|L8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = K2_Pin|K3_Pin|K4_Pin|K1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = L1_Pin|L2_Pin|L3_Pin|L4_Pin
                          |L5_Pin|L6_Pin|L7_Pin|L8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void SetLeds(uint8_t dat) {
// LED亮灭控制，低电平亮，高电平灭
// 8个灯对应dat的低8位
HAL_GPIO_WritePin( L1_GPIO_Port, L1_Pin, (dat & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin( L2_GPIO_Port, L2_Pin, (dat & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin( L3_GPIO_Port, L3_Pin, (dat & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin( L4_GPIO_Port, L4_Pin, (dat & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin( L5_GPIO_Port, L5_Pin, (dat & 0x10) ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin( L6_GPIO_Port, L6_Pin, (dat & 0x20) ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin( L7_GPIO_Port, L7_Pin, (dat & 0x40) ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin( L8_GPIO_Port, L8_Pin, (dat & 0x80) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
uint8_t ScanKey(void) {
// 按键按下时，K1～K4低电平有效
uint8_t key = 0;
if (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_RESET) key |= K1_Pin;
if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_RESET) key |= K2_Pin;
if (HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin) == GPIO_PIN_RESET) key |= K3_Pin;
if (HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin) == GPIO_PIN_RESET) key |= K4_Pin;
if (key > 0){
 osDelay(10); // 按键延时10毫秒消抖
uint8_t key2 = 0;
if (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_RESET) key2 |= K1_Pin;
if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_RESET) key2 |= K2_Pin;
if (HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin) == GPIO_PIN_RESET) key2 |= K3_Pin;
if (HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin) == GPIO_PIN_RESET) key2 |= K4_Pin;
if (key == key2) return key; // 返回有效按键
else return 0;
}
return 0;
}
/* USER CODE END 2 */
