/**
  ******************************************************************************
  * @file    bsp.h
  * @author  Vipul Panchal
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
#define BSP_SW_VERSION      200
#define BSP_MB_SMALL        1
#define BSP_MB_BIG          0

/* Board I/Os configuration */
#define DEM0_MSC_PORT (GPIOA)
#define DEM0_MSC_PIN  (GPIO_PIN_3)

#define MUX0_MSB_PORT (GPIOA)
#define MUX0_MSB_PIN  (GPIO_PIN_4)

#define DISP_LE0_PORT (GPIOA)
#define DISP_LE0_PIN  (GPIO_PIN_6)

#define SENSOR_PORT   (GPIOB)
#define SENSOR_PIN    (GPIO_PIN_0)
#define SENSOR_EXTI   (EXTI_PORT_GPIOB)
#define SENSOR_EXTI_SENSE  (EXTI_SENSITIVITY_RISE_FALL)

#define STAMP_PORT    (GPIOB)
#define STAMP_PIN     (GPIO_PIN_2)

#define BATCH_PORT    (GPIOB)
#define BATCH_PIN     (GPIO_PIN_3)

#define SW_AUTO_PORT  (GPIOB)
#define SW_AUTO_PIN   (GPIO_PIN_4)

#define SW_CAM_PORT   (GPIOB)
#define SW_CAM_PIN    (GPIO_PIN_5)

#define MUX0_MSC_PORT (GPIOB)
#define MUX0_MSC_PIN  (GPIO_PIN_7)

#define DISP_DB_PORT  (GPIOD)

#define DISP_DB0_PORT (GPIOD)
#define DISP_DB0_PIN  (GPIO_PIN_0)

#define DISP_DB1_PORT (GPIOD)
#define DISP_DB1_PIN  (GPIO_PIN_1)

#define DISP_DB2_PORT (GPIOD)
#define DISP_DB2_PIN  (GPIO_PIN_2)

#define DISP_DB3_PORT (GPIOD)
#define DISP_DB3_PIN  (GPIO_PIN_3)

#define DISP_DB4_PORT (GPIOD)
#define DISP_DB4_PIN  (GPIO_PIN_4)

#define DISP_DB5_PORT (GPIOD)
#define DISP_DB5_PIN  (GPIO_PIN_5)

#define DISP_DB6_PORT (GPIOD)
#define DISP_DB6_PIN  (GPIO_PIN_6)

#define DISP_DB7_PORT (GPIOD)
#define DISP_DB7_PIN  (GPIO_PIN_7)

#define DISP_MS0_PORT (GPIOE)
#define DISP_MS0_PIN  (GPIO_PIN_0)

#if (MOTHER_BOARD_TYPE == BSP_MB_BIG)

#define DISP_MS1_PORT (GPIOE)
#define DISP_MS1_PIN  (GPIO_PIN_1)

#define DISP_MS2_PORT (GPIOE)
#define DISP_MS2_PIN  (GPIO_PIN_2)

#else

#define DISP_MS1_PORT (GPIOG)
#define DISP_MS1_PIN  (GPIO_PIN_6)

#define DISP_MS2_PORT (GPIOG)
#define DISP_MS2_PIN  (GPIO_PIN_7)

#endif

#define DISP_MS3_PORT (GPIOE)
#define DISP_MS3_PIN  (GPIO_PIN_3)

#define DISP_LE1_PORT (GPIOE)
#define DISP_LE1_PIN  (GPIO_PIN_4)

#define TRIACD_PORT   (GPIOE)
#define TRIACD_PIN    (GPIO_PIN_5)

#define TRIACC_PORT   (GPIOE)
#define TRIACC_PIN    (GPIO_PIN_6)

#define UV_AIN_PORT   (GPIOE)
#define UV_AIN_PIN    (GPIO_PIN_7)

#define DISP_LOE_PORT (GPIOF)
#define DISP_LOE_PIN  (GPIO_PIN_0)

