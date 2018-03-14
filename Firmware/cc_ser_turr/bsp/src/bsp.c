/**
  ******************************************************************************
  * @file    bsp.c
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    11-August-2015
  * @brief   This file contains the board related functions
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
#define CPU_CLOCK_SPEED   16000000ul
#define TIM4_PERIOD       124

/* Private typedef -----------------------------------------------------------*/
/* Private constants----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t SystemTimer = 0;
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

  /* Initialization of the clock */
  /* Clock divider to HSI/1 */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

}

/**
  * @brief  Configure GPIO for LEDs available on the evaluation board
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{

  /* Initialize Display Data bits Output */
  GPIO_Init(DISP_DB0_PORT, (GPIO_Pin_TypeDef)DISP_DB0_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB1_PORT, (GPIO_Pin_TypeDef)DISP_DB1_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB2_PORT, (GPIO_Pin_TypeDef)DISP_DB2_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB3_PORT, (GPIO_Pin_TypeDef)DISP_DB3_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB4_PORT, (GPIO_Pin_TypeDef)DISP_DB4_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB5_PORT, (GPIO_Pin_TypeDef)DISP_DB5_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DISP_DB6_PORT, (GPIO_Pin_TypeDef)DISP_DB6_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  /* Initialize Display Select Enable bits */
  GPIO_Init(DISP_EN0_PORT, (GPIO_Pin_TypeDef)DISP_EN0_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN1_PORT, (GPIO_Pin_TypeDef)DISP_EN1_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN2_PORT, (GPIO_Pin_TypeDef)DISP_EN2_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(DISP_EN3_PORT, (GPIO_Pin_TypeDef)DISP_EN3_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
}

/**
  * @brief  Configure TIM4 to generate an update interrupt each 1ms 
  * @param  None
  * @retval None
  */
static void TIM4_Config(void)
{
  /* TIM4 configuration:
   - TIM4CLK is set to 12 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 12 MHz / 128 = 93750 Hz
  - With 93750 Hz we can generate time base:
      max time base is 2.730 ms if TIM4_PERIOD = 255 --> (255 + 1) / 93750 = 2.730 ms
      min time base is 0.021 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 93750 = 0.021 ms
  - In this example we need to generate a time base equal to 1 ms
   so TIM4_PERIOD = (0.001 * 93750 - 1) = 187 */

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
  * @brief  Configure UART1 for the communication with Controller
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
             UART1_MODE_RX_ENABLE);
  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
    receive data register is not empty */
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  UART1_ClearITPendingBit(UART1_IT_RXNE);

  /* Enable UART */
  UART1_Cmd(ENABLE);
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

  /* Clock configuration */
  CLK_Config();

  /* TIM4 configuration */
  TIM4_Config();

  /* UART1 configuration */
  UART1_Config();

  /* Enable general interrupts */
  enableInterrupts();
}
/***********************END OF FILE************************/
