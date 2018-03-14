/**
  ******************************************************************************
  * @file    disp.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    11-August-2015
  * @brief   This file contains display related functions
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
/* Single Refresh Rate in Millisec */
#define DISP_REFERSH_MS      (1)

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint8_t SevenSeg[DISP_UPPER_MAX_NB + DISP_LOWER_MAX_NB];
  uint8_t led;
} DisplayType_t;

/* Private constants----------------------------------------------------------*/

/* Segment data for Seven Segment Display */
#define S7_A 0b00000001
#define S7_B 0b00000010
#define S7_C 0b00000100
#define S7_D 0b00001000
#define S7_E 0b00010000
#define S7_F 0b00100000
#define S7_G 0b01000000

/* Font Table of 7 Segment Display for Numbers */
static const char SEG_7N[] =
{
  /* 0 */ S7_A + S7_B + S7_C + S7_D + S7_E + S7_F,
  /* 1 */ S7_B + S7_C,
  /* 2 */ S7_A + S7_B + S7_D + S7_E + S7_G,
  /* 3 */ S7_A + S7_B + S7_C + S7_D + S7_G,
  /* 4 */ S7_B + S7_C + S7_F + S7_G,
  /* 5 */ S7_A + S7_C + S7_D + S7_F + S7_G,
  /* 6 */ S7_A + S7_C + S7_D + S7_E + S7_F + S7_G,
  /* 7 */ S7_A + S7_B + S7_C,
  /* 8 */ S7_A + S7_B + S7_C + S7_D + S7_E + S7_F + S7_G,
  /* 9 */ S7_A + S7_B + S7_C + S7_D + S7_F + S7_G,
};

/* Font Table of 7 Segment Display for Alphabets */
static const char SEG_7A[] =
{
  /* A */ S7_A + S7_B + S7_C + S7_E + S7_F + S7_G,
  /* B */ S7_C + S7_D + S7_E + S7_F + S7_G,
  /* C */ S7_A + S7_D + S7_E + S7_F,
  /* D */ S7_B + S7_C + S7_D + S7_E + S7_G,
  /* E */ S7_A + S7_D + S7_E + S7_F + S7_G,
  /* F */ S7_A + S7_E + S7_F + S7_G,
  /* G */ S7_A + S7_C + S7_D + S7_E + S7_F,
  /* H */ S7_B + S7_C + S7_E + S7_F + S7_G,
  /* I */ S7_B + S7_C,
  /* J */ S7_B + S7_C + S7_D + S7_E,
  /* K */ S7_B + S7_E + S7_F + S7_G,
  /* L */ S7_D + S7_E + S7_F,
  /* M */ S7_A + S7_C + S7_E + S7_G,
  /* N */ S7_C + S7_E + S7_G,
  /* O */ S7_A + S7_B + S7_C + S7_D + S7_E + S7_F,
  /* P */ S7_A + S7_B + S7_E + S7_F + S7_G,
  /* Q */ S7_A + S7_B + S7_C + S7_F + S7_G,
  /* R */ S7_E + S7_G,
  /* S */ S7_A + S7_C + S7_D + S7_F + S7_G,
  /* T */ S7_D + S7_E + S7_F + S7_G,
  /* U */ S7_B + S7_C + S7_D + S7_E + S7_F,
  /* V */ S7_C + S7_D + S7_E,
  /* W */ S7_A + S7_D + S7_G,
  /* X */ S7_A + S7_D + S7_G,
  /* Y */ S7_B + S7_C + S7_D + S7_F + S7_G,
  /* Z */ S7_D + S7_G
};

