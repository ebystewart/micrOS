#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"                  // Device header

void TIM_Tim1_Init(void);
void TIM_Tim2_Init(void);
void TIM_Tim3_Init(void);
void TIM_Tim4_Init(void);

void TIM_Tim1_DeInit(void);
void TIM_Tim2_DeInit(void);
void TIM_Tim3_DeInit(void);
void TIM_Tim4_DeInit(void);

void TIM_Tim1_Start(void);
void TIM_Tim2_Start(void);
void TIM_Tim3_Start(void);
void TIM_Tim4_Start(void);

void TIM_Tim1_Stop(void);
void TIM_Tim2_Stop(void);
void TIM_Tim3_Stop(void);
void TIM_Tim4_Stop(void);

void TIM_Tim1_Reload(void);
void TIM_Tim2_Reload(void);
void TIM_Tim3_Reload(void);
void TIM_Tim4_Reload(void);

void TIM1_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

#endif



