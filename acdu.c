#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"


void ACDU(void)
{
unsigned short feeddog;
int i,ACDU_flag=1;
int fd,nwrite,nread;
unsigned char ACDU_time_alarm[6];
unsigned char ACDUaddr=0,ACDU_rec_flag=0;
unsigned char sendbuf[8],buff[40],recbuff[40],ASCIIbuff[40];
unsigned char ACDU_START=0,ACDU_END=0;
unsigned char len,ACDU_receive_time=0;
int sumac;
int connection_status;
int data_status;
sendbuf[0]=0x23;
sendbuf[1]=0x30;
sendbuf[2]=0x31;
sendbuf[3]=0x41;   
sendbuf[4]=0x0d;
sendbuf[5]=0x0a;
int status,iRtn;

//初始化acdu数据
//电压值初始化为0，状态为无效
//通信状态初始化为断开，状态为有效
sumac=0;
data_status=0xff;
for(i=1;i<=ACDU_SIZE;i++)
{
	gs_NewDataMng.fSetCData(ACDU_DEVICE,i,DATA,&sumac);
	gs_NewDataMng.fSetCData(ACDU_DEVICE,i,STATUS,&data_status);
}
connection_status=0;
data_status=0;
gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_CONNECTION_1,DATA,&connection_status);
gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_CONNECTION_1,STATUS,&data_status);
gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_CONNECTION_2,DATA,&connection_status);
gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_CONNECTION_2,STATUS,&data_status);

while(ACDU_flag!=0)
{  
	sendbuf[2]=0x31+ACDUaddr;
	fd = OpenDev(comTASK.ACDU[0]);
	set_speed(fd,comTASK.ACDU[1]);
	set_Parity(fd,comTASK.ACDU[2],comTASK.ACDU[4],comTASK.ACDU[3]);
	memset(recbuff,0,40);
	ioctl(fd, TIOCSERGETLSR, &iRtn);     	       
	ioctl(fd,TIOCMGET,&status);
	status&=~TIOCM_RTS;
	ioctl(fd,TIOCMSET,&status);	
	nwrite=write(fd,sendbuf,6);
	printf("\nACDU_nwrite=%d\n",nwrite);
	iRtn = 0;
	ioctl(fd,TIOCMGET,&status);
	status|=TIOCM_RTS;
	ioctl(fd,TIOCMSET,&status);
	ACDU_receive_time=0;
	len=0;
	ACDU_END=0;
	ACDU_START=0;
	ACDU_rec_flag=0;
	while (ACDU_END==0&&ACDU_receive_time<7) 
	{
		if((nread=read(fd,buff,30))>0)
		{
			ACDU_rec_flag=1;
			for(i=0;i<nread;i++)
			{
				if((buff[i]==0x3E)&&(ACDU_START==0))
				{
					ACDU_START=1;
					len=1;
					recbuff[0]=0x3E;
					continue;
				}
				if(ACDU_START==1)
				{
					recbuff[len++]=buff[i];
				}  
				if(len>=30) 
				{
					ACDU_END=1;ACDU_START=0;break;
				}
				else
					continue;
			}
		}
		else
		{
			sleep(1);
			SelfTest.fGetSelftest(0,&feeddog);
			feeddog++;
			if(feeddog>65530)
			{feeddog=0;}
			SelfTest.fSetSelftest(0,&feeddog);
			ACDU_receive_time++;
		}
	}  

	if(ACDU_receive_time<6||ACDU_rec_flag==1)
	{
		ACDU_time_alarm[ACDUaddr]=0;
		for(i=1;i<30;i++) 
		{
			if ((recbuff[i])<0x41)
			ASCIIbuff[i]=recbuff[i]&0x0f;
			else
			ASCIIbuff[i]=recbuff[i]-0x41+10;
		}
		sumac=ASCIIbuff[1]*4096+ASCIIbuff[2]*256+ASCIIbuff[3]*16+ASCIIbuff[4];
		sumac=sumac/10; 
		gs_NewDataMng.fSetCData(ACDU_DEVICE,1+ACDUaddr*4,DATA,&sumac);
		printf("\nACDU NUM%d V1=%d  %dn",ACDUaddr,sumac,ASCIIbuff[1]);
		gs_EventMng.fJudgeAI(ACDU_DEVICE,1+ACDUaddr*4,sumac,AlarmStat.acdu_alarm_flag[1+ACDUaddr*4],60);

		sumac=ASCIIbuff[5]*4096+ASCIIbuff[6]*256+ASCIIbuff[7]*16+ASCIIbuff[8];
		sumac=sumac/10; 
		gs_NewDataMng.fSetCData(ACDU_DEVICE,2+ACDUaddr*4,DATA,&sumac);
		printf("\nACDU NUM%d V2=%d\n",ACDUaddr,sumac);
		gs_EventMng.fJudgeAI(ACDU_DEVICE,2+ACDUaddr*4,sumac,AlarmStat.acdu_alarm_flag[2+ACDUaddr*4],66);


		sumac=ASCIIbuff[9]*4096+ASCIIbuff[10]*256+ASCIIbuff[11]*16+ASCIIbuff[12];
		sumac=sumac/10; 
		gs_NewDataMng.fSetCData(ACDU_DEVICE,3+ACDUaddr*4,DATA,&sumac);
		printf("\nACDU NUM%d V3=%d\n",ACDUaddr,sumac);
		gs_EventMng.fJudgeAI(ACDU_DEVICE,3+ACDUaddr*4,sumac,AlarmStat.acdu_alarm_flag[3+ACDUaddr*4],72);
		
	}
	else 
	{
		ACDU_time_alarm[ACDUaddr]++;
		printf("\nACDU %d out of time\n",(ACDUaddr+1));
	}              

	if(ACDU_time_alarm[ACDUaddr]==0)
	{
		//通信正常
		connection_status=1;
		gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_CONNECTION_1+ACDUaddr*4,DATA,&connection_status);
		gs_EventMng.fJudgeDI(ACDU_DEVICE,ACDU_CONNECTION_1+ACDUaddr*4,connection_status,AlarmStat.acdu_alarm_flag[ACDU_CONNECTION_1+ACDUaddr*4],80,ALARM_CONTENT_ALARM);
	}	
	if(ACDU_time_alarm[ACDUaddr]>=5)
	{
		//通信断开，相应模块数据值的数据状态写成0xff,通信状态的数据状态写成alarmLevel
		ACDU_time_alarm[ACDUaddr]=5;
		connection_status=0;
		gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_CONNECTION_1+ACDUaddr*4,DATA,&connection_status);
		gs_EventMng.fJudgeDI(ACDU_DEVICE,ACDU_CONNECTION_1+ACDUaddr*4,connection_status,AlarmStat.acdu_alarm_flag[ACDU_CONNECTION_1+ACDUaddr*4],80,ALARM_CONTENT_ALARM);
		data_status=0xff;
		for(i=1;i<=3;i++)
		{
			gs_NewDataMng.fSetCData(ACDU_DEVICE,i+ACDUaddr*4,STATUS,&data_status);
		}
	} 
	sleep(1);
	close(fd);
	if(ACDUaddr+1<comTASK.ACDU[6]) 
		ACDUaddr++;
	else
		ACDUaddr=0;
	SelfTest.fGetSelftest(0,&feeddog);
	feeddog++;
	if(feeddog>65530)
	{feeddog=0;}
	SelfTest.fSetSelftest(0,&feeddog);
}
}	    
