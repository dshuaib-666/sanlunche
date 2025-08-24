#include "SPORT.h"
#include "NRF_COUNTER.h"
#include "PID_COUNTER.h"
#include "NRF.h"
extern struct NRF_BUFFER NBF_BUFF;  //定义一个结构体来接收数据 
void SPORT(void)
{    NRF_dispose();
	if(NBF_BUFF.satus==1||NBF_BUFF.satus==2||NBF_BUFF.satus==3||NBF_BUFF.satus==4)
    { NRF_Location_spin();}
    //if()
	
   
   

}
