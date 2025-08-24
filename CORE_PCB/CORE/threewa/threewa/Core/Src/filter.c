#include "filter.h"
#include "MPU9250.h"

#include <math.h>
#include <stdio.h>

static float angle, angle_dot; 
#define FILTER_COUNT  16
int16_t gx_buf[FILTER_COUNT], ax_buf[FILTER_COUNT], ay_buf[FILTER_COUNT],az_buf[FILTER_COUNT];
extern int16_t temp, gx, gy, gz, ax ,ay, az, temperature;
const float Q_angle = 0.002, Q_gyro = 0.002, R_angle = 0.5, dt = 0.01;			
static float P[2][2]={
				       { 1, 0 },
			           { 0, 1 }
			         };	
static float Pdot[4] = {0, 0, 0, 0};
const uint8_t C_0 = 1;
static float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1; 

/************************************************
功能：陀螺仪数据与加速度计数据通过滤波算法融合
输出参数：滤波后的角度与角速度
************************************************/
void kalman_filter(float angle_m, float gyro_m, float *angle_f, float *angle_dot_f)			
{
  angle += (gyro_m - q_bias) * dt;
	
  Pdot[0]  =Q_angle - P[0][1] - P[1][0];
  Pdot[1] = -P[1][1];
  Pdot[2] = -P[1][1];
  Pdot[3] = Q_gyro;
	
  P[0][0] += Pdot[0] * dt;
  P[0][1] += Pdot[1] * dt;
  P[1][0] += Pdot[2] * dt;
  P[1][1] += Pdot[3] * dt;
	
  angle_err = angle_m - angle;
	
  PCt_0=C_0 * P[0][0];
  PCt_1=C_0 * P[1][0];
	
  E = R_angle + C_0 * PCt_0;
	
  K_0 = PCt_0 / E;
  K_1 = PCt_1 / E;
	
  t_0 = PCt_0;
  t_1 = C_0 * P[0][1];

  P[0][0] -= K_0 * t_0;
  P[0][1] -= K_0 * t_1;
  P[1][0] -= K_1 * t_0;
  P[1][1] -= K_1 * t_1;
		
  angle	+= K_0 * angle_err;
  q_bias += K_1 * angle_err;
  angle_dot = gyro_m - q_bias;

  *angle_f = angle;
  *angle_dot_f = angle_dot;
}



void acc_filter(void)//加速度滤波
{
  uint8_t i;
  int32_t ax_sum = 0, ay_sum = 0, az_sum = 0; 
  for(i = 1 ; i < FILTER_COUNT; i++)
  {
    ax_buf[i - 1] = ax_buf[i];
		ay_buf[i - 1] = ay_buf[i];
		az_buf[i - 1] = az_buf[i];
  }
  ax_buf[FILTER_COUNT - 1] = ax;
  ay_buf[FILTER_COUNT - 1] = ay;
  az_buf[FILTER_COUNT - 1] = az;
  for(i = 0 ; i < FILTER_COUNT; i++)
  {
    ax_sum += ax_buf[i];
		ay_sum += ay_buf[i];
		az_sum += az_buf[i];
  }
  ax = (int16_t)(ax_sum / FILTER_COUNT);
  ay = (int16_t)(ay_sum / FILTER_COUNT);
  az = (int16_t)(az_sum / FILTER_COUNT);
}


