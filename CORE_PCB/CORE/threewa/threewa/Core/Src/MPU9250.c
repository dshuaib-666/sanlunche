#include "MPU9250.h"
#include "i2c.h"

mpu6500 mpu6500_Data; //将DMA的数据存入这个数组里
#define MPU6500_ADDR       0xd0    //IIC写入，读入时的地址字节数据，找到这个就不用0x68了
#define CONFIG             0x1a   //配置数字低通滤波器
#define GYRO_CONFIG        0x1b  //角速度陀螺仪配置寄存器
#define ACCEL_CONFIG       0x1c	 //加速度计配置寄存器
#define INT_PIN_CFG        0x37  //bypass mode
#define MPU6500_BURST_ADDR 0x3b   //读取值得首地址，三轴加速度的值
#define USER_CTRL          0x6a	     
#define PWR_MGMT1          0x6b	 //电源管理寄存器1    
#define PWR_MGMT2          0x6c  //电源寄存器2，使加速度计陀螺仪工作
#define MPU6500_ID_ADDR	   0x75
#define MPU6500_ID	       0x68

void Mpu6050_init(void)
{  
	
    uint8_t data_buf = 0;

    // 设置为Bypass模式
    data_buf = 0x02;
    HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDR, INT_PIN_CFG, I2C_MEMADD_SIZE_8BIT, &data_buf, 1, 10000);
    HAL_Delay(50);
    // 清除所有传感器寄存器
    data_buf = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDR, USER_CTRL, I2C_MEMADD_SIZE_8BIT, &data_buf, 1, 10000);
     HAL_Delay(50);
    // 解除休眠状态，唤醒MPU6500
    data_buf = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDR, PWR_MGMT1, I2C_MEMADD_SIZE_8BIT, &data_buf, 1, 10000);
    HAL_Delay(50);
    // 设置陀螺仪和加速度计的滤波器
    data_buf = 0x06;
    HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDR, CONFIG, I2C_MEMADD_SIZE_8BIT, &data_buf, 1, 10000);
   HAL_Delay(50);
    // 设置陀螺仪量程为±2000度/秒
    data_buf = 0x18;
    HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDR, GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &data_buf, 1, 10000);
    HAL_Delay(50);
    // 设置加速度计量程为±8g
    data_buf = 0x08;
    HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDR, ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &data_buf, 1, 10000);
  HAL_Delay(50);
}

void Mpu6050_get_data(int16_t *gx, int16_t *gy,int16_t *gz, int16_t *ax,int16_t *ay, int16_t *az,int16_t*temperature)
{
	 uint8_t data_buf[14]; 
	  HAL_I2C_Mem_Read(&hi2c1,MPU6500_ADDR,MPU6500_BURST_ADDR,I2C_MEMADD_SIZE_8BIT,&data_buf[0],14,10000);
	  //高把位低八位 0x100=1*16*16+0*16+0*1=256
	  //数据传输时先传输高8位，再传输低八位，所以0是高位
		*ax = data_buf[0] * 0x100 + data_buf[1];// 
		*ay = data_buf[2] * 0x100 + data_buf[3];
		*az = data_buf[4] * 0x100 + data_buf[5];//
		*temperature = data_buf[6] * 0x100 + data_buf[7];//
		*gx = data_buf[8] * 0x100 + data_buf[9];
		*gy = data_buf[10] * 0x100 + data_buf[11];
		*gz = data_buf[12] * 0x100 + data_buf[13];//
	
	
	
	if( mpu6500_Data.yaw<0){
   mpu6500_Data. yaw_current=(mpu6500_Data.yaw+((int)(mpu6500_Data.yaw/-360))*360)+(((int)((mpu6500_Data.yaw+((int)(mpu6500_Data.yaw/-360))*360)/-180))*360);
	}
 if(mpu6500_Data.yaw>0)
  {
   mpu6500_Data. yaw_current=(mpu6500_Data.yaw-360*(int)(mpu6500_Data.yaw/360))-((int)((mpu6500_Data.yaw-360*(int)(mpu6500_Data.yaw/360))/180))*360;
  }
}

void MPU6500_DATA_INIT(void)
{
	mpu6500_Data.pitch=0;
	mpu6500_Data.roll=0;
	mpu6500_Data.yaw=0;
	mpu6500_Data.yaw_current=0;
	mpu6500_Data.yaw_v= 0;
  mpu6500_Data.yaw_w= 0;
}




