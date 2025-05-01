#include "timer.h"
#include "gpio.h"
#include "gprs.h"
uint8_t count3 = 0;

/*  Timer 1 	*/ 
void TIM_Tim1_Init(void)
{
	RCC->APB2ENR |= (1u<<11); /* Enable Timer 1 Clock 	*/
}

void TIM_Tim1_DeInit(void)
{
	RCC->APB2RSTR |= (1u<<11); /* Reset Timer 1	*/
	
}

void TIM_Tim1_Start(void)
{
	
}

void TIM_Tim1_Stop(void)
{
	
}

void TIM_Tim1_Reload(void)
{
	
}

/*  Timer 2 	*/

void TIM_Tim2_DeInit(void)
{
	RCC->APB1RSTR |= 1u; /* Reset Timer 2	*/
	
}

void TIM_Tim2_Init(void)
{
	RCC->APB1ENR |= 1u; 				/* Enable Timer 2 Clock 	*/
	TIM2->PSC = 23999;          // Set prescaler to 24 000 (PSC + 1)
  TIM2->ARR = 1000;           // Auto reload value 1000
  TIM2->DIER = 0x01; 					/*	update interrupt enabled	*/
	TIM2->CR1 = 0x00000081; 		/* No clock division, auto reload enabled, upcounter */
  NVIC_EnableIRQ(TIM2_IRQn); 	// Enable interrupt from TIM3 (NVIC level)
}

/*  Timer 3 	*/

void TIM_Tim3_DeInit(void)
{
	RCC->APB1RSTR |= (1u<<1); /* Reset Timer 3	*/
	
}

void TIM_Tim3_Init(void)
{
	RCC->APB1ENR |= (1u<<1); /* Enable Timer 3 Clock 	*/
}

/*  Timer 4 	*/

void TIM_Tim4_DeInit(void)
{
	RCC->APB1RSTR |= (1u<<2); /* Reset Timer 4	*/
	
}

void TIM_Tim4_Init(void)
{
	RCC->APB1ENR |= (1u<<2); /* Enable Timer 4 Clock 	*/
}

//void TIM2_IRQHandler(void)
//{
//if(TIM2->SR & 0x00000001) 	// if UIF flag is set
//  {
//  TIM2->SR ^= 0x00000001; 	// clear UIF flag
//  //Probe_PA5(); 							// toggle LED state
//		count3++;
//  }
//	   asm(	"CPSID 	I\n"
//					"PUSH 	{R4-R11}\n"		  // saves r4,r5,r6,r7,r8,r9,r10,r11
//					"LDR 	  R0,=currentPt1\n"	// r0 points to current pointer
//					"LDR		R1,[R0]\n"			// r1 points to r0 which has currentPt
//					"STR		SP,[R1]\n"			// store stack pointer with currentPt
//					"LDR		R1,[R1,#4]\n"		// r1 equals currentPt->next
//					"STR		R1,[R0]\n"			// currentPt = R1
//					"LDR 	  SP,[R1]\n"			// SP = currentPt->stackPt
//					"POP		{R4-R11}\n"
//					"CPSIE	I\n"
//					"BX		  LR\n");
//}

