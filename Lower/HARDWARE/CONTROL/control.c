#include "control.h"
//#include "communicate.h"
//#include "pwm.h"

//SYSTEM_STATE_e g_iSystemState = STOP;
//u8 Flag_Stop,delay_50,delay_flag; 

//S_PID Test;								//������
//S_PID Angle;							//�Ƕ�ֵ
//S_PID Position;						//���������������

//void GlobalControl(void)				//ȫ�ֿ���
//{
//		static int Position_Target = 0;
//		AngleControl(&Angle);
//		if(delay_flag==1)
//		{
//			if(++delay_50==10)	 delay_50=0,delay_flag=0;          //===���������ṩ50ms�ľ�׼��ʱ
//		}		
//		if(++Position_Target == 10)
//		{
//			//PositionControl(&Position);
////			Send_Information(Angle.Now, 1);
//			Position_Target = 0;
//		}
//		MotorOutput(Angle.Out - Position.Out);
//		//MotorOutput(50);
//}

//void AngleControl(S_PID * pid)					//ת�ǿ���
//{
//		pid->Last2_Error = pid->Last_Error;
//		pid->Last_Error = pid->Error;
//		pid->Now = Get_Adc_Average(ADC_Channel_4,2);
//		pid->Error = pid->Set - pid->Now;
//		pid->DError = pid->Error - pid->Last_Error;
//	
////		pid->Pout = pid->Kp * pid->DError;
////		pid->Iout = pid->Ki * pid->Error;
////		pid->Dout = pid->Kd * (pid->Error - 2*pid->Last_Error + pid->Last2_Error);
////	
////		pid->PIDOut = pid->Pout + pid->Iout + pid->Dout + pid->PIDOut;
//	
//		pid->Pout = pid->Kp * pid->Error;
//		pid->Iout = pid->Ki * pid->Error + pid->Iout;
//		pid->Dout = pid->Kd * pid->DError;

//		pid->PIDOut = pid->Pout + pid->Iout + pid->Dout;
//	
//		if(pid->PIDOut > pid->Max)	pid->PIDOut = pid->Max;
//		if(pid->PIDOut < pid->Min)	pid->PIDOut = pid->Min;
//	  
//		if(pid->Now > 2488 || pid->Now < 1188)
//			pid->Out = 0;
//		else
//			pid->Out = pid->PIDOut;
//		
//}

//void PositionControl(S_PID * pid)			//ת�ǿ���
//{

//		pid->Last_Error = pid->Error;
//		pid->Now = Read_Encoder(2);			//���±�����λ����Ϣ
//		pid->Error = pid->Error*0.8 + (pid->Set - pid->Now)*0.2;
//		pid->DError = pid->Error - pid->Last_Error;
//	
//		pid->Pout = pid->Kp * pid->Error;
//		pid->Iout = pid->Ki * pid->Error + pid->Iout;
//		pid->Dout = pid->Kd * pid->DError;

//		pid->PIDOut = pid->Pout + pid->Iout + pid->Dout;
//	
//		if(pid->PIDOut > pid->Max)	pid->PIDOut = pid->Max;
//		if(pid->PIDOut < pid->Min)	pid->PIDOut = pid->Min;
//		
//		pid->Out = pid->PIDOut;
//}
//		
