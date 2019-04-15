#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)			   //宏定义 PA8 PD2输出 为采集数据做准备

#define KEY PAin(8)  

typedef enum
{
	FREE,
	PRESS,
	DCLICK,
}KEY_STATE;

void KEY_Init(void);//IO初始化
KEY_STATE KEY_Check(u8 mode);//按键检测 

#endif