static const uint8_t MS_PIN[DISP_MAX_NB_SEL][7] = 
{
  MUX0_MSA_PIN * 0, MUX0_MSB_PIN * 1, MUX0_MSC_PIN * 0, DISP_EN2_PIN * 0, DISP_EN3_PIN * 0, DISP_EN4_PIN * 0, DISP_EN5_PIN * 0,
  MUX0_MSA_PIN * 0, MUX0_MSB_PIN * 0, MUX0_MSC_PIN * 0, DISP_EN2_PIN * 1, DISP_EN3_PIN * 0, DISP_EN4_PIN * 0, DISP_EN5_PIN * 0,
  MUX0_MSA_PIN * 0, MUX0_MSB_PIN * 0, MUX0_MSC_PIN * 0, DISP_EN2_PIN * 0, DISP_EN3_PIN * 1, DISP_EN4_PIN * 0, DISP_EN5_PIN * 0,
  MUX0_MSA_PIN * 0, MUX0_MSB_PIN * 0, MUX0_MSC_PIN * 0, DISP_EN2_PIN * 0, DISP_EN3_PIN * 0, DISP_EN4_PIN * 1, DISP_EN5_PIN * 0,
  MUX0_MSA_PIN * 0, MUX0_MSB_PIN * 0, MUX0_MSC_PIN * 0, DISP_EN2_PIN * 0, DISP_EN3_PIN * 0, DISP_EN4_PIN * 0, DISP_EN5_PIN * 1,
  MUX0_MSA_PIN * 1, MUX0_MSB_PIN * 1, MUX0_MSC_PIN * 0, DISP_EN2_PIN * 0, DISP_EN3_PIN * 0, DISP_EN4_PIN * 0, DISP_EN5_PIN * 0,
  MUX0_MSA_PIN * 0, MUX0_MSB_PIN * 0, MUX0_MSC_PIN * 1, DISP_EN2_PIN * 0, DISP_EN3_PIN * 0, DISP_EN4_PIN * 0, DISP_EN5_PIN * 0,
  MUX0_MSA_PIN * 1, MUX0_MSB_PIN * 0, MUX0_MSC_PIN * 1, DISP_EN2_PIN * 0, DISP_EN3_PIN * 0, DISP_EN4_PIN * 0, DISP_EN5_PIN * 0,
  MUX0_MSA_PIN * 0, MUX0_MSB_PIN * 1, MUX0_MSC_PIN * 1, DISP_EN2_PIN * 0, DISP_EN3_PIN * 0, DISP_EN4_PIN * 0, DISP_EN5_PIN * 0
};
/* Private variables ---------------------------------------------------------*/
static DisplayType_t DisplayData;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Calculates 7 segment data for a character
  * @param  ch - Display to which the data needs to written
  * @retval 8 bit segment data
  */
