/**
  ******************************************************************************
  * @file    ui_key.c
  * @author  CG Global R&D MCoEx - D&A Team
  * @version V1.0.0
  * @date    13-November-2014
  * @brief   User Interface Keypad Interface Source File.
  *           + Implements the keypad callback to map to UI keypad messages
  *
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

/** @addtogroup UI_Key_Private_Includes
  * @{
  */
#include "bsp.h"

#include "ui.h"

#define KEY_PRESS_BUZZ_TIME    100
/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint8_t  keyNb;
  uint8_t  keyMsg;
  uint8_t  buzzEn;
} KEY_MSG_T;

/** @addtogroup UI_Key_Private_Constants_Tables
  * @{
  */
/* UI Key code Mapping to BSP Key code */
static const KEY_MSG_T MSG_KEY_CODE[] =
{
  #ifdef KPD_KEY_DIG0
  KPD_KEY_DIG0, UIMSG_KEY_DIG0, TRUE,
  #endif

  #ifdef KPD_KEY_DIG1
  KPD_KEY_DIG1, UIMSG_KEY_DIG1, TRUE,
  #endif

  #ifdef KPD_KEY_DIG2
  KPD_KEY_DIG2, UIMSG_KEY_DIG2, TRUE,
  #endif

  #ifdef KPD_KEY_DIG3
  KPD_KEY_DIG3, UIMSG_KEY_DIG3, TRUE,
  #endif

  #ifdef KPD_KEY_DIG4
  KPD_KEY_DIG4, UIMSG_KEY_DIG4, TRUE,
  #endif

  #ifdef KPD_KEY_DIG5
  KPD_KEY_DIG5, UIMSG_KEY_DIG5, TRUE,
  #endif

  #ifdef KPD_KEY_DIG6
  KPD_KEY_DIG6, UIMSG_KEY_DIG6, TRUE,
  #endif

  #ifdef KPD_KEY_DIG7
  KPD_KEY_DIG7, UIMSG_KEY_DIG7, TRUE,
  #endif

  #ifdef KPD_KEY_DIG8
  KPD_KEY_DIG8, UIMSG_KEY_DIG8, TRUE,
  #endif

  #ifdef KPD_KEY_DIG9
  KPD_KEY_DIG9, UIMSG_KEY_DIG9, TRUE,
  #endif

  #ifdef KPD_KEY_ADD
  KPD_KEY_ADD, UIMSG_KEY_ADD, TRUE,
  #endif

  #ifdef KPD_KEY_ADD_UV
  KPD_KEY_ADD_UV, UIMSG_KEY_ADD_UV, TRUE,
  #endif

  #ifdef KPD_KEY_VALM
  KPD_KEY_VALM, UIMSG_KEY_VALM, TRUE,
  #endif

  #ifdef KPD_KEY_UV
  KPD_KEY_UV, UIMSG_KEY_UV, TRUE,
  #endif

  #ifdef KPD_KEY_AUTO
  KPD_KEY_AUTO, UIMSG_KEY_AUTO, TRUE,
  #endif

  #ifdef KPD_KEY_MANUAL
  KPD_KEY_MANUAL, UIMSG_KEY_MANUAL, TRUE,
  #endif

  #ifdef KPD_KEY_MODE
  KPD_KEY_MODE, UIMSG_KEY_MODE, TRUE,
  #endif

  #ifdef KPD_KEY_FUNC
  KPD_KEY_FUNC, UIMSG_KEY_FUNC, TRUE,
  #endif

  #ifdef KPD_KEY_UP
  KPD_KEY_UP, UIMSG_KEY_UP, TRUE,
  #endif

  #ifdef KPD_KEY_DOWN
  KPD_KEY_DOWN, UIMSG_KEY_DOWN, TRUE,
  #endif

  #ifdef KPD_KEY_BACK
  KPD_KEY_BACK, UIMSG_KEY_BACK, TRUE,
  #endif

  #ifdef KPD_KEY_NEXT
  KPD_KEY_NEXT, UIMSG_KEY_NEXT, TRUE,
  #endif

  #ifdef KPD_KEY_ENT
  KPD_KEY_ENT, UIMSG_KEY_ENT, TRUE,
  #endif

  #ifdef KPD_KEY_CLR
  KPD_KEY_CLR, UIMSG_KEY_CLR, TRUE,
  #endif

  KPD_KEY_SWI, UIMSG_KEY_SWI, FALSE,
  KPD_KEY_SWH, UIMSG_KEY_SWH, FALSE,
  KPD_KEY_RST, UIMSG_KEY_RST, TRUE
};

/**
  * @}
  */

/** @addtogroup UI_Key_Public_Functions
  * @{
  */

/**
  * @brief  Callback function for keypad
  *         Generates a UI Message when a state change in
  *         any key is detected
  * @param  keyNb - Key Number for which it is called back
  * @param  keyState - Key State change which was detected
  * @retval None
  */
void UI_KeyCallBack(uint8_t keyNb, uint8_t keyState)
{
  UI_MSG_T msg = {0, 0};
  uint8_t index;
  uint8_t totalNbKeys = sizeof(MSG_KEY_CODE) / sizeof(KEY_MSG_T);

  for(index = 0; index < totalNbKeys;)
  {
    if(MSG_KEY_CODE[index].keyNb == keyNb)
    {
      break;
    }
    else
    {
      index++;
    }
  }

  switch(keyState)
  {
    /*  Commented the State as it is not required in this case.
        case KEY_STATE_IDLE:
        break;
    */
    case KEY_STATE_PRESSED:
      if(MSG_KEY_CODE[index].keyMsg != UIMSG_INVALID)
      {
        msg.message = MSG_KEY_CODE[index].keyMsg;
        msg.param   = (uint8_t)UI_KEY_PRESS;

        if(MSG_KEY_CODE[index].buzzEn == TRUE)
        {
          BSP_EnableBuzzer(KEY_PRESS_BUZZ_TIME);
        }
      }
      break;

    case KEY_STATE_RELEASED:
      if(MSG_KEY_CODE[index].keyMsg != UIMSG_INVALID)
      {
        msg.message = MSG_KEY_CODE[index].keyMsg;
        msg.param   = (uint8_t)UI_KEY_RELEASE;
      }
      break;

    default:
      return;
  }

  UI_PostMessage(&msg);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Crompton Greaves ******END OF FILE*****/
