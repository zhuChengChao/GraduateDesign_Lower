#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "oled.h"
#include "pwm.h"
#include "control.h"


int main(void)
{
	Car_Params_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();			
	LED_Init();	
	KEY_Init();		
	OLED_Init();	
	TIM2_PWM_Init(899,0);		
	uart_init(115200);
	delay_ms(1000);   
		
	while(1)
	{		
		if(ReceiveFlag == 1)
		{
			Car_Control();
			ReceiveFlag = 0;
		}
		OLED_Show();
	}
}


