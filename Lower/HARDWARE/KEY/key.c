#include "key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	 															//�ṹ�嶨��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);												//����GPIOAʱ��
	
	//��ʼ�� GPIOA.8	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 															//PA8���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);																			//��ʼ��
}



KEY_STATE KEY_Check(u8 mode)
{
	static u8 key_up = 1;
	if(mode)
		key_up = 1;
	
	if(key_up&&(KEY==0))
	{
		delay_ms(10);
		key_up = 0;
		if(KEY==0)
		{
			delay_ms(50);
			return PRESS;
		}
	}
	else if(KEY==1) 
		key_up=1; 	 
	
	return FREE;
}

/*
KEY_STATE KEY_Check(void)
{
	static int scanTime = 0;
	static int doubleClickFalg = 0;
	KEY_STATE keyState = FREE;
	KEY_STATE keyStateLast = FREE;
	if(++scanTime == 100)
	{
		scanTime = 0;

		if(KEY == 0)	//����
		{
			keyState = PRESS;
		}
		else
		{
			keyState = FREE;
		}
	}				
	if(keyState != keyStateLast)
	{
		OLED_Clear();
	}
	keyStateLast = keyState;
	return keyState;
}
*/
