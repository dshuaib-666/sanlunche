#include "NRF_COUNTER.h"
 #define pi 	3.14159265358979
extern struct NRF_BUFFER NBF_BUFF;  //定义一个结构体来接收数据 
extern uint8_t Receive[33]; 
void NRF_BUFFER_Init(void)
{
	NBF_BUFF.one=2040;	
	NBF_BUFF.two=2040;	
	for(int k=0;k<=10;k++)
	{
	     Receive[k]=102;
	
	}
	for(int k=20;k<=32;k++)
	{
	     Receive[k]=0;
	
	}
}
int sa_yaw1=0;
int sa_yaw2=0;
float yaw1=0;
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
int sa_yaw3=0;
int sa_yaw4=0;
float yaw2=0;
int motor_left2=0;
void NRF_sport_Right(void)
{
   NRF_dispose();//接收摇杆的数据
  if ((NBF_BUFF.two>1500)&&(NBF_BUFF.two<2500)){NBF_BUFF.two=2040;}
  if ((NBF_BUFF.one>2000)&&(NBF_BUFF.one<2100)){NBF_BUFF.one=2040;}
  sa_yaw3= 90*(NBF_BUFF.one-2040)/2064;
	  	sa_yaw4= 90*(NBF_BUFF.two-2040)/2184;
	  yaw2=-(atan2(sa_yaw3,sa_yaw4)*180.0 / pi);
	  if(yaw2<-180&yaw2>-270){yaw2=yaw2+360;}
	  if(yaw2>180||yaw2<-180){yaw2=0;}	
		
		 //sa_bete=atan2 (NBF_BUFF.three,NBF_BUFF.four);
		
		motor_left2= (((((NBF_BUFF.one-2040)/20)*(NBF_BUFF.one-2040)/20) +((NBF_BUFF.four-2040)/20)*((NBF_BUFF.four-2040)/20))*2)/3;
       
  

}

 
