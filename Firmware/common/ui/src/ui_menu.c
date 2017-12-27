/**
  ******************************************************************************
  * @file    ui_menu.c
  * @author  Vipul Panchal
  * @brief   User Interface Menu Handling Source File.
  *           + Implements Functions to update menu
  *           + Implements menu tree
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Menu
  * @{
  */

/** @addtogroup UI_Menu_Private_Includes
  * @{
  */
#include "bsp.h"

#include "ui.h"

/**
  * @}
  */

/** @addtogroup UI_Menu_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Menu_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Menu_Private_Constant_Tables
  * @{
  */
/**
  *  Child info of Main Menu
  */
const UI_MENU_INFO_T MENU_MAIN_CHILD_INFO[] =
{
  #if (UI_PROC_AUTO_DEF == 1)
  {
    "AUTO",
    UI_PROC_AUTO_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_MENU_MANL_DEF == 1)
  {
    "MANUL",
    UI_MENU_MANL_ID,
    UI_TYPE_MENU
  },
  #endif

  #if (UI_PROC_SETM_DEF == 1)
  {
    "SETMODE",
    UI_PROC_SETM_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_CNTLG_DEF == 1)
  {
    "CNTLG",
    UI_PROC_CNTLG_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_STPEN_DEF == 1)
  {
    "STAMP",
    UI_PROC_STPEN_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_UVSET_DEF == 1)
  {
    "UVSET",
    UI_PROC_UVSET_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_UVENB_DEF == 1)
  {
    "UV",
    UI_PROC_UVENB_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_WMSG_DEF == 1)
  {
    "MSGSET",
    UI_PROC_WMSG_ID,
    UI_TYPE_PROCESS
  },
  #endif
};

/**
  *  Child info of Menu Manual
  */
#if (UI_MENU_MANL_DEF == 1)
const UI_MENU_INFO_T MENU_MANL_CHILD_INFO[] =
{
  #if (UI_MENU_MOTOR_DEF == 1)
  {
    "MOTOR",
    UI_MENU_MOTOR_ID,
    UI_TYPE_MENU
  },
  #endif

  #if (UI_MENU_COIL_DEF == 1)
  {
    "COIL",
    UI_MENU_COIL_ID,
    UI_TYPE_MENU
  },
  #endif

  #if (UI_PROC_KBRD_DEF == 1)
  {
    "K-BRD",
    UI_PROC_KBRD_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_MENU_SWTCH_DEF == 1)
  {
    "SWTCH",
    UI_MENU_SWTCH_ID,
    UI_TYPE_MENU
  },
  #endif

  #if (UI_PROC_SEG_DEF == 1)
  {
    "SEG",
    UI_PROC_SEG_ID,
    UI_TYPE_PROCESS
  },
  #endif
};
#endif


/**
  *  Child info of Menu Motor
  */
#if (UI_MENU_MOTOR_DEF == 1)
const UI_MENU_INFO_T MENU_MOTOR_CHILD_INFO[] =
{
  #if (UI_PROC_PUMP_DEF == 1)
  {
    "PUMP",
    UI_PROC_PUMP_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_HOPPR_DEF == 1)
  {
    "HOPPR",
    UI_PROC_HOPPR_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_SPNDL_DEF == 1)
  {
    "SPNDL",
    UI_PROC_SPNDL_ID,
    UI_TYPE_PROCESS
  },
  #endif
};
#endif

/**
  *  Child info of Menu Coil
  */
#if (UI_MENU_COIL_DEF == 1)
const UI_MENU_INFO_T MENU_COIL_CHILD_INFO[] =
{
  #if (UI_PROC_BCOIL_DEF == 1)
  {
    "BCOIL",
    UI_PROC_BCOIL_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_SCOIL_DEF == 1)
  {
    "SCOIL",
    UI_PROC_SCOIL_ID,
    UI_TYPE_PROCESS
  },
  #endif
};
#endif

/**
  *  Child info of Menu Switch
  */
#if (UI_MENU_SWTCH_DEF == 1)
const UI_MENU_INFO_T MENU_SWTCH_CHILD_INFO[] =
{
  #if (UI_PROC_HSWT_DEF == 1)
  {
    "H-SWT",
    UI_PROC_HSWT_ID,
    UI_TYPE_PROCESS
  },
  #endif

  #if (UI_PROC_ISWT_DEF == 1)
  {
    "I-SWT",
    UI_PROC_ISWT_ID,
    UI_TYPE_PROCESS
  },
  #endif
};
#endif

