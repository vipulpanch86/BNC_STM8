/**
  ******************************************************************************
  * @file    reg.h
  * @author  Vipul Panchal
  * @brief   This file contains the register handling definations and prototype.
  ******************************************************************************
  */

#ifndef __REG_H
#define __REG_H

/* REGISTER LOCATIONS*/
#define REG_ID_SW_VERSION              (0)
#define REG_ID_POWER_ON_FLAG           (1)
#define REG_ID_STAMP_EN_FLAG           (2)
#define REG_ID_UV_EN_FLAG              (3)
#define REG_ID_VALUE_COUNTER           (4)
#define REG_ID_NOTE_C_COUNT            (5)
#define REG_ID_NOTE_B_COUNT            (6)
#define REG_ID_NOTE_S_COUNT            (7)
#define REG_ID_NOTE_V_COUNT            (8)
#define REG_ID_ACC_SENSOR_C_CTR        (9)
#define REG_ID_ACC_SENSOR_B_CTR        (10)
#define REG_ID_ACC_SENSOR_F_CTR        (11)
#define REG_ID_ACC_SENSOR_S_CTR        (12)
#define REG_ID_ACC_SENSOR_V_CTR        (13)
#define REG_ID_C_TRUE_COUNT            (14)
#define REG_ID_C_OVER_COUNT            (15)
#define REG_ID_C_UNDER_COUNT           (16)
#define REG_ID_UV_LVL                  (17)
#define REG_MAX_NB                     (18)

#define REG_ID_INVALID                 (255)

void REG_Init(uint8_t initDefault);
uint8_t REG_SetValue(uint32_t *pValue, uint8_t index);
uint8_t REG_GetValue(uint32_t *pValue, uint8_t index);
uint8_t REG_GetMinValue(uint32_t *pValue, uint8_t index);
uint8_t REG_GetMaxValue(uint32_t *pValue, uint8_t index);

#endif /* __REG_H */
/******************************************************************************
*      End Of File
*****************************************************************************/

