#include "sys.h"
#include "usart.h"	  
#include "string.h"
#include "stdio.h"  
#include "led.h"
#include "control.h"

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 


u8 RxNum = 0;
u8 RxData[8] = {0};
u8 ReceiveFlag = 0;

void uart_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能USART3，GPIOB时钟

	//USART3_TX   GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10

	//USART3_RX	  GPIOB.11初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART3, ENABLE);                    //使能串口3 
}



void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	u8 Res,sum = 0,i = 0;
	//LED_Turn();
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART3);	//读取接收到的数据
		if(RxNum == 0 && Res == 0xa0)
		{
			//帧头
			RxData[0] = Res;
			RxNum = 1;
		}
		else if(RxNum == 1)
		{
			//角度方向
			RxData[1] = Res;
			RxNum = 2;
		}
		else if(RxNum == 2)
		{
			//角度大小
			RxData[2] = Res;
			RxNum = 3;
		}
		else if(RxNum == 3)
		{
			//距离低8位
			RxData[3] = Res;
			RxNum = 4;
		}
		else if(RxNum == 4)
		{
			//距离高8位
			RxData[4] = Res;
			RxNum = 5;
		}
		else if(RxNum == 5)
		{
			//找点的个数
			RxData[5] = Res;
			RxNum = 6;
		}
		else if(RxNum == 6)
		{
			//校验位
			RxData[6] = Res;
			for(i=1;i<6;i++)
				sum += RxData[i];
			
			if(sum == RxData[6])
				RxNum = 7;
				//LED_Turn();
		}
		else if(RxNum == 7 && Res == 0x0a)
		{
			//帧尾
			RxData[RxNum] = Res;
			LED_Turn();
			//RxNum = 0;
			Handle_Data();
			ReceiveFlag = 1;
		}
		else
		{
			RxNum = 0;
		}
	} 
} 

//数据解析函数
void Handle_Data()
{
	CarLoction.AngleDir = RxData[1];
	CarLoction.AngleValue = RxData[2];
	CarLoction.FindState = RxData[5];
	CarLoction.Distance = RxData[4]*256 + RxData[3];
}

