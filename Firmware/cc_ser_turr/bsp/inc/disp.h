/**
  ******************************************************************************
  * @file    disp.h
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    16-August-2015
  * @brief   This file contains definitions for dsiplay resources.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISP_H
#define __DISP_H

#ifdef __cplusplus
extern "C" {
#endif

#define DISP_MAX_NB_BITS     (7)
#define DISP_MAX_NB_SEL      (4)

void DISP_Init(void);
void DISP_Enable(void);
void DISP_Disable(void);
void DISP_Clear(void);
void DISP_PutStr(char * pStr, uint8_t startDispNo);
void DISP_WriteRAW(uint8_t dispNo, uint8_t data);
void DISP_Exec(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISP_H */

/******************************END OF FILE*****/
