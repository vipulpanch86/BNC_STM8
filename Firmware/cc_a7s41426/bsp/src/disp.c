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
  uint16_t SixteenSeg[DISP_UPPER_MAX_NB];
  uint16_t SevenSeg[DISP_LOWER_MAX_NB];
  uint16_t led;
  uint16_t turret[DISP_TURRET_MAX_NB];
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

/* Segment data for Sixteen Segment Display */
#define S16_A1 0b0000000000000001
#define S16_A2 0b0000000000000010
#define S16_B  0b0000000000000100
#define S16_C  0b0000000000001000
#define S16_D1 0b0000000000010000
#define S16_D2 0b0000000000100000
#define S16_E  0b0000000001000000
#define S16_F  0b0000000010000000
#define S16_G1 0b0000000100000000
#define S16_G2 0b0000001000000000
#define S16_H  0b0000010000000000
#define S16_I  0b0000100000000000
#define S16_J  0b0001000000000000
#define S16_K  0b0010000000000000
#define S16_L  0b0100000000000000
#define S16_M  0b1000000000000000

/* Font Table of 16 Segment Display for Numbers */
static const uint16_t SEG_16N[] =
{
  /* 0 */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_E + S16_F,
  /* 1 */ S16_B + S16_C,
  /* 2 */ S16_A1 + S16_A2 + S16_B + S16_G1 + S16_G2 + S16_E + S16_D1 + S16_D2,
  /* 3 */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_G1 + S16_G2,
  /* 4 */ S16_B + S16_C + S16_G1 + S16_G2 + S16_F,
  /* 5 */ S16_A1 + S16_A2 + S16_C + S16_D1 + S16_D2 + S16_F + S16_G1 + S16_G2,
  /* 6 */ S16_A1 + S16_A2 + S16_C + S16_D1 + S16_D2 + S16_E + S16_F + S16_G1 + S16_G2,
  /* 7 */ S16_A1 + S16_A2 + S16_B + S16_C,
  /* 8 */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_E + S16_F + S16_G1 + S16_G2,
  /* 9 */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_F + S16_G1 + S16_G2
};

/* Font Table of 16 Segment Display for alphabets */
static const uint16_t SEG_16A[] =
{
  /* A */ S16_A1 + S16_A2 + S16_B + S16_C + S16_E + S16_F + S16_G1 + S16_G2,
  /* B */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_G2 + S16_I + S16_L,
  /* C */ S16_A1 + S16_A2 + S16_D1 + S16_D2 + S16_E + S16_F,
  /* D */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_I + S16_L,
  /* E */ S16_A1 + S16_A2 + S16_D1 + S16_D2 + S16_E + S16_F + S16_G1 + S16_G2,
  /* F */ S16_A1 + S16_A2 + S16_E + S16_F + S16_G1,
  /* G */ S16_A1 + S16_A2 + S16_C + S16_D1 + S16_D2 + S16_E + S16_F + S16_G2,
  /* H */ S16_B + S16_C + S16_E + S16_F + S16_G1 + S16_G2,
  /* I */ S16_A1 + S16_A2 + S16_I + S16_L + S16_D1 + S16_D2,
  /* J */ S16_B + S16_C + S16_D1 + S16_D2 + S16_E,
  /* K */ S16_E + S16_F + S16_G1 + S16_J + S16_K,
  /* L */ S16_D1 + S16_D2 + S16_E + S16_F,
  /* M */ S16_B + S16_C + S16_E + S16_F + S16_H + S16_J,
  /* N */ S16_B + S16_C + S16_E + S16_F + S16_H + S16_K,
  /* O */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_E + S16_F,
  /* P */ S16_A1 + S16_A2 + S16_B + S16_E + S16_F + S16_G1 + S16_G2,
  /* Q */ S16_A1 + S16_A2 + S16_B + S16_C + S16_D1 + S16_D2 + S16_E + S16_F + S16_K,
  /* R */ S16_A1 + S16_A2 + S16_B + S16_E + S16_F + S16_G1 + S16_G2 + S16_K,
  /* S */ S16_A1 + S16_A2 + S16_C + S16_D1 + S16_D2 + S16_F + S16_G1 + S16_G2,
  /* T */ S16_A1 + S16_A2 + S16_I + S16_L,
  /* U */ S16_B + S16_C + S16_D1 + S16_D2 + S16_E + S16_F,
  /* V */ S16_E + S16_F + S16_J + S16_M,
  /* W */ S16_B + S16_C + S16_E + S16_F + S16_K + S16_M,
  /* X */ S16_H + S16_J + S16_K + S16_M,
  /* Y */ S16_H + S16_J + S16_L,
  /* Z */ S16_A1 + S16_A2 + S16_D1 + S16_D2 + S16_J + S16_M
};

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

