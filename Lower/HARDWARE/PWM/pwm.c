#include "pwm.h"

//TIM1 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数

void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
 
    //设置该引脚为复用输出功能,输出TIM2 CH1~4的PWM脉冲波形	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; //TIM_CH1~4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3; //TIM_CH2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
    //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM2 Channe1~4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2
	//TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
	//TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
	//TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	//TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
 
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
	
	Moter_Control(0, 0);
}



//电机输出函数
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

