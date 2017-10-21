/**
  ******************************************************************************
  * @file    key.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    14-August-2015
  * @brief   Contains the functions to handle matrix keypad scanning,
  *          read/write keypad status
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
/* Keypad Matrix Definitions */
#define MAX_SC_LINES   (7)

#define NB_SC_4_RT0    (7)
#define NB_SC_4_RT1    (7)
#define NB_SC_4_RT2    (7)
#define NB_SC_4_RT3    (5)
#define NB_SC_4_RT4    (1)
#define NB_SC_4_RT5    (1)
#define NB_SC_4_RT6    (1)

#define SC_NB_MUXED    (7)

#define MAX_RT_LINES   (7)

#define NB_RT_4_SC0    (7)
#define NB_RT_4_SC1    (4)
#define NB_RT_4_SC2    (4)
#define NB_RT_4_SC3    (4)
#define NB_RT_4_SC4    (4)
#define NB_RT_4_SC5    (3)
#define NB_RT_4_SC6    (3)

#define RT_NB_MUXED    (4)

#define NB_KEYS \
(NB_RT_4_SC0 + NB_RT_4_SC1 + NB_RT_4_SC2 + NB_RT_4_SC3 + \
 NB_RT_4_SC4 + NB_RT_4_SC5 + NB_RT_4_SC6)

#define OPEN           (0)
#define CLOSED         (1)

#define LOW            (0)
#define HIGH           (1)

#define FALSE          (0)
#define TRUE           (1)

/* Private constants----------------------------------------------------------*/
/* List of Keypad Return Lines GPIO Port Pins */
static const GPIO_TypeDef* RET_PORT[MAX_RT_LINES - RT_NB_MUXED] = 
{
  KEY_RST_PORT,
  SW_CAM_PORT,
  SW_AUTO_PORT
};

/* List of Keypad Return Lines GPIO Port Pins */
static const uint8_t RET_PIN[MAX_RT_LINES - RT_NB_MUXED] = 
{
  KEY_RST_PIN,
  SW_CAM_PIN,
  SW_AUTO_PIN
};

static const uint8_t NB_SC_4_RT[MAX_RT_LINES] =
{
  NB_SC_4_RT0,
  NB_SC_4_RT1,
  NB_SC_4_RT2,
  NB_SC_4_RT3,
  NB_SC_4_RT4,
  NB_SC_4_RT5,
  NB_SC_4_RT6
};

static const uint8_t NB_SC_4_RT_ACC[MAX_RT_LINES] =
{
  0,
  NB_SC_4_RT0,
  NB_SC_4_RT0 + NB_SC_4_RT1,
  NB_SC_4_RT0 + NB_SC_4_RT1 + NB_SC_4_RT2,
  NB_SC_4_RT0 + NB_SC_4_RT1 + NB_SC_4_RT2 + NB_SC_4_RT3,
  NB_SC_4_RT0 + NB_SC_4_RT1 + NB_SC_4_RT2 + NB_SC_4_RT3 + NB_SC_4_RT4,
  NB_SC_4_RT0 + NB_SC_4_RT1 + NB_SC_4_RT2 + NB_SC_4_RT3 + NB_SC_4_RT4 + NB_SC_4_RT5
};

static const uint8_t NB_RT_4_SC[MAX_SC_LINES] =
{
  NB_RT_4_SC0,
  NB_RT_4_SC1,
  NB_RT_4_SC2,
  NB_RT_4_SC3,
  NB_RT_4_SC4,
  NB_RT_4_SC5,
  NB_RT_4_SC6
};

static const uint8_t NB_RT_4_SC_ACC[MAX_SC_LINES] =
{
  0,
  NB_RT_4_SC0,
  NB_RT_4_SC0 + NB_RT_4_SC1,
  NB_RT_4_SC0 + NB_RT_4_SC1 + NB_RT_4_SC2,
  NB_RT_4_SC0 + NB_RT_4_SC1 + NB_RT_4_SC2 + NB_RT_4_SC3,
  NB_RT_4_SC0 + NB_RT_4_SC1 + NB_RT_4_SC2 + NB_RT_4_SC3 + NB_RT_4_SC4,
  NB_RT_4_SC0 + NB_RT_4_SC1 + NB_RT_4_SC2 + NB_RT_4_SC3 + NB_RT_4_SC4 + NB_RT_4_SC5
};

/* Private variables ---------------------------------------------------------*/
static  uint8_t    KeyState[NB_KEYS]             = {0};
static  uint8_t    KeyPress[NB_KEYS]             = {0};
static  uint8_t    KeyDebounce[NB_KEYS]          = {0};
static  uint32_t   KeyBkpTime[NB_KEYS]           = {0};

