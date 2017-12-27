/**
  ******************************************************************************
  * @file    ui_processsetm.c
  * @author  Vipul Panchal
  * @brief   This file contains ui Set Mode process function
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Set Mode Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessSetM(void * pParam, UI_MSG_T * pMsg)
{
  static const char * SET_MODE_STR[] = {"M-MANL", "M-AUTO"};
  static uint8_t flagAutoCount = FALSE;
  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      flagAutoCount = AUTO_GetFlag();
      
      DISP_ClearAll();
    }
    break;

    #ifdef KPD_KEY_UP
    #ifdef KPD_KEY_DOWN
    case UIMSG_KEY_UP:
    case UIMSG_KEY_DOWN:
      if((uint8_t)pMsg->param == UI_KEY_RELEASE)
      {
        flagAutoCount = (uint8_t)(flagAutoCount == FALSE ? TRUE : FALSE);
      }
      break;
    #endif
    #endif

    #ifdef KPD_KEY_BACK
    #ifdef KPD_KEY_NEXT
    case UIMSG_KEY_BACK:
    case UIMSG_KEY_NEXT:
      if((uint8_t)pMsg->param == UI_KEY_RELEASE)
      {
        flagAutoCount = (uint8_t)(flagAutoCount == FALSE ? TRUE : FALSE);
      }
      break;
    #endif
    #endif

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_RELEASE)
      {
        return UI_RC_FINISH;
      }
      break;

    #ifdef KPD_KEY_ENT
    case UIMSG_KEY_ENT:
      if((uint8_t)pMsg->param == UI_KEY_RELEASE)
      {
        AUTO_SetFlag(flagAutoCount);
      }

      break;
    #endif
  }

  DISP_UpperClear();
  DISP_UpperPutStr((char *)SET_MODE_STR[flagAutoCount], 0);

  return UI_RC_CONTINUE;
}
/**********************************END OF FILE*********************************/
