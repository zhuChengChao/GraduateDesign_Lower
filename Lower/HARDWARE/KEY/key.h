#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)			   //�궨�� PA8 PD2��� Ϊ�ɼ�������׼��

#define KEY PAin(8)  

typedef enum
{
	FREE,
	PRESS,
	DCLICK,
}KEY_STATE;

void KEY_Init(void);//IO��ʼ��
KEY_STATE KEY_Check(u8 mode);//������� 

#endif

