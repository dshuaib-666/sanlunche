#ifndef __MPU9250_H
#define __MPU9250_H



#include "i2c.h"
#include "stdint.h"
 
#define MPU9250_RA_INT_ENABLE       0x38
#define MPU9250_RA_PWR_MGMT_1       0x6B
#define MPU9250_RA_GYRO_CONFIG      0x1B
#define MPU9250_RA_ACCEL_CONFIG     0x1C
#define MPU9250_RA_CONFIG           0x1A
#define MPU9250_RA_SMPLRT_DIV       0x19
#define MPU9250_RA_INT_PIN_CFG      0x37
 
//设置低通滤波
#define MPU9250_DLPF_BW_256         0x00
#define MPU9250_DLPF_BW_188         0x01
#define MPU9250_DLPF_BW_98          0x02
#define MPU9250_DLPF_BW_42          0x03
#define MPU9250_DLPF_BW_20          0x04
#define MPU9250_DLPF_BW_10          0x05
#define MPU9250_DLPF_BW_5           0x06
 
#define MPU9250_RA_ACCEL_XOUT_H     0x3B
 
#define MPU9250_RA_TEMP_OUT_H       0x41
 
#define MPU9250_RA_GYRO_XOUT_H      0x43

//MPU9250内部封装了一个AK8963磁力计,地址和ID如下:
#define AK8963_ADDR			0X0C	//AK8963的I2C地址
#define AK8963_ID			0X48	//AK8963的器件ID
//AK8963的内部寄存器
#define MAG_WIA				0x00	//AK8963的器件ID寄存器地址
#define MAG_XOUT_L			0X03
void MPU9250_Init(void);

void Read_Accel_Data(float *ax, float *ay, float *az); 

void Read_Gyro_Data(float *gx, float *gy, float *gz) ;

void Read_Mag_Data(float *mx, float *my, float *mz) ;

#endif
