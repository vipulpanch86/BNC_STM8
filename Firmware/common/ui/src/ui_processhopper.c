/**
  ******************************************************************************
  * @file    ui_processhopper.c
  * @author  Vipul Panchal
  * @brief   This file contains ui hopper process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Hopper Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessHopper(void *pParam, UI_MSG_T *pMsg)
{
  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      BSP_H_MotorEnable(TRUE);
    }
    break;

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        BSP_H_MotorEnable(FALSE);
        return UI_RC_FINISH;
      }
      break;
  }

  return UI_RC_CONTINUE;
}
/**********************************END OF FILE*********************************/
