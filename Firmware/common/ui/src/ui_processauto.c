/**
  ******************************************************************************
  * @file    ui_processauto.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    16-August-2015
  * @brief   This file contains ui auto process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Private typedef -----------------------------------------------------------*/
#define AUTO_ACCUMULATE_SET  (10000)

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  PROC_AUTO_START_H_MOTOR,
  PROC_AUTO_START_S_MOTOR,
  PROC_AUTO_START_B_COIL,
  PROC_AUTO_STOP_H_MOTOR,
  PROC_AUTO_START_S_COIL,
  PROC_AUTO_ADD_DELAY,
  PROC_AUTO_BEEP,
  PROC_AUTO_ERROR_01,

  PROC_AUTO_MAX

} AUTO_PROCESS_LIST;

/* Private function prototypes -----------------------------------------------*/
static uint8_t ProcAutoStartHMotor(void *param, UI_MSG_T *pMsg);
static uint8_t ProcAutoStartSMotor(void *param, UI_MSG_T *pMsg);
static uint8_t ProcAutoStartBCoil(void *param, UI_MSG_T *pMsg);
static uint8_t ProcAutoStopHMotor(void *param, UI_MSG_T *pMsg);
static uint8_t ProcAutoStartSCoil(void *param, UI_MSG_T *pMsg);
static uint8_t ProcAutoAddDelay(void *param, UI_MSG_T *pMsg);
static uint8_t ProcAutoBeep(void *param, UI_MSG_T *pMsg);
static uint8_t ProcAutoError01(void *param, UI_MSG_T *pMsg);

/* Private constants----------------------------------------------------------*/
static const UI_PROC_PF PF_PROC_AUTO_LIST[] =
{
  ProcAutoStartHMotor,
  ProcAutoStartSMotor,
  ProcAutoStartBCoil,
  ProcAutoStopHMotor,
  ProcAutoStartSCoil,
  ProcAutoAddDelay,
  ProcAutoBeep,
  ProcAutoError01
};

/* Private variables ---------------------------------------------------------*/
static UI_PROC_PF pfProcAuto = NULL;
static uint32_t AutoAccumulateCount = 0;
static uint32_t AutoTestCompleteCount = 0;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Internal Function for switching Auto Sub Proecess
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t SwitchAutoSubProcess(void *param, UI_MSG_T *pMsg)
{
  UI_ClearAllMessage();
	
  return (pfProcAuto(param, pMsg));	
}

/**
  * @brief  Internal Function for managing displaying while counting
  * @param  None
  * @retval None
  */
static void AutoDispCounter(uint8_t state)
{
  static uint8_t BlinkOn = TRUE;
  uint8_t string[8];

  DISP_ClearAll();

  switch(state)
  {
    case PROC_AUTO_START_H_MOTOR:
    case PROC_AUTO_START_S_MOTOR:
    case PROC_AUTO_START_B_COIL:
    case PROC_AUTO_STOP_H_MOTOR:
    case PROC_AUTO_START_S_COIL:
    {
      if(AutoTestCompleteCount > 0)
      {
        sprintf(&string[0], DISP_LOWER_STR_FORMAT, AutoTestCompleteCount);
        DISP_LowerPutStr(&string[0], 0);
      }

      if(AutoAccumulateCount > 0)
      {
        sprintf(&string[0], DISP_UPPER_STR_FORMAT, AutoAccumulateCount);

        if(AutoAccumulateCount < AUTO_ACCUMULATE_SET)
        {
          DISP_UpperPutStr(&string[0], 0);
          DISP_UpperPutStr("A", 0);
        }
        else
        {
          DISP_UpperPutStr(&string[0], 0);
        }
      }
      else
      {
        DISP_UpperPutStr("A", 0);
      }

      BlinkOn = TRUE;
    }
    break;

    case PROC_AUTO_BEEP:
      BlinkOn = TRUE;

    case PROC_AUTO_ADD_DELAY:
    {
      if(AutoTestCompleteCount > 0)
      {
        sprintf(&string[0], DISP_LOWER_STR_FORMAT, AutoTestCompleteCount);
        DISP_LowerPutStr(&string[0], 0);
      }

      if(BlinkOn == TRUE)
      {
        BlinkOn = FALSE;

        if(AutoAccumulateCount > 0)
        {
          sprintf(&string[0], DISP_UPPER_STR_FORMAT, AutoAccumulateCount);

          if(AutoAccumulateCount < AUTO_ACCUMULATE_SET)
          {
            DISP_UpperPutStr(&string[0], 0);
            DISP_UpperPutStr("A", 0);
          }
          else
          {
            DISP_UpperPutStr(&string[0], 0);
          }
        }
        else
        {
          DISP_UpperPutStr("A", 0);
        }
      }
      else
      {
        BlinkOn = TRUE;
      }
    }
    break;

    case PROC_AUTO_ERROR_01:
    {
      DISP_UpperPutStr("ERR-1", 0);
    }
    break;
  }

}

