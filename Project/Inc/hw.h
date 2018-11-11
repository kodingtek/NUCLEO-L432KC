/**
  ******************************************************************************
  * @file           : hw.h
  * @author         : 
  * @version        : 
  * @date           : 
  * @brief          : contains all hardware driver
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_H__
#define __HW_H__

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_conf.h"
#include "hw_conf.h"
#include "hw_msp.h"


/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

#ifdef __cplusplus
}
#endif

#endif /* __HW_H__ */