@inline static uint8_t S7_CalcSegments(uint8_t ch)
{
  if((ch >= 'A') && (ch <= 'Z'))
  {
    return SEG_7A[ch - 'A'];  /* A-Z */
  }
  else if((ch >= 'a') && (ch <= 'z'))
  {
    return SEG_7A[ch - 'a'];  /* a-z */
  }
  else if((ch >= '0') && (ch <= '9'))
  {
    return SEG_7N[ch - '0'];  /* 0-9 */
  }
  else if(ch == '-')
  {
    return S7_G;
  }
  else if(ch == '_')
  {
    return S7_D;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Writes the actual data to display
  * @param  dispNo - Display to which the data needs to written
  *         data - Data to be written to display
  * @retval None
  */
@inline static void WriteToDisplay(uint8_t dispNo, volatile uint8_t data)
{
  /* Deselect All Display */
  MUX0_MSA_PORT->ODR &= (uint8_t)~MUX0_MSA_PIN;
  MUX0_MSB_PORT->ODR &= (uint8_t)~MUX0_MSB_PIN;
  MUX0_MSC_PORT->ODR &= (uint8_t)~MUX0_MSC_PIN;
  DISP_EN2_PORT->ODR |= (uint8_t)DISP_EN2_PIN;
  DISP_EN3_PORT->ODR |= (uint8_t)DISP_EN3_PIN;
  DISP_EN4_PORT->ODR |= (uint8_t)DISP_EN4_PIN;
  DISP_EN5_PORT->ODR |= (uint8_t)DISP_EN5_PIN; 

  /* Write Byte on Port */
  DISP_DB_PORT->ODR = (uint8_t)data;

  MUX0_MSA_PORT->ODR |= (uint8_t)MS_PIN[dispNo][0];
  MUX0_MSB_PORT->ODR |= (uint8_t)MS_PIN[dispNo][1];
  MUX0_MSC_PORT->ODR |= (uint8_t)MS_PIN[dispNo][2];
  DISP_EN2_PORT->ODR &= (uint8_t)~MS_PIN[dispNo][3];
  DISP_EN3_PORT->ODR &= (uint8_t)~MS_PIN[dispNo][4];
  DISP_EN4_PORT->ODR &= (uint8_t)~MS_PIN[dispNo][5];
  DISP_EN5_PORT->ODR &= (uint8_t)~MS_PIN[dispNo][6];

}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Initialzation Function for Display
  * @param  None
  * @retval None
  */
void DISP_Init(void)
{
  memset(&DisplayData, 0x00, sizeof(DisplayType_t));
}

/**
  * @brief  clears the Lower display
  * @param  None
  * @retval None
  */
void DISP_LowerClear(void)
{
  uint8_t count;

  for(count = 0; count < DISP_LOWER_MAX_NB; count++)
  {
    DisplayData.SevenSeg[DISP_LOWER_START_NB + count] = 0;
  }
}

/**
  * @brief  Displays a String on the Lower display
  * @param  pStr - Pointer to the String to be displayed
  *         startDispNo - Start Display No.
  * @retval None
  */
void DISP_LowerPutStr(char *pStr, uint8_t startDispNo)
{
  if(startDispNo < DISP_LOWER_MAX_NB)
  {
    uint8_t count = 0;
    uint8_t strlength = (uint8_t)strlen(pStr);
    uint8_t maxChar = (uint8_t)(((DISP_LOWER_MAX_NB - startDispNo) < strlength) ?
                                (DISP_LOWER_MAX_NB - startDispNo) :
                                (strlength));

    for(count = 0; count < maxChar; count++)
    {
      DisplayData.SevenSeg[DISP_LOWER_START_NB + startDispNo + count] =
        S7_CalcSegments(pStr[count]);
    }
  }
}

/**
  * @brief  clears the upper display
  * @param  None
  * @retval None
  */
void DISP_UpperClear(void)
{
  uint8_t count;

  for(count = 0; count < DISP_UPPER_MAX_NB; count++)
  {
    DisplayData.SevenSeg[DISP_UPPER_START_NB + count] = 0;
  }
}


/**
  * @brief  Displays a Character on the Upper display
  * @param  chr - Character to be displayed
  *         dispNo - Display No. on which character to be displayed
  * @retval None
  */
void DISP_UpperPutChar(char chr, uint8_t dispNo)
{
 if(dispNo < DISP_UPPER_MAX_NB)
  {
    DisplayData.SevenSeg[DISP_UPPER_START_NB + dispNo] = S7_CalcSegments(chr);
  }
}

/**
  * @brief  Displays a String on the Upper display
  * @param  pStr - Pointer to the String to be displayed
  *         startDispNo - Start Display No.
  * @retval None
  */
void DISP_UpperPutStr(char *pStr, uint8_t startDispNo)
{
  if(startDispNo < DISP_UPPER_MAX_NB)
  {
    uint8_t count = 0;
    uint8_t strlength = (uint8_t)strlen(pStr);
    uint8_t maxChar = (uint8_t)(((DISP_UPPER_MAX_NB - startDispNo) < strlength) ?
                                (DISP_UPPER_MAX_NB - startDispNo) :
                                (strlength));

    for(count = 0; count < maxChar; count++)
    {
      DisplayData.SevenSeg[DISP_UPPER_START_NB + startDispNo + count] =
        S7_CalcSegments(pStr[count]);
    }
  }
}

/**
  * @brief  clears the turret display
  * @param  None
  * @retval None
  */
void DISP_TurrClear(void)
{
  TUR_EN_PORT->ODR |= (uint8_t)TUR_EN_PIN;
}

/**
  * @brief  Displays a String on the Turret display
  * @param  pStr - Pointer to the String to be displayed
  *         startDispNo - Start Display No.
  * @retval None
  */
void DISP_TurrPutStr(char *pStr, uint8_t startDispNo)
{
  TUR_EN_PORT->ODR &= (uint8_t)~TUR_EN_PIN;
}

/**
  * @brief  Turns an LED ON/OFF
  * @param  ledNo - Led No to display
  *         enable - ON /OFF
  * @retval None
  */
void DISP_Led(uint8_t ledNo, uint8_t enable)
{
  if(ledNo < DISP_LED_MAX_NB)
  {
    DisplayData.led &= (uint8_t)(~(1 << ledNo));
    DisplayData.led |= (uint8_t)((enable & 0x01) << ledNo);
  }
}

/**
  * @brief  Writes a RAW 8-bit data
  * @param  data - data to be displayed
  *         dispNo - One of the n Displays
  * @retval None
  */
void DISP_WriteRAW(uint8_t dispNo, uint8_t data)
{
  uint8_t *pDisplayData = (uint8_t *)&DisplayData;

  if(dispNo < DISP_MAX_NB_SEL)
  {
    pDisplayData[dispNo] = data;
  }
}

/**
  * @brief  Displays all Segments & led's ON
  * @param  None
  * @retval None
  */
void DISP_SetAll(void)
{
  memset(&DisplayData, 0xFF, sizeof(DisplayType_t));
  TUR_EN_PORT->ODR &= (uint8_t)~TUR_EN_PIN;
}

/**
  * @brief  Displays all Segments & led's OFF
  * @param  None
  * @retval None
  */
void DISP_ClearAll(void)
{
  memset(&DisplayData, 0x00, sizeof(DisplayType_t));
  TUR_EN_PORT->ODR |= (uint8_t)TUR_EN_PIN;
}

/**
  * @brief  Enables a single displays and puts data on it
  * @param  None
  * @retval None
  */
void DISP_Exec(void)
{
  static uint8_t DispNo = 0;
  uint8_t *pDisplayData = (uint8_t *)&DisplayData;

  WriteToDisplay(DispNo, pDisplayData[DispNo]);
  DispNo++;
  DispNo %= DISP_MAX_NB_SEL;
}
/***********************END OF FILE************************/