static const uint8_t MS_PIN[DISP_MAX_NB_SEL][4] = 
{
  DISP_MS0_PIN * 1, DISP_MS1_PIN * 0, DISP_MS2_PIN * 0, DISP_MS3_PIN * 1,
  DISP_MS0_PIN * 0, DISP_MS1_PIN * 1, DISP_MS2_PIN * 0, DISP_MS3_PIN * 1,
  DISP_MS0_PIN * 1, DISP_MS1_PIN * 1, DISP_MS2_PIN * 0, DISP_MS3_PIN * 1,
  DISP_MS0_PIN * 0, DISP_MS1_PIN * 0, DISP_MS2_PIN * 1, DISP_MS3_PIN * 1,
  DISP_MS0_PIN * 1, DISP_MS1_PIN * 0, DISP_MS2_PIN * 1, DISP_MS3_PIN * 1,
  DISP_MS0_PIN * 0, DISP_MS1_PIN * 1, DISP_MS2_PIN * 1, DISP_MS3_PIN * 1,
  DISP_MS0_PIN * 1, DISP_MS1_PIN * 1, DISP_MS2_PIN * 1, DISP_MS3_PIN * 1,
  DISP_MS0_PIN * 1, DISP_MS1_PIN * 0, DISP_MS2_PIN * 0, DISP_MS3_PIN * 0,
  DISP_MS0_PIN * 0, DISP_MS1_PIN * 1, DISP_MS2_PIN * 0, DISP_MS3_PIN * 0,
  DISP_MS0_PIN * 1, DISP_MS1_PIN * 1, DISP_MS2_PIN * 0, DISP_MS3_PIN * 0,
  DISP_MS0_PIN * 0, DISP_MS1_PIN * 0, DISP_MS2_PIN * 1, DISP_MS3_PIN * 0,
  DISP_MS0_PIN * 1, DISP_MS1_PIN * 0, DISP_MS2_PIN * 1, DISP_MS3_PIN * 0
};

static const uint8_t TURR_PIN[DISP_TURRET_MAX_NB][4] = 
{
  DISP_MS2_PIN * 1, DISP_MS3_PIN * 0, DISP_LE1_PIN * 0, DISP_LE0_PIN * 0,
  DISP_MS2_PIN * 0, DISP_MS3_PIN * 1, DISP_LE1_PIN * 0, DISP_LE0_PIN * 0,
  DISP_MS2_PIN * 0, DISP_MS3_PIN * 0, DISP_LE1_PIN * 1, DISP_LE0_PIN * 0,
  DISP_MS2_PIN * 0, DISP_MS3_PIN * 0, DISP_LE1_PIN * 0, DISP_LE0_PIN * 1,
};
/* Private variables ---------------------------------------------------------*/
static DisplayType_t DisplayData;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Calculates 16 segment data for a character
  * @param  ch - Display to which the data needs to written
  * @retval 16 bit segment data
  */
