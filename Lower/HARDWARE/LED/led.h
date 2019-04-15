#ifndef	__LED_H
#define __LED_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "sys.h"

#define LED_ON GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LED_OFF GPIO_SetBits(GPIOA,GPIO_Pin_1)

void LED_Init(void);//≥ı ºªØ
void LED_Turn(void);
#endif



