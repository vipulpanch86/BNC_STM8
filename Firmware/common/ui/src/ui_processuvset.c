/**
  ******************************************************************************
  * @file    ui_processuvset.c
  * @author  Vipul Panchal
  * @brief   This file contains ui UV Setting process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  PROC_UVSET_EDIT,
  PROC_UVSET_WRITE,

  PROC_UVSET_MAX

} UVSET_PROCESS_LIST;

/* Private function prototypes -----------------------------------------------*/
static uint8_t ProcUvsetEdit(void *param, UI_MSG_T *pMsg);
static uint8_t ProcUvsetWrite(void *param, UI_MSG_T *pMsg);

/* Private constants----------------------------------------------------------*/
static const UI_PROC_PF PF_PROC_UVSET_LIST[] =
{
  ProcUvsetEdit,
  ProcUvsetWrite
};

/* Private variables ---------------------------------------------------------*/
static UI_PROC_PF pfProcUvset = NULL;

/**
  * @brief  Process Function for UV Setting Editing Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t ProcUvsetEdit(void *pParam, UI_MSG_T *pMsg)
{
#define KEY_INVALID 0xFF
#define KEY_TENS    0x80
#define KEY_UNITS   0x40
  
  static uint32_t EditVal = 0;
  static uint8_t  EditEnable = FALSE;
  char string[8];
  uint8_t digitVal = KEY_INVALID;

  uint32_t EditMinVal = 0, EditMaxVal = 0;
  REG_GetMinValue(&EditMinVal, REG_ID_UV_LVL);
  REG_GetMaxValue(&EditMaxVal, REG_ID_UV_LVL);

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      EditEnable = FALSE;
      EditVal = 0;
    }
    break;

    #ifdef KPD_KEY_DIG0
    case UIMSG_KEY_DIG0:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 0;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG1
    case UIMSG_KEY_DIG1:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 1;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG2
    case UIMSG_KEY_DIG2:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 2;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG3
    case UIMSG_KEY_DIG3:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 3;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG4
    case UIMSG_KEY_DIG4:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 4;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG5
    case UIMSG_KEY_DIG5:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 5;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG6
    case UIMSG_KEY_DIG6:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 6;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG7
    case UIMSG_KEY_DIG7:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 7;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG8
    case UIMSG_KEY_DIG8:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 8;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_DIG9
    case UIMSG_KEY_DIG9:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = 9;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_TENS
    case UIMSG_KEY_TENS:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = KEY_TENS;
        EditEnable = TRUE;
      }
      break;
    #endif

    #ifdef KPD_KEY_UNITS
    case UIMSG_KEY_UNITS:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        digitVal = KEY_UNITS;
        EditEnable = TRUE;
      }
      break;
    #endif
    
    #ifdef KPD_KEY_CLR
    case UIMSG_KEY_CLR:
    #endif
    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        if(EditEnable == TRUE)
        {
          if(EditVal < 10)
          {
            EditVal = 0;
            EditEnable = FALSE;
          }
          else
          {
            EditVal /= 10;
          }
        }
        else
        {
          return UI_RC_FINISH;
        }
      }
      break;

    #ifdef KPD_KEY_ENT
    case UIMSG_KEY_ENT:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcUvset = PF_PROC_UVSET_LIST[PROC_UVSET_WRITE];

        REG_SetValue(&EditVal, REG_ID_UV_LVL);

        EditVal = 0;
        EditEnable = FALSE;

        return (pfProcUvset(pParam, &msg));
      }
      break;
    #endif
  }

  if(EditEnable == TRUE)
  {
    if(digitVal != KEY_INVALID)
    {
      if(digitVal == KEY_TENS)
      {
        if((EditVal + 10) <= EditMaxVal)
        {
          EditVal += 10;
        }
        else
        {
          EditVal = 0;
        }
      }
      else if (digitVal == KEY_UNITS)
      {
        if(EditVal % 10 == 9)
        {
          EditVal -= 9;
        }
        else
        {
          if((EditVal + 1) <= EditMaxVal)
          {
            EditVal += 1;
          }
          else
          {
            EditVal = 0;
          }
        }
      }
      else
      {
        if(((EditVal * 10) + digitVal) <= EditMaxVal)
        {
          EditVal = (EditVal * 10) + digitVal;
        }      
      }
    }    

    sprintf((char *)&string[0], DISP_LOWER_STR_FORMAT, EditVal);
  }
  else
  {
    uint32_t uvLevel = 0;

    REG_GetValue(&uvLevel, REG_ID_UV_LVL);
    sprintf((char *)&string[0], DISP_LOWER_STR_FORMAT, uvLevel);
  }

  DISP_ClearAll();

  DISP_UpperPutStr("UVSET", 0);
  DISP_LowerPutStr((char *)&string[0], 0);

  return UI_RC_CONTINUE;

#undef KEY_INVALID
#undef KEY_TENS
#undef KEY_UNITS
}

/**
  * @brief  Internal Process Function for Home Write Memory
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcUvsetWrite(void *param, UI_MSG_T *pMsg)
{
  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      UI_MSG_T msg = {0, UIMSG_INIT};

      pfProcUvset = PF_PROC_UVSET_LIST[PROC_UVSET_EDIT];

      return (pfProcUvset(param, &msg));
    }

    default:
      break;
  }

  return UI_RC_CONTINUE;
}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for UV Setting
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessUvset(void *param, UI_MSG_T *pMsg)
{
  if(pMsg->message == UIMSG_INIT)
  {
    pfProcUvset = PF_PROC_UVSET_LIST[PROC_UVSET_EDIT];
  }

  return (pfProcUvset(param, pMsg));
}
/**********************************END OF FILE*********************************/