/**
  * @brief  Internal Process Function for Auto Start H Motor
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoStartHMotor(void *param, UI_MSG_T *pMsg)
{
#define CAM_SW_TIMEOUT    (3000)

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      SENSOR_SetCount(0);

      BSP_H_MotorEnable(TRUE);
      BSP_V_PumpEnable(TRUE);

      UI_SetRefreshMsg(CAM_SW_TIMEOUT);
    }
    break;

    case UIMSG_REFRESH:
    {
      /* Display Error Message */
      UI_MSG_T msg = {0, UIMSG_INIT};

      pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_ERROR_01];

      BSP_H_MotorEnable(FALSE);
      BSP_V_PumpEnable(FALSE);

      return(SwitchAutoSubProcess(param, &msg));
    }
    break;

    case UIMSG_KEY_SWH:
    {
      if((uint8_t)pMsg->param == UI_KEY_RELEASE)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_START_S_MOTOR];

        /* Hopper Position Set, Turn Off H-Motor, Turn On S-Motor & Pump */
        BSP_H_MotorEnable(FALSE);
        UI_SetRefreshMsg(0);

        return(SwitchAutoSubProcess(param, &msg));
      }
    }
    break;

    case UIMSG_KEY_RST:
    {
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_STOP_H_MOTOR];

        BSP_H_MotorEnable(FALSE);
        BSP_V_PumpEnable(FALSE);

        UI_SetRefreshMsg(0);

        return(SwitchAutoSubProcess(param, &msg));
      }
    }
    break;
  }

  AutoDispCounter(PROC_AUTO_START_H_MOTOR);
  return UI_RC_CONTINUE;

#undef CAM_SW_TIMEOUT
#undef CAM_ERR_TIMEOUT
}