/**
  * UI Menu Child Info Listing
  */
const UI_MENU_INFO_T *UI_MENU_CHILD_INFO_LIST[] =
{
  MENU_MAIN_CHILD_INFO,

  #if (UI_MENU_MANL_DEF == 1)
  MENU_MANL_CHILD_INFO,
  #endif

  #if (UI_MENU_MOTOR_DEF == 1)
  MENU_MOTOR_CHILD_INFO,
  #endif

  #if (UI_MENU_COIL_DEF == 1)
  MENU_COIL_CHILD_INFO,
  #endif

  #if (UI_MENU_SWTCH_DEF == 1)
  MENU_SWTCH_CHILD_INFO,
  #endif
};

/**
  * UI Menu Child Count Listing
  */
const uint8_t UI_MENU_NB_CHILD_LIST[] =
{
  sizeof(MENU_MAIN_CHILD_INFO) / sizeof(UI_MENU_INFO_T),

  #if (UI_MENU_MANL_DEF == 1)
  sizeof(MENU_MANL_CHILD_INFO) / sizeof(UI_MENU_INFO_T),
  #endif

  #if (UI_MENU_MOTOR_DEF == 1)
  sizeof(MENU_MOTOR_CHILD_INFO) / sizeof(UI_MENU_INFO_T),
  #endif

  #if (UI_MENU_COIL_DEF == 1)
  sizeof(MENU_COIL_CHILD_INFO) / sizeof(UI_MENU_INFO_T),
  #endif

  #if (UI_MENU_SWTCH_DEF == 1)
  sizeof(MENU_SWTCH_CHILD_INFO) / sizeof(UI_MENU_INFO_T),
  #endif
};

/**
  * @}
  */

/** @addtogroup UI_Menu_Private_Variables
  * @{
  */
/**
  * UI Menu Child status
  */
static uint8_t MenuMainChildStatus[sizeof(MENU_MAIN_CHILD_INFO) / sizeof(
                                     UI_MENU_INFO_T)];

#if (UI_MENU_MANL_DEF == 1)
static uint8_t MenuManlChildStatus[sizeof(MENU_MANL_CHILD_INFO) / sizeof(
                                     UI_MENU_INFO_T)];
#endif

#if (UI_MENU_MOTOR_DEF == 1)
static uint8_t MenuMotorChildStatus[sizeof(MENU_MOTOR_CHILD_INFO) / sizeof(
                                      UI_MENU_INFO_T)];
#endif

#if (UI_MENU_COIL_DEF == 1)
static uint8_t MenuCoilChildStatus[sizeof(MENU_COIL_CHILD_INFO) / sizeof(
                                     UI_MENU_INFO_T)];
#endif

#if (UI_MENU_SWTCH_DEF == 1)
static uint8_t MenuSwtchChildStatus[sizeof(MENU_SWTCH_CHILD_INFO) / sizeof(
                                      UI_MENU_INFO_T)];
#endif

/**
  * UI Menu Child Status Listing
  */
static const uint8_t *MENU_CHILD_STATUS_LIST[] =
{
  &MenuMainChildStatus[0],

  #if (UI_MENU_MANL_DEF == 1)
  &MenuManlChildStatus[0],
  #endif

  #if (UI_MENU_MOTOR_DEF == 1)
  &MenuMotorChildStatus[0],
  #endif

  #if (UI_MENU_COIL_DEF == 1)
  &MenuCoilChildStatus[0],
  #endif

  #if (UI_MENU_SWTCH_DEF == 1)
  &MenuSwtchChildStatus[0],
  #endif
};

/**
  * @}
  */

/** @addtogroup UI_Menu_Private_Functions
  * @{
  */


/**
  * @}
  */

/** @addtogroup UI_Menu_Public_Functions
  * @{
  */

/**
  * @brief  Enables / Disables a menu child item
  *         Sets the Flag to Enable / Disable a Child in a Menu
  * @param  menuId - Menu Identification No.
  * @param  childNo - Child No of the Menu
  * @param  en - Enable / Disable the Child
  * @retval None
  */
