/**
  ******************************************************************************
  * @file    ui.c
  * @author  CG Global R&D MCoEx - D&A Team
  * @version V1.0.0
  * @date    15-July-2014
  * @brief   User Interface Source File.
  *          Implements Functions to interface a input device such as
  *          keyboard to a output device such as display
  *
  * User Interface implements a menu tree with a display and a keypad.
  * UI related messages are passed from keypad to the UI core via
  * UI_MSG_T structure.
  * UI interfaces the hardware display in the file ui_display.c &
  * Keypad in ui_keypad.c
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 Crompton Greaves</center></h2>
  *
  * This material is considered a trade secret by Crompton Greaves Limited.
  * Unauthorized access prohibited
  * This software is provided "as is" without warranty or merchantability or
  * fitness for a particular purpose.
  * Further, Crompton Greaves doesn't warrant/guarantee, or make any
  * representations regarding the use, or the result of the use, of the
  * software interms of correctness, accuracy, readability or otherwise.
  *
  ******************************************************************************
  */

/** @addtogroup User_Interface
  * @{
  */

/** @addtogroup UI_Core
  * @{
  */

/** @addtogroup UI_Core_Private_Includes
  * @{
  */
#include <stdlib.h>
#include <string.h>

#include "bsp.h"

#include "ui.h"

/**
  * @}
  */

/** @addtogroup UI_Core_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Core_Private_Defines
  * @{
  */
#define CONTEXT_SZ             UI_CONTEXT_SIZE
#define MSG_STACK_SZ           UI_MSG_STACK_SIZE

/**
  * @}
  */

/** @addtogroup UI_Core_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Core_Private_Variables
  * @{
  */
static uint8_t  ContextPtr;          /* pointer for context buffer position  */
static uint32_t RefreshMsgInterval;  /* timer interval in ms for refresh msg */
static uint32_t BkupRefreshTimer;    /* refresh timer back-up time           */
static UI_CONTEXT_T CurContext;      /* current context info                 */
static UI_CONTEXT_T ContextBuffer[CONTEXT_SZ];            /* context buffer */

static uint8_t MsgRdIdx;             /* message stack read index pointer     */
static uint8_t MsgWrIdx;             /* message stack write index pointer    */
static uint8_t MsgUnProcessed;       /* number of un-processed message       */
static UI_MSG_T MsgStack[MSG_STACK_SZ];                   /* message stack  */
/**
  * @}
  */

/** @addtogroup UI_Core_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup UI_Core_Private_Functions
  * @{
  */
/**
  * @brief  pushes current context
  *         current context is stored in context buffer
  * @param  None
  * @retval UI_SUCCESS - If context storing was successful;
  *         UI_FAILURE - If context buffer was full
  */
static uint8_t StoreContext(void)
{
  if(ContextPtr < CONTEXT_SZ)
  {
    /* Store the current context in the context buffer */
    ContextBuffer[ContextPtr] = CurContext;
    ContextPtr++;

    return UI_SUCCESS;
  }

  return UI_FAILURE;
}

/**
  * @brief  retrieves context in the buffer
  *         context is retrieved from context buffer
  * @param  None
  * @retval UI_SUCCESS - If context retrieving was successful;
  *         UI_FAILURE - If context buffer was empty
  */
static uint8_t RestoreContext(void)
{
  if(ContextPtr > 0)
  {
    /* Restore the current context from the context buffer */
    ContextPtr--;
    CurContext = ContextBuffer[ContextPtr];

    return UI_SUCCESS;
  }

  return UI_FAILURE;
}
/**
  * @}
  */

/** @addtogroup UI_Core_Public_Functions
  * @{
  */


/**
  * @brief  User Interface Initialization
  *         Initialize the Message Buffer, the Menu Tree,
  *         the current Context & Home Process
  * @param  None
  * @retval None
  */
