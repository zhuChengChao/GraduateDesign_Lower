#include "pwm.h"

//TIM1 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��

void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ�ܶ�ʱ��2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
 
    //���ø�����Ϊ�����������,���TIM2 CH1~4��PWM���岨��	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; //TIM_CH1~4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3; //TIM_CH2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
 
    //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM2 Channe1~4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2
	//TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
	//TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
	//TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	//TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
 
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
	
	Moter_Control(0, 0);
}



//����������
void Moter_Control(int left_output, int right_output)
{
	if(left_output >= 900)
		left_output = 899;
//	else if(left_output <= -600)
//		left_output = -600;
	
	if(right_output >= 900)
		right_output = 899;
//	else if(right_output <= -2600)
//		right_output = -600;
	
//	if(left_output >= 0)
//	{
//		TIM_SetCompare1(TIM2, left_output);
//		TIM_SetCompare2(TIM2, 0);
//	}
//	else
//	{
//		TIM_SetCompare1(TIM2, 0);
//		TIM_SetCompare2(TIM2, -left_output);
//	}
//	
//	if(right_output >= 0)
//	{
//		TIM_SetCompare3(TIM2, right_output);
//		TIM_SetCompare4(TIM2, 0);
//	}
//	else
//	{
//		TIM_SetCompare3(TIM2, 0);
//		TIM_SetCompare4(TIM2, -right_output);
//	}

	TIM_SetCompare1(TIM2, left_output);
	TIM_SetCompare4(TIM2, right_output);
}

