#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "oled.h"
#include "pwm.h"


int main(void)
{
	u8 key_value = 0;
	//u16 pwm_value = 500;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();			
	LED_Init();	
	KEY_Init();		
	OLED_Init();	
	TIM2_PWM_Init(899,0);	
	uart_init(9600);
	delay_ms(1000);   
		
	while(1)
	{		
		key_value = KEY_Check(1);
		if(key_value == PRESS)
		{
			LED_Turn();
		}

		
		OLED_ShowNum(0,0,12345,5,16);
		//LED_Turn();
		delay_ms(200);
	}
}


