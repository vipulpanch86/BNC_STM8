/**
  ******************************************************************************
  * @file    bsp.c
  * @author  Vipul Panchal
  * @brief   This file contains the board related functions
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
#define CPU_CLOCK_SPEED   24000000ul
#define TIM4_PERIOD       187
#define DATA_START_ADDR   0x004080

/* Private typedef -----------------------------------------------------------*/
/* Private constants----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t  BuzzerEnable = FALSE;
uint32_t BuzzerOnTime = 0;
uint16_t AdcValue = 0;
__IO uint32_t SystemTimer = 0;
__IO uint32_t BspSensorCounter = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Configure system clock to run at 16Mhz
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
  CLK_DeInit();

  /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  
  /* Configure the HSI prescaler to the optimal value */
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

  /* Configure the system clock to use HSE clock source and to run at 24Mhz */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE,
                        CLK_CURRENTCLOCKSTATE_DISABLE);
}

/**
  * @brief  Configure GPIO for LEDs available on the evaluation board
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
  /* Initialize TRIAC Output */
#if (MOTHER_BOARD_TYPE == BSP_MB_BIG)
  GPIO_Init(TRIACB_PORT, TRIACB_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(TRIACC_PORT, TRIACC_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(TRIACD_PORT, TRIACD_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
#else
  GPIO_Init(TRIACB_PORT, TRIACB_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(TRIACC_PORT, TRIACC_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(TRIACD_PORT, TRIACD_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
#endif

  /* Initialize Display Data bits Output */
  GPIO_Init(DISP_DB0_PORT, DISP_DB0_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB1_PORT, DISP_DB1_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB2_PORT, DISP_DB2_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB3_PORT, DISP_DB3_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB4_PORT, DISP_DB4_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB5_PORT, DISP_DB5_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB6_PORT, DISP_DB6_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB7_PORT, DISP_DB7_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

  /* Initialize Display Enable lines */
  GPIO_Init(DISP_EN1_PORT, DISP_EN1_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN2_PORT, DISP_EN2_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN3_PORT, DISP_EN3_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN4_PORT, DISP_EN4_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN5_PORT, DISP_EN5_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN6_PORT, DISP_EN6_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN7_PORT, DISP_EN7_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN8_PORT, DISP_EN8_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN9_PORT, DISP_EN9_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);

  /* Initialize Multiplexer 0 lines */
  GPIO_Init(DEM0_MSA_PORT, DEM0_MSA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DEM0_MSB_PORT, DEM0_MSB_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DEM0_MSC_PORT, DEM0_MSC_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  /* Initialize Keypad Return Pin as Input */
  GPIO_Init(KEY_RET0_PORT, KEY_RET0_PIN, GPIO_MODE_IN_FL_NO_IT);

  /* Initalize Reset as Input */
  GPIO_Init(KEY_RST_PORT, KEY_RST_PIN, GPIO_MODE_IN_PU_NO_IT);

  /* Initialize CAM Switch as Input */
  GPIO_Init(SW_CAM_PORT, SW_CAM_PIN, GPIO_MODE_IN_PU_NO_IT);

  /* Initialize AUTO Switch as Input */
  GPIO_Init(SW_AUTO_PORT, SW_AUTO_PIN, GPIO_MODE_IN_PU_NO_IT);

  /* Initialize Turret as Output */
  GPIO_Init(TUR_EN_PORT, TUR_EN_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);

  /* Initialize Batch as Output */
  GPIO_Init(BATCH_PORT, BATCH_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

  /* Initialize Stamp as Output */
  GPIO_Init(STAMP_PORT, STAMP_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

  /* Initalize Buzzer as Output */
  GPIO_Init(BUZZER_PORT, BUZZER_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
}

/**
  * @brief  Configures Sensor GPIO and EXTI Line.
  * @param  None
  * @retval None
  */
void SENSOR_Config(void)
{
  /* Configure Sensor pin as input */
  GPIO_Init(SENSOR_PORT, SENSOR_PIN, GPIO_MODE_IN_FL_IT);
  /* Connect Sensor EXTI Line to Sensor GPIO Pin */
  EXTI_SetExtIntSensitivity(SENSOR_EXTI, SENSOR_EXTI_SENSE);

}

/**
  * @brief  Configure the FLASH for block programming
  * @param  None
  * @retval None
  */
void FLASH_Config(void)
{
  FLASH_DeInit();
  
  /* Define flash programming Time*/
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
}

/**
  * @brief  Configure TIM4 to generate an update interrupt each 1ms
  * @param  None
  * @retval None
  */
static void TIM4_Config(void)
{
  /* TIM4 configuration:
   - TIM4CLK is set to 24 MHz, the TIM4 Prescaler is equal to 128 so the
     TIM1 counter clock used is 24 MHz / 128 = 187500 Hz
   - With 187500 Hz we can generate time base:
      max time base is 1.365 ms if TIM4_PERIOD = 255 -> (255 + 1) / 187500 = 1.365 ms
      min time base is 0.001 ms if TIM4_PERIOD = 1   -> (  1 + 1) / 187500 = 0.001 ms
  -  In this example we need to generate a time base equal to 1 ms
     so TIM4_PERIOD = (0.001 * 187500 - 1) = 187 */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}

/**
  * @brief  Configure UART1 for the communication with Turret
  * @param  None
  * @retval None
  */
static void UART1_Config(void)
{
  /* Deinitializes the UART1 peripheral */
  UART1_DeInit();

  /* UART1 configuration -------------------------------------------------*/
  /* UART configured as follow:
        - BaudRate = 9600 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Receive and transmit enabled
        - UART Clock disabled
  */

  UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1,
             UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE,
             UART1_MODE_TXRX_ENABLE);

  /* Enable UART */
  UART1_Cmd(ENABLE);
}

/**
  * @brief  UV Configuration
  * @param  None
  * @retval None
  */
static void UV_Config(void)
{
  /* Configure the UV Enable as Output
     Default State is High (UV Disable)
  */
  GPIO_Init(UV_ENB_PORT, UV_ENB_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);

  /*  Init GPIO for UV AIN */
  GPIO_Init(UV_AIN_PORT, UV_AIN_PIN, GPIO_MODE_IN_FL_NO_IT);
  
  /* De-Init ADC peripheral*/
  ADC2_DeInit();

  /* Init ADC2 peripheral */
  ADC2_Init(ADC2_CONVERSIONMODE_CONTINUOUS, ADC2_CHANNEL_8, ADC2_PRESSEL_FCPU_D18, \
            ADC2_EXTTRIG_TIM, DISABLE, ADC2_ALIGN_RIGHT, ADC2_SCHMITTTRIG_CHANNEL8, \
            DISABLE);
  /* Enable EOC interrupt */
  ADC2_ITConfig(ENABLE);

  /* Start ADC2 Conversion */
  ADC2_StartConversion();
}

/**
  * @brief  Executes Buzzer
  * @param  None
  * @retval None
  */
void BSP_BuzzerExec(void)
{
  static uint32_t BackupSysTime = 0;

  if(BuzzerEnable == TRUE)
  {
    if(labs((int32_t)(SystemTimer - BackupSysTime)) >= BuzzerOnTime)
    {
      BuzzerEnable = FALSE;
      BuzzerOnTime = 0;
      BackupSysTime = 0;

      BSP_ClrGPIO(BUZZER_PORT, BUZZER_PIN);
    }
  }
  else
  {
    if(BuzzerOnTime > 0)
    {
      BuzzerEnable = TRUE;
      BackupSysTime = SystemTimer;
      
      BSP_SetGPIO(BUZZER_PORT, BUZZER_PIN);
    }
  }
}

/**
  * @brief  Executes ADC
  * @param  None
  * @retval None
  */
void BSP_AdcExec(void)
{
  uint16_t adcVal;

  ADC2_ClearFlag();
  adcVal = ADC2_GetConversionValue();
  ADC2_StartConversion();
  AdcValue = (AdcValue >> 1) + (adcVal >> 1);
}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Initialzation Board for Functionallity
  * @param  None
  * @retval None
  */
void BSP_Init(void)
{
  /* GPIO configuration */
  GPIO_Config();

  /* Sensor COnfiguration */
  SENSOR_Config();
  
  /* Flash configuration */
  FLASH_Config();

  /* Clock configuration */
  CLK_Config();

  /* TIM4 configuration */
  TIM4_Config();

  /* UART1 configuration */
  UART1_Config();

  /* ADC configuration */
  UV_Config();

  /* Enable general interrupts */
  enableInterrupts();
}

/**
  * @brief  Inserts Delay in Milliseconds
  * @param  Value in Milliseconds to crreate delay
  * @retval None
  */
void BSP_DelayMs(uint16_t delay)
{
  uint32_t backupSysTmr = SystemTimer;
  
  while(labs(SystemTimer - backupSysTmr) < delay);
}

/**
  * @brief  Reads from Flash
  * @param  size - No of bytes to be read
  * @param  pData - Pointer to the Buffer where data needs to be read
  * @retval None
  */
void BSP_ReadFromFlash(uint16_t size, uint8_t *pData)
{
  uint16_t cnt;

  for(cnt = 0; cnt < size; cnt++)
  {
    pData[cnt] = FLASH_ReadByte(DATA_START_ADDR + cnt);
  }
}

/**
  * @brief  Writes to Flash
  * @param  size - No of bytes to be Written
  * @param  pData - Pointer to the Buffer from where data needs to be written
  * @retval None
  */
void BSP_WriteToFlash(uint16_t size, uint8_t *pData)
{
  uint16_t cnt;

  FLASH_Unlock(FLASH_MEMTYPE_DATA);

  while(FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);

  for(cnt = 0; cnt < size; cnt++)
  {
    FLASH_EraseByte(DATA_START_ADDR + cnt);
    FLASH_ProgramByte(DATA_START_ADDR + cnt, pData[cnt]);
  }

  FLASH_Lock(FLASH_MEMTYPE_DATA);
}
/***********************END OF FILE************************/
