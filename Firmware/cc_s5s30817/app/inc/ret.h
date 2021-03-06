/**
  ******************************************************************************
  * @file    ret.h
  * @author  Vipul Panchal
  * @brief   This file contains the retention memory definitions and prototype.
  ******************************************************************************
  */

#ifndef __RET_H
#define __RET_H

/* Device Signature Base Address and Size */
#define RET_SIGN_BASE_ADDR         (0)
#define RET_SIGN_DATA_SIZE         (2)

/* Device Calibration Data Base Address and Size */
#define RET_CALIB_BASE_ADDR        (8)
#define RET_CALIB_DATA_SIZE        (32)

/* Device Retentive Register Data Base Address and Size */
#define RET_REG_BASE_ADDR          (64)
#define RET_REG_DATA_SIZE          (64)

void RET_Init(void);
void RET_WriteMem(uint8_t idx, uint32_t *pData);
void RET_ReadMem(uint8_t idx, uint32_t *pData);
void RET_UpdateFlash(void);

#endif /* __RET_H */
/*********************************END OF FILE**********************************/