/**
  * @brief  Internal Process Function for Auto Start S Motor
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoStartSMotor(void *param, UI_MSG_T *pMsg)
{
#define FREE_RUN_TIMEOUT  (5000)

  uint32_t sensorCounter = 0;
  sensorCounter = SENSOR_GetCount();

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      SENSOR_SetEnable(TRUE);
      
      BSP_S_MotorEnable(TRUE);
      BSP_V_PumpEnable(TRUE);

      UI_SetRefreshMsg(FREE_RUN_TIMEOUT);
    }
    break;

    case UIMSG_COUNTER:
    {
      AutoAccumulateCount++;

      if(sensorCounter >= 100)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_START_B_COIL];

        UI_SetRefreshMsg(0);

        BSP_S_MotorEnable(FALSE);
        BSP_V_PumpEnable(FALSE);

        SENSOR_SetEnable(FALSE);

        return(SwitchAutoSubProcess(param, &msg));
      }
    }
    break;

    case UIMSG_REFRESH:
    {
      UI_MSG_T msg = {0, UIMSG_INIT};
      pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_START_B_COIL];

      BSP_V_PumpEnable(FALSE);
      BSP_S_MotorEnable(FALSE);

      SENSOR_SetEnable(FALSE);

      return(SwitchAutoSubProcess(param, &msg));
    }
    break;

    case UIMSG_KEY_RST:
    {
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_STOP_H_MOTOR];

        BSP_V_PumpEnable(FALSE);
        BSP_S_MotorEnable(FALSE);

        SENSOR_SetEnable(FALSE);

        UI_SetRefreshMsg(0);

        return(SwitchAutoSubProcess(param, &msg));
      }
    }
    break;
  }

  AutoDispCounter(PROC_AUTO_START_S_MOTOR);
  return UI_RC_CONTINUE;

#undef FREE_RUN_TIMEOUT
}

/**
  * @brief  Internal Process Function for Auto Start B Coil
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoStartBCoil(void *param, UI_MSG_T *pMsg)
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
      UI_MSG_T msg = {0, UIMSG_INIT};

      pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_STOP_H_MOTOR];

      BSP_B_CoilEnable(FALSE);

      return (SwitchAutoSubProcess(param, &msg));
    }
    break;

  }

  AutoDispCounter(PROC_AUTO_START_B_COIL);
  return UI_RC_CONTINUE;

#undef BATCH_COIL_TIME
}


/**
  * @brief  Internal Process Function for Auto Stop H Motor
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoStopHMotor(void *param, UI_MSG_T *pMsg)
{
#define CAM_SW_TIMEOUT    (3000)

  static uint8_t SetCamSwitchTimeOut = FALSE;

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      BSP_H_MotorEnable(TRUE);

      SetCamSwitchTimeOut = TRUE;
      UI_SetRefreshMsg(CAM_SW_TIMEOUT);
    }
    break;

    case UIMSG_REFRESH:
    {
      UI_MSG_T msg = {0, UIMSG_INIT};

      pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_ERROR_01];

      BSP_H_MotorEnable(FALSE);

      return(SwitchAutoSubProcess(param, &msg));
    }
    break;

    case UIMSG_KEY_SWH:
    {
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};

        uint32_t sensorCounter = 0;
        sensorCounter = SENSOR_GetCount();

        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_START_S_COIL];

        /* Hopper Position Set, Turn OFF H-Motor */
        BSP_H_MotorEnable(FALSE);
        UI_SetRefreshMsg(0);

        return (SwitchAutoSubProcess(param, &msg));
      }
    }
    break;

  }

  AutoDispCounter(PROC_AUTO_STOP_H_MOTOR);
  return UI_RC_CONTINUE;

#undef CAM_SW_TIMEOUT
#undef CAM_ERR_TIMEOUT
}

/**
  * @brief  Internal Process Function for Auto Start S Coil
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoStartSCoil(void *param, UI_MSG_T *pMsg)
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

      UI_MSG_T msg = {0, UIMSG_INIT};

      if(AutoAccumulateCount >= AUTO_ACCUMULATE_SET)
      {
        AutoTestCompleteCount++;
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_BEEP];
      }
      else
      {
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_ADD_DELAY];
      }

      if(stampEnable == TRUE)
      {
        BSP_S_CoilEnable(FALSE);
      }

      return (SwitchAutoSubProcess(param, &msg));
    }
    break;
  }

  AutoDispCounter(PROC_AUTO_START_S_COIL);
  return UI_RC_CONTINUE;

#undef STAMP_COIL_TIME
}

/**
  * @brief  Internal Process Function for Auto Stop H Motor
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoAddDelay(void *param, UI_MSG_T *pMsg)
{
#define NORMAL_DELAY_TIME   (1000)
#define LARGE_DELAY_TIME    (300000)
  static int32_t largeDelayCnt = 0;

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      /* Check if it is 10000, if so delay must be 10 mins, Beep for 3  Seconds, increment lower display to 1
         else proceed with delay of 1sec
      */
      UI_SetRefreshMsg(NORMAL_DELAY_TIME);

      largeDelayCnt = LARGE_DELAY_TIME;
    }
    break;

    case UIMSG_REFRESH:
    {
      UI_MSG_T msg = {0, UIMSG_INIT};

      if(AutoAccumulateCount >= AUTO_ACCUMULATE_SET)
      {
        largeDelayCnt -= NORMAL_DELAY_TIME;

        if(largeDelayCnt <= 0)
        {
          AutoAccumulateCount = 0;
          pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_START_H_MOTOR];
          return (SwitchAutoSubProcess(param, &msg));
        }
        else
        {
          UI_SetRefreshMsg(NORMAL_DELAY_TIME);
        }
      }
      else
      {
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_START_H_MOTOR];
        return (SwitchAutoSubProcess(param, &msg));
      }
    }
    break;

    case UIMSG_KEY_RST:
    {
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        uint32_t sensorCounter = 0;

        UI_SetRefreshMsg(0);

        AutoAccumulateCount = 0;
        AutoTestCompleteCount = 0;

        SENSOR_SetCount(sensorCounter);

        return UI_RC_FINISH;
      }
    }
    break;
  }

  AutoDispCounter(PROC_AUTO_ADD_DELAY);
  return UI_RC_CONTINUE;