void UI_SetMenuEnableFlag(uint8_t menuId, uint8_t childNo, uint8_t en)
{
  if(menuId < UI_MENU_MAX_ITEM)
  {
    uint8_t *pMenuChildStatus = (uint8_t *)MENU_CHILD_STATUS_LIST[menuId];

    if(childNo < UI_MENU_NB_CHILD_LIST[menuId])
    {
      pMenuChildStatus[childNo] = en;
    }
  }
}

/**
  * @brief  Reads the Enable / Disable flag of menu child
  * @param  menuId - Menu Identification No.
  * @param  childNo - Child No of the Menu
  * @retval Enable / Disable status of the menu child
  */
uint8_t UI_GetMenuEnableFlag(uint8_t menuId, uint8_t childNo)
{
  if(menuId < UI_MENU_MAX_ITEM)
  {
    uint8_t *pMenuChildStatus = (uint8_t *)MENU_CHILD_STATUS_LIST[menuId];

    if(childNo < UI_MENU_NB_CHILD_LIST[menuId])
    {
      return pMenuChildStatus[childNo];
    }
  }

  return UI_DISABLED;
}

/**
  * @brief  Returns the no. of enabled child items of a menu
  * @param  menuId - Menu Identification No.
  * @retval No. of enabled child items of a menu
  */
uint8_t UI_GetMenuNbEnabledChild(uint8_t menuId)
{
  uint8_t  *pMenuChildStatus = (uint8_t *)MENU_CHILD_STATUS_LIST[menuId];
  uint8_t cnt, enabledChildCnt, totalChildCnt;

  totalChildCnt = UI_MENU_NB_CHILD_LIST[menuId];
  enabledChildCnt = 0;

  for(cnt = 0; cnt < totalChildCnt; cnt++)
  {
    if(pMenuChildStatus[cnt] == UI_ENABLED)
    {
      enabledChildCnt++;
    }
  }

  return enabledChildCnt;
}

/**
  * @brief  Returns the no. of total child items of a menu
  * @param  menuId - Menu Identification No.
  * @retval No. of total child items of a menu
  */
uint8_t UI_GetMenuNbTotalChild(uint8_t menuId)
{
  return UI_MENU_NB_CHILD_LIST[menuId];
}

/**
  * @brief  Returns the child info
  * @param  menuId - Menu Identification No.
  * @param  childNo - Child No of the Menu
  * @retval Pointer to Menu Info structure of the child
  */
UI_MENU_INFO_T *UI_GetMenuChildInfo(uint8_t menuId, uint8_t childNo)
{
  UI_MENU_INFO_T *pChild = 0;
  uint8_t *pMenuChildStatus = (uint8_t *)MENU_CHILD_STATUS_LIST[menuId];
  uint8_t cnt, enabledChildCnt, totalChildCnt;

  totalChildCnt = UI_MENU_NB_CHILD_LIST[menuId];
  enabledChildCnt = 0;

  for(cnt = 0; cnt < totalChildCnt; cnt++)
  {
    if(pMenuChildStatus[cnt] == UI_ENABLED)
    {
      if(enabledChildCnt == childNo)
      {
        pChild = (UI_MENU_INFO_T *)UI_MENU_CHILD_INFO_LIST[menuId];
        break;
      }

      enabledChildCnt++;
    }
  }

  return &pChild[cnt];
}

/**
  * @brief  Reads the current context and draws the menu display
  * @param  None
  * @retval None
  */
void UI_UpdateMenu(void)
{
  UI_CONTEXT_T context;

  UI_GetContext(&context);

  if(context.type == UI_TYPE_MENU)
  {
    UI_MENU_INFO_T *pChild =
      (UI_MENU_INFO_T *)UI_GetMenuChildInfo(context.menu, context.child);

    /* Update Menu String */
    DISP_ClearAll();
    DISP_UpperPutStr((char *)pChild->pString, 0);
  }
}

/**
  * @brief  Initializes all the menu items
  * @param  None
  * @retval None
  */
void UI_MenuInit(void)
{
  uint8_t menuCnt, childCnt;

  for(menuCnt = 0; menuCnt < UI_MENU_MAX_ITEM; menuCnt++)
  {
    uint8_t *pMenuChildStatus = (uint8_t *)MENU_CHILD_STATUS_LIST[menuCnt];

    for(childCnt = 0; childCnt < UI_MENU_NB_CHILD_LIST[menuCnt]; childCnt++)
    {
      pMenuChildStatus[childCnt] = UI_ENABLED;
    }
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
