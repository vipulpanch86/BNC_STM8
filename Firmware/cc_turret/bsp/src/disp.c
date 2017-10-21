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
/* Private constants----------------------------------------------------------*/

/* Segment data for Seven Segment Display */
#define S7_A 0b01000000
#define S7_B 0b00000001
#define S7_C 0b00000100
#define S7_D 0b00001000
#define S7_E 0b00010000
#define S7_F 0b00100000
#define S7_G 0b00000010

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

/* List of Display Enable GPIO Port Bits */
static GPIO_TypeDef *DISP_EN_PORT[DISP_MAX_NB_SEL] =
{
  DISP_EN0_PORT,
  DISP_EN1_PORT,
  DISP_EN2_PORT,
  DISP_EN3_PORT
};

/* List of Keypad Scan Lines GPIO Port Pins */
static const uint8_t DISP_EN_PIN[DISP_MAX_NB_SEL] =
{
  DISP_EN0_PIN,
  DISP_EN1_PIN,
  DISP_EN2_PIN,
  DISP_EN3_PIN
};

/* Private variables ---------------------------------------------------------*/
static uint8_t DisplayData[DISP_MAX_NB_SEL];

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
  DISP_EN0_PORT->ODR |= (uint8_t)DISP_EN0_PIN;
  DISP_EN1_PORT->ODR |= (uint8_t)DISP_EN1_PIN;
  DISP_EN2_PORT->ODR |= (uint8_t)DISP_EN2_PIN;
  DISP_EN3_PORT->ODR |= (uint8_t)DISP_EN3_PIN;

  /* Write Byte on Port */
  DISP_DB_PORT->ODR = (uint8_t)data;

  DISP_EN_PORT[dispNo]->ODR &= (uint8_t)~DISP_EN_PIN[dispNo];

}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Initialzation Function for Display
  * @param  None
  * @retval None
  */
void DISP_Init(void)
{
  memset(&DisplayData, 0x00, DISP_MAX_NB_SEL);
}

/**
  * @brief  Enables Display
  * @param  None
  * @retval None
  */
void DISP_Enable(void)
{
  GPIO_WriteLow(DISP_OEN_PORT, DISP_OEN_PIN);
}

/**
  * @brief  Disables Display
  * @param  None
  * @retval None
  */
void DISP_Disable(void)
{
  GPIO_WriteHigh(DISP_OEN_PORT, DISP_OEN_PIN);
}

/**
  * @brief  clears the display
  * @param  None
  * @retval None
  */
void DISP_Clear(void)
{
  uint8_t count;
  for(count = 0; count < DISP_MAX_NB_SEL; count++)
  {
    DisplayData[count] = 0x00;
  }
}

/**
  * @brief  Displays a String on the display
  * @param  pStr - Pointer to the String to be displayed
  *         startDispNo - Start Display No.
  * @retval None
  */
void DISP_PutStr(char *pStr, uint8_t startDispNo)
{
  if(startDispNo < DISP_MAX_NB_SEL)
  {
    uint8_t count = 0;
    uint8_t strlength = (uint8_t)strlen(pStr);
    uint8_t maxChar = (uint8_t)(((DISP_MAX_NB_SEL - startDispNo) < strlength) ?
                                (DISP_MAX_NB_SEL - startDispNo) :
                                (strlength));

    for(count = 0; count < maxChar; count++)
    {
      DisplayData[startDispNo + count] = S7_CalcSegments(pStr[count]);
    }
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
  if(dispNo < DISP_MAX_NB_SEL)
  {
    DisplayData[dispNo] = data;
  }
}

/**
  * @brief  Enables a single displays and puts data on it
  * @param  None
  * @retval None
  */
void DISP_Exec(void)
{
  static uint8_t DispNo = 0;
  WriteToDisplay(DispNo, DisplayData[DispNo]);
  DispNo++;
  DispNo %= DISP_MAX_NB_SEL;
}
/***********************END OF FILE************************/
