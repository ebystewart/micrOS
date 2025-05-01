#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H

#include "stm32f10x.h"

void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));
void osKernelStackInit(uint8_t i);
void osThreadYield(void);

#endif
