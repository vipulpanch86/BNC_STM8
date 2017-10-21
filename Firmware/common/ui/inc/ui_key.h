/**
  ******************************************************************************
  * @file    ui_key.h
  * @author  CG Global R&D MCoEx - D&A Team
  * @version V1.0.0
  * @date    13-November-2014
  * @brief   This file contains definitions related to User Interface
  *          keypad interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 Crompton Greaves</center></h2>
  *
  * This material is considered a trade secret by Crompton Greaves Limited.
  * Unauthorized access prohibited
  * This software is provided "as is" without warranty or merchantability or
  * fitness for a particular purpose.
  * Further, Crompton Greaves doesn't warrant/guarantee, or make any
  * representations regarding the use, or the result of the use, of the
  * software interms of correctness, accuracy, readability or otherwise.
  *
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Key
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UI_KEY_H
#define __UI_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UI_Key_Includes
  * @{
  */
/**
  * @}
  */

/** @addtogroup UI_Key_Exported_Constants
  * @{
  */
/* Status definitions of a Keypad */
#define  UI_KEY_PRESS          0
#define  UI_KEY_RELEASE        1

/**
  * @}
  */

/** @addtogroup UI_Key_Exported_Functions
  * @{
  */
void UI_KeyCallBack(uint8_t keyNb, uint8_t keyState);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__UI_KEY_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ END OF FILE ***********/
