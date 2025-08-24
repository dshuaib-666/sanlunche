#include "MOTOR_COUNTER.H"
#include "math.h"
#include "MOTOR.h"
 #define pi 	3.14159f
//原地旋转
void MOTOR_SPORT_turn(int speed)
{
 Motor_370_respectively  (speed,speed,-speed);
}

void MOTOR_SPORT_fnort(int speed)
{
   
    float yaw_angle_R=(0.0f+30.0f)*pi/180;
    float yaw_angle_L=(0.0f-30.0f)*pi/180;
     int F_SPEED=0,R_SPEED=speed/cos(yaw_angle_R),L_SPEED=speed/cos(yaw_angle_L);
     Motor_370_respectively(F_SPEED,R_SPEED,L_SPEED);




}

 float v_x=0.0f,v_y=0.0f;
 float v_a=0.0f,v_b=0.0f,v_c=0.0f;

void MOTOR_SPORT(int speed,float yaw)
{
    yaw=yaw*pi/180;
    v_x=speed*sin(yaw);
    v_y=speed*cos(yaw);
    v_a=v_x;
    v_b=v_x/2+v_y*0.866f;  
    v_c=v_x/2+v_y*0.866f; 
    Motor_370_respectively(v_a,v_b,v_c);




}

