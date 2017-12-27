/**
  ******************************************************************************
  * @file    ui_processspindle.c
  * @author  Vipul Panchal
  * @brief   This file contains ui Spindle process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Spindle Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessSpindle(void *pParam, UI_MSG_T *pMsg)
{
  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      BSP_S_MotorEnable(TRUE);
    }
    break;

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        BSP_S_MotorEnable(FALSE);
        return UI_RC_FINISH;
      }
      break;
  }

  return UI_RC_CONTINUE;
}
/**********************************END OF FILE*********************************/
