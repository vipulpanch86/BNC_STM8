/**
  ******************************************************************************
  * @file    main.c
  * @author  Mahajan Electronics Team
  * @version  V1.0.0
  * @date     11-August-2015
  * @brief   This file contains the main function for Currency counting 
  *          application.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
#define DISP_EXEC_MS (1)

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  /* BSP Initialization -----------------------------------------*/
  BSP_Init();
  DISP_Init();
  while(1)
  {
    static uint32_t BkupDispExecTime = 0;
    
    uint32_t sysTime = BSP_GetSysTime();
    
    if((sysTime - BkupDispExecTime) >= DISP_EXEC_MS)
    {
      BkupDispExecTime = sysTime;
      DISP_Exec();
    }
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while(1)
  {
  }
}
#endif
/***********************END OF FILE************************/