static  uint8_t    KeyScanNo                     = 0;
static  uint8_t    DebounceTime                  = 0;
static  uint32_t   KeyScanTimer                  = 0;
static  void (* KeypadCB)(uint8_t, uint8_t);

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure Scan Lines for I/O Function
  *         Enable the GPIO Clock, Initialize GPIO as Output for
  *         each Scan Line
  * @param  None
  * @retval None
  */
#define ConfigScanLinesIO() \
  do{ \
  }while(0)

/**
  * @brief  Configure Return Lines for I/O Function
  *         Enable the GPIO Clock, Initialize GPIO as Input for
  *         each Return Line
  * @param  None
  * @retval None
  */
#define ConfigReturnLinesIO() \
  do{ \
  }while(0)

/**
  * @brief  Clear all Scan Line to Logic Level Low
  * @param  None
  * @retval None
  */
#define ClrAllScanLines() { \
    DEM0_MSA_PORT->ODR &= (uint8_t)~DEM0_MSA_PIN; \
    DEM0_MSB_PORT->ODR &= (uint8_t)~DEM0_MSB_PIN; \
    DEM0_MSC_PORT->ODR &= (uint8_t)~DEM0_MSC_PIN; \
  }

/**
  * @brief  Set a Scan Line to Logic Level High
  * @param  nb - ranges form 0 to NB_SC_4_RT_DEF - 1
  * @retval None
  */
#define SetScanLine(nb) { \
  ((nb) & 0x01) ? (DEM0_MSA_PORT->ODR |= (uint8_t)DEM0_MSA_PIN) : (DEM0_MSA_PORT->ODR &= (uint8_t)~DEM0_MSA_PIN); \
  ((nb) & 0x02) ? (DEM0_MSB_PORT->ODR |= (uint8_t)DEM0_MSB_PIN) : (DEM0_MSB_PORT->ODR &= (uint8_t)~DEM0_MSB_PIN); \
  ((nb) & 0x04) ? (DEM0_MSC_PORT->ODR |= (uint8_t)DEM0_MSC_PIN) : (DEM0_MSC_PORT->ODR &= (uint8_t)~DEM0_MSC_PIN); \
}

/**
  * @brief  Get the Logic Level on a Return Line
  * @param  None
  * @retval returns Mux Value
  */
#define GetReturnVal(val) { \
  val = 0; \
  val |= (uint8_t)((MUX0_MSA_PORT->IDR & MUX0_MSA_PIN) ? 0: 1<<0); \
  val |= (uint8_t)((MUX0_MSB_PORT->IDR & MUX0_MSB_PIN) ? 0: 1<<1); \
  val |= (uint8_t)((MUX0_MSC_PORT->IDR & MUX0_MSC_PIN) ? 0: 1<<2); \
}

/**
  * @brief  Set the current state of the key
  *         Change the current key status depending on the previous
  *         state of the key
  * @param  keyNo - ranges form 0 to NB_KEYS - 1
  * @param  pressState - the key press state OPEN / CLOSED
  * @retval None
  */
@inline static void SetKeyState(uint8_t keyNo, uint8_t pressState)
{
  /* Waiting for a keypress */
  if(KeyState[keyNo] == KEY_STATE_IDLE)
  {
    if(pressState == CLOSED)
    {
      /* Update the state to pressed */
      KeyState[keyNo] = KEY_STATE_PRESSED;

      /* Generate a callback */
      if(KeypadCB != NULL)
      {
        KeypadCB(keyNo, KeyState[keyNo]);
      }
    }
  }
  else if(KeyState[keyNo] == KEY_STATE_PRESSED)
  {
    if(pressState == OPEN)
    {
      KeyState[keyNo] = KEY_STATE_RELEASED;

      /* Generate a callback */
      if(KeypadCB != NULL)
      {
        KeypadCB(keyNo, KeyState[keyNo]);
      }
    }
  }
  else
  {
    KeyState[keyNo] = KEY_STATE_IDLE;
  }
}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Initialize the Keypad
  *         Initialize Row & Column Lines of the Matrix,
  *         Set key debounce value,
  *         Set key hold time,
  *         Install call back function.
  * @param  debounce - key debounce value in milliseconds
  * @param  hold - key state change from pressed to hold after this value
  * @param  cb - callback function when a key state changes
  * @retval None
  */
void KPD_Init(uint8_t debounce, void (* cb)(uint8_t, uint8_t))
{
  uint8_t keyCnt;

  ConfigScanLinesIO();
  ConfigReturnLinesIO();

  KPD_SetDebounceTime(debounce);
  KPD_AddEventListener(cb);

  KeyScanTimer = 0;
  KeyScanNo = 0;

  for(keyCnt = 0; keyCnt < NB_KEYS; keyCnt++)
  {
    KeyState[keyCnt] = KEY_STATE_IDLE;
    KeyPress[keyCnt] = OPEN;
    KeyDebounce[keyCnt] = FALSE;
    KeyBkpTime[keyCnt] = 0;
  }
}

