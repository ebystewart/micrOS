#include "usart.h"
#include "gps.h"

static uint16_t rxBuffIndex;
uint8_t read_succ_u8 = 1u;

void Uart_Init(uint8_t numUart)
{
	if (numUart == 1u)
	{
		// make sure the relevant pins are appropriately set up.
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;              // enable clock for GPIOA
		GPIOA->CRH   |= (0x0BUL  << 4);                  // Tx (PA9) alt. out push-pull
		GPIOA->CRH   |= (0x04UL  << 8);                  // Rx (PA10) in floating
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;            // enable clock for USART1
		USART1->BRR  = 72000000UL/9600UL;                // set baudrate
		USART1->CR1 |= ((1<<3));  // RX, TX enable
		USART1->CR1 |= (1<<13);                    // USART enable
	}
	else if (numUart == 2u)
	{
		 // PA.2 = RX    Floating Input
     // PA.3 = TX    Alternate function output Push-pull 50 MHz
     RCC->APB2ENR = RCC->APB2ENR | (1<<2);
     RCC->APB1ENR |= (1<<17);      // enable clock for  USART2.

      GPIOA->CRL   &= ~(0xFFUL  << 8);                      // Clear PA2, PA3
      GPIOA->CRL   |=  (0x0BUL  << 8);                      // USART2 Tx (PA2)  alternate output push-pull
      GPIOA->CRL   |=  (0x04UL  << 12);                     // USART2 Rx (PA3)  input floating

     USART2->BRR  = (72000000UL/19200UL); /* Baud rate set to 9600bps	*/ 
     USART2->CR1  |= ((1<<2) | (1<<3));  // RX, TX enable. 
     USART2->CR1  |= (1<<13);                   // USART2 enable.  
     USART2->CR1  |=  (1<<5);    // UART2 Receive Interrupt Enable.
     // Enable interrupt fromUSART2(NVIC level) 
     NVIC_EnableIRQ(USART2_IRQn);
	}
	else if (numUart == 3u)
	{
     // PB.11 = RX    Floating Input
     // PB.10 = TX    Alternate function output Push-pull 50 MHz
		 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
     AFIO->MAPR   &= ~(3 << 4);                              // clear USART3 remap
     RCC->APB2ENR = RCC->APB2ENR | (1<<3); //enable clock for GPIO B
     RCC->APB1ENR |= (1<<18);      // enable clock for  USART3.

      GPIOB->CRH   &= ~(0xFFUL  <<  8);                     // Clear PB10, PB11
      GPIOB->CRH   |=  (0x0BUL  <<  8);                     // USART3 Tx (PB10) alternate output push-pull
      GPIOB->CRH   |=  (0x04UL  << 12);                     // USART3 Rx (PB11) input floating

     USART3->BRR  = (72000000UL/19200UL);   /* Baud rate set to 9600bps	*/
     USART3->CR1  |= ((1<<2) | (1<<3));  // RX, TX enable.   
     USART3->CR1  |=  (1<<5);    // UART3 Receive Interrupt Enable.
     // Enable interrupt fromUSART3(NVIC level) 
     NVIC_EnableIRQ(USART3_IRQn); 
		 USART3->CR1  |= (1<<13);                   // USART3 enable.
	}
	else if (numUart == 4u)
	{
		RCC->APB1ENR |= (uint32_t)(1<<19);
		GPIOB->CRH |= 0x000004B0;  /* Pin direction - PB.10 (Rx), PB.11 (Tx)	*/
	}
	else if (numUart == 5u)
	{
		RCC->APB1ENR ^= (uint32_t)(1<<20);
	}	
}



void Uart_DeInit(uint8_t numUart)
{
	if (numUart == 2u)
	{
		 // PA.2 = RX    Floating Input
     // PA.3 = TX    Alternate function output Push-pull 50 MHz
     RCC->APB2ENR = RCC->APB2ENR ^ (1<<2);
     RCC->APB1ENR ^= (1<<17);      // enable clock for  USART2.

     //GPIOA->CRL = GPIOA->CRL & 0xFFFF00FF;
     GPIOA->CRL = GPIOA->CRL ^ 0x000004B0;

     //USART3->BRR  =72000000/9600;                    // set baudrate. 
     USART3->CR1  ^= ((1<<2) | (1<<3));  // RX, TX enable. 
     USART3->CR1  ^= (1<<13);                   // USART2 enable.  
     USART3->CR1  ^=  (1<<5);    // UART2 Receive Interrupt Enable.
     // Enable interrupt fromUSART2(NVIC level) 
     NVIC_DisableIRQ(USART2_IRQn);
	}
}

void Uart1_Transmit(uint8_t txData)
{
	while (!(USART1->SR & (1<<7)));		/* Check if TXE=1	*/
	USART1->DR = (txData & 0x1FF); 	
	while(!((USART1->SR) & (1<<6)));	/* Check if TC=1	*/
}
void Uart2_Transmit(uint8_t txData)
{
	while (!(USART2->SR & (1<<7))); 		/* Check if TXE=1	*/
	USART2->DR = (txData & 0x1FF);
	while(!((USART2->SR) & (1<<6)));	/* Check if TC=1	*/
}
void Uart3_Transmit(char txData)
{
  while (!(USART3->SR & (uint32_t)(1<<7)));
  USART3->DR = (txData & 0x1FF);
}

void Uart1_Str_Tx (uint8_t *txstrData)
{
	int i=0;
	while(txstrData[i] != '\0')
	{
		Uart1_Transmit(txstrData[i]);
		i++;
	}
}
void Uart2_Str_Tx (uint8_t *txstrData)
{
	int i=0;
	while(txstrData[i] != '\0')
	{
		Uart2_Transmit(txstrData[i]);
		i++;
	}
}
void Uart3_Str_Tx (uint8_t *txstrData)
{
	int i=0;
	while(txstrData[i] != '\0')
	{
		Uart3_Transmit(txstrData[i]);
		i++;
	}
}
void Uart_Receive(uint8_t *rxData)
{
	
}

void USART1_IRQHandler(void)
{
	if((USART1->SR) & (1<<5))   /* check if RXNE=1	*/
	{
		// Do Something
	}
}	
void USART2_IRQHandler(void)
{
	if(USART2->SR & ((1<<1)|(1<<3)))
	{
		(void)USART2->DR;
	}
  if((USART2->SR & (1<<5)) && (read_succ_u8 == 1u))
  {
		USART2->SR ^= (1<<15);
    Uart2_Acc.rxBuffer[rxBuffIndex] = USART2->DR;		
		Uart1_Transmit(Uart2_Acc.rxBuffer[rxBuffIndex]);
		if (rxBuffIndex >= 500u)
		{
			rxBuffIndex = 0u;
		}
		else {
		rxBuffIndex++;}
  }
}
void USART3_IRQHandler(void)
{
  //if(USART3->SR & (1<<5))
  //{
    // Do Something
  //}
}
