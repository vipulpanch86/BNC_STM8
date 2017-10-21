/**
  ******************************************************************************
  * @file    ui.h
  * @author  CG Global R&D MCoEx - D&A Team
  * @version V1.0.0
  * @date    15-July-2014
  * @brief   This file contains definitions related to core User Interface
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

/** @addtogroup UI_Core
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UI_H
#define __UI_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UI_Core_Includes
  * @{
  */
#include "bsp.h"


/**
  * @}
  */


/** @addtogroup UI_Core_Exported_Types
  * @{
  */
/* UI Message Structure */
typedef struct
{
  uint8_t param;
  uint8_t message;
} UI_MSG_T;

/* UI Context */
typedef struct
{
  uint8_t menu;
  uint8_t process;
  uint8_t child;
  uint8_t type;
} UI_CONTEXT_T;


/**
  * @}
  */

/** @addtogroup UI_Core_Exported_Constants
  * @{
  */
/* Type of UI Item */
#define UI_TYPE_MENU           0
#define UI_TYPE_PROCESS        1

/* Return Values of the UI Process */
#define UI_RC_FINISH           0
#define UI_RC_CONTINUE         1

/* UI Success and Failure return values */
#define UI_FAILURE             0
#define UI_SUCCESS             1

/* UI Enabled and Disabled return values */
#define UI_DISABLED            0
#define UI_ENABLED             1

/**
  * @}
  */

/** @addtogroup UI_Core_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Core_Exported_Functions
  * @{
  */
void UI_Init(void);
uint8_t  UI_GetMessage(UI_MSG_T *pMsg);
uint8_t UI_PostMessage(UI_MSG_T *pMsg);
void UI_ClearAllMessage(void);
void UI_GetContext(UI_CONTEXT_T *pContext);
uint8_t UI_GetNbOfMsgUnProcessed(void);
uint8_t UI_InvokeMenu(uint8_t id);
uint8_t UI_InvokeProcess(uint8_t id);
void UI_SetRefreshMsg(uint32_t interval);
void UI_Exec(void);
void UI_ProcessMsg(void);

/**
  * @}
  */

#include "ui_key.h"
#include "ui_config.h"
#include "ui_menu.h"
#include "ui_process.h"

#ifdef __cplusplus
}
#endif

#endif /*__UI_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Crompton Greaves ******END OF FILE*****/
