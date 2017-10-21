/**
  ******************************************************************************
  * @file    ui_processiswitch.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    16-August-2015
  * @brief   This file contains ui input switch process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for input switch Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessISwitch(void *pParam, UI_MSG_T *pMsg)
{
#define KEY_PRESS_BUZZ_TIME  200

  uint8_t iSwitchStatus = (uint8_t)BSP_ReadAutoSwitch();

  switch(pMsg->message)
  {
    case UIMSG_KEY_SWI:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        BSP_EnableBuzzer(KEY_PRESS_BUZZ_TIME);
      }

      break;

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        return UI_RC_FINISH;
      }
      break;
  }

  DISP_LowerClear();

  if(iSwitchStatus == TRUE)
  {
    DISP_LowerPutStr("H", DISP_LOWER_MAX_NB - 1);
  }
  else
  {
    DISP_LowerPutStr("L", DISP_LOWER_MAX_NB - 1);
  }

  return UI_RC_CONTINUE;

#undef KEY_PRESS_BUZZ_TIME
}
/**********************************END OF FILE*********************************/
