#25年三轮车

  电控：陈树泽
  
  结构：王家豪

该项目是25年1月份制作，当时技术经验上不足。

仅供参考，开源README的编写与代码时间间隔过长，已经忘记其中的具体联系了

仅开源电控部分(三轮车代码+PCB及遥控器代码+PCB)<br>
  
`电控`：
===
 
  这是我第一次尝试堆叠板，底层电源板，中间主控板，顶层分线板（连接电机）
  并且使用加长排母，作为板与板之间的信号传递及电源流动。加长排母开以保证板与板之间不会由于类似铝电容之类的高元器件挡住。

该代码的局限性在于不能使用编码器来计算当前的位置，我认为是打滑的问题。想要使用加速度计来计算，但由于买的是淘宝的二手MPU9050，质量差，加速度计是坏的，无法得到位置。（当时解算偏航角仅使用的陀螺仪。）

也就是仅停留在玩具阶段。
 
  核心主要在于三轮车的运行结算。网上的都是带矩阵的解算，我选择使用代数解算。
  核心代码
```

//直接给三个轮子  //左侧轮子的方向为逆反，其他两个为正
void Motor_370_respectively(int f_Duty,int r_Duty,int l_Duty)//规定正负
{
	//在底层进行限幅
	if(f_Duty>12000){f_Duty=12000;}
	if(f_Duty<-12000){f_Duty=-12000;}
	if(r_Duty>12000){r_Duty=12000;}
	if(r_Duty<-12000){r_Duty=-12000;}
	if(l_Duty>12000){l_Duty=12000;}
	if(l_Duty<-12000){l_Duty=-12000;}
			Motor_370_F(f_Duty);
			Motor_370_L(-l_Duty);
			Motor_370_R(r_Duty);


}
//输入目标方向，以及三个速度
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
//
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
//遥控控制
void NRF_Location_spin(void)
{
	static int  motor_right1;
      NRF_dispose();//接收摇杆的数据
		if ((NBF_BUFF.three>1940)&&(NBF_BUFF.three<1990)){NBF_BUFF.three=1960;}
		if ((NBF_BUFF.four>1800)&&(NBF_BUFF.four<1860)){NBF_BUFF.four=1840;}
		if ((NBF_BUFF.three>1940)&&(NBF_BUFF.three<1990)){NBF_BUFF.three=1960;}
		if ((NBF_BUFF.four>1800)&&(NBF_BUFF.four<1860)){NBF_BUFF.four=1840;}
		sa_yaw1= 90*(NBF_BUFF.three-1960)/2064;
	  	sa_yaw2= 90*(NBF_BUFF.four-1840)/2184;
		yaw1=(atan2(sa_yaw1,sa_yaw2)*180.0 / pi)-90;
		if(yaw1<-180&yaw1>-270){yaw1=yaw1+360;}
		if(yaw1>180||yaw1<-180){yaw1=0;}	
          motor_right1= (((((NBF_BUFF.three-1960)/20)*(NBF_BUFF.three-1960)/20) +((NBF_BUFF.four-1840)/20)*((NBF_BUFF.four-1840)/20))*2)/3;
       if(motor_right1<200){
	         yaw1=0;
	   }
		if(NBF_BUFF.satus==1)
        {TURN_PID(yaw1,4000,4000,4000);}
		if(NBF_BUFF.satus==2)
		{
			YAW_PID(motor_right1,yaw1);
		}
		if(NBF_BUFF.satus==3)
		{
			  if(motor_right1>200){
	            turn_sport_pid(10000,yaw1,12000);
					}
			  else{
			         turn_sport_pid(0,yaw1,12000);
			  }
		}
		if(NBF_BUFF.satus==4)
		{
			turn_sport_pid(motor_right1,yaw1,0);
		}

}
``` 

'运行效果'<br>
=
https://www.bilibili.com/video/BV1kMeEzbEZT/?spm_id_from=333.1387.homepage.video_card.click<br>








 

 

    
           
           
           
  

  

