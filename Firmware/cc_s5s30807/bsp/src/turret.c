/**
  ******************************************************************************
  * @file    turret.c
  * @author  Vipul Panchal
  * @brief   This file contains the parser for serial turret.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TURR_REFERSH_MS     25

#define TURR_START          0xAA

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t  TurretData[TURR_MAX_PKT_LEN];
uint8_t  TurretTxPointer = 0;
uint8_t  TurretExecute = FALSE;
uint16_t TurretValue = 0xFFFF;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  clears the turret display
  * @param  None
  * @retval None
  */
void TURR_Clear(void)
{
  if(TurretValue != 0xFFFF)
  {
    TurretValue = 0xFFFF;
    TurretExecute = TRUE;
    /* Set to Blank Value  */
    TurretData[0] = TURR_START;
    TurretData[1] = 0xAF;
    TurretData[2] = 0xFA;
  }
}

/**
  * @brief  Displays a String on the Turret display
  * @param  pStr - Pointer to the String to be displayed
  *         startDispNo - Seven Segment Start Display No.
  *         nbChar - No. of characters to be displayed
  * @retval None
  */
void TURR_PutVal(uint16_t value)
{
  if(TurretValue != value)
  {
    TurretValue = value;
    TurretExecute = TRUE;
    /* Default start of frame */
    TurretData[0] = TURR_START;
  
    /* Units Place at Lower Nibble */
    TurretData[1] = (uint8_t)(((value / 1) % 10) << 0);
  
    /* Tens place at Higher Nibble*/
    TurretData[1] |= (uint8_t)((value > 9) ? (((value / 10) % 10) << 4) : 0xA0);
  
    /* Hundreds Place at Lower Nibble */
    TurretData[2] = (uint8_t)((value > 99) ? (((value / 100) % 10) << 0) : 0x0A);
  
    /* Thousands place at Higher Nibble*/
    TurretData[2] |= (uint8_t)((value > 999) ? (((value / 1000) % 10) << 4) : 0xF0);
  }
}

/**
  * @brief  Regulary Transmits Data on to Turret Display
  * @param  None
  * @retval None
  */
void TURR_Exec(void)
{
  TurretExecute = FALSE;
    
  TurretTxPointer = 0;
  /* Enable the TURR_COM Transmit interrupt: this interrupt is generated when the 
  TURR_COM transmit data register is empty */  
  UART1_ITConfig(UART1_IT_TXE, ENABLE);
}
/***********************END OF FILE************************/
