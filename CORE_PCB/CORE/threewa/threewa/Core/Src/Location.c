#include "Location.h"

float sa4=0.0f,sa5=0.0f,sa6=0.0f;
float sa_x=0.0f,sa_y=0.0f;
 #define pi 	3.14159f
 #define car_wheel 0.027f //轮子半径
extern mpu6500 mpu6500_Data;
float Encoder_X=0.0f,Encoder_Y=0.0f; //编码器得到的值
float slip_f=0.0f,slip_l=0.0f,slip_r=0.0f;//打滑系数
 float Encoder_F_V=0.0f, Encoder_L_V=0.0f,Encoder_R_V=0.0f;

void X_Y_count(float *X,float *Y)
{           
   
       
       
        READ_SPEED(&Encoder_F_V,&Encoder_L_V,&Encoder_R_V);
        sa4=car_wheel*2.0f*pi*Encoder_F_V/1365.0f;
        sa5=car_wheel*2.0f*pi*Encoder_L_V/1365.0f;
        sa6=car_wheel*2.0f*pi*Encoder_R_V/1365.0f;

       // Encoder_F_V=


        sa_x=-sa4+sa5/2.0f+sa6/2.0f;
        sa_y=-sa5/0.866f+sa6/0.866f;    
        mpu6500_Data.yaw_current_angle=(mpu6500_Data.yaw_current*pi)/180.0f;
        
		mpu6500_Data.yaw_v=mpu6500_Data.yaw_current_angle* car_wheel;
	
		
        Encoder_Y=(sa_y*cos(mpu6500_Data.yaw_current_angle)+sa_x*sin(mpu6500_Data.yaw_current_angle))*100.0f+Encoder_Y;
        Encoder_X=(sa_x*cos(mpu6500_Data.yaw_current_angle)-sa_y*sin(mpu6500_Data.yaw_current_angle))*100.0f+Encoder_X;




} 

