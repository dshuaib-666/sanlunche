#ifndef __PID_COUNTER_H
#define __PID_COUNTER_H

#include "PID.h"
 #include "MPU9250.h"
 #include "MOTOR_COUNTER.h"
 #include "MOTOR.h"
 #include <math.h>
 #include "LED.h"
void TURN_PID(float expect_yaw,int F_speed,int R_speed,int L_speed);

void YAW_PID(int speed,float yaw);

 void turn_sport_pid(int speed,float yaw,int turn_speed);
#endif
