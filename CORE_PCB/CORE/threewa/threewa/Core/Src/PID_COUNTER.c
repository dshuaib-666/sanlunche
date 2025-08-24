#include "PID_COUNTER.h"

extern mpu6500 mpu6500_Data;


float yaw_bias=0;
float speed_bias=0;

 int f_motor=0,l_motor=0,r_motor=0;
 extern int16_t gz;
 int LED_TIM=0;
void TURN_PID(float expect_yaw,int F_speed,int R_speed,int L_speed)
{
  if(gz==0) {LED_TIM++; if(LED_TIM>100){LED_TogglePin(); LED_TIM=0;} return ;}
 
  yaw_bias=expect_yaw - mpu6500_Data. yaw_current;//get bias
  speed_bias=position_pid_for_turn(yaw_bias);
//  f_motor=speed_bias*(F_speed/16000.0f)*8;
//  l_motor=speed_bias*(R_speed/16000.0f)*8;
 // r_motor=speed_bias*(L_speed/16000.0f)*8;
	if(((expect_yaw - mpu6500_Data. yaw_current)>=180)||((expect_yaw - mpu6500_Data. yaw_current)<=-180))
	{
	f_motor=-speed_bias*(F_speed/16000.0f)*8;
	l_motor=-speed_bias*(R_speed/16000.0f)*8;
	r_motor=-speed_bias*(L_speed/16000.0f)*8;

	} 
	if(((expect_yaw - mpu6500_Data. yaw_current)<180)&&((expect_yaw - mpu6500_Data. yaw_current)>-180))
	{
	f_motor=speed_bias*(F_speed/16000.0f)*8;
	l_motor=speed_bias*(R_speed/16000.0f)*8;
	r_motor=speed_bias*(L_speed/16000.0f)*8;

	} 
	
	
  Motor_370_respectively(f_motor,r_motor,l_motor);
}
 #define pi 	3.14159f
extern  float v_x1=0.0f,v_y1=0.0f;
float yaw_bias1=0.0f;
int speed_bias1=0;
#define car_long 0.18
void YAW_PID(int speed,float yaw)
{
  static int f_motor=0,l_motor=0,r_motor=0;
   yaw=yaw*pi/180.0f;
    v_x1=speed*sin(yaw);
    v_y1=speed*cos(yaw);
//    f_motor=v_x1-mpu6500_Data.yaw_w*car_long*50.0f*(pi/180.0f);
//    r_motor=v_x1/2-v_y1*0.866f-mpu6500_Data.yaw_w*car_long*50.0f*(pi/180.0f);  
//    l_motor=v_x1/2-v_y1*0.866f+mpu6500_Data.yaw_w*car_long*50.0f*(pi/180.0f); 
		f_motor=v_x1-mpu6500_Data.yaw_w*car_long*50.0f*(pi/180.0f)*700;
		r_motor=-v_x1/2+v_y1*0.866f-mpu6500_Data.yaw_w*car_long*50.0f*(pi/180.0f)*700;
		l_motor=-v_x1/2-v_y1*0.866f-mpu6500_Data.yaw_w*car_long*50.0f*(pi/180.0f)*700;
   // yaw_bias1= 0-  mpu6500_Data. yaw_current;///GET BIAS
    
//    speed_bias1=position_pid_for_yaw(yaw_bias1);
//    f_motor=f_motor-speed_bias1;
//    l_motor=r_motor-speed_bias1;
//    r_motor=r_motor-speed_bias1;

	Motor_370_respectively(f_motor,r_motor,l_motor);
	//TURN_PID(0,f_motor,r_motor,l_motor);
//    Motor_370_respectively(f_motor,r_motor,l_motor);

	
}

void turn_sport_pid(int speed,float yaw,int turn_speed)
{
	static float next_yaw;
	static int speed_f,speed_l,speed_r;
	next_yaw=yaw-mpu6500_Data.yaw_current;
	             next_yaw=next_yaw*pi/180.0f;
				v_x1=speed*sin(next_yaw);
    			v_y1=speed*cos(next_yaw);

		speed_f=v_x1				+	turn_speed;
		speed_r=-v_x1/2+v_y1*0.866f	+	turn_speed;
		speed_l=-v_x1/2-v_y1*0.866f	+	turn_speed;
	Motor_370_respectively_turn(speed_f,speed_r,speed_l);

}
