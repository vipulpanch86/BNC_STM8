/**
  ******************************************************************************
  * @file    reg.c
  * @author  Vipul Panchal
  * @brief   This file contains the register handling function.
  ******************************************************************************
  */

/* Board Files Includes */
#include "bsp.h"

/* Application Includes */
#include "reg.h"
#include "ret.h"

/* Private define ------------------------------------------------------------*/
#define RET_BASE                     (0)

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  const uint16_t rw      : 1;     /* Specifies if R/W Capability of the Reg */
  const uint16_t ret     : 1;     /* Specifies if the Reg is Retentive type */
  const uint16_t retAddr : 14;    /* Specifies the Retention Addr of the Reg */
  const uint32_t minVal;          /* Specifies Minimum Value of the Reg */
  const uint32_t maxVal;          /* Specifies Maximum Value of the Reg */
  const uint32_t defVal;          /* Specifies Default Value of the Reg */
} REG_INFO_T;

/* Private Constant ----------------------------------------------------------*/
static const REG_INFO_T REG[] =
{
  /* Software Version */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 0,       /* Retntion Address*/
    1,                  /* Min  */
    9999,               /* Max  */
    BSP_SW_VERSION      /* Default value */
  },
  /* Power ON FLAG */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    FALSE,              /* Min  */
    TRUE,               /* Max  */
    FALSE               /* Default value */
  },
  /* STAMP Enable FLAG */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 1,       /* Retntion Address*/
    FALSE,              /* Min  */
    TRUE,               /* Max  */
    TRUE                /* Default value */
  },
  /* UV Enable FLAG */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 2,       /* Retntion Address*/
    FALSE,              /* Min  */
    TRUE,               /* Max  */
    TRUE                /* Default value */
  },
  /* Value Counter */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    0,                  /* Min  */
    MAX_ADD_COUNT,      /* Max  */
    0                   /* Default value */
  },
  /* NOTE Verify Count */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    1,                  /* Min  */
    200,                /* Max  */
    DEF_NOTE_C_COUNT    /* Default value */
  },
  /* NOTE Batch Count */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    1,                  /* Min  */
    250,                /* Max  */
    DEF_NOTE_B_COUNT    /* Default value */
  },
  /* NOTE Stamp Count */
  {
    FALSE,              /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    1,                  /* Min  */
    100,                /* Max  */
    DEF_NOTE_S_COUNT    /* Default value */
  },
  /* NOTE Value Count */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    10,                 /* Min  */
    1000,               /* Max  */
    DEF_NOTE_V_COUNT    /* Default value */
  },
  /* Accumulated Sensor Counter C Mode */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 3,       /* Retntion Address*/
    0,                  /* Min  */
    MAX_ADD_COUNT,      /* Max  */
    0                   /* Default value */
  },
  /* Accumulated Sensor Counter B Mode */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 4,       /* Retntion Address*/
    0,                  /* Min  */
    MAX_ADD_COUNT,      /* Max  */
    0                   /* Default value */
  },
  /* Accumulated Sensor Counter F Mode */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 5,       /* Retntion Address*/
    0,                  /* Min  */
    MAX_ADD_COUNT,      /* Max  */
    0                   /* Default value */
  },
  /* Accumulated Sensor Counter S Mode */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 6,       /* Retntion Address*/
    0,                  /* Min  */
    MAX_ADD_COUNT,      /* Max  */
    0                   /* Default value */
  },
  /* Accumulated Sensor Counter V Mode */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 7,       /* Retntion Address*/
    0,                  /* Min  */
    MAX_ADD_COUNT,      /* Max  */
    0                   /* Default value */
  },
  /* Verify Mode True Count */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    0,                  /* Min  */
    MAX_LCD_RESLN,      /* Max  */
    0                   /* Default value */
  },
  /* Verify Mode Over Count */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    0,                  /* Min  */
    MAX_LCD_RESLN,      /* Max  */
    0                   /* Default value */
  },
  /* Verify Mode Under Count */
  {
    TRUE,               /* Read Write Enable*/
    FALSE,              /* Retention */
    0,                  /* Retntion Address*/
    0,                  /* Min  */
    MAX_LCD_RESLN,      /* Max  */
    0                   /* Default value */
  },
  /* UV Level */
  {
    TRUE,               /* Read Write Enable*/
    TRUE,               /* Retention */
    RET_BASE + 8,       /* Retntion Address*/
    1,                  /* Min  */
    255,                /* Max  */
    20                  /* Default value */
  }
};

