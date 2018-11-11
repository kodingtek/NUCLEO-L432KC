/**
  ******************************************************************************
  * @file           : hw_conf.h
  * @author         : 
  * @version        : 
  * @date           : 
  * @brief          : contains hardware configuration Macros and Constants
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONF_H__
#define __HW_CONF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/



/* Exported types ------------------------------------------------------------*/
typedef enum 
{
  LED1 = 0,
  LED_RDY = LED1,
  LD2 = LED1
} Led_TypeDef;

typedef enum 
{  
  BUTTON_USER = 0,
  /* Alias */
  BUTTON_KEY  = BUTTON_USER
} Button_TypeDef;

/* Exported constants --------------------------------------------------------*/

/* --------------------------- RTC HW definition -------------------------------- */
#define RTC_OUTPUT       

/* --------------------------- USART HW definition -------------------------------*/

#define USARTX                           USART2
#define USARTX_CLK_ENABLE()              __USART2_CLK_ENABLE();
#define USARTX_RX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define USARTX_TX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE() 

#define USARTX_FORCE_RESET()             __USART3_FORCE_RESET()
#define USARTX_RELEASE_RESET()           __USART3_RELEASE_RESET()


/* Definition for USARTx Pins */
#define USARTX_TX_PIN                  GPIO_PIN_10
#define USARTX_TX_GPIO_PORT            GPIOB  
#define USARTX_TX_AF                   GPIO_AF7_USART3
#define USARTX_RX_PIN                  GPIO_PIN_11
#define USARTX_RX_GPIO_PORT            GPIOB 
#define USARTX_RX_AF                   GPIO_AF7_USART3

/* Definition for USARTx's NVIC */
#define USARTX_IRQn                      USART3_IRQn
#define USARTX_IRQHandler                USART3_IRQHandler


#ifdef __cplusplus
}
#endif

#endif /* __HW_CONF_H__ */