#define BUZZER_PORT   (GPIOF)
#define BUZZER_PIN    (GPIO_PIN_3)

#define KEY_RST_PORT  (GPIOF)
#define KEY_RST_PIN   (GPIO_PIN_4)

#define DEM0_MSB_PORT (GPIOF)
#define DEM0_MSB_PIN  (GPIO_PIN_5)

#define DEM0_MSA_PORT (GPIOF)
#define DEM0_MSA_PIN  (GPIO_PIN_6)

#define MUX0_MSA_PORT (GPIOF)
#define MUX0_MSA_PIN  (GPIO_PIN_7)

#define TUR_EN_PORT   (GPIOG)
#define TUR_EN_PIN    (GPIO_PIN_0)

#define UV_ENB_PORT   (GPIOG)
#define UV_ENB_PIN    (GPIO_PIN_4)

#define TRIACB_PORT   (GPIOG)
#define TRIACB_PIN    (GPIO_PIN_5)

/**
  * @brief Welcome Message Definition
  */  
#define WELCOME_MSG_SIZE        16
#define WELCOME_MSG_ADDR        0x004000

/**
  * @brief  Writes high level to the specified GPIO pins.
  * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
  * @param  PortPins : Specifies the pins to be turned high to the port output.
  *         data register.
  * @retval None
  */
@inline void BSP_SetGPIO(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef Pins)
{
  GPIOx->ODR |= (uint8_t)Pins;
}

/**
  * @brief  Writes low level to the specified GPIO pins.
  * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
  * @param  PortPins : Specifies the pins to be turned low to the port output.
  *         data register.
  * @retval None
  */
@inline void BSP_ClrGPIO(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef Pins)
{
  GPIOx->ODR &= (uint8_t)~Pins;
}

/**
  * @brief  Read Cam Switch
  * @param  None
  * @retval True - Cam Switch Pressed
  */
#define BSP_ReadCamSwitch() \
  (((uint8_t)SW_CAM_PORT->IDR & SW_CAM_PIN) ? \
   (FALSE) : (TRUE));

/**
  * @brief  Read Auto Switch
  * @param  None
  * @retval True - Auto Switch Pressed
  */
#define BSP_ReadAutoSwitch() \
  (((uint8_t)SW_AUTO_PORT->IDR & SW_AUTO_PIN) ? \
   (FALSE) : (TRUE));

/**
  * @brief  H-Motor Enable / Disable
  * @param  state - True (Enable) / False (Disable)
  * @retval None
  */
#if (MOTHER_BOARD_TYPE == BSP_MB_BIG)

#define BSP_H_MotorEnable(state) { \
    (state == TRUE) ? \
    (TRIACD_PORT->ODR &= (uint8_t)~TRIACD_PIN) : \
    (TRIACD_PORT->ODR |= (uint8_t)TRIACD_PIN); \
  }

#else

#define BSP_H_MotorEnable(state) { \
    (state == FALSE) ? \
    (TRIACD_PORT->ODR &= (uint8_t)~TRIACD_PIN) : \
    (TRIACD_PORT->ODR |= (uint8_t)TRIACD_PIN); \
  }

#endif

/**
  * @brief  S-Motor Enable / Disable
  * @param  state - True (Enable) / False (Disable)
  * @retval None
  */
#if (MOTHER_BOARD_TYPE == BSP_MB_BIG)

#define BSP_S_MotorEnable(state) { \
    (state == TRUE) ? \
    (TRIACC_PORT->ODR &= (uint8_t)~TRIACC_PIN) : \
    (TRIACC_PORT->ODR |= (uint8_t)TRIACC_PIN); \
  }

#else

#define BSP_S_MotorEnable(state) { \
    (state == FALSE) ? \
    (TRIACC_PORT->ODR &= (uint8_t)~TRIACC_PIN) : \
    (TRIACC_PORT->ODR |= (uint8_t)TRIACC_PIN); \
  }

