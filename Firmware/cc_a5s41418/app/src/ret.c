/**
  ******************************************************************************
  * @file    ret.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    28-August-2015
  * @brief   This file contains the retention memory handling function.
  ******************************************************************************
  */

/* Board Files Includes */
#include "bsp.h"

/* Application Includes */
#include "ret.h"

/* Private define ------------------------------------------------------------*/
#define RET_MEM_SIZE       64

/* Private typedef -----------------------------------------------------------*/
/* Private Constant ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* RAM Memory in synchronization with Retentive Memory */
static uint32_t RetentionMem[RET_MEM_SIZE / 4];
/* Flag to Indicate to the Exec process to update the Retentive memory */
static uint8_t UpdateRet = FALSE, EnableRet = FALSE;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Reads the Retentive Memory and stores in the RAM
  * @param  None
  * @retval None
  */
void RET_Init(void)
{
  BSP_ReadFromFlash(RET_MEM_SIZE, (uint8_t *)&RetentionMem[0]);
  UpdateRet = FALSE;
}

/**
  * @brief  Clears the Retentive Memory and stores in the RAM
  * @param  None
  * @retval None
  */
void RET_ClearMemory(void)
{
  uint16_t cnt;

  for(cnt = 0; cnt < (RET_MEM_SIZE / 4); cnt++)
  {
    RetentionMem[cnt] = 0;
  }

  UpdateRet = TRUE;
}

/**
  * @brief  Writes a 16 bit Register to Retentive Memory
  * @param  idx  - Retentive Memory Index
  * @param  pData - Input data pointer
  * @retval None
  */
void RET_WriteMem(uint8_t idx, uint32_t *pData)
{
  RetentionMem[idx]  = *pData;
  UpdateRet = TRUE;
}

/**
  * @brief  Reads a 16 bit Register from Retentive Memory
  * @param  idx  - Retentive Memory Index
  * @param  pData - Input data pointer
  * @retval None
  */
void RET_ReadMem(uint8_t idx, uint32_t *pData)
{
  *pData = RetentionMem[idx];
}

/**
  * @brief  Enable / Diable Writing to Retentive Memory
  * @param  enable - True / False
  * @retval None
  */
void RET_WriteRetEnbale(uint8_t enable)
{
  EnableRet = (uint8_t)(enable ? TRUE : FALSE);
}

/**
  * @brief  Updates the Retention Memory to Flash
  * @param  None
  * @retval None
  */
void RET_UpdateFlash(void)
{
  BSP_WriteToFlash(RET_MEM_SIZE, (uint8_t *)&RetentionMem[0]);
}

/**
  * @brief  Executes Retention memory update
  * @param  none
  * @retval None
  */
void RET_Exec(void)
{
  if((UpdateRet == TRUE) && (EnableRet == TRUE))
  {
    UpdateRet = FALSE;
    BSP_WriteToFlash(RET_MEM_SIZE, (uint8_t *)&RetentionMem[0]);
  }
}
/*********************************END OF FILE**********************************/
