#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"                  // Device header

/* Typedef Declarations	*/
static struct
	{
		uint8_t lenData;
		uint8_t txBuffer[10];
		uint8_t rxBuffer[256];
  }Uart2_Acc;;

	
/*	Function Declarations	*/	
void Uart_Init(uint8_t numUart);
void Uart_DeInit(uint8_t numUart);
void Uart1_Transmit(uint8_t txData);
void Uart1_Str_Tx (uint8_t *txstrData);	
void Uart_Receive(uint8_t *rxData);
void Uart2_Transmit(uint8_t txData);
void Uart2_Str_Tx (uint8_t *txstrData);
void Uart3_Transmit(char txData);
void Uart3_Str_Tx (uint8_t *txstrData);
	
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);	



#endif
