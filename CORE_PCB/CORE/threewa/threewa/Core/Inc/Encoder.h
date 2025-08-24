#ifndef __Encoder_H
#define __Encoder_H


#include "tim.h"
#include "gpio.h"

void Encoder_Init(void);
 int Read_Speed(TIM_HandleTypeDef *htim);
 void READ_SPEED(float *Encoder_front,float *Encoder_Left,float *Encoder_Right);
void X_Y_Pulse_sum(float *Encoder_front_sum,float *Encoder_Left_sum,float *Encoder_Right_sum);
#endif