#undef NORMAL_DELAY_TIME
#undef LARGE_DELAY_TIME
}

/**
  * @brief  Internal Process Function for Auto Beep
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoBeep(void *param, UI_MSG_T *pMsg)
{
#define BEEP_ON_TIME    (300)
#define BEEP_OFF_TIME   (700)
#define TOTAL_BEEP_TIME (3000)

  static uint8_t  BeepOn = FALSE;
  static uint32_t StartBeepTime = 0;

  switch(pMsg->message)
  {
    case UIMSG_INIT:
      StartBeepTime  = BSP_GetSysTime();

    case UIMSG_REFRESH:
    {
      uint32_t sysTime = BSP_GetSysTime();

      if(absolute((int32_t)(sysTime - StartBeepTime)) >= TOTAL_BEEP_TIME)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_ADD_DELAY];

        BeepOn = FALSE;
        BSP_DisableBuzzer();

        UI_SetRefreshMsg(0);

        return (SwitchAutoSubProcess(param, &msg));
      }
      else
      {
        if(BeepOn == TRUE)
        {
          BeepOn = FALSE;

          BSP_DisableBuzzer();
          UI_SetRefreshMsg(BEEP_OFF_TIME);
        }
        else
        {
          BeepOn = TRUE;

          BSP_EnableBuzzer(BEEP_ON_TIME);
          UI_SetRefreshMsg(BEEP_ON_TIME);
        }
      }
    }
    break;

    case UIMSG_KEY_RST:
    {
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        UI_MSG_T msg = {0, UIMSG_INIT};
        pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_ADD_DELAY];

        BeepOn = FALSE;
        BSP_DisableBuzzer();

        UI_SetRefreshMsg(0);

        return (SwitchAutoSubProcess(param, &msg));
      }
    }
    break;

    default:
      break;
  }

  AutoDispCounter(PROC_AUTO_BEEP);
  return UI_RC_CONTINUE;

#undef BEEP_ON_TIME
#undef BEEP_OFF_TIME
#undef TOTAL_BEEP_TIME
}


/**
  * @brief  Internal Process Function for Auto Error 01
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
static uint8_t ProcAutoError01(void *param, UI_MSG_T *pMsg)
{
  AutoDispCounter(PROC_AUTO_ERROR_01);

  return UI_RC_CONTINUE;
}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for Auto
  * @param  param - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessAuto(void *param, UI_MSG_T *pMsg)
{
  if(pMsg->message == UIMSG_INIT)
  {
    pfProcAuto = PF_PROC_AUTO_LIST[PROC_AUTO_START_H_MOTOR];
  }

  return (pfProcAuto(param, pMsg));
}

/**********************************END OF FILE*********************************/