/**
  * @brief  Scan the Keypad
  *         scans each key sequentially and updates the key status
  * @note   Must be called in a continious loop
  * @param  None
  * @retval None
  */
void KPD_Scan(void)
{
  uint8_t keyScanNo = 0, scanLine = 0, retLine = 0;
  uint8_t keyPressBit[(NB_KEYS / 8) + ((NB_KEYS % 8) ? (1) : (0)) ] = {0};
  uint32_t bspSysTime = BSP_GetSysTime();
  
  /* Check if any key is pressed in Muxed lines */
  ClrAllScanLines();
  GetReturnVal(retLine);
  
  if(retLine > 0)
  {
    for(scanLine = 0; scanLine < NB_SC_4_RT[retLine - 1]; scanLine++)  
    {
      uint8_t retVal = 0;
      
      SetScanLine(scanLine + 1);
      GetReturnVal(retVal);
      
      if(retVal == 0)
      {
        keyScanNo = (uint8_t)(NB_SC_4_RT_ACC[retLine - 1] + scanLine);
        /* change the key press state */
        keyPressBit[keyScanNo >> 3] |= (uint8_t)(1 << (keyScanNo & 0x7));
        
        break;
      }
    }
  }

  /* Scan Non Muxed Keys */
  scanLine = 0;
  for(retLine = RT_NB_MUXED; retLine <  NB_RT_4_SC[scanLine]; retLine++)
  {
    keyScanNo = (uint8_t)(NB_SC_4_RT_ACC[retLine] + scanLine);
    if((RET_PORT[retLine - RT_NB_MUXED]->IDR & RET_PIN[retLine - RT_NB_MUXED]) == 0)
    {
      keyPressBit[keyScanNo >> 3] |= (uint8_t)(1 << (keyScanNo & 0x7));
    }
  }

  /* Set Key State */  
  for(keyScanNo = 0; keyScanNo < NB_KEYS; keyScanNo++)
  {
    uint8_t keyPressState;
    keyPressState = (uint8_t)((keyPressBit[keyScanNo >> 3] & (1 << (keyScanNo & 0x7))) ? CLOSED : OPEN);

    /* Check if the key state is changed */
    if(keyPressState != KeyPress[keyScanNo])
    {
      /* Check if the debounce verification is done */
      if(KeyDebounce[keyScanNo] == TRUE)
      {
        /* wait for debounce verification */
        if((bspSysTime - KeyBkpTime[keyScanNo]) >= DebounceTime)
        {
          /* change the key press state */
          KeyPress[keyScanNo] = (uint8_t)(
            KeyPress[keyScanNo] == OPEN ? CLOSED : OPEN);
          KeyDebounce[keyScanNo] = FALSE;
        }
      }
      else
      {
        /* Pre debounce check
           Mark the bsp timer for debounce check,
           set the debounce check start flag as true
         */
        KeyBkpTime[keyScanNo] = bspSysTime;
        KeyDebounce[keyScanNo] = TRUE;
      }
    }
		else
		{
			KeyDebounce[keyScanNo] = FALSE;
		}
    SetKeyState(keyScanNo, KeyPress[keyScanNo]);
  }
}

/**
  * @brief  Checks if a key is pressed
  *         Checks the key buffer status for KEY_STATE_PRESSED & KEY_STATE_HOLD
  * @param  keyNo - The Key whose status needs to be checked
  * @retval TRUE if key is pressed, FALSE if key is released
  */
uint8_t KPD_IsPressed(uint8_t keyNo)
{

  if(KeyState[keyNo] == KEY_STATE_PRESSED)
  {
    return KPD_KEY_PRESSED;
  }
  else
  {
    return KPD_KEY_RELEASED;
  }
}

/**
  * @brief  Sets the key debounce time
  *         Sets the key debounce time in milliseconds
  * @param  debounce - key debounce value in milliseconds
  * @retval None
  */
void KPD_SetDebounceTime(uint8_t debounce)
{
  (debounce < 1) ? (DebounceTime = 1) : (DebounceTime = debounce);
}

/**
  * @brief  Gets the key debounce time in milliseconds
  * @param  None
  * @retval Returns set debounce time in milliseconds
  */
uint8_t KPD_GetDebounceTime(void)
{
  return DebounceTime;
}

/**
  * @brief  Installs a callback for a keypad event change
  * @param  cb - pointer to the callback function
  * @retval None
  */
void KPD_AddEventListener(void (* cb)(uint8_t, uint8_t))
{
  KeypadCB = cb;
}
/***********************END OF FILE************************/