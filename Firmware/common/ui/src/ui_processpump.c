/**
  ******************************************************************************
  * @file    ui_processpump.c
  * @author  Vipul Panchal
  * @brief   This file contains ui pump process function
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ui.h"

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Process Function for pump Process
  * @param  pParam - Pointer to the any parameters
  * @param  pMsg - Pointer to the ui message
  * @retval status of the process (continue or Finish)
  */
uint8_t UI_ProcessPump(void *pParam, UI_MSG_T *pMsg)
{
  char string[8];
  uint32_t sensorCounter = 0;

  switch(pMsg->message)
  {
    case UIMSG_INIT:
    {
      SENSOR_SetCount(0);
      SENSOR_SetEnable(TRUE);

      BSP_V_PumpEnable(TRUE);
    }
    break;

    case UIMSG_KEY_RST:
      if((uint8_t)pMsg->param == UI_KEY_PRESS)
      {
        SENSOR_SetEnable(FALSE);
        SENSOR_SetCount(0);
        
        BSP_V_PumpEnable(FALSE);

        return UI_RC_FINISH;
      }
      break;
  }
  
  sensorCounter = SENSOR_GetCount();

  sprintf((char *)&string[0], DISP_LOWER_STR_FORMAT, sensorCounter);
  DISP_LowerClear();
  DISP_LowerPutStr((char *)&string[0], 0);

  return UI_RC_CONTINUE;
}
/**********************************END OF FILE*********************************/
