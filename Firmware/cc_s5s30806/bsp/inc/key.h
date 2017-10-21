/**
  ******************************************************************************
  * @file    key.h
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    14-August-2015
  * @brief   This file contains definitions for keypad resources.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Key Press Status */
#define KPD_KEY_RELEASED               (0)
#define KPD_KEY_PRESSED                (1)

/* Key Status Definition */
#define KEY_STATE_IDLE                 (0)
#define KEY_STATE_PRESSED              (1)
#define KEY_STATE_RELEASED             (2)

/* Keypad Key List */
#define KPD_KEY_MODE   (0)
#define KPD_KEY_ADD_UV (1)
#define KPD_KEY_AUTO   (2)
#define KPD_KEY_UP     (3)
#define KPD_KEY_DOWN   (4)
#define KPD_KEY_ENT    (5)
#define KPD_KEY_RST    (6)
#define KPD_KEY_SWH    (7)
#define KPD_KEY_SWI    (8)

#define KPD_KEY_TENS   (KPD_KEY_UP)
#define KPD_KEY_UNITS  (KPD_KEY_DOWN)

void KPD_Init(uint8_t debounce, void (* cb)(uint8_t, uint8_t));
void KPD_Scan(void);
uint8_t KPD_IsPressed(uint8_t keyNo);
void KPD_SetDebounceTime(uint8_t debounce);
uint8_t KPD_GetDebounceTime(void);
void KPD_AddEventListener(void (* cb)(uint8_t, uint8_t));

#ifdef __cplusplus
}
#endif

#endif /* __KEY_H */

/******************************END OF FILE*****/
