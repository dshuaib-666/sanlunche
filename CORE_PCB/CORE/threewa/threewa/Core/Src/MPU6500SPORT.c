#include "MPU6500SPORT.h"
#include "stdint.h"
#include "filter.h"
#include <math.h>
#include "MPU9250.h"

#include "Location.h"
extern mpu6500 mpu6500_Data;
 int16_t gx, gy, gz=0, ax ,ay, az, temperature;
 float temp;
extern float Encoder_F_V, Encoder_L_V,Encoder_R_V; 
int ax_sum=0,ay_sum=0;
      int z_sta=0;
	    float ax_zero=0.0f,ay_zero=0.0f;
	  float z_zero=0;
	   int z_stat=0;
void MPU6500_READ(void)
{
	
  static  float gz_deta=0,vg_deta=0;
  
  int16_t GX_OFFSET = 0x00;
  int16_t AX_OFFSET = 0x00;
  int16_t AY_OFFSET = 0x00;
  int16_t AZ_OFFSET = 0x00;
		
		
  static float  angle_dot ,f_angle_dot;  //f_angle������ angle�M�L
//  static int ax_ay_sta=0 ;
  

        gz=0;
  
  
  

         Mpu6050_get_data(&gx,&gy,&gz,&ax,&ay,&az,&temperature);
		 acc_filter();
	
		 temp=36.53+((double)temperature)/340;
			gx -= GX_OFFSET;//?????��??
			ax -= AX_OFFSET;
			ay -= AY_OFFSET;
			az -= AZ_OFFSET;         
	 
	 if(z_sta<=30)
	   {z_zero+=gz;
	   z_sta++;
	   
		   if(z_sta>=20&&z_sta<=30)
		   {    ax_zero+=ax;
				ay_zero+=ay;
		   
		   }
		   
	   }

	    if(z_sta>30&&z_stat==0) {z_zero=z_zero/31.0f;z_stat=1;
		ax_zero=ax_zero/11.0f; ay_zero=ay_zero/11.0f;
		}
			if(z_stat==1)
			{ 
				ay=ay-ay_zero;
				ax=ax-ax_zero;
				 gz= gz-z_zero;
				mpu6500_Data.yaw_w=vg_deta*GYRO_SCALE;
	   vg_deta=(((float)gz)-z_zero);
	   if(vg_deta>=-10&&vg_deta<=10){vg_deta=0;}
	   gz_deta=vg_deta*GYRO_SCALE *0.02f;
	   mpu6500_Data.yaw=gz_deta+mpu6500_Data.yaw; 
			  angle_dot = -gy * GYRO_SCALE;  //+-2000  0.060975 ?/LSB
		mpu6500_Data.pitch = atan(ax / sqrt(ay * ay + az * az ));//??????
		mpu6500_Data.pitch = mpu6500_Data.pitch * 57.295780f;    //180/pi
		kalman_filter(mpu6500_Data.pitch, angle_dot, &mpu6500_Data.roll, &f_angle_dot);
		
			} 
	  
	}


	 
	 

   

        
		


