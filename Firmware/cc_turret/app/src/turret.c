/**
  ******************************************************************************
  * @file    turret.c
  * @author  Mahajan Electronics Team
  * @version  V1.0.0
  * @date     05-January-2015
  * @brief   This file contains the communication parser for turret.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TURR_MAX_PKT_LEN    3

#define TURR_START          0xAA

#define MSG_WAIT_START      0
#define MSG_IN_PARTIAL      1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ParsePkt.
  *         This function extracts the data values from a Turret packet
  *         and returns the values.
  * @param  pTurrPkt - a memory buffer with the entire Turret packet
  * @retval Extacted Turret Value from packet.
  */
@inline uint16_t ParsePkt (uint8_t * pTurrPkt)
{
  uint8_t nibbleMask = 0;
  uint16_t value = 0;
  
  nibbleMask = (uint8_t)((pTurrPkt[2] & 0xF0) >> 4);
  value = (nibbleMask < 0xA) ? (value + nibbleMask) : (value);
  
  value *= 10;

  nibbleMask = (uint8_t)(pTurrPkt[2] & 0x0F);
  value = (nibbleMask < 0xA) ? (value + nibbleMask) : (value);
  
  value *= 10;

  nibbleMask = (uint8_t)((pTurrPkt[1] & 0xF0) >> 4);
  value = (nibbleMask < 0xA) ? (value + nibbleMask) : (value);

  value *= 10;
  
  nibbleMask = (uint8_t)(pTurrPkt[1] & 0x0F);
  value = (nibbleMask < 0xA) ? (value + nibbleMask) : (value);

  return value; 
}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Turret Byte Received callback.
  *         This routine executes the Parser for Turret communication.
  *         (Called from Uart ISR, When a byte is read)
  * @param  readByte - Read Byte from uart
  * @retval None
  */
void TURR_ByteRxCallBack(uint8_t readByte)
{
  static __IO uint8_t RecvBuff[TURR_MAX_PKT_LEN + 1];
  static __IO uint8_t ReceiveState = MSG_WAIT_START;
  static __IO uint8_t PktLen = 0;

  if(ReceiveState == MSG_WAIT_START) 
  {
    if (readByte == TURR_START)
    { 
      ReceiveState = MSG_IN_PARTIAL;
      RecvBuff[PktLen++] = readByte;
    }
  }
  else
  {
    RecvBuff[PktLen++] = readByte;
    if(PktLen == TURR_MAX_PKT_LEN)
    {
      char dispBuff[DISP_MAX_NB_SEL + 1] = {0};
      uint16_t turrValue = 0;
      
      PktLen = 0;
      ReceiveState = MSG_WAIT_START;
      
      turrValue = ParsePkt(&RecvBuff[0]);
      DISP_Clear();
      if(turrValue < 10000)
      {
        sprintf(&dispBuff[0], "%4u", (uint16_t)turrValue);
        DISP_PutStr(&dispBuff[0], 0);
      }
    }
  }
}


/***********************END OF FILE************************/