/* Private variables ---------------------------------------------------------*/
static uint32_t RegisterBuff[REG_MAX_NB];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Initializes the Registers.
  * @param  initDefault - Initialize to Default Value / Retention Value
  * @retval None
  */
void REG_Init(uint8_t initDefault)
{
  uint8_t index;
  uint32_t value;

  /* initialize all Registers */
  for(index = 0; index < REG_MAX_NB; index++)
  {
    /* Check if the default value for the Reg is in Range */
    /* else set the value as zero */
    if((REG[index].defVal <= REG[index].maxVal) &&
       (REG[index].defVal >= REG[index].minVal))
    {
      value = REG[index].defVal;
    }
    else
    {
      value = 0;
    }

    /* check if the register is retentive */
    if(REG[index].ret == TRUE)
    {
      /* Write the default value to Retention memory if the System
         Initialzation sets to default, read the retention value */
      if(initDefault == TRUE)
      {
        RET_WriteMem((uint8_t)REG[index].retAddr, &value);
      }
      else
      {
        RET_ReadMem((uint8_t)REG[index].retAddr, &value);
      }
    }

    RegisterBuff[index] = value;
  }
}

/**
  * @brief  Sets value of a Register.
  * @param  pValue - pointer to the value, which needs to be set
  * @param  index - index of the Register
  * @retval TRUE - If Register writting was successful
  */
uint8_t REG_SetValue(uint32_t *pValue, uint8_t index)
{
  /* Check if the Index is In range */
  if(index < REG_MAX_NB)
  {
    /* Check if the Register is R/W */
    if(REG[index].rw == TRUE)
    {
      /* Check if the Value is in range */
      if((*pValue <= REG[index].maxVal) &&
         (*pValue >= REG[index].minVal))
      {
        /* Set the Value in Array */
        RegisterBuff[index] = *pValue;

        /* Write to the Retention memory if the Register is set to be Retentive */
        if(REG[index].ret == TRUE)
        {
          RET_WriteMem((uint8_t)REG[index].retAddr, pValue);
        }

        return TRUE;
      }
    }
  }

  return FALSE;
}

/**
  * @brief  Reads value of a Register.
  * @param  pValue - pointer to the value, which needs to be set
  * @param  index - index of the Register
  * @retval TRUE - If Register writting was successful
  */
uint8_t REG_GetValue(uint32_t *pValue, uint8_t index)
{
  /* Check if the Index is In range */
  if(index < REG_MAX_NB)
  {
    /* Get the Value from the Array */
    *pValue = RegisterBuff[index];

    return TRUE;
  }

  return FALSE;
}

/**
  * @brief  Reads the Minimum value of a Register
  * @param  pValue - pointer to the value, which needs to be set
  * @param  index - index of the Register
  * @retval TRUE - If Register reading was successful
  */
uint8_t REG_GetMinValue(uint32_t *pValue, uint8_t index)
{
  /* Check if the Index is In range */
  if(index < REG_MAX_NB)
  {
    /* Get the Value from the Info Array */
    *pValue = REG[index].minVal;
    return TRUE;
  }

  return FALSE;
}

/**
  * @brief  Reads the Maximum value of a Register
  * @param  pValue - pointer to the value, which needs to be set
  * @param  index - index of the Register
  * @retval TRUE - If Register reading was successful
  */
uint8_t REG_GetMaxValue(uint32_t *pValue, uint8_t index)
{
  /* Check if the Index is In range */
  if(index < REG_MAX_NB)
  {
    /* Get the Value from the Info Array */
    *pValue = REG[index].maxVal;
    return TRUE;
  }

  return FALSE;
}
/*********************************END OF FILE**********************************/
