#ifndef __ENCODER_H
#define __ENCODER_H
#include  <sys.h>	 
#include  "stm32f10x_tim.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);

int Read_Encoder(u8 TIMX);
#endif

