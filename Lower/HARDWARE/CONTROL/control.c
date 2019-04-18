#include "control.h"
#include "pwm.h"

Car_State_E g_iCarState = STOP;
CAR_PID_S PID;	
CAR_LOCTION_S CarLoction;
CAr_SPEED_S CarSpeed;


void Car_Params_Init(void)
{
	CarSpeed.Speed_Set = 400;
	CarSpeed.Left_Speed = 0;
	CarSpeed.Right_Speed = 0;
	
	PID.Turn_P = 1;
}

//小车整体控制
void Car_Control(void)
{
	if(CarLoction.FindState > 2)
	{
		//找到三个灯的处理
		CarSpeed.Speed_Set = 500;
		Turn_Contorl();
		Speed_Control();
	}
	else if(CarLoction.FindState == 2)
	{
		//找到两个灯的处理
		CarSpeed.Speed_Set = 500;
		Turn_Contorl();
		if(CarLoction.Distance < 50)
			Stop();
		else Speed_Control();
	}
	else
	{
		Stop();
	}		
		
	
	
	
}

//小车方向控制
void Turn_Contorl(void)
{
	if(CarLoction.FindState != 0)
	{
		if(CarLoction.AngleDir == LEFT)
		{
			CarSpeed.Left_Speed = CarSpeed.Speed_Set - PID.Turn_P*CarLoction.AngleValue;
			CarSpeed.Right_Speed = CarSpeed.Speed_Set + PID.Turn_P*CarLoction.AngleValue;
		}
		else if(CarLoction.AngleDir == RIGHT)
		{
			CarSpeed.Left_Speed = CarSpeed.Speed_Set + PID.Turn_P*CarLoction.AngleValue;
			CarSpeed.Right_Speed = CarSpeed.Speed_Set - PID.Turn_P*CarLoction.AngleValue;
		}
	}
	
	Speed_Control();
}

//小车的速度控制
void Speed_Control(void)
{
	Moter_Control(CarSpeed.Left_Speed, CarSpeed.Right_Speed);
}

//停车
void Stop(void)
{
	Moter_Control(0, 0);
}


//显示函数
void OLED_Show(void)
{
	//显示角度
	if(CarLoction.AngleDir == LEFT)
		OLED_ShowString(0,0,"Car Loc's Left  ");
	else if(CarLoction.AngleDir == RIGHT)
		OLED_ShowString(0,0,"Car Loc's Right");
	else OLED_ShowString(0,0,"Error!!!    ");
	
	
	//显示状态
	if(CarLoction.FindState == 2)
		OLED_ShowString(0,2,"Find 2 Point");
	else if(CarLoction.AngleDir == 3)
		OLED_ShowString(0,2,"Find 3 Point");
	else OLED_ShowString(0,2,"None!!!    ");
	
	//显示角度大小
	OLED_ShowString(0,4, "A_Value:");
	OLED_ShowNum(72,4,CarLoction.AngleValue,3,16);
	
	//显示距离
	OLED_ShowString(0,6, "C_Dist:");
	OLED_ShowNum(72,6,CarLoction.Distance,3,16);
}

//void GlobalControl(void)				//全局控制
//{
//		static int Position_Target = 0;
//		AngleControl(&Angle);
//		if(delay_flag==1)
//		{
//			if(++delay_50==10)	 delay_50=0,delay_flag=0;          //===给主函数提供50ms的精准延时
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

//void AngleControl(S_PID * pid)					//转角控制
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

//void PositionControl(S_PID * pid)			//转角控制
//{

//		pid->Last_Error = pid->Error;
//		pid->Now = Read_Encoder(2);			//更新编码器位置信息
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
