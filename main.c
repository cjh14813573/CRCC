/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : main.c
 *  CREATOR  : RTU Team                 DATE: 2008-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/
#include "stdsys.h"
#include <sys/types.h>
#include "task.h"
#include "typedef.h"
#include "main.h"
#include "property.h"

struct task M500FTask;
struct task TcpipTask;
struct task AirControlTask;
struct task DataBlockTask;
struct task ComserTask;
struct task ModemTask;
struct task AutoModemTask;
struct task AIMeasureTask;
struct task DIMeasureTask;
struct task DOMeasureTask;
struct task lcdTask;
struct task selftestTask;
struct task upstask;
struct task ACDUTask;
struct task FLTask;
//struct task AccessTask;
//struct task sqlTask;
int com7=0;
extern int flag16;
extern int flag27;

int main(void)
{
	init_alarm();
	init_SelfTest();
	init_gs_EventMng();
	init_gs_AirControlDataMng();
	init_gs_pwalarmMng();
	init_gs_cfgMng();
	init_gs_DOMng();
	init_serialport();
	init_gs_NewDataMng();
	init_property();
	TaskCreat(&selftestTask, "self_test", (void*)Self_Test);    
	TaskCreat(&lcdTask,"tasklcd",(void*)lcd);
	TaskCreat(&AIMeasureTask, "AIMeasures", (void*)AIMeasure);
	TaskCreat(&DIMeasureTask, "DIMeasures", (void*)DIMeasure);
	TaskCreat(&DOMeasureTask, "DOMeasures", (void*)DOMeasure);
	//TaskCreat(&AccessTask, "access", (void*)Access);
	printf("\n%d,%d,%d 222222",comTASK.IC[0],comTASK.sb[0],comTASK.db[0]);
	if(comTASK.IC[0]!=0xff)  //  ·ÀÀ×
	{
		if(comTASK.IC[0]==7)
	   	{
			com7=1;
			flag27=0;
	   	}
		else
		{
	   		com7=0;
			flag27=1;
		}
		TaskCreat(&FLTask, "access", (void*)Access);
	}
	if((comTASK.mn[0]==0xff)&&(comTASK.sb[0]==0xff))
	{
		TaskCreat(&TcpipTask, "Tcpipserver", (void*)Tcpipser);
	}
	if(comTASK.pw[0]!=0xff)
	{
	  TaskCreat(&M500FTask, "M500F", (void*)M500F);//choose pw model
	}
	if(comTASK.ac[0]!=0xff)
	{
		TaskCreat(&AirControlTask,"AirControl",(void*)AirCon); 
	}
	if(comTASK.ACDU[0]!=0xff)
	{
		TaskCreat(&ACDUTask,"acdu",(void*)ACDU);
	}
	if(comTASK.UPS[0]!=0xff)
	{
		TaskCreat(&upstask, "ups", (void*)UPS);//choose pw model
	}
	if(comTASK.db[0]!=0xff)
	{
		TaskCreat(&DataBlockTask,"DataBlock",(void*)DataBlock);
	}
	while(1)
		sleep(1);
}
