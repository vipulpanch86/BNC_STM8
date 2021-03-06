/**
  ******************************************************************************
  * @file    disp.h
  * @author  Vipul Panchal
  * @brief   This file contains definitions for display resources.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISP_H
#define __DISP_H

#ifdef __cplusplus
extern "C" {
#endif

#define DISP_LEDSEG_START_NB (8)
#define DISP_LEDSEG_MAX_NB   (1)
#if (COUNT_MODE_V_EN)
#define DISP_LED_MAX_NB      (14)
#else
#define DISP_LED_MAX_NB      (8)
#endif

#define DISP_MAX_NB_SEL      (9)


/* Max display definition */
#define DISP_UPPER_START_NB  (0)
#define DISP_UPPER_MAX_NB    (5)
#define DISP_LOWER_START_NB  (5)
#define DISP_LOWER_MAX_NB    (3)
#define DISP_TURRET_START_NB (0)
#define DISP_TURRET_MAX_NB   (4)

/* Max Value definition for display strings */
#define DISP_LOWER_MAX_VALUE  (999)
#define DISP_UPPER_MAX_VALUE  (99999)
#define DISP_TURRET_MAX_VALUE (9999)

/* Display Wrap Character Definition */
#define DISP_WRAP_CHAR       ((char)'L')

/* LED position */
#define DISP_LED_VERIFY      (0)
#define DISP_LED_BATCH       (1)
#define DISP_LED_FREE        (2)
#define DISP_LED_STAMP       (3)
#define DISP_LED_MANUAL      (5)
#define DISP_LED_ADD         (6)
#define DISP_LED_UV          (7)
#define DISP_LED_AUTO        (4)

#if (COUNT_MODE_V_EN)
#define DISP_LED_V_10        (8)
#define DISP_LED_V_20        (12)
#define DISP_LED_V_50        (10)
#define DISP_LED_V_100       (11)
#define DISP_LED_V_500       (9)
#define DISP_LED_V_1000      (13)
#endif

/* Format Specifier for display strings */
#define DISP_LOWER_STR_FORMAT "%3lu"
#define DISP_UPPER_STR_FORMAT "%5lu"
#define DISP_TURR_STR_FORMAT  "%4lu"

void DISP_Init(void);
void DISP_Enable(void);
void DISP_Disable(void);
void DISP_LowerClear(void);
void DISP_LowerPutStr(char *pStr, uint8_t startDispNo);
void DISP_UpperClear(void);
void DISP_UpperPutChar(char chr, uint8_t dispNo);
void DISP_UpperPutStr(char *pStr, uint8_t startDispNo);
void DISP_TurrClear(void);
void DISP_TurrPutStr(char *pStr, uint8_t startDispNo);
void DISP_Led(uint8_t ledNo, uint8_t enable);
void DISP_WriteRAW(uint8_t dispNo, uint8_t data);
void DISP_SetAll(void);
void DISP_ClearAll(void);
void DISP_Exec(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISP_H */

/******************************END OF FILE*****/
