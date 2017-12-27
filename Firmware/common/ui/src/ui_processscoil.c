/**
  ******************************************************************************
  * @file    ui_processscoil.c
  * @author  Vipul Panchal
  * @brief   This file contains ui stamp coil process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Stamp Coil Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessSCoil(void *pParam, UI_MSG_T *pMsg)
{
#define STAMP_COIL_TIME  (500)

  uint32_t stampEnable = FALSE;
  REG_GetValue(&stampEnable, REG_ID_STAMP_EN_FLAG);
  
  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      if(stampEnable == TRUE)
      {
        BSP_S_CoilEnable(TRUE);
      }
      
      UI_SetRefreshMsg(STAMP_COIL_TIME);
    }
    break;

    case UIMSG_REFRESH:
    {
      if(stampEnable == TRUE)
      {
        BSP_S_CoilEnable(FALSE);
      }
      
      return UI_RC_FINISH;
    }

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        if(stampEnable == TRUE)
        {
          BSP_S_CoilEnable(FALSE);
        }

        return UI_RC_FINISH;
      }
      break;
  }

  return UI_RC_CONTINUE;

#undef STAMP_COIL_TIME
}
/**********************************END OF FILE*********************************/
