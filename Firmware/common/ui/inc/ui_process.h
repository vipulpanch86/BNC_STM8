/**
  ******************************************************************************
  * @file    ui_process.h
  * @author  Vipul Panchal
  * @brief   This file contains definitions related to User Interface Processes
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Process
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UI_PROCESS_H
#define __UI_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UI_Process_Includes
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Process_Exported_Types
  * @{
  */
/**
  *  Process List
  */
typedef enum
{
  UI_PROC_HOME_ID,

  #if (UI_PROC_AUTO_DEF == 1)
  UI_PROC_AUTO_ID,
  #endif

  #if (UI_PROC_SETM_DEF == 1)
  UI_PROC_SETM_ID,
  #endif

  #if (UI_PROC_CNTLG_DEF == 1)
  UI_PROC_CNTLG_ID,
  #endif

  #if (UI_PROC_STPEN_DEF == 1)
  UI_PROC_STPEN_ID,
  #endif

  #if (UI_PROC_UVSET_DEF == 1)
  UI_PROC_UVSET_ID,
  #endif

  #if (UI_PROC_UVENB_DEF == 1)
  UI_PROC_UVENB_ID,
  #endif

  #if (UI_PROC_KBRD_DEF == 1)
  UI_PROC_KBRD_ID,
  #endif

  #if (UI_PROC_SEG_DEF == 1)
  UI_PROC_SEG_ID,
  #endif

  #if (UI_PROC_PUMP_DEF == 1)
  UI_PROC_PUMP_ID,
  #endif

  #if (UI_PROC_HOPPR_DEF == 1)
  UI_PROC_HOPPR_ID,
  #endif

  #if (UI_PROC_SPNDL_DEF == 1)
  UI_PROC_SPNDL_ID,
  #endif

  #if (UI_PROC_BCOIL_DEF == 1)
  UI_PROC_BCOIL_ID,
  #endif

  #if (UI_PROC_SCOIL_DEF == 1)
  UI_PROC_SCOIL_ID,
  #endif

  #if (UI_PROC_HSWT_DEF == 1)
  UI_PROC_HSWT_ID,
  #endif

  #if (UI_PROC_ISWT_DEF == 1)
  UI_PROC_ISWT_ID,
  #endif

  #if (UI_PROC_WMSG_DEF == 1)
  UI_PROC_WMSG_ID,
  #endif

  UI_PROC_MAX_ITEM

} UI_PROC_ID_LIST;

/* UI Process Function Type */
typedef uint8_t (* UI_PROC_PF)(void *, UI_MSG_T *);

/**
  * @}
  */


/** @addtogroup UI_Process_Exported_Functions
  * @{
  */

UI_PROC_PF UI_GetProcessInfo(uint16_t processId);


/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__UI_PROCESS_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Crompton Greaves ******END OF FILE*****/
