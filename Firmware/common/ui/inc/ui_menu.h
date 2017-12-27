/**
  ******************************************************************************
  * @file    ui_menu.h
  * @author  Vipul Panchal
  * @brief   This file contains definitions related to
  *          User Interface Menu Items
  *
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Menu
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UI_MENU_H
#define __UI_MENU_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UI_Menu_Includes
  * @{
  */

#include "ui.h"

/**
  * @}
  */

/** @addtogroup UI_Menu_Exported_Types
  * @{
  */

/* UI Menu Info Structure */
typedef struct
{
  const char *pString;
  uint8_t    index;
  uint8_t    type;
} UI_MENU_INFO_T;

/**
  * @}
  */

/** @addtogroup UI_Menu_Exported_Types
  * @{
  */
/**
  *  Menu List
  */
typedef enum
{
  UI_MENU_MAIN_ID,

  #if (UI_MENU_MANL_DEF == 1)
  UI_MENU_MANL_ID,
  #endif

  #if (UI_MENU_MOTOR_DEF == 1)
  UI_MENU_MOTOR_ID,
  #endif

  #if (UI_MENU_COIL_DEF == 1)
  UI_MENU_COIL_ID,
  #endif

  #if (UI_MENU_SWTCH_DEF == 1)
  UI_MENU_SWTCH_ID,
  #endif

  UI_MENU_MAX_ITEM
} UI_MENU_ID_LIST;

/** @addtogroup UI_Menu_Exported_Functions
  * @{
  */

void UI_SetMenuEnableFlag(uint8_t menuId, uint8_t childNo, uint8_t en);
uint8_t UI_GetMenuEnableFlag(uint8_t menuId, uint8_t childNo);
uint8_t UI_GetMenuNbEnabledChild(uint8_t menuId);
uint8_t UI_GetMenuNbTotalChild(uint8_t menuId);
UI_MENU_INFO_T *UI_GetMenuChildInfo(uint8_t menuId, uint8_t childNo);
void UI_UpdateMenu(void);
void UI_MenuInit(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__UI_MENU_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Crompton Greaves ******END OF FILE*****/
