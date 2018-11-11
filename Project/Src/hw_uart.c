/**
  ******************************************************************************
  * @file           : hw_msp.c
  * @author         : 
  * @version        : 
  * @date           : 
  * @brief          : system hardware driver
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
  
#include "hw.h"
#include "hw_uart.h"
#include <stdarg.h>


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFSIZE 256

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static char buff[BUFSIZE]; // buffer
__IO uint16_t iw=0; // buffer write index
static uint16_t ir=0; // buffer read index
static UART_HandleTypeDef UartHandle; // Uart Handle

/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

void UART_Init(void)
{
  /*## Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = ODD parity
      - BaudRate = 115200 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance        = USARTX;
  
  UartHandle.Init.BaudRate   = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  HAL_NVIC_SetPriority(USARTX_IRQn, 0x1, 0);
  HAL_NVIC_EnableIRQ(USARTX_IRQn);
}


void UART_DeInit(void)
{
#if 1
  HAL_UART_DeInit(&UartHandle);
#endif
}

void UART_Send( char *format, ... )
{
  va_list args;
  va_start(args, format);
  uint8_t len;
  uint8_t lenTop;
  char tempBuff[128];
  
  BACKUP_PRIMASK();
  DISABLE_IRQ();
  
  /*convert into string at buff[0] of length iw*/
  len = vsprintf(&tempBuff[0], format, args);
  
  if (iw+len<BUFSIZE)
  {
    memcpy( &buff[iw], &tempBuff[0], len);
    iw+=len;
  }
  else
  {
    lenTop=BUFSIZE-iw;
    memcpy( &buff[iw], &tempBuff[0], lenTop);
    len-=lenTop;
    memcpy( &buff[0], &tempBuff[lenTop], len);
    iw = len;
  }
  RESTORE_PRIMASK();
  
  HAL_NVIC_SetPendingIRQ(USARTX_IRQn);
    
  va_end(args);
}

/* modifes only ir*/
void UART_Print( void)
{
  char* CurChar;
  while( ( (iw+BUFSIZE-ir)%BUFSIZE) >0 )
  {
    BACKUP_PRIMASK();
    DISABLE_IRQ();
    
    CurChar = &buff[ir];
    ir= (ir+1) %BUFSIZE;
    
    RESTORE_PRIMASK();
    
    HAL_UART_Transmit(&UartHandle,(uint8_t *) CurChar, 1, 300);    
  }
  HAL_NVIC_ClearPendingIRQ(USARTX_IRQn);
}

void UART_Send_Lp( char *format, ... )
{
  va_list args;
  va_start(args, format);
  uint8_t len;
  uint8_t lenTop;
  char tempBuff[128];
  
  BACKUP_PRIMASK();
  DISABLE_IRQ();
  
  /*convert into string at buff[0] of length iw*/
  len = vsprintf(&tempBuff[0], format, args);
  
  if (iw+len<BUFSIZE)
  {
    memcpy( &buff[iw], &tempBuff[0], len);
    iw+=len;
  }
  else
  {
    lenTop=BUFSIZE-iw;
    memcpy( &buff[iw], &tempBuff[0], lenTop);
    len-=lenTop;
    memcpy( &buff[0], &tempBuff[lenTop], len);
    iw = len;
  }
  RESTORE_PRIMASK();  
  
  va_end(args);
}

/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/

  /* Enable USART1 clock */
  USARTX_CLK_ENABLE(); 
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  UART_IoInit( );
}

void UART_IoInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct={0};
    /* Enable GPIO TX/RX clock */
  USARTX_TX_GPIO_CLK_ENABLE();
  USARTX_RX_GPIO_CLK_ENABLE();
    /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTX_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = USARTX_TX_AF;

  HAL_GPIO_Init(USARTX_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTX_RX_PIN;
  GPIO_InitStruct.Alternate = USARTX_RX_AF;

  HAL_GPIO_Init(USARTX_RX_GPIO_PORT, &GPIO_InitStruct);
}

void UART_IoDeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure={0};
  
  USARTX_TX_GPIO_CLK_ENABLE();
  USARTX_RX_GPIO_CLK_ENABLE();

  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  
  GPIO_InitStructure.Pin =  USARTX_TX_PIN ;
  HAL_GPIO_Init(  USARTX_TX_GPIO_PORT, &GPIO_InitStructure );
  
  GPIO_InitStructure.Pin =  USARTX_RX_PIN ;
  HAL_GPIO_Init(  USARTX_RX_GPIO_PORT, &GPIO_InitStructure ); 
}

/**
  * @brief UART MSP DeInit
  * @param huart: uart handle
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  UART_IoDeInit( );
}


