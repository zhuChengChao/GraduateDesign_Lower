#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;					 //����GPIO�ṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			 	//LED-->PA.1 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.1
	GPIO_SetBits(GPIOA,GPIO_Pin_1);						 	//PA.1 �����
}


void LED_Turn(void)
{
	unsigned char led_status = GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1);
	
	if(led_status == Bit_SET)
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	else GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
