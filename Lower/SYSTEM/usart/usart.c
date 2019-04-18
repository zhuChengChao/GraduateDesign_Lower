#include "sys.h"
#include "usart.h"	  
#include "string.h"
#include "stdio.h"  
#include "led.h"
#include "control.h"

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 


u8 RxNum = 0;
u8 RxData[8] = {0};
u8 ReceiveFlag = 0;

void uart_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART3��GPIOBʱ��

	//USART3_TX   GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10

	//USART3_RX	  GPIOB.11��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11  

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 
}



void USART3_IRQHandler(void)                	//����3�жϷ������
{
	u8 Res,sum = 0,i = 0;
	//LED_Turn();
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART3);	//��ȡ���յ�������
		if(RxNum == 0 && Res == 0xa0)
		{
			//֡ͷ
			RxData[0] = Res;
			RxNum = 1;
		}
		else if(RxNum == 1)
		{
			//�Ƕȷ���
			RxData[1] = Res;
			RxNum = 2;
		}
		else if(RxNum == 2)
		{
			//�Ƕȴ�С
			RxData[2] = Res;
			RxNum = 3;
		}
		else if(RxNum == 3)
		{
			//�����8λ
			RxData[3] = Res;
			RxNum = 4;
		}
		else if(RxNum == 4)
		{
			//�����8λ
			RxData[4] = Res;
			RxNum = 5;
		}
		else if(RxNum == 5)
		{
			//�ҵ�ĸ���
			RxData[5] = Res;
			RxNum = 6;
		}
		else if(RxNum == 6)
		{
			//У��λ
			RxData[6] = Res;
			for(i=1;i<6;i++)
				sum += RxData[i];
			
			if(sum == RxData[6])
				RxNum = 7;
				//LED_Turn();
		}
		else if(RxNum == 7 && Res == 0x0a)
		{
			//֡β
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

//���ݽ�������
void Handle_Data()
{
	CarLoction.AngleDir = RxData[1];
	CarLoction.AngleValue = RxData[2];
	CarLoction.FindState = RxData[5];
	CarLoction.Distance = RxData[4]*256 + RxData[3];
}

