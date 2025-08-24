#ifndef __MOTOR_H
#define __MOTOR_H

  #include "stm32f1xx.h"                  // Device header
#include "tim.h"
#include "gpio.h"
   
//TIMͨ����ʼ������
                                      
#define Motor_370_Front_TIM			&htim3	
#define Motor_370_Front_Channel		     TIM_CHANNEL_4

#define Motor_370_Right_TIM			&htim3
#define Motor_370_Right_Channel			TIM_CHANNEL_3
                                      
#define Motor_370_Left_TIM			&htim4	
#define Motor_370_Left_Channel		     TIM_CHANNEL_3
	

//��������ת����

#define F_Ain1_GPIO		GPIOC
#define F_Ain1_Pin		 GPIO_PIN_3

#define F_Ain2_GPIO		GPIOB
#define F_Ain2_Pin		  GPIO_PIN_11

#define R_Bin1_GPIO		GPIOB
#define R_Bin1_Pin		 GPIO_PIN_15

#define R_Bin2_GPIO		GPIOB
#define R_Bin2_Pin		 GPIO_PIN_12
                          
#define L_Ain1_GPIO		GPIOD
#define L_Ain1_Pin		 GPIO_PIN_2

#define L_Ain2_GPIO		GPIOC
#define L_Ain2_Pin		  GPIO_PIN_2
                          

void MOTOR_Init(void);
void Motor_370_F(int Duty);

void Motor_370_R(int Duty);

void Motor_370_L(int Duty);
void Motor_370_respectively(int f_Duty,int r_Duty,int l_Duty);

 void Motor_370_respectively_turn(int f_Duty,int r_Duty,int l_Duty);






#endif
