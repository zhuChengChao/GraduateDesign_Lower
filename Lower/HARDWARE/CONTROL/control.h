#ifndef __CONTROL_H_
#define __CONTROL_H_
#include "sys.h"

#define LEFT 1
#define RIGHT 0

typedef struct
{
	float Turn_P;
	float Turn_I;
	float Turn_D;
	
	float Speed_P;
	float Speed_I;
	float Speed_D;
}CAR_PID_S;

typedef struct
{
	float AngleDir;
	float AngleValue;
	int FindState;
	int Distance;
}CAR_LOCTION_S;

typedef struct
{
    int Speed_Set;
	int Left_Speed;
	int Right_Speed;
} CAr_SPEED_S;

typedef enum
{
    STOP = 0,			//ֹͣ
	START,
	BACK2CENTER,
	FINDBEACON
} Car_State_E;




//����ǰ��״̬
extern Car_State_E g_iCarState;
//����PID����
extern CAR_PID_S PID;
//����λ��
extern CAR_LOCTION_S CarLoction;
//�����ٶ�����
extern CAr_SPEED_S CarSpeed;


void Car_Params_Init(void);
void Car_Control(void);
void Speed_Control(void);
void Turn_Contorl(void);
void Stop(void);
void OLED_Show(void);
	

//void GlobalControl(void);					//ȫ�ֿ���
//void AngleControl(S_PID * pid);
//void PositionControl(S_PID * pid);			//ת�ǿ���
#endif
