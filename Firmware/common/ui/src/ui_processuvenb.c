/**
  ******************************************************************************
  * @file    ui_processuvenb.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    29-October-2015
  * @brief   This file contains ui UV Enable process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  PROC_UVENB_EDIT,
  PROC_UVENB_WRITE,

  PROC_UVENB_MAX

} UVENB_PROCESS_LIST;

/* Private function prototypes -----------------------------------------------*/
static uint8_t ProcUvenbEdit(void *param, UI_MSG_T *pMsg);
static uint8_t ProcUvenbWrite(void *param, UI_MSG_T *pMsg);

/* Private constants----------------------------------------------------------*/
static const UI_PROC_PF PF_PROC_UVENB_LIST[] =
{
  ProcUvenbEdit,
  ProcUvenbWrite
};

/* Private variables ---------------------------------------------------------*/
static UI_PROC_PF pfProcUvenb = NULL;

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for UV Enable Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcUvenbEdit(void *pParam, UI_MSG_T *pMsg)
{
  static const char *LOWER_STR[] = {"DIS", "EN"};
  static const char *UPPER_STR[] = {"DISBL", "ENBLE"};

  static uint32_t uvEnable = FALSE;

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      REG_GetValue(&uvEnable, REG_ID_UV_EN_FLAG);

      DISP_ClearAll();
      
      DISP_LowerPutStr(LOWER_STR[uvEnable], 0);
    }
    break;

    #ifdef KPD_KEY_UP
    #ifdef KPD_KEY_DOWN
    case UIMSG_KEY_UP:
    case UIMSG_KEY_DOWN:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        uvEnable = uvEnable == FALSE ? TRUE : FALSE;
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
        uvEnable = uvEnable == FALSE ? TRUE : FALSE;
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
        pfProcUvenb = PF_PROC_UVENB_LIST[PROC_UVENB_WRITE];

        if(uvEnable == FALSE)
        {
          uint8_t flagUVDetect = FALSE;
          UV_SetDetectFlag(flagUVDetect);
        }

        REG_SetValue(&uvEnable, REG_ID_UV_EN_FLAG);

        return (pfProcUvenb(pParam, &msg));
      }
      break;
    #endif
  }

  DISP_UpperClear();
  DISP_UpperPutStr(UPPER_STR[uvEnable], 0);

  return UI_RC_CONTINUE;
}


/**
  * @brief  Internal Process Function for Home Write Memory
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcUvenbWrite(void *param, UI_MSG_T *pMsg)
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

      pfProcUvenb = PF_PROC_UVENB_LIST[PROC_UVENB_EDIT];

      return (pfProcUvenb(param, &msg));
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
uint8_t UI_ProcessUvenb(void *param, UI_MSG_T *pMsg)
{
  if(pMsg->message == UIMSG_INIT)
  {
    pfProcUvenb = PF_PROC_UVENB_LIST[PROC_UVENB_EDIT];
  }

  return (pfProcUvenb(param, pMsg));
}
/**********************************END OF FILE*********************************/
