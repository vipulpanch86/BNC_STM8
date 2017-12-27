/**
  ******************************************************************************
  * @file    ui_process.c
  * @author  Vipul Panchal
  * @brief   User Interface Process Handling Source File.
  *           + Implements Functions to get information about process
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Process
  * @{
  */

/** @addtogroup UI_Process_Private_Includes
  * @{
  */

#include "ui.h"

#include "ui_processhome.c"

#if (UI_PROC_AUTO_DEF == 1)
  #include "ui_processauto.c"
#endif

#if (UI_PROC_SETM_DEF == 1)
  #include "ui_processsetm.c"
#endif

#if (UI_PROC_CNTLG_DEF == 1)
  #include "ui_processcntlg.c"
#endif

#if (UI_PROC_STPEN_DEF == 1)
  #include "ui_processstpen.c"
#endif

#if (UI_PROC_UVSET_DEF == 1)
  #include "ui_processuvset.c"
#endif

#if (UI_PROC_UVENB_DEF == 1)
  #include "ui_processuvenb.c"
#endif

#if (UI_PROC_KBRD_DEF == 1)
  #include "ui_processkbrd.c"
#endif

#if (UI_PROC_SEG_DEF == 1)
  #include "ui_processseg.c"
#endif

#if (UI_PROC_PUMP_DEF == 1)
  #include "ui_processpump.c"
#endif

#if (UI_PROC_HOPPR_DEF == 1)
  #include "ui_processhopper.c"
#endif

#if (UI_PROC_SPNDL_DEF == 1)
  #include "ui_processspindle.c"
#endif

#if (UI_PROC_BCOIL_DEF == 1)
  #include "ui_processbcoil.c"
#endif

#if (UI_PROC_SCOIL_DEF == 1)
  #include "ui_processscoil.c"
#endif

#if (UI_PROC_HSWT_DEF == 1)
  #include "ui_processhswitch.c"
#endif

#if (UI_PROC_ISWT_DEF == 1)
  #include "ui_processiswitch.c"
#endif

#if (UI_PROC_WMSG_DEF == 1)
  #include "ui_processmsgset.c"
#endif
/**
  * @}
  */

/** @addtogroup UI_Process_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Process_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Process_Private_Constant_Tables
  * @{
  */

/*
 * UI Process Info Listing
 */
const UI_PROC_PF UI_PROCESS_INFO_LIST[] =
{
  UI_ProcessHome,

  #if (UI_PROC_AUTO_DEF == 1)
  UI_ProcessAuto,
  #endif

  #if (UI_PROC_SETM_DEF == 1)
  UI_ProcessSetM,
  #endif

  #if (UI_PROC_CNTLG_DEF == 1)
  UI_ProcessCntlg,
  #endif

  #if (UI_PROC_STPEN_DEF == 1)
  UI_ProcessStpen,
  #endif

  #if (UI_PROC_UVSET_DEF == 1)
  UI_ProcessUvset,
  #endif

  #if (UI_PROC_UVENB_DEF == 1)
  UI_ProcessUvenb,
  #endif

  #if (UI_PROC_KBRD_DEF == 1)
  UI_ProcessKeyboard,
  #endif

  #if (UI_PROC_SEG_DEF == 1)
  UI_ProcessSegment,
  #endif

  #if (UI_PROC_PUMP_DEF == 1)
  UI_ProcessPump,
  #endif

  #if (UI_PROC_HOPPR_DEF == 1)
  UI_ProcessHopper,
  #endif

  #if (UI_PROC_SPNDL_DEF == 1)
  UI_ProcessSpindle,
  #endif

  #if (UI_PROC_BCOIL_DEF == 1)
  UI_ProcessBCoil,
  #endif

  #if (UI_PROC_SCOIL_DEF == 1)
  UI_ProcessSCoil,
  #endif

  #if (UI_PROC_HSWT_DEF == 1)
  UI_ProcessHSwitch,
  #endif

  #if (UI_PROC_ISWT_DEF == 1)
  UI_ProcessISwitch,
  #endif

  #if (UI_PROC_WMSG_DEF == 1)
  UI_ProcessMsgSet,
  #endif
};

/**
  * @}
  */

/** @addtogroup UI_Menu_Public_Functions
  * @{
  */

/**
  * @brief  Returns the Process Information
  * @param  menuId - Menu Identification No.
  * @param  childNo - Child No of the Menu
  * @param  en - Enable / Disable the Child
  * @retval None
  */
UI_PROC_PF UI_GetProcessInfo(uint16_t processId)
{
  if(processId < UI_PROC_MAX_ITEM)
  {
    return (UI_PROCESS_INFO_LIST[processId]);
  }
  else
  {
    return (0);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Crompton Greaves ******END OF FILE*****/
