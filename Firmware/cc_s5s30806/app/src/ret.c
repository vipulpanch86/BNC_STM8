/**
  ******************************************************************************
  * @file    ret.c
  * @author  Vipul Panchal
  * @brief   This file contains the retention memory handling function.
  ******************************************************************************
  */

/* Board Files Includes */
#include "bsp.h"

/* Application Includes */
#include "ret.h"

/* Private define ------------------------------------------------------------*/
#define RET_MEM_SIZE       64
#define DATA_START_ADDR    0x004080

/* Private typedef -----------------------------------------------------------*/
/* Private Constant ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* RAM Memory in synchronization with Retentive Memory */
static uint32_t RetentionMem[RET_MEM_SIZE / 4];
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
}

/**
  * @brief  Writes a 16 bit Register to Retentive Memory
  * @param  idx  - Retentive Memory Index
  * @param  pData - Input data pointer
  * @retval None
  */
void RET_WriteMem(uint8_t idx, uint32_t *pData)
{
  uint32_t * pFlashPtr = (uint32_t *)DATA_START_ADDR;
  RetentionMem[idx]  = *pData;
  /* Unlock Data memory */
  FLASH_Unlock(FLASH_MEMTYPE_DATA);

  /* Program word at address */
  FLASH_ProgramWord((uint32_t)&pFlashPtr[idx], *pData);
  
  FLASH_Lock(FLASH_MEMTYPE_DATA);
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
  * @brief  Updates the Retention Memory to Flash
  * @param  None
  * @retval None
  */
void RET_UpdateFlash(void)
{
  BSP_WriteToFlash(RET_MEM_SIZE, (uint8_t *)&RetentionMem[0]);
}
/*********************************END OF FILE**********************************/
