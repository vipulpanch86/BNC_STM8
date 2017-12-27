/**
  ******************************************************************************
  * @file    ui_callback.h
  * @author  Vipul Panchal
  * @brief   This file contains definitions related to Callback Functions to 
  *          User Interface
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Callback
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UI_CALLBACK_H
#define __UI_CALLBACK_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UI_Callback_Includes
  * @{
  */
/**
  * @}
  */

/** @addtogroup UI_Callback_Exported_Constants
  * @{
  */
/* Status definitions of a Keypad */
#define  UI_KEY_PRESS          0
#define  UI_KEY_RELEASE        1

/**
  * @}
  */

/** @addtogroup UI_Callback_Exported_Functions
  * @{
  */
void UI_KeyCallBack(uint8_t keyNb, uint8_t keyState);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __UI_CALLBACK_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ END OF FILE ***********/
