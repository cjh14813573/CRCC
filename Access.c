#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

int flag16=0;
int flag27=0;
extern int UPS_flag;
extern int com7;
int Identification(unsigned long long lsum,char *str2)
{
	if((*str2==(char)(lsum&0x000000ff))&&(*(str2+1)==(char)((lsum>>8)&0x000000ff))&&(*(str2+2)==(char)((lsum>>16)&0x000000ff))&&(*(str2+3)==((lsum>>24)&0x000000ff)))
		return 0;
	else
		return 1;
}


void Access(void)
{/*
	unsigned char notify_alarm_status[165]={0};
	unsigned char aircon_alarm_status[155];
	unsigned short feeddog;
	int outtime,fd,Access_flag=1,fl_scan_flag=10,fl_db_flag=10;
	unsigned char AIRaddr=0;
	Event_TypeDef *AirMarkEvent;
	Event_TypeDef Air_Alarm_Table[1];
	AirMarkEvent=Air_Alarm_Table;
	unsigned int OrModal16[]={1,2,4,8,0x10,0x20,0x40,0x80,0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};                       
	signed short Air_Alarmmessage,air_receive_buff1;
	unsigned short air_receive_buff,airadd;
	unsigned char air_message[24],airbuff[256]={0},air_receive_bufftemp;
	unsigned short crc1=0,crc2=0,crc22=0,crc21=0,ALARM;
	int status,iRtn,nwrite,nread,Air_con_alarm_flag=0,sum,i,sum1,AIRTEMP;
	ioctl(fd,TIOCMGET,&status);
	status&=~TIOCM_RTS;
	ioctl(fd,TIOCMSET,&status);
	fd = OpenDev(comTASK.IC[0]);
	printf("\nACCSEE TASK=%d\n",fd);
	set_speed(fd,comTASK.IC[1]);
	set_Parity(fd,comTASK.IC[2],comTASK.IC[4],comTASK.IC[3]);

	while(Access_flag!=0)
	{  
		if(flag27==1)
		{
			switch (fl_scan_flag)
			{
				case 10:
					ioctl(fd,0x6001,0);     
					air_message[0]=0x01; 
					air_message[1]=0x02;
					air_message[2]=0x20;
					air_message[3]=0x01;
					air_message[4]=0x00;
					air_message[5]=0x12;
					crc1=cal_crc(&air_message[0],6);   
					air_message[7]=(crc1&0xff); 
					air_message[6]=((crc1>>8)&0xff);
					nwrite=write(fd,air_message,8);  
					iRtn = 0;
					while(!iRtn)
					{
						ioctl(fd, TIOCSERGETLSR, &iRtn);
						printf("%d",iRtn);
					} 
					ioctl(fd,0x6002,0);   
					fl_db_flag=10;
					break;

				case 11:
					ioctl(fd,0x6001,0);     
					air_message[0]=0x01; 
					air_message[1]=0x03;
					air_message[2]=0x30;
					air_message[3]=0x31;
					air_message[4]=0x00;
					air_message[5]=0x03;
					crc1=cal_crc(&air_message[0],6);   
					air_message[7]=(crc1&0xff); 
					air_message[6]=((crc1>>8)&0xff);
					nwrite=write(fd,air_message,8);  
					iRtn = 0;
					while(!iRtn)
					{
						ioctl(fd, TIOCSERGETLSR, &iRtn);
						printf("%d",iRtn);
					} 
					ioctl(fd,0x6002,0);   
					fl_db_flag=11;
					break;

				default:
					fl_scan_flag=10;
					break;
			}
			sleep(1);
			nread=read(fd,airbuff,255);
			if(nread>5)
			{
				ALARM=0;
				air_receive_buff1=0;
				gs_NewDataMng.fSetNewData(170,&air_receive_buff1);	
				if(aircon_alarm_status[106]==1)
				{      
					aircon_alarm_status[106]=0;
					AirMarkEvent->ID=106;
					AirMarkEvent->Name=1;
					AirMarkEvent->Flag=0;
					AirMarkEvent->Value=0;
					if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
						printf("\nset event Ok");
					else
						printf("set event nok");
				}
				crc1=cal_crc(&airbuff[0],nread-2);
				printf("\n @@@ FL CHECK ==  %x  , %x , %x \n",crc1,airbuff[nread-2],airbuff[nread-1]);
				if(crc1!=0&&((crc1&0xff)==airbuff[nread-1])&&(((crc1>>8)&0xff)==airbuff[nread-2]))
				{
					switch(fl_db_flag)
					{
						case 10:
							if((airbuff[4]&0x40)==0x40)    // 断一 路时告警
							{
								gs_NewDataMng.fGetNewData(161,&sum);	
								sum=(sum|0x04);
								gs_NewDataMng.fSetNewData(161,&sum);	
								if(aircon_alarm_status[147]==0)
								{      
									aircon_alarm_status[147]=1;
									AirMarkEvent->ID=147;
									AirMarkEvent->Name=1;
									AirMarkEvent->Flag=1;
									AirMarkEvent->Value=10;
									if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
										printf("\nset event Ok");
									else
										printf("set event nok");
								}
							}
							else
							{
								gs_NewDataMng.fGetNewData(161,&sum);	
								sum=(sum&0xfB);
								gs_NewDataMng.fSetNewData(161,&sum);	
								if(aircon_alarm_status[147]==1)
								{      
									aircon_alarm_status[147]=0;
									AirMarkEvent->ID=147;
									AirMarkEvent->Name=1;
									AirMarkEvent->Flag=0;
									AirMarkEvent->Value=0;
									if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
										printf("\nset event Ok");
									else 
										printf("set event nok");
								}
							}
							if((airbuff[4]&0x80)==0x80)    // 断二 路时告警
							{
								gs_NewDataMng.fGetNewData(161,&sum);	
								sum=(sum|0x08);
								gs_NewDataMng.fSetNewData(161,&sum);	
								if(aircon_alarm_status[148]==0)
								{      
									aircon_alarm_status[148]=1;
									AirMarkEvent->ID=148;
									AirMarkEvent->Name=1;
									AirMarkEvent->Flag=1;
									AirMarkEvent->Value=10;
									if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
										printf("\nset event Ok");
									else
										printf("set event nok");
								}
							}
							else
							{
								gs_NewDataMng.fGetNewData(161,&sum);	
								sum=(sum&0xf7);
								gs_NewDataMng.fSetNewData(161,&sum);	
								if(aircon_alarm_status[148]==1)
								{      
									aircon_alarm_status[148]=0;
									AirMarkEvent->ID=148;
									AirMarkEvent->Name=1;
									AirMarkEvent->Flag=0;
									AirMarkEvent->Value=0;
									if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
										printf("\nset event Ok");
									else
										printf("set event nok");
								}
							}
							fl_scan_flag++;
							break;

						case 11:
							sum=((airbuff[3]<<8)|airbuff[4]);  //  雷击次数
							gs_NewDataMng.fSetNewData(169,&sum);	
							sum=((airbuff[7]<<8)|airbuff[8]);  //  雷击电流   
							gs_NewDataMng.fSetNewData(168,&sum);	
							fl_scan_flag=10;
							break;
					}
				}
				else
				{
					printf(" FANGLEI  CHECK WRONG");
					fl_scan_flag=10;
				}
			}
			else
			{
				ALARM++;
				if(ALARM>6)
				{
					ALARM=7;
					air_receive_buff1=1;
					gs_NewDataMng.fSetNewData(170,&air_receive_buff1);	
					if(aircon_alarm_status[106]==0)
					{      
						aircon_alarm_status[106]=1;
						AirMarkEvent->ID=106;
						AirMarkEvent->Name=1;
						AirMarkEvent->Flag=1;
						AirMarkEvent->Value=10;
						if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
							printf("\nset event Ok");
						else
							printf("set event nok");
					}
				}
			}
			sleep(1);
			SelfTest.fGetSelftest(7,&feeddog);
			feeddog++;
			printf("~~~~~~~~~~~~~~))))%d",feeddog); 
			if(feeddog>65530)
			{feeddog=0;}
			SelfTest.fSetSelftest(7,&feeddog);
			if(com7==1)
			{
				UPS_flag=10;
				flag27=0;
			}
		}
	}
	close(fd);	*/
} 

