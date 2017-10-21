/**
  ******************************************************************************
  * @file    ui_processbcoil.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    16-August-2015
  * @brief   This file contains ui batch coil process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Batch Coil Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessBCoil(void *pParam, UI_MSG_T *pMsg)
{
#define BATCH_COIL_TIME  (500)

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      BSP_B_CoilEnable(TRUE);
      UI_SetRefreshMsg(BATCH_COIL_TIME);
    }
    break;

    case UIMSG_REFRESH:
    {
      BSP_B_CoilEnable(FALSE);
      return UI_RC_FINISH;
    }
    break;

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        BSP_B_CoilEnable(FALSE);
        return UI_RC_FINISH;
      }
      break;
  }

  return UI_RC_CONTINUE;

#undef BATCH_COIL_TIME
}
/**********************************END OF FILE*********************************/