@inline static uint16_t S16_CalcSegments(uint8_t ch)
{
  if((ch >= 'A') && (ch <= 'Z'))
  {
    return SEG_16A[ch - 'A'];  /* A-Z */
  }
  else if((ch >= 'a') && (ch <= 'z'))
  {
    return SEG_16A[ch - 'a'];  /* a-z */
  }
  else if((ch >= '0') && (ch <= '9'))
  {
    return SEG_16N[ch - '0'];  /* 0-9 */
  }
  else if(ch == '-')
  {
    return S16_G1 + S16_G2;
  }
  else if(ch == '+')
  {
    return S16_G1 + S16_G2 + S16_I + S16_L;
  }
  else if(ch == '<')
  {
    return S16_J + S16_K;
  }
  else if(ch == '>')
  {
    return S16_H + S16_M;
  }
  else if(ch == '/')
  {
    return S16_J + S16_M;
  }
  else
  {
    return 0;  /* blank */
  }
}

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
@inline static void WriteToDisplay(uint8_t dispNo, volatile uint16_t data)
{
  volatile uint8_t data8bit = 0;
  
  /* Turret Disable */
  TUR_EN_PORT->ODR |= (uint8_t)TUR_EN_PIN;

  /* Output Disable */
  DISP_LOE_PORT->ODR |= (uint8_t)DISP_LOE_PIN;
  
  if(dispNo < DISP_MAX_NB_SEL)
  {
    /* Write Low Byte on Port */
    data8bit = (uint8_t)((data >> 0) & 0xFF);
    DISP_DB_PORT->ODR = (uint8_t)data8bit;

    /* Latch Low byte */
    DISP_LE0_PORT->ODR |= (uint8_t)DISP_LE0_PIN;
    DISP_LE0_PORT->ODR &= (uint8_t)~DISP_LE0_PIN;
    
    /* Write High Byte on Port */
    data8bit = (uint8_t)((data >> 8) & 0xFF);
    DISP_DB_PORT->ODR = (uint8_t)data8bit;

    /* Latch High byte */
    DISP_LE1_PORT->ODR |= (uint8_t)DISP_LE1_PIN;
    DISP_LE1_PORT->ODR &= (uint8_t)~DISP_LE1_PIN;

    /* Select the Corresponding Display */
    DISP_MS3_PORT->ODR &= (uint8_t)~DISP_MS3_PIN;
    DISP_MS3_PORT->ODR |= (uint8_t)MS_PIN[dispNo][3];
    
    DISP_MS2_PORT->ODR &= (uint8_t)~DISP_MS2_PIN;
    DISP_MS2_PORT->ODR |= (uint8_t)MS_PIN[dispNo][2];
    
    DISP_MS1_PORT->ODR &= (uint8_t)~DISP_MS1_PIN;
    DISP_MS1_PORT->ODR |= (uint8_t)MS_PIN[dispNo][1];
    
    DISP_MS0_PORT->ODR &= (uint8_t)~DISP_MS0_PIN;
    DISP_MS0_PORT->ODR |= (uint8_t)MS_PIN[dispNo][0];

    /* Output Enable*/
    DISP_LOE_PORT->ODR &= (uint8_t)~DISP_LOE_PIN;
  }
  else if(dispNo < (DISP_MAX_NB_SEL + DISP_TURRET_MAX_NB))
  {
  
    dispNo -= DISP_MAX_NB_SEL;
  
    /* Select the Corresponding Display */
    DISP_MS2_PORT->ODR |= (uint8_t)DISP_MS2_PIN;
    DISP_MS3_PORT->ODR |= (uint8_t)DISP_MS3_PIN;
    DISP_LE1_PORT->ODR |= (uint8_t)DISP_LE1_PIN;
    DISP_LE0_PORT->ODR |= (uint8_t)DISP_LE0_PIN;
    
    /* Write Byte on Port */
    data8bit = (uint8_t)((data >> 0) & 0xFF);
    DISP_DB_PORT->ODR = (uint8_t)data8bit;

    DISP_MS2_PORT->ODR &= (uint8_t)~TURR_PIN[dispNo][0];
    DISP_MS3_PORT->ODR &= (uint8_t)~TURR_PIN[dispNo][1];
    DISP_LE1_PORT->ODR &= (uint8_t)~TURR_PIN[dispNo][2];
    DISP_LE0_PORT->ODR &= (uint8_t)~TURR_PIN[dispNo][3];


    TUR_EN_PORT->ODR &= (uint8_t)~TUR_EN_PIN;
  }
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
    DisplayData.SevenSeg[count] = 0x00;
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
      DisplayData.SevenSeg[startDispNo + count] = S7_CalcSegments(pStr[count]);
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
    DisplayData.SixteenSeg[count] = 0;
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
    DisplayData.SixteenSeg[dispNo] = S16_CalcSegments(chr);
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
      DisplayData.SixteenSeg[startDispNo + count] = S16_CalcSegments(pStr[count]);
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
  uint8_t count;

  for(count = 0; count < DISP_TURRET_MAX_NB; count++)
  {
    DisplayData.turret[count] = 0;
  }
}

/**
  * @brief  Displays a String on the Turret display
  * @param  pStr - Pointer to the String to be displayed
  *         startDispNo - Start Display No.
  * @retval None
  */
void DISP_TurrPutStr(char *pStr, uint8_t startDispNo)
{
  if(startDispNo < DISP_UPPER_MAX_NB)
  {
    uint8_t count = 0;
    uint8_t strlength = (uint8_t)strlen(pStr);
    uint8_t maxChar = (uint8_t)(((DISP_TURRET_MAX_NB - startDispNo) < strlength) ?
                                (DISP_TURRET_MAX_NB - startDispNo) :
                                (strlength));

    for(count = 0; count < maxChar; count++)
    {
      DisplayData.turret[startDispNo + count] = S7_CalcSegments(pStr[count]);
    }
  }
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
    DisplayData.led &= (uint16_t)(~(1 << ledNo));
    DisplayData.led |= (uint16_t)((enable & 0x01) << ledNo);
  }
}

/**
  * @brief  Writes a RAW 16-bit data
  * @param  data - data to be displayed
  *         dispNo - One of the n Displays
  * @retval None
  */
void DISP_WriteRAW(uint8_t dispNo, uint16_t data)
{
  uint16_t *pDisplayData = (uint16_t *)&DisplayData;

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
}

/**
  * @brief  Displays all Segments & led's OFF
  * @param  None
  * @retval None
  */
void DISP_ClearAll(void)
{
  memset(&DisplayData, 0x00, sizeof(DisplayType_t));
}

/**
  * @brief  Enables a single displays and puts data on it
  * @param  None
  * @retval None
  */
void DISP_Exec(void)
{
  static uint8_t DispNo = 0;
  uint16_t *pDisplayData = (uint16_t *)&DisplayData;

  WriteToDisplay(DispNo, pDisplayData[DispNo]);
  DispNo++;
  DispNo %= (DISP_MAX_NB_SEL + DISP_TURRET_MAX_NB);
}
/***********************END OF FILE************************/
