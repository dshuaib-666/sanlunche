#include "MOTOR.h"

void MOTOR_Init(void)
{
		HAL_TIM_PWM_Start(Motor_370_Left_TIM,Motor_370_Left_Channel);//����PWM��ʼ��	
		HAL_TIM_PWM_Start(Motor_370_Right_TIM,Motor_370_Right_Channel);	//�ҵ��PWM��ʼ��
		HAL_TIM_PWM_Start(Motor_370_Front_TIM,Motor_370_Front_Channel);	//�ҵ��PWM��ʼ��

}




//ǰ�������ռ�ձ�(��ת)	
//��Χ��-16800,+16800��

void Motor_370_F(int Duty)
{
	if(Duty > 16800 && Duty < -16800)
	{Duty = 0;}
	if(Duty > 0)
	{
			//370(��)��ת
		HAL_GPIO_WritePin(F_Ain1_GPIO,F_Ain1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_Ain2_GPIO,F_Ain2_Pin,GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(Motor_370_Front_TIM,Motor_370_Front_Channel,Duty);			
	}
	else
	{
			//370(��)��ת
		HAL_GPIO_WritePin(F_Ain1_GPIO,F_Ain1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(F_Ain2_GPIO,F_Ain2_Pin,GPIO_PIN_SET);
		__HAL_TIM_SetCompare(Motor_370_Front_TIM,Motor_370_Front_Channel,-Duty);
	}
}


//�ҵ������ռ�ձ�(��ת)	
//��Χ��-16800,+16800��

void Motor_370_R(int Duty)
{
	if(Duty > 16800 && Duty < -16800)
	{Duty = 0;}
	if(Duty > 0)
	{
			//370(��)��ת
		HAL_GPIO_WritePin(R_Bin1_GPIO,R_Bin1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R_Bin2_GPIO,R_Bin2_Pin,GPIO_PIN_SET);
		__HAL_TIM_SetCompare(Motor_370_Right_TIM,Motor_370_Right_Channel,Duty);			
	}
	else
	{
			//370(��)��ת
		HAL_GPIO_WritePin(R_Bin1_GPIO,R_Bin1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(R_Bin2_GPIO,R_Bin2_Pin,GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(Motor_370_Right_TIM,Motor_370_Right_Channel,-Duty);
	}
}

//��������ռ�ձ�(��ת)	
//��Χ��-16800,+16800��

void Motor_370_L(int Duty)
{
	if(Duty > 16800 && Duty < -16800)
		Duty = 0;
	if(Duty > 0)
	{
			//370(��)��ת
		      HAL_GPIO_WritePin(L_Ain1_GPIO,L_Ain1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(L_Ain2_GPIO,L_Ain2_Pin,GPIO_PIN_SET);
		__HAL_TIM_SetCompare(Motor_370_Left_TIM,Motor_370_Left_Channel,Duty);			
	}
	else
	{
			//370(��)��ת      
		     HAL_GPIO_WritePin(L_Ain1_GPIO,L_Ain1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(L_Ain2_GPIO,L_Ain2_Pin,GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(Motor_370_Left_TIM,Motor_370_Left_Channel,-Duty);
	}
}
//直接给三个轮子  //左侧轮子的方向为逆反，其他两个为正
void Motor_370_respectively(int f_Duty,int r_Duty,int l_Duty)
{
	//在底层进行限幅
	if(f_Duty>12000){f_Duty=12000;}
	if(f_Duty<-12000){f_Duty=-12000;}
	if(r_Duty>12000){r_Duty=12000;}
	if(r_Duty<-12000){r_Duty=-12000;}
	if(l_Duty>12000){l_Duty=12000;}
	if(l_Duty<-12000){l_Duty=-12000;}
			Motor_370_F(f_Duty);
			Motor_370_L(-l_Duty);
			Motor_370_R(r_Duty);


}

void Motor_370_respectively_turn(int f_Duty,int r_Duty,int l_Duty)
{
	//在底层进行限幅
			Motor_370_F(f_Duty);
			Motor_370_L(-l_Duty);
			Motor_370_R(r_Duty);


}


	
