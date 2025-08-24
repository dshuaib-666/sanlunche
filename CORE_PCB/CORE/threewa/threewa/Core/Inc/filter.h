#ifndef _filter_h
#define _filter_h


#define	GYRO_SCALE 0.06097609f  

void kalman_filter(float angle_m, float gyro_m, float *angle_f, float *angle_dot_f);
void acc_filter(void);

#endif
