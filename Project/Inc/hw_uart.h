/**
  ******************************************************************************
  * @file           : hw_uart.h
  * @author         : 
  * @version        : 
  * @date           : 
  * @brief          : Header for hw_uart.c module
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */ 

/** 
* @brief  Init the UART.
* @param  None
* @return None
*/
void UART_Init(void);

   /** 
* @brief  DeInit the UART.
* @param  None
* @return None
*/
void UART_DeInit(void);

   /** 
* @brief  Init the UART IOs.
* @param  None
* @return None
*/
void UART_IoInit(void);
  
   /** 
* @brief  DeInit the UART IOs.
* @param  None
* @return None
*/
void UART_IoDeInit(void);
  
/** 
* @brief  Records string on circular Buffer and set SW interrupt
* @note   Set NVIC to call UART_Send
* @param  string
* @return None
*/
void UART_Send( char *format, ... );

/** 
* @brief  Sends circular Buffer on com port in IT mode
* @note   called from low Priority interrupt
* @param  None
* @return None
*/
void UART_Print( void);

/** 
* @brief  Records string on circular Buffer
* @note   To be called only from critical section from low power section
*         Other wise use UART_Send
* @param  string
* @return None
*/
void UART_Send_Lp( char *format, ... );

/* Exported macros -----------------------------------------------------------*/
#if 1
#define PRINTF(...)            UART_Send(__VA_ARGS__)
#define DBG_PRINTF(...)        UART_Send(__VA_ARGS__)
#else
#define PRINTF(...)
#endif


#ifdef __cplusplus
}
#endif

#endif /* __UART_H__*/

