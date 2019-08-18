#ifndef _HCSR04_H
#define _HCSR04_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

void HCSR04_Init(void);
void Timer3_Init(void);
void HCSR04_Timer3_Get_Distance(void);

extern TIM_HandleTypeDef TIM3_Handler;

#endif

