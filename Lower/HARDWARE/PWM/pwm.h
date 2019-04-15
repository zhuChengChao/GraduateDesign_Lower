#ifndef __PWM_H
#define __PWM_H
#include "sys.h"


//TIM1PWMÒý½Å
//PBA0 1 2 3
void TIM2_PWM_Init(u16 arr,u16 psc);
void Moter_Control(int left_output, int right_output);

#endif
