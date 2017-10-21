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
#if (HW_VARIANT == 0)

#define KPD_KEY_DIG1   (3)
#define KPD_KEY_DIG2   (4)
#define KPD_KEY_DIG3   (5)
#define KPD_KEY_DIG4   (6)
#define KPD_KEY_DIG5   (7)
#define KPD_KEY_DIG6   (8)
#define KPD_KEY_DIG7   (9)
#define KPD_KEY_DIG8   (10)
#define KPD_KEY_DIG9   (11)
#define KPD_KEY_ADD    (12)
#define KPD_KEY_DIG0   (13)
#define KPD_KEY_ENT    (14)
#define KPD_KEY_MODE   (18)
#define KPD_KEY_UV     (19)
#define KPD_KEY_VALM   (20)
#define KPD_KEY_UP     (21)
#define KPD_KEY_BACK   (22)
#define KPD_KEY_FUNC   (23)
#define KPD_KEY_NEXT   (24)
#define KPD_KEY_DOWN   (25)
#define KPD_KEY_RST    (26)
#define KPD_KEY_SWH    (27)
#define KPD_KEY_SWI    (28)

#define KPD_KEY_V10    (KPD_KEY_DIG6)
#define KPD_KEY_V20    (KPD_KEY_DIG5)
#define KPD_KEY_V50    (KPD_KEY_DIG4)
#define KPD_KEY_V100   (KPD_KEY_DIG3)
#define KPD_KEY_V500   (KPD_KEY_DIG2)
#define KPD_KEY_V1000  (KPD_KEY_DIG1)

#else

#define KPD_KEY_DIG1   (3)
#define KPD_KEY_DIG2   (4)
#define KPD_KEY_DIG3   (5)
#define KPD_KEY_DIG4   (6)
#define KPD_KEY_DIG5   (7)
#define KPD_KEY_DIG6   (8)
#define KPD_KEY_DIG7   (9)
#define KPD_KEY_DIG8   (10)
#define KPD_KEY_DIG9   (11)
#define KPD_KEY_DIG0   (13)
#define KPD_KEY_AUTO   (21)
#define KPD_KEY_MANUAL (22)
#define KPD_KEY_MODE   (23)
#define KPD_KEY_ADD_UV (24)
#define KPD_KEY_ENT    (25)
#define KPD_KEY_RST    (26)
#define KPD_KEY_SWH    (27)
#define KPD_KEY_SWI    (28)

#define KPD_KEY_BACK   (KPD_KEY_MANUAL)
#define KPD_KEY_NEXT   (KPD_KEY_ADD_UV)

#endif

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