#endif

/**
  * @brief  V-Pump Enable / Disable
  * @param  state - True (Enable) / False (Disable)
  * @retval None
  */
#if (MOTHER_BOARD_TYPE == BSP_MB_BIG)

#define BSP_V_PumpEnable(state) { \
    (state == TRUE) ? \
    (TRIACB_PORT->ODR &= (uint8_t)~TRIACB_PIN) : \
    (TRIACB_PORT->ODR |= (uint8_t)TRIACB_PIN); \
  }

#else

#define BSP_V_PumpEnable(state) { \
    (state == FALSE) ? \
    (TRIACB_PORT->ODR &= (uint8_t)~TRIACB_PIN) : \
    (TRIACB_PORT->ODR |= (uint8_t)TRIACB_PIN); \
  }

#endif

/**
  * @brief  B-Coil Enable / Disable
  * @param  state - True (Enable) / False (Disable)
  * @retval None
  */
#define BSP_B_CoilEnable(state) { \
    (state == TRUE) ? \
    (BATCH_PORT->ODR |= (uint8_t)BATCH_PIN): \
    (BATCH_PORT->ODR &= (uint8_t)~BATCH_PIN); \
  }

/**
  * @brief  S-Coil Enable / Disable
  * @param  state - True (Enable) / False (Disable)
  * @retval None
  */
#define BSP_S_CoilEnable(state) { \
    (state == TRUE) ? \
    (STAMP_PORT->ODR |= (uint8_t)STAMP_PIN): \
    (STAMP_PORT->ODR &= (uint8_t)~STAMP_PIN); \
  }

/**
  * @brief  UV LED Enable / Disable
  * @param  state - True (Enable) / False (Disable)
  * @retval None
  */
#define BSP_UV_DetectEnable(state) { \
    (state == TRUE) ? \
    (UV_ENB_PORT->ODR &= (uint8_t)~UV_ENB_PIN) : \
    (UV_ENB_PORT->ODR |= (uint8_t)UV_ENB_PIN); \
  }

/**
  * @brief  S-Fan Enable / Disable
  * @param  state - True (Enable) / False (Disable)
  * @retval None
  */
#define BSP_S_FanEnable(state) { \
    (state == TRUE) ? \
    (STAMP_PORT->ODR |= (uint8_t)STAMP_PIN): \
    (STAMP_PORT->ODR &= (uint8_t)~STAMP_PIN); \
  }
  
extern uint32_t BuzzerOnTime;
extern uint16_t AdcValue;
extern __IO uint32_t SystemTimer;
extern __IO uint32_t BspSensorCounter;

/**
  * @brief  Returns the SystemTimer variable.
  * @param  None
  * @retval System Timer Variable
  */
@inline uint32_t BSP_GetSysTime(void)
{
  return SystemTimer;
}

/**
  * @brief  Enables Buzzer
  * @param  buzzTime - Time for which the buzzer remains ON
  * @retval None
  */
@inline void BSP_EnableBuzzer(uint32_t buzzTime)
{
  BuzzerOnTime = buzzTime;
}

/**
  * @brief  Disables Buzzer
  * @param  None
  * @retval None
  */
@inline void BSP_DisableBuzzer(void)
{
  BuzzerOnTime = 0;
}

/**
  * @brief  Returns ADC Value
  * @param  None
  * @retval None
  */
@inline uint16_t BSP_GetADC(void)
{
  return AdcValue;
}

void BSP_Init(void);
void BSP_DelayMs(uint16_t delay);
void BSP_BuzzerExec(void);
void BSP_AdcExec(void);
void BSP_ReadFromFlash(uint16_t size, uint8_t *pData);
void BSP_WriteToFlash(uint16_t size, uint8_t *pData);

#include "main.h"
#include "disp.h"
#include "key.h"
#include "turret.h"

#endif /* __BSP_H */

/***********************END OF FILE************************/
