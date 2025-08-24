#ifndef _mpu9250_h
#define _mpu9250_h
#include <stdio.h>
#include <stdint.h>

typedef struct mpu6500
{
		float yaw;//偏航角
        float pitch;//俯仰角
        float roll;//横滚
		float yaw_current;//角度值，范围-180 - 180	
		float yaw_w;//v speed
		float yaw_v;
		float yaw_current_angle;//弧度制
}mpu6500;
 void MPU6500_DATA_INIT(void);
void Mpu6050_init(void);
void Mpu6050_get_data(int16_t *gx, int16_t *gy,int16_t *gz, int16_t *ax,int16_t *ay, int16_t *az,int16_t*temperature);


#endif
