/**
  ******************************************************************************
  * @file     main.h
  * @author   Mahajan Electronics Team
  * @version  V1.0.0
  * @date     17-August-2015
  * @brief    This file contains the external declarations for main file
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifndef HW_VARIANT
#error Hardware Variant Not Defined
#endif

#if (HW_VARIANT == 0)
#define COUNT_MODE_V_EN   (1)
#else
#define COUNT_MODE_V_EN   (0)
#endif

typedef enum
{
  COUNT_MODE_C,
  COUNT_MODE_B,
  COUNT_MODE_F,
  COUNT_MODE_S,
  #if (COUNT_MODE_V_EN)
  COUNT_MODE_V,
  #endif
  COUNT_MODE_MAX
} COUNT_MODE_LIST_T;

#define MAX_LCD_RESLN     (99999)
#define MAX_ADD_COUNT     (999999999)

#define LCD_WRAP_CHAR     ((char)'L')

#define DEF_NOTE_C_COUNT  (100)
#define DEF_NOTE_B_COUNT  (100)
#define DEF_NOTE_S_COUNT  (100)
#define DEF_NOTE_V_COUNT  (1000)

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern uint8_t  FlagAutoCount;
extern uint8_t  FlagAddCount;
extern uint8_t  FlagUvDetect;
extern uint8_t  FlagSensorEn;
extern uint8_t  CounterMode;
extern uint32_t SensorCounter;

extern int32_t absolute(int32_t value);

/**
  * @brief  Sets the AUTO Count Variable
  * @param  AUTO Count Variable
  * @retval None
  */
@inline void AUTO_SetFlag(uint8_t flag)
{
  FlagAutoCount = flag;
}

/**
  * @brief  Returns the AUTO Count Variable
  * @param  None
  * @retval AUTO Count Variable
  */
@inline uint8_t AUTO_GetFlag(void)
{
  return FlagAutoCount;
}

/**
  * @brief  Sets the ADD Count Variable
  * @param  ADD Count Variable
  * @retval None
  */
@inline void ADD_SetFlag(uint8_t flag)
{
  FlagAddCount = flag;
}

/**
  * @brief  Returns the ADD Count Variable
  * @param  None
  * @retval ADD Count Variable
  */
@inline uint8_t ADD_GetFlag(void)
{
  return FlagAddCount;
}

/**
  * @brief  Sets the UV Detect Variable
  * @param  UV Detect Variable
  * @retval None
  */
@inline void UV_SetDetectFlag(uint8_t flag)
{
  FlagUvDetect = flag;
}

/**
  * @brief  Returns the UV Detect Variable
  * @param  None
  * @retval UV Detect Variable
  */
@inline uint8_t UV_GetDetectFlag(void)
{
  return FlagUvDetect;
}

/**
  * @brief  Sets the Sensor Enable Variable
  * @param  Sensor Enable Variable
  * @retval None
  */
@inline void SENSOR_SetEnable(uint8_t se)
{
  FlagSensorEn = se;
}

/**
  * @brief  Returns the Sensor Enable Variable
  * @param  None
  * @retval Sensor Enable Variable
  */
@inline uint8_t SENSOR_GetEnable(void)
{
  return FlagSensorEn;
}

/**
  * @brief  Sets the Counter Mode Variable
  * @param  Counter Mode Variable
  * @retval None
  */
@inline void COUNTER_SetMode(uint8_t mode)
{
  CounterMode = mode;
}

/**
  * @brief  Returns the Counter Mode Variable
  * @param  None
  * @retval Counter Mode Variable
  */
@inline uint8_t COUNTER_GetMode(void)
{
  return CounterMode;
}

/**
  * @brief  Sets the Sensor Counter Variable
  * @param  Sensor Counter Variable
  * @retval None
  */
@inline void SENSOR_SetCount(uint32_t sc)
{
  SensorCounter = sc;
}

/**
  * @brief  Returns the Sensor Counter Variable
  * @param  None
  * @retval Sensor Counter Variable
  */
@inline uint32_t SENSOR_GetCount(void)
{
  return SensorCounter;
}

#include "ret.h"
#include "reg.h"

#endif /* __MAIN_H */

/*********************************END OF FILE**********************************/
