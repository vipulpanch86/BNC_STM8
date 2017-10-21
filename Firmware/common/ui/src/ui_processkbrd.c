/**
  ******************************************************************************
  * @file    ui_processkbrd.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    16-August-2015
  * @brief   This file contains ui keyboard process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Keyboard Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessKeyboard(void *pParam, UI_MSG_T *pMsg)
{
  static uint8_t testReset = TRUE;

  if(pMsg->message == UIMSG_INIT)
  {
    testReset = TRUE;
    DISP_LowerClear();
  }
  else

  #ifdef KPD_KEY_DIG0
  if(pMsg->message == UIMSG_KEY_DIG0)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-0", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG1
  if(pMsg->message == UIMSG_KEY_DIG1)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-1", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG2
  if(pMsg->message == UIMSG_KEY_DIG2)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-2", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG3
  if(pMsg->message == UIMSG_KEY_DIG3)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-3", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG4
  if(pMsg->message == UIMSG_KEY_DIG4)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-4", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG5
  if(pMsg->message == UIMSG_KEY_DIG5)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-5", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG6
  if(pMsg->message == UIMSG_KEY_DIG6)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-6", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG7
  if(pMsg->message == UIMSG_KEY_DIG7)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-7", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG8
  if(pMsg->message == UIMSG_KEY_DIG8)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-8", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DIG9
  if(pMsg->message == UIMSG_KEY_DIG9)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("KEY-9", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_ADD
  if(pMsg->message == UIMSG_KEY_ADD)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("ADD", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_ADD_UV
  if(pMsg->message == UIMSG_KEY_ADD_UV)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("AD-UV", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_VALM
  if(pMsg->message == UIMSG_KEY_VALM)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("VALUE", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_UV
  if(pMsg->message == UIMSG_KEY_UV)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("UV", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_AUTO
  if(pMsg->message == UIMSG_KEY_AUTO)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("AUTO", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_MANUAL
  if(pMsg->message == UIMSG_KEY_MANUAL)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("MANUAL", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_MODE
  if(pMsg->message == UIMSG_KEY_MODE)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("MODE", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_FUNC
  if(pMsg->message == UIMSG_KEY_FUNC)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("FUNC", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_TENS
  if(pMsg->message == UIMSG_KEY_TENS)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("TENS", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_UNITS
  if(pMsg->message == UIMSG_KEY_UNITS)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("UNITS", 0);
    }
  }
  else
  #endif
  
  #ifdef KPD_KEY_UP
  if(pMsg->message == UIMSG_KEY_UP)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("UP", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_DOWN
  if(pMsg->message == UIMSG_KEY_DOWN)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("DOWN", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_BACK
  if(pMsg->message == UIMSG_KEY_BACK)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("BACK", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_NEXT
  if(pMsg->message == UIMSG_KEY_NEXT)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("NEXT", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_ENT
  if(pMsg->message == UIMSG_KEY_ENT)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("ENTER", 0);
    }
  }
  else
  #endif

  #ifdef KPD_KEY_CLR
  if(pMsg->message == UIMSG_KEY_CLR)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("CLEAR", 0);
    }
  }
  else
  #endif

  if(pMsg->message == UIMSG_KEY_SWI)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("SW-I", 0);
    }
  }
  else

  if(pMsg->message == UIMSG_KEY_SWH)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      testReset = TRUE;
      DISP_UpperClear();
      DISP_UpperPutStr("SW-H", 0);
    }
  }
  else

  if(pMsg->message == UIMSG_KEY_RST)
  {
    if((uint8_t)pMsg->param == UI_KEY_PRESS)
    {
      if(testReset == TRUE)
      {
        testReset = FALSE;

        DISP_UpperClear();
        DISP_UpperPutStr("RESET", 0);
      }
      else
      {
        testReset = TRUE;

        return UI_RC_FINISH;
      }
    }
  }
    
  return UI_RC_CONTINUE;
}
/**********************************END OF FILE*********************************/
