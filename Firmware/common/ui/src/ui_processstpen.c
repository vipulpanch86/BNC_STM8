/**
  ******************************************************************************
  * @file    ui_processstpen.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    29-October-2015
  * @brief   This file contains ui Stamp Enable process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  PROC_STPEN_EDIT,
  PROC_STPEN_WRITE,

  PROC_STPEN_MAX

} STPEN_PROCESS_LIST;

/* Private function prototypes -----------------------------------------------*/
static uint8_t ProcStpenEdit(void *param, UI_MSG_T *pMsg);
static uint8_t ProcStpenWrite(void *param, UI_MSG_T *pMsg);

/* Private constants----------------------------------------------------------*/
static const UI_PROC_PF PF_PROC_STPEN_LIST[] =
{
  ProcStpenEdit,
  ProcStpenWrite
};

/* Private variables ---------------------------------------------------------*/
static UI_PROC_PF pfProcStpen = NULL;

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for STAMP Enable Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcStpenEdit(void *pParam, UI_MSG_T *pMsg)
{
  static const char *LOWER_STR[] = {"DIS", "EN"};
  static const char *UPPER_STR[] = {"DISBL", "ENBLE"};

  static uint32_t stampEnable = FALSE;

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      REG_GetValue(&stampEnable, REG_ID_STAMP_EN_FLAG);

      DISP_ClearAll();
      DISP_LowerPutStr(LOWER_STR[stampEnable], 0);
    }
    break;

    #ifdef KPD_KEY_UP
    #ifdef KPD_KEY_DOWN
    case UIMSG_KEY_UP:
    case UIMSG_KEY_DOWN:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        stampEnable = stampEnable == FALSE ? TRUE : FALSE;
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
        stampEnable = stampEnable == FALSE ? TRUE : FALSE;
      }
      break;
    #endif
    #endif
    
    #ifdef KPD_KEY_CLR
    case UIMSG_KEY_CLR:
    #endif
    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        return UI_RC_FINISH;
      }
      break;

    #ifdef KPD_KEY_ENT
    case UIMSG_KEY_ENT:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcStpen = PF_PROC_STPEN_LIST[PROC_STPEN_WRITE];

        if(stampEnable == FALSE)
        {
          uint8_t cntMode = COUNTER_GetMode();

          if(cntMode == COUNT_MODE_S)
          {
            cntMode = COUNT_MODE_C;
            COUNTER_SetMode(cntMode);
          }
        }

        REG_SetValue(&stampEnable, REG_ID_STAMP_EN_FLAG);

        return (pfProcStpen(pParam, &msg));
      }
      break;
    #endif
  }

  DISP_UpperClear();
  DISP_UpperPutStr(UPPER_STR[stampEnable], 0);

  return UI_RC_CONTINUE;
}


/**
  * @brief  Internal Process Function for Home Write Memory
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcStpenWrite(void *param, UI_MSG_T *pMsg)
{
#define  MEMORY_WRITE_TIME  700

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      DISP_ClearAll();
      
      RET_WriteRetEnbale(TRUE);

      UI_SetRefreshMsg(MEMORY_WRITE_TIME);
    }
    break;

    case UIMSG_REFRESH:
    {
      UI_MSG_T msg = {0, UIMSG_INIT};

      RET_WriteRetEnbale(FALSE);

      pfProcStpen = PF_PROC_STPEN_LIST[PROC_STPEN_EDIT];

      return (pfProcStpen(param, &msg));
    }
    break;

    default:
      break;
  }

  return UI_RC_CONTINUE;

#undef  MEMORY_WRITE_TIME
}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Stop Enable
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessStpen(void *param, UI_MSG_T *pMsg)
{
  if(pMsg->message == UIMSG_INIT)
  {
    pfProcStpen = PF_PROC_STPEN_LIST[PROC_STPEN_EDIT];
  }

  return (pfProcStpen(param, pMsg));
}
/**********************************END OF FILE*********************************/
