#include "osKernel.h"

#define NUM_OF_THREADS  3
#define STACK_SIZE      100
#define BUS_FREQ 8000000
#define SYSPRI3   (*((volatile uint32_t *)0xE000ED20))
#define INTCTRL   (*((volatile uint32_t *)0xE000ED04))

uint32_t MILLIS_PRESCALER; 
void osSchedulerLaunch(void);

struct tcb
	{
		uint32_t *stackPt;
		struct tcb *nextPt;
	};

typedef struct tcb tcbType;	
tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPt;

uint32_t TCB_STACK[NUM_OF_THREADS][STACK_SIZE];

void osKernelStackInit(uint8_t i)
{
	tcbs[i].stackPt = &TCB_STACK[i][STACK_SIZE-16];
	TCB_STACK[i][STACK_SIZE-1] = 0x01000000;
}	

uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void))
{
	__disable_irq();
	tcbs[0].nextPt = &tcbs[1];
	tcbs[1].nextPt = &tcbs[2];
	tcbs[2].nextPt = &tcbs[0];
	osKernelStackInit(0);
	TCB_STACK[0][STACK_SIZE-2] = (uint32_t)(task0);
	
	osKernelStackInit(1);
	TCB_STACK[1][STACK_SIZE-2] = (uint32_t)(task1);
	
	osKernelStackInit(2);
	TCB_STACK[2][STACK_SIZE-2] = (uint32_t)(task2);
	
	currentPt = &tcbs[0];
	__enable_irq();
	return 1;
}

void osKernelInit()
{
	__disable_irq();
	MILLIS_PRESCALER = BUS_FREQ/1000;
	
}

void osKernelLaunch(uint32_t quanta)
{
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SYSPRI3 = (SYSPRI3 & 0x00FFFFFF) | 0xE0000000; /* Set systick priority to least: Priority 7 */
	SysTick->LOAD = (quanta * MILLIS_PRESCALER) - 1;   /* closck source equals bus clock */
	SysTick->CTRL = 0x00000007;						/* Initialize systick */
	osSchedulerLaunch();
}

void osThreadYield(void)
{
	INTCTRL = 0x04000000;		/* Trigger SysTick Interrupt	*/
}

