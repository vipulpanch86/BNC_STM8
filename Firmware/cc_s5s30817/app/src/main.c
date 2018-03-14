/**
  ******************************************************************************
  * @file    main.c
  * @author  Vipul Panchal
  * @brief   This file contains the main function for Currency counting
  *          application.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "ui.h"

/* Private typedef -----------------------------------------------------------*/
#define DISP_EXEC_MS (1)
#define KPD_SCAN_MS  (1)
#define BUZZ_EXEC_MS (100)
#define SNR_EXEC_MS  (1)
#define UI_EXEC_MS   (10)

/* Private define ------------------------------------------------------------*/
#ifdef _RAISONANCE_
#define PUTCHAR_PROTOTYPE int putchar (char c)
#define GETCHAR_PROTOTYPE int getchar (void)
#elif defined (_COSMIC_)
#define PUTCHAR_PROTOTYPE char putchar (char c)
#define GETCHAR_PROTOTYPE char getchar (void)
#else /* _IAR_ */
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
#endif /* _RAISONANCE_ */

#define SENSOR_EXEC_WAIT_COUNTING_EN  (0)
#define SENSOR_EXEC_EXECUTE_COUNTING  (1)
#define WAIT_FOR_SENSOR_DISABLE_MS    (50)
  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t  FlagAutoCount = TRUE;
uint8_t  FlagAddCount = 0;
uint8_t  FlagUvDetect = 0;
uint8_t  FlagSensorEn = 0;
uint8_t  CounterMode = COUNT_MODE_C;
uint16_t AmbientUvValue = 0;
uint32_t SensorCounter = 0;

static uint8_t SensorExecState = SENSOR_EXEC_WAIT_COUNTING_EN;
static uint8_t UvDetected = FALSE;
static uint32_t BkupSensorCounter = 0;
static uint8_t WaitLastNoteCount = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Sensor Scan Execution.
  * @param  None
  * @retval None
  */
@inline void SENSOR_Exec(void)
{
  extern __IO uint32_t BspSensorCounter;
  
  if(SensorExecState == SENSOR_EXEC_WAIT_COUNTING_EN)
  {
    
    SensorExecState = (uint8_t)((FlagSensorEn == TRUE)?
                        (SENSOR_EXEC_EXECUTE_COUNTING):
                        (SensorExecState));
    if(FlagSensorEn == TRUE)
    {
      uint32_t stampEnable = 0;
      REG_GetValue(&stampEnable, REG_ID_STAMP_EN_FLAG);
          
      SensorExecState = SENSOR_EXEC_EXECUTE_COUNTING;
      WaitLastNoteCount = WAIT_FOR_SENSOR_DISABLE_MS;
      BspSensorCounter = 0;
      UvDetected = FALSE;
      
      if(stampEnable == FALSE)
      {
        BSP_S_FanEnable(TRUE);
      }
    }
  }
  else
  {
    uint32_t bspSensorCounter = (BspSensorCounter >> 1) + (BspSensorCounter & 0x1);
    
    WaitLastNoteCount = (uint8_t)((WaitLastNoteCount > 0) ? (WaitLastNoteCount - 1) : 0);
    if(bspSensorCounter != BkupSensorCounter)
    {
      UI_MSG_T msg = {0, UIMSG_COUNTER};

      SensorCounter += (bspSensorCounter - BkupSensorCounter);
      BkupSensorCounter = bspSensorCounter;
      
      WaitLastNoteCount = WAIT_FOR_SENSOR_DISABLE_MS;
      UI_PostMessage(&msg);
    }
    /* Execute UV Detection */
    if((FlagUvDetect == TRUE) && (UvDetected == FALSE))
    {
      uint16_t adcValue = BSP_GetADC();
      uint32_t uvThresValue = 0;
      REG_GetValue(&uvThresValue, REG_ID_UV_LVL);
      /* Add the ambient light value to UV Threshold value */
      uvThresValue += AmbientUvValue;
      
      if(adcValue > uvThresValue)
      {
        UI_MSG_T msg = {0, UIMSG_UVDETECT};
        
        UvDetected = TRUE;
  
        /* Post Message to stop Counting */
        UI_PostMessage(&msg);
      }
    }
    
    if((FlagSensorEn == FALSE) && (WaitLastNoteCount == 0))
    {
      uint32_t stampEnable = 0;
      REG_GetValue(&stampEnable, REG_ID_STAMP_EN_FLAG);

      SensorExecState = SENSOR_EXEC_WAIT_COUNTING_EN;
      BkupSensorCounter = 0;
      UvDetected = FALSE;
      
      if(stampEnable == FALSE)
      {
        BSP_S_FanEnable(FALSE);
      }
    }
  }
}



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  uint32_t swVersion = 0;

  /* BSP Initialization -----------------------------------------*/
  BSP_Init();
  /* Power DElay 1.5 Seconds */
  BSP_DelayMs(1500);
  DISP_Init();
  TURR_Clear();

  /* Initialize Keypad */
  KPD_Init(20, NULL);
  KPD_AddEventListener(UI_KeyCallBack);

  RET_Init();
  REG_Init(FALSE);
  REG_GetValue(&swVersion, REG_ID_SW_VERSION);

  if(swVersion != BSP_SW_VERSION)
  {
    REG_Init(TRUE);
    RET_UpdateFlash();
  }

  UI_Init();

  while(1)
  {
    static uint32_t BkupDispExecTime = 0;
    static uint32_t BkupKpdScanTime = 0;
    static uint32_t BkupBuzzExecTime = 0;
    static uint32_t BkupRetExecTime = 0;
    static uint32_t BkupSnrExecTime = 0;
    static uint32_t BkupUiExecTime = 0;
    
    uint32_t sysTime = BSP_GetSysTime();
    
    if((sysTime - BkupDispExecTime) >= DISP_EXEC_MS)
    {
      BkupDispExecTime = sysTime;
      DISP_Exec();
    }
    
    if((sysTime - BkupKpdScanTime) >= KPD_SCAN_MS)
    {
      BkupKpdScanTime = sysTime;
      KPD_Scan();
    }

    if(TURR_GetNewDataFlag())
    {
      TURR_Exec();
    }
  
    if((sysTime - BkupBuzzExecTime) >= BUZZ_EXEC_MS)
    {
      BkupBuzzExecTime = sysTime;
      BSP_BuzzerExec();
    }
	   
    if((sysTime - BkupSnrExecTime) >= SNR_EXEC_MS)
    {
      BkupSnrExecTime = sysTime;
      SENSOR_Exec();
    }

    if((sysTime - BkupUiExecTime) >= UI_EXEC_MS)
    {
      BkupUiExecTime = sysTime;
      UI_Exec();
    }
    
    if(UI_GetNbOfMsgUnProcessed())
    {
      UI_ProcessMsg();
    }
  }
}

/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
PUTCHAR_PROTOTYPE
{
  /* Write a character to the UART1 */
  UART1_SendData8(c);
  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);

  return (c);
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval char Character to Read
  */
GETCHAR_PROTOTYPE
{
#ifdef _COSMIC_
  char c = 0;
#else
  int c = 0;
#endif
  /* Loop until the Read data register flag is SET */
  while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
    c = UART1_ReceiveData8();
  return (c);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
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
