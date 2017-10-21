/**
  ******************************************************************************
  * @file    turret.h
  * @author  Mahajan Electronics Team
  * @version V1.0.0
  * @date    28-February-2016
  * @brief   This file contains definitions for turret resources.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TURRET_H
#define __TURRET_H

#define TURR_MAX_PKT_LEN    3

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t  TurretExecute;

/**
  * @brief  Returns the New Turret Available Flag
  * @param  None
  * @retval Turret Data Available Flag
  */
@inline uint8_t TURR_GetNewDataFlag(void)
{
  return TurretExecute;
}

void TURR_Clear(void);
void TURR_PutVal(uint16_t value);
void TURR_Exec(void);


#ifdef __cplusplus
}
#endif

#endif /* __TURRET_H */

/******************************END OF FILE*****/
