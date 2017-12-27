/**
  ******************************************************************************
  * @file    ui_config.h
  * @author  Vipul Panchal
  * @brief   This file contains definitions related to
  *          User Interface Configuration
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Config
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UI_CONFIG_H
#define __UI_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UI_Config_Includes
  * @{
  */
/**
  * @}
  */


/** @addtogroup UI_Config_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Config_Exported_Constants
  * @{
  */
/* UI Message Stack Size */
#define UI_MSG_STACK_SIZE      8
/* UI Context Buffer Size */
#define UI_CONTEXT_SIZE        8

/* UI General Messages (0-7) */
#define UIMSG_INIT             0
#define UIMSG_REFRESH          1

/* UI Key Messages (8-63) */
#ifdef KPD_KEY_DIG0
#define UIMSG_KEY_DIG0       (8 + KPD_KEY_DIG0)
#endif

#ifdef KPD_KEY_DIG1
#define UIMSG_KEY_DIG1       (8 + KPD_KEY_DIG1)
#endif

#ifdef KPD_KEY_DIG2
#define UIMSG_KEY_DIG2       (8 + KPD_KEY_DIG2)
#endif

#ifdef KPD_KEY_DIG3
#define UIMSG_KEY_DIG3       (8 + KPD_KEY_DIG3)
#endif

#ifdef KPD_KEY_DIG4
#define UIMSG_KEY_DIG4       (8 + KPD_KEY_DIG4)
#endif

#ifdef KPD_KEY_DIG5
#define UIMSG_KEY_DIG5       (8 + KPD_KEY_DIG5)
#endif

#ifdef KPD_KEY_DIG6
#define UIMSG_KEY_DIG6       (8 + KPD_KEY_DIG6)
#endif

#ifdef KPD_KEY_DIG7
#define UIMSG_KEY_DIG7       (8 + KPD_KEY_DIG7)
#endif

#ifdef KPD_KEY_DIG8
#define UIMSG_KEY_DIG8       (8 + KPD_KEY_DIG8)
#endif

#ifdef KPD_KEY_DIG9
#define UIMSG_KEY_DIG9       (8 + KPD_KEY_DIG9)
#endif

#ifdef KPD_KEY_ADD
#define UIMSG_KEY_ADD        (8 + KPD_KEY_ADD)
#endif

#ifdef KPD_KEY_ADD_UV
#define UIMSG_KEY_ADD_UV     (8 + KPD_KEY_ADD_UV)
#endif

#ifdef KPD_KEY_VALM
#define UIMSG_KEY_VALM       (8 + KPD_KEY_VALM)
#endif

#ifdef KPD_KEY_UV
#define UIMSG_KEY_UV         (8 + KPD_KEY_UV)
#endif

#ifdef KPD_KEY_AUTO
#define UIMSG_KEY_AUTO       (8 + KPD_KEY_AUTO)
#endif

#ifdef KPD_KEY_MANUAL
#define UIMSG_KEY_MANUAL     (8 + KPD_KEY_MANUAL)
#endif

#ifdef KPD_KEY_MODE
#define UIMSG_KEY_MODE       (8 + KPD_KEY_MODE)
#endif

#ifdef KPD_KEY_FUNC
#define UIMSG_KEY_FUNC       (8 + KPD_KEY_FUNC)
#endif

#ifdef KPD_KEY_UP
#define UIMSG_KEY_UP         (8 + KPD_KEY_UP)
#endif

#ifdef KPD_KEY_DOWN
#define UIMSG_KEY_DOWN       (8 + KPD_KEY_DOWN)
#endif

#ifdef KPD_KEY_BACK
#define UIMSG_KEY_BACK       (8 + KPD_KEY_BACK)
#endif

#ifdef KPD_KEY_NEXT
#define UIMSG_KEY_NEXT       (8 + KPD_KEY_NEXT)
#endif

#ifdef KPD_KEY_TENS
#define UIMSG_KEY_TENS       (8 + KPD_KEY_TENS)
#endif

#ifdef KPD_KEY_UNITS
#define UIMSG_KEY_UNITS      (8 + KPD_KEY_UNITS)
#endif

#ifdef KPD_KEY_ENT
#define UIMSG_KEY_ENT        (8 + KPD_KEY_ENT)
#endif

#ifdef KPD_KEY_CLR
#define UIMSG_KEY_CLR        (8 + KPD_KEY_CLR)
#endif

#ifdef KPD_KEY_V10
#define UIMSG_KEY_V10        (8 + KPD_KEY_V10)
#endif

#ifdef KPD_KEY_V20
#define UIMSG_KEY_V20        (8 + KPD_KEY_V20)
#endif

#ifdef KPD_KEY_V50
#define UIMSG_KEY_V50        (8 + KPD_KEY_V50)
#endif

#ifdef KPD_KEY_V100
#define UIMSG_KEY_V100       (8 + KPD_KEY_V100)
#endif

#ifdef KPD_KEY_V500
#define UIMSG_KEY_V500       (8 + KPD_KEY_V500)
#endif

#ifdef KPD_KEY_V1000
#define UIMSG_KEY_V1000      (8 + KPD_KEY_V1000)
#endif

#define UIMSG_KEY_SWI        (8 + KPD_KEY_SWI)
#define UIMSG_KEY_SWH        (8 + KPD_KEY_SWH)
#define UIMSG_KEY_RST        (8 + KPD_KEY_RST)


/* UI Application Specific Message (64-127) */
#define UIMSG_COUNTER          64
#define UIMSG_UVDETECT         65

/* UI Invalid Message 255 */
#define UIMSG_INVALID          255

/* UI Menu Enabling Defines */
#define UI_MENU_MANL_DEF       1
#define UI_MENU_MANL_DEF       1
#define UI_MENU_MOTOR_DEF      1
#define UI_MENU_COIL_DEF       1
#define UI_MENU_SWTCH_DEF      1

/* UI Process Enabling Defines */
#define UI_PROC_AUTO_DEF       1
#define UI_PROC_SETM_DEF       1
#define UI_PROC_CNTLG_DEF      1
#define UI_PROC_STPEN_DEF      1
#define UI_PROC_UVSET_DEF      1
#define UI_PROC_UVENB_DEF      1
#define UI_PROC_KBRD_DEF       1
#define UI_PROC_SEG_DEF        1
#define UI_PROC_PUMP_DEF       1
#define UI_PROC_HOPPR_DEF      1
#define UI_PROC_SPNDL_DEF      1
#define UI_PROC_BCOIL_DEF      1
#define UI_PROC_SCOIL_DEF      1
#define UI_PROC_HSWT_DEF       1
#define UI_PROC_ISWT_DEF       1
#define UI_PROC_WMSG_DEF       1

/**
  * @}
  */

/** @addtogroup UI_Config_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Config_Exported_Functions
  * @{
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __UI_CONFIG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Crompton Greaves ******END OF FILE*****/