void UI_Init(void)
{
  uint32_t cnt;
  UI_MSG_T msg = {0, UIMSG_INIT};

  MsgWrIdx = 0;
  MsgRdIdx = 0;
  MsgUnProcessed = 0;

  RefreshMsgInterval = 0;
  BkupRefreshTimer = 0;

  /* Flush Message stack */
  for(cnt = 0; cnt < MSG_STACK_SZ; cnt++)
  {
    MsgStack[cnt].message = 0;
    MsgStack[cnt].param = 0;
  }

  /* Initialize Menu Status according to the Protection Code */
  UI_MenuInit();

  /* Default Process is Home Process */
  CurContext.process = UI_PROC_HOME_ID;
  /* Default menu is Main Menu */
  CurContext.menu = UI_MENU_MAIN_ID;
  CurContext.type = UI_TYPE_PROCESS;
  CurContext.child = 0;

  /* Post Message to Initialize Home Process */
  UI_PostMessage(&msg);
}

/**
  * @brief  User Interface read message from the buffer
  *         Read any unprocessed message from the message buffer
  * @param  pMsg - Pointer to a message, where message needs to be read
  * @retval UI_SUCCESS if any unprocessed message found else returns UI_FAILURE
  */
uint8_t UI_GetMessage(UI_MSG_T *pMsg)
{
  if((MsgWrIdx != MsgRdIdx) && (MsgUnProcessed) && (pMsg != 0))
  {
    pMsg->message = MsgStack[MsgRdIdx].message;
    pMsg->param = MsgStack[MsgRdIdx].param;
    MsgRdIdx = (uint8_t)((MsgRdIdx + 1 == MSG_STACK_SZ) ? (0) : (MsgRdIdx + 1));
    MsgUnProcessed--;
    return UI_SUCCESS;
  }

  return UI_FAILURE;
}

/**
  * @brief  User Interface write message to the buffer
  *         Write a message to the message buffer if the buffer is not full
  * @param  pMsg - Pointer to a message, which needs to be written
  * @retval UI_SUCCESS if message written successfully else returns UI_FAILURE
  */
uint8_t UI_PostMessage(UI_MSG_T *pMsg)
{
  if(((MsgWrIdx != MsgRdIdx) || (!MsgUnProcessed)) && (pMsg != 0))
  {
    MsgStack[MsgWrIdx].message = pMsg->message;
    MsgStack[MsgWrIdx].param = pMsg->param;
    MsgWrIdx = (uint8_t)((MsgWrIdx + 1 == MSG_STACK_SZ) ? (0) : (MsgWrIdx + 1));
    MsgUnProcessed++;
    return UI_SUCCESS;
  }

  return UI_FAILURE;          /* Unprocessed UI_MSG_T Stack Full */
}

/**
  * @brief  User Interface Clear message stack
  * @param  None
  * @retval None
  */
void UI_ClearAllMessage(void)
{
  uint32_t cnt;

  MsgWrIdx = 0;
  MsgRdIdx = 0;
  MsgUnProcessed = 0;

  RefreshMsgInterval = 0;
  BkupRefreshTimer = 0;
	
  /* Flush Message stack */
  for(cnt = 0; cnt < MSG_STACK_SZ; cnt++)
  {
    MsgStack[cnt].message = 0;
    MsgStack[cnt].param = 0;
  }
}

/**
  * @brief  Reads the current context in pContext
  * @param  pContext - Pointer to context information,
  *                    where current context need to be read.
  * @retval None
  */
void UI_GetContext(UI_CONTEXT_T *pContext)
{
  memcpy(pContext, &CurContext, sizeof(UI_CONTEXT_T));
}

/**
  * @brief  Reads the Number of un processed Messages
  * @param  None
  * @retval number of un processed Message
  */
uint8_t UI_GetNbOfMsgUnProcessed(void)
{
  return MsgUnProcessed;
}

/**
  * @brief  Invokes a menu item
  * @param  id - Menu to be invoked
  * @retval Returns UI_SUCCESS if pop up menu successful
  */
