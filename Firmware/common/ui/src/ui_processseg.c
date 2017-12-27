/**
  ******************************************************************************
  * @file    ui_processseg.c
  * @author  Vipul Panchal
  * @brief   This file contains ui segment process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Segment Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessSegment(void *pParam, UI_MSG_T *pMsg)
{
#define REFRESH_TIME_MS        1000

#define FLASH_DISP_TEST_CNT    5
#define SEG_DISP_TEST_CNT      10

#define FLASH_DISP_TEST        0
#define SEG_DISP_TEST          1

  static uint8_t testCount = 0;
  static uint8_t processState = FLASH_DISP_TEST;
  static uint8_t flashON = TRUE;
  char string[8];

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      testCount = 0;
      UI_SetRefreshMsg(REFRESH_TIME_MS);

      processState = FLASH_DISP_TEST;
      flashON = TRUE;

      /* Blank All Display & LED */
      TURR_Clear();
      DISP_ClearAll();
    }
    break;

    case UIMSG_REFRESH:
    {
      switch(processState)
      {
        case FLASH_DISP_TEST:
        {
          if(flashON == TRUE)
          {
            flashON = FALSE;
            DISP_SetAll();
          }
          else
          {
            testCount++;

            flashON = TRUE;
            DISP_ClearAll();
          }

          if(testCount >= FLASH_DISP_TEST_CNT)
          {
            TURR_Clear();
            DISP_ClearAll();

            testCount = 0;
            processState =  SEG_DISP_TEST;
          }

          UI_SetRefreshMsg(REFRESH_TIME_MS);
        }
        break;

        case SEG_DISP_TEST:
        {
          DISP_ClearAll();
          
          memset(&string[0], (char)('0' + testCount), DISP_LOWER_MAX_NB);
          DISP_LowerPutStr(&string[0], 0);

          memset(&string[0], (char)('0' + testCount), DISP_UPPER_MAX_NB);
          DISP_UpperPutStr(&string[0], 0);
          
          memset(&string[0], (char)('0' + testCount), DISP_TURRET_MAX_NB);
          DISP_TurrPutStr(&string[0], 0);

          TURR_Clear();
          TURR_PutVal(testCount * 1111);
          
          testCount++;

          if(testCount > SEG_DISP_TEST_CNT)
          {
            DISP_ClearAll();
            TURR_Clear();

            testCount = 0;
            UI_SetRefreshMsg(0);
            return UI_RC_FINISH;
          }

          UI_SetRefreshMsg(REFRESH_TIME_MS);
        }
        break;
      }
    }
    break;

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        UI_SetRefreshMsg(0);
        return UI_RC_FINISH;
      }
      break;

    default:
      break;
  }

  return UI_RC_CONTINUE;

#undef REFRESH_TIME_MS

#undef FLASH_DISP_TEST_CNT
#undef SEG_DISP_TEST_CNT

#undef FLASH_DISP_TEST
#undef SEG_DISP_TEST
}
/**********************************END OF FILE*********************************/
