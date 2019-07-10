/**
  ******************************************************************************
  * @file    bsp.h
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    11-August-2015
  * @brief   This file contains the board related definitions.
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H
#define __BSP_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Contains the description of all STM8 hardware registers */
#include "stm8s.h"

/* Private define ------------------------------------------------------------*/
#define BSP_SW_VERSION      100

/* Board I/Os configuration */
#define DISP_DB0_PORT (GPIOD)
#define DISP_DB0_PIN  (GPIO_PIN_3)

#define DISP_DB1_PORT (GPIOD)
#define DISP_DB1_PIN  (GPIO_PIN_2)

#define DISP_DB2_PORT (GPIOC)
#define DISP_DB2_PIN  (GPIO_PIN_7)

#define DISP_DB3_PORT (GPIOC)
#define DISP_DB3_PIN  (GPIO_PIN_6)

#define DISP_DB4_PORT (GPIOC)
#define DISP_DB4_PIN  (GPIO_PIN_5)

#define DISP_DB5_PORT (GPIOC)
#define DISP_DB5_PIN  (GPIO_PIN_4)

#define DISP_DB6_PORT (GPIOC)
#define DISP_DB6_PIN  (GPIO_PIN_3)

#define DISP_EN0_PORT (GPIOA)
#define DISP_EN0_PIN  (GPIO_PIN_2)

#define DISP_EN1_PORT (GPIOA)
#define DISP_EN1_PIN  (GPIO_PIN_1)

#define DISP_EN2_PORT (GPIOD)
#define DISP_EN2_PIN  (GPIO_PIN_5)

#define DISP_EN3_PORT (GPIOD)
#define DISP_EN3_PIN  (GPIO_PIN_4)

extern __IO uint32_t SystemTimer;

/**
  * @brief  Returns the SystemTimer variable.
  * @param  None
  * @retval System Timer Variable
  */
@inline uint32_t BSP_GetSysTime(void)
{
  return SystemTimer;
}

void BSP_Init(void);
#include "disp.h"

#endif /* __BSP_H */

/***********************END OF FILE************************/
