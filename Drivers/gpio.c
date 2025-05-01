#include "gpio.h"



void GPIO_PA_Init(void)
{
	/*	Enable Peripheral Clcok for Port A		*/
	RCC->APB2ENR |= 0x00000004;
  GPIOA->CRL |= 0x66630000;	
}

void GPIO_PA_DeInit(void)
{
	/*	Enable Peripheral Clcok for Port A		*/
	RCC->APB2ENR &= ~0x00000004;	
	GPIOA->CRL &= ~0x66660000;
}

void Probe_PA4(void)
{
	GPIOA->ODR ^= 0x00000010;
}

void Probe_PA5(void)
{
	GPIOA->ODR ^= 0x00000020;
}

void Probe_PA6(void)
{
	GPIOA->ODR ^= 0x00000040;
}

void Probe_PA7(void)
{
	GPIOA->ODR ^= 0x00000080;
}