uint8_t UI_InvokeMenu(uint8_t id)
{
  uint8_t cnt = UI_GetMenuNbEnabledChild(id);

  if(cnt > 0)
  {
    if(StoreContext() == UI_SUCCESS)
    {
      if(id < UI_MENU_MAX_ITEM)
      {
        CurContext.menu = id;
        CurContext.child = 0;
        CurContext.type = UI_TYPE_MENU;
        CurContext.process = 0;

        UI_UpdateMenu();

        return UI_SUCCESS;
      }
    }
  }

  return UI_FAILURE;
}

/**
  * @brief  Invokes a process
  * @param  id - process to be invoked
  * @retval Returns UI_SUCCESS if pop up process successful
  */
uint8_t UI_InvokeProcess(uint8_t id)
{
  if(StoreContext() == UI_SUCCESS)
  {
    if(id < UI_PROC_MAX_ITEM)
    {
      UI_MSG_T ini = {0, UIMSG_INIT};

      CurContext.menu = 0;
      CurContext.child = 0;
      CurContext.type = UI_TYPE_PROCESS;
      CurContext.process = id;

      UI_PostMessage(&ini);

      return UI_SUCCESS;
    }
  }

  return UI_FAILURE;
}

/**
  * @brief  Sets the Timeout for generating delayed exit message
  * @note   Should be called if process is displaying a message and
  *         needs a delayed exit for the user to read the message correctly.
  * @param  interval - delayed exit timeoout
  * @retval None
  */
void UI_SetRefreshMsg(uint32_t interval)
{
  RefreshMsgInterval = interval;
  BkupRefreshTimer = BSP_GetSysTime();
}

/**
  * @brief  Execute user interface
  *         Timer related events
  * @note   Should be executed in continious execution loop
  * @param  None
  * @retval None
  */
void UI_Exec(void)
{
  /* Check if Refresh Timer is Enabled */
  if(RefreshMsgInterval != 0)
  {
    uint32_t sysTime = BSP_GetSysTime();

    /* Check if the Refresh Interval is Reached */
    if(absolute((int32_t)(sysTime - BkupRefreshTimer)) >= RefreshMsgInterval)
    {
      UI_MSG_T rfshMsg = {0, UIMSG_REFRESH};

      RefreshMsgInterval = 0;
      UI_PostMessage(&rfshMsg);
    }
  }
}

/**
  * @brief  Execute user interface
  *         Handles messages from the user inputs, delayed timeout and
  *         screen timeout
  * @note   Should be executed in continious execution loop
  * @param  None
  * @retval None
  */
