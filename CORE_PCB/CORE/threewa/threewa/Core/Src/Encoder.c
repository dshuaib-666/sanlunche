 #include "Encoder.h"
 
       
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start_IT(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start_IT(&htim5,TIM_CHANNEL_ALL);	
	HAL_TIM_Encoder_Start_IT(&htim8,TIM_CHANNEL_ALL);
	
	__HAL_TIM_ENABLE_IT(&htim2,TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&htim5,TIM_IT_UPDATE);//ҠëǷא׏ߪǴ
	__HAL_TIM_ENABLE_IT(&htim8,TIM_IT_UPDATE);//ҠëǷא׏ߪǴ
}

int Read_Speed(TIM_HandleTypeDef *htim)
{ 
	
	int temp;
	temp=(short)__HAL_TIM_GetCounter(htim);
	__HAL_TIM_SetCounter(htim,0);
	return temp;
	
}

void READ_SPEED(float *Encoder_front,float *Encoder_Left,float *Encoder_Right)
{  	*Encoder_Left=0;
	*Encoder_Right=0;
    *Encoder_front=0;
	*Encoder_Left=-Read_Speed(&htim5);
	*Encoder_Right=-Read_Speed(&htim8);
	*Encoder_front=-Read_Speed(&htim2);
}


void X_Y_Pulse_sum(float *Encoder_front_sum,float *Encoder_Left_sum,float *Encoder_Right_sum)
{
	static int  Encoder_Left=0;
	static int Encoder_Right=0;
   	static int  Encoder_front=0;
	Encoder_Left=-Read_Speed(&htim5);
	Encoder_Right=-Read_Speed(&htim8);
	Encoder_front=-Read_Speed(&htim2);
    
	*Encoder_front_sum=Encoder_front+*Encoder_front_sum;
	*Encoder_Left_sum=Encoder_Left+*Encoder_Left_sum;
	*Encoder_Right_sum=Encoder_Right+*Encoder_Right_sum;
}