void UI_ProcessMsg(void)
{
  UI_MSG_T msg;

  /* Get any un-addressed message */
  if(UI_GetMessage(&msg) == UI_SUCCESS)
  {
    if(CurContext.type == UI_TYPE_PROCESS)
    {
      /* Execute the process if the UI item is a process */
      UI_PROC_PF pfProcess = UI_GetProcessInfo(CurContext.process);

      if(pfProcess != 0)
      {
        /*
        Execute the Process by passing the UI message,
        Check if the Process execution is finished.
        If the process execution is finished, Restore the context and
        Update the Menu
        */
        if(pfProcess((void *)&CurContext, &msg) != UI_RC_FINISH)
        {
          return;
        }
      }

      if(CurContext.type == UI_TYPE_PROCESS)
      {
        RestoreContext();
      }

      if(CurContext.type == UI_TYPE_MENU)
      {
        UI_UpdateMenu();
      }
      else
      {
        UI_MSG_T ini = {0, UIMSG_INIT};

        UI_PostMessage(&ini);
      }
    }
    else
    {
      /* Execute the Menu if the UI item is a Menu */
      switch(msg.message)
      {
        case UIMSG_INIT:
          UI_UpdateMenu();
          break;

        #ifdef KPD_KEY_BACK
        case UIMSG_KEY_BACK:
        #endif
        #ifdef KPD_KEY_UP
        case UIMSG_KEY_UP:
        #endif
          if((uint8_t)msg.param == UI_KEY_PRESS)
          {
            /* Scroll down */
            uint8_t curChildNo = CurContext.child;
            uint8_t nbTotalChild = UI_GetMenuNbTotalChild(CurContext.menu);

            while(1)
            {
              uint8_t enFlag;

              curChildNo = (uint8_t)((curChildNo < (nbTotalChild - 1)) ?
                                     (curChildNo + 1) : 0);
              enFlag = UI_GetMenuEnableFlag(CurContext.menu, curChildNo);

              if(enFlag == UI_ENABLED)
              {
                CurContext.child = curChildNo;
                UI_UpdateMenu();
                break;
              }
            }
          }
          break;

        #ifdef KPD_KEY_NEXT
        case UIMSG_KEY_NEXT:
        #endif
        #ifdef KPD_KEY_DOWN
        case UIMSG_KEY_DOWN:
        #endif
          if((uint8_t)msg.param == UI_KEY_PRESS)
          {
            /* Scroll up */
            uint8_t curChildNo = CurContext.child;
            uint8_t nbTotalChild = UI_GetMenuNbTotalChild(CurContext.menu);

            while(1)
            {
              uint8_t enFlag;

              curChildNo = (uint8_t)((curChildNo > 0) ? (curChildNo - 1) :
                                     (nbTotalChild - 1));
              enFlag = UI_GetMenuEnableFlag(CurContext.menu, curChildNo);

              if(enFlag == UI_ENABLED)
              {
                CurContext.child = curChildNo;
                UI_UpdateMenu();
                break;
              }
            }
          }
          break;

        #ifdef KPD_KEY_CLR
        case UIMSG_KEY_CLR:
        #endif
        case UIMSG_KEY_RST:

          /* Go Back to the Previous Menu */
          if((uint8_t)msg.param == UI_KEY_PRESS)
          {
            if(RestoreContext() == UI_SUCCESS)
            {
              if(CurContext.type == UI_TYPE_MENU)
              {
                UI_UpdateMenu();
              }
              else
              {
                UI_MSG_T ini = {0, UIMSG_INIT};
                UI_PostMessage(&ini);
              }
            }
            else
            {
            }
          }
          break;

        #ifdef KPD_KEY_ENT
        case UIMSG_KEY_ENT:
          /* Enter the Menu */
          if((uint8_t)msg.param == UI_KEY_PRESS)
          {
            UI_MENU_INFO_T *pChild;
            pChild = UI_GetMenuChildInfo(CurContext.menu, CurContext.child);

            if(pChild->type == UI_TYPE_MENU)
            {
              if(UI_GetMenuNbEnabledChild(CurContext.menu) > 0)
              {
                if(StoreContext() == UI_SUCCESS)
                {
                  uint8_t nbTotalChild;
                  uint8_t curChildNo = 0;

                  nbTotalChild = UI_GetMenuNbTotalChild(CurContext.menu);

                  CurContext.menu = pChild->index;
                  CurContext.type = UI_TYPE_MENU;
                  CurContext.process = 0;

                  while(curChildNo < nbTotalChild)
                  {
                    uint8_t enFlag;

                    enFlag = UI_GetMenuEnableFlag(CurContext.menu, curChildNo);

                    if(enFlag == UI_ENABLED)
                    {
                      CurContext.child = curChildNo;
                      break;
                    }
                    else
                    {
                      curChildNo++;
                    }
                  }
                }
              }

              UI_UpdateMenu();
            }
            else
            {
              if(StoreContext() == UI_SUCCESS)
              {
                UI_MSG_T ini = {0, UIMSG_INIT};

                CurContext.process = pChild->index;
                CurContext.type = UI_TYPE_PROCESS;

                UI_PostMessage(&ini);
              }
            }
          }
          break;
        #endif

        default:
          break;
      }
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
