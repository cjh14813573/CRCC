#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

void Airmessageswitch(unsigned char length,unsigned char *Air_message,unsigned char *Air_sendbuf)
{
	int Air_send_i=1,Air_len;
	for(Air_len=1;Air_len<length;Air_len++)
	{
		if(*(Air_message+Air_len)==0x7d||*(Air_message+Air_len)==0X7e||*(Air_message+Air_len)<0x20)
		{
			*(Air_sendbuf+Air_send_i)=0x7d;
			*(Air_sendbuf+Air_send_i+1)=*(Air_message+Air_len)^0x20;
			Air_send_i+=2;
		}
		else
		{
			*(Air_sendbuf+Air_send_i)=*(Air_message+Air_len);
			Air_send_i++;
		}
	}
	*Air_sendbuf=0x7e;
}


int readairbuf(char fd,unsigned char *mergebuff,int *length,int *time)
{
	unsigned short feeddog;
	unsigned char buff[1024]={0};
	int pw_START=0,pw_END=0,nread,len=0,i,time_rec=0,read_flag=0;
	while (pw_END==0&&time_rec<7) 
	{
		if((nread=read(fd,buff,1024))>0)
		{ 
			read_flag=1;
			for(i=0;i<nread;i++)
			{
				if((buff[i]==0x7e)&&(pw_START==0)) 
				{
					pw_START=1;
					len=0;
				}
				if(pw_START==1)
				{
					mergebuff[len]=buff[i];
				}
				if(mergebuff[len]==0x0d||len>500) 
				{
					pw_END=1;
					len++;
					break;
				}
				len++;
			}
		}
		else    
		{
			sleep(1);
			time_rec++;
			SelfTest.fGetSelftest(5,&feeddog);
			feeddog++;
			if(feeddog>65530)
			{feeddog=0;}
			SelfTest.fSetSelftest(5,&feeddog);
		}
	}
	*length=len;
	*time=time_rec;
	return(read_flag);
}


void AirCon(void)  
{
	unsigned char notify_alarm_status[165]={0};
	unsigned short feeddog;
	int Air_nwrite,Air_nread=0,*outtimeaddr,outtime;
	outtimeaddr=&outtime;
	Event_TypeDef *AirMarkEvent;
	Event_TypeDef Air_Alarm_Table[1];
	AirMarkEvent=Air_Alarm_Table;
	unsigned char ControlToReport[8]={2,4,32,8,0,0,0,0};
	unsigned char Function[]={0,8,8,0x9,0xb,0xb,0xa,7};//Function[]={0x0,8,8,0x0b,0xc,0xa,0x9};                              
	unsigned char Airchecksum,Air_ii,Air_con_flag,Air_addr=0,sign7d,fd,Air_con_alarm_flag=0,air_receive_time,air_i,air_START=0,air_END=0,air_receive_len=0,air_alarm=0,Air_flag=1;;
	signed short Air_Alarmmessage,air_receive_buff1,air_receive_buff2;
	unsigned short air_receive_buff;
	unsigned char air_message[7],air_setcommand[4],air_send_buffer[20],airbuff[20]={0},airmergebuff[30]={0};
	fd = OpenDev(comTASK.ac[0]);
	printf("air~~~~~~~~~%d~~~~",fd);
	set_speed(fd,comTASK.ac[1]);
	set_Parity(fd,comTASK.ac[2],comTASK.ac[4],comTASK.ac[3]);
	int status;
	ioctl(fd,TIOCMGET,&status);
	status&=~TIOCM_RTS;
	ioctl(fd,TIOCMSET,&status);
	//GetAlarmStat(2,&notify_alarm_status[0]);
	Air_con_alarm_flag=notify_alarm_status[0];//超时标记与告警标记同步
	while(Air_flag!=0)
	{
		if(Air_con_alarm_flag==0)
		{
			air_receive_buff1=0;
			gs_NewDataMng.fSetNewData(135,&air_receive_buff1);	
			if(notify_alarm_status[0]==1)
			{      
				notify_alarm_status[0]=0;
				AirMarkEvent->ID=31;
				AirMarkEvent->Name=1;
				AirMarkEvent->Flag=0;
				AirMarkEvent->Value=0;
				if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
				printf("\nset event Ok");
				else printf("set event nok");
			}	   
			Air_con_alarm_flag=0;
		}	
		if(Air_con_alarm_flag==1)
		{
			air_receive_buff1=1;
			gs_NewDataMng.fSetNewData(135,&air_receive_buff1);	
			if(notify_alarm_status[0]==0)
			{      
				notify_alarm_status[0]=1;
				AirMarkEvent->ID=31;
				AirMarkEvent->Name=1;
				AirMarkEvent->Flag=1;
				AirMarkEvent->Value=10;
				if(gs_EventMng.fSetEvent(AirMarkEvent)==TRUE)
				printf("\nset event Ok");
				else printf("set event nok");
			}	    
		}
		gs_AirControlMng.AirConGetData(7,&Air_con_flag);
		gs_AirControlMng.AirConGetData(5,&Air_addr);
		if(Air_addr==1)
		{
			switch(Air_con_flag)
			{
				case 0xf2:	
					air_message[0]=0x7e;
					air_message[1]=0;
					gs_AirControlMng.AirConGetData(5,&air_setcommand[0]);
					gs_AirControlMng.AirConGetData(6,&air_setcommand[1]);
					gs_AirControlMng.AirConGetData(3,&air_setcommand[2]);
					air_message[2]=0;
					air_message[3]= air_setcommand[1];
					if((air_setcommand[2]&0x80)==0x80) 
					{
						air_setcommand[3]=24;
						air_setcommand[2]=7;
					}
					else
					{	
						gs_AirControlMng.AirConGetData(4,&air_setcommand[3]);
					}
					air_message[4]=Function[air_setcommand[2]]|((air_setcommand[3]-16)<<4);
					air_message[5]=0x0;
					Airchecksum=0;
					for(Air_ii=1;Air_ii<6;Air_ii++)
					{
						Airchecksum=Airchecksum+air_message[Air_ii];
					}
					air_message[6]=Airchecksum;
					Airmessageswitch(7,&air_message[0],&air_send_buffer[0]); 
					Air_nwrite=write(fd,air_send_buffer,strlen(air_send_buffer));
					printf("\n#11 send");unsigned int i;
					for(i=0;i<strlen(air_send_buffer);i++)
					{
						printf("\n%x #### ",air_send_buffer[i]);
						printf(" ");
					}
					memset(air_send_buffer,0,20);
					break;  

				case 0xf1:
					air_message[0]=0x7e;
					air_message[1]=0x00;
					air_message[2]=0x00;
					air_message[3]=0xf1;
					air_message[4]=0x00;
					air_message[5]=0x00;
					Airchecksum=0;
					for(Air_ii=1;Air_ii<6;Air_ii++)
					{
						Airchecksum=Airchecksum+air_message[Air_ii];
					}
					air_message[6]=Airchecksum;
					Airmessageswitch(7,&air_message[0],&air_send_buffer[0]); 
					Air_nwrite=write(fd,air_send_buffer,strlen(air_send_buffer));//sizeof(air_send_buffer)
					printf("\n+++33++++++++++AIR FI FI FI\n");
					memset(air_send_buffer,0,20);
					break;

				default:
					break;
			}
			switch(Air_con_flag)
			{
				case 0xf2:
					sign7d=0;
					air_receive_time=0;
					air_END=0;
					air_receive_len=0;
					while (air_END==0&&air_receive_time<7) 
					{
						if((Air_nread=read(fd,airbuff,7))>0)
						{
							printf("%d\n%x",Air_con_flag,Air_nread);
							Air_con_alarm_flag=0;
							for(air_i=0;air_i<Air_nread;air_i++)
							{ 
								if((airbuff[air_i]==0x7e)&&(air_START==0))
								{
									air_START=1;
									air_receive_len=1;
									airmergebuff[0]=0x7e;
									continue;
								}
								if(air_START==1&&airbuff[air_i]==0x7d)
								{
									sign7d=1;
									continue;
								}
								if(sign7d==1)
								{
									airmergebuff[air_receive_len++]=(airbuff[air_i]^0x20);
									sign7d=0;
									if(air_receive_len==7) 
									{
										air_END=1;
										air_START=0;
										break;
									}
									continue;
								}
								if((airbuff[air_i]!=0x7d)&&(sign7d==0))
								{
									airmergebuff[air_receive_len++]=airbuff[air_i];
								}
								if(air_receive_len==7) 
								{
									air_END=1;
									air_START=0;
									break;
								}
								else
									continue;
							}
						}
						else
						{
							sleep(1);
							SelfTest.fGetSelftest(5,&feeddog);
							feeddog++;
							if(feeddog>65530)
							{feeddog=0;}
							SelfTest.fSetSelftest(5,&feeddog);
							air_receive_time++;
						}
					}  
					printf("\nairairairair\n");int i;
					for(i=0;i<air_receive_len;i++)
					{
						printf("%x",airmergebuff[i]);
						printf(" ");
					}
					if(air_receive_time<7)
					{      
						Airchecksum=0;
						Air_con_flag=0xff;
						gs_AirControlMng.AirConSetData(7,&Air_con_flag); 
						for(Air_ii=1;Air_ii<6;Air_ii++)
						{
							Airchecksum=Airchecksum+airmergebuff[Air_ii];
						}
						if(Airchecksum==airmergebuff[6])
						{
							printf("\nAircon 0xf2 check ok!!!");
						}
						else
							printf("\nAircon 0xf2 wrong");
					}
					else  
					{  
						Air_con_alarm_flag=1;
						printf("\nout time");
					}
					air_START=0;
					air_END=0;
					memset(airbuff,0,20);
					memset(airmergebuff,0,30);
					sleep(3);
					break;

				case 0xf1:
					sign7d=0;
					air_receive_time=0;
					air_receive_len=0;
					air_END=0;
					while (air_END==0&&air_receive_time<7) 
					{
						if((Air_nread=read(fd,airbuff,7))>0)
						{
							printf("%x,%d\n",Air_con_flag,Air_nread);
							Air_con_alarm_flag=0;
							for(air_i=0;air_i<Air_nread;air_i++)
							{ 
								if((airbuff[air_i]==0x7e)&&(air_START==0))
								{
									air_START=1;
									air_receive_len=1;
									airmergebuff[0]=0x7e;
									continue;
								}
								if(air_START==1&&airbuff[air_i]==0x7d)
								{
									sign7d=1;
									continue;
								}
								if(sign7d==1)
								{
									airmergebuff[air_receive_len++]=(airbuff[air_i]^0x20);
									sign7d=0;
									if(air_receive_len==7) 
									{
										air_END=1;
										air_START=0;
										break;
									}
									continue;
								}
								if((airbuff[air_i]!=0x7d)&&(sign7d==0))
								{
									airmergebuff[air_receive_len++]=airbuff[air_i];
								}
								if(air_receive_len==7) 
								{
									air_END=1;
									air_START=0;
									break;
								}
								else
									continue;
							}
						}
						else {
						sleep(1);
						SelfTest.fGetSelftest(5,&feeddog);
						feeddog++;
						if(feeddog>65530)
						{feeddog=0;}
						SelfTest.fSetSelftest(5,&feeddog);
						air_receive_time++;
						}
					}  
					if(air_receive_time<7)
					{	
						int qq;for(qq=0;qq<7;qq++)
						{
							printf("%x",airmergebuff[qq]);
							printf(" ");
						}
						printf("\n");
						Air_con_flag=0xff;
						gs_AirControlMng.AirConSetData(7,&Air_con_flag); 
						Airchecksum=0;
						for(Air_ii=1;Air_ii<6;Air_ii++)
						{
							Airchecksum=Airchecksum+airmergebuff[Air_ii];
						}
						printf("%d",Airchecksum);
						if(Airchecksum==airmergebuff[6])
						{
							printf("\nAircon 0xf1 check ok!!!");
							air_receive_buff=airmergebuff[4];
							air_receive_buff=(air_receive_buff<<8)|airmergebuff[5];
							gs_AirControlMng.AirConSetData(2,&air_receive_buff);
						}
						else
						{
							printf("\nAircon 0xf1 wrong");
						}
					}
					else
					{
						printf("\nout time");
						Air_con_alarm_flag=1;
					}
					air_START=0;
					air_END=0;
					memset(airbuff,0,20);
					memset(airmergebuff,0,30);
					sleep(1);
					break;     


				default:
					break;
			}
		}
		air_message[0]=0x7e;
		air_message[1]=0;
		air_message[2]=0;
		air_message[3]=0xf0;
		air_message[4]=0x0;
		air_message[5]=0x0;
		Airchecksum=0;
		for(Air_ii=1;Air_ii<6;Air_ii++)
		{
			Airchecksum=Airchecksum+air_message[Air_ii];
		}
		air_message[6]=Airchecksum;
		Airmessageswitch(7,&air_message[0],&air_send_buffer[0]); 
		Air_nwrite=write(fd,air_send_buffer,sizeof(air_send_buffer));
		memset(air_send_buffer,0,20);
		sign7d=0;
		air_receive_time=0;
		air_receive_len=0;
		air_END=0;
		while (air_END==0&&air_receive_time<7) 
		{
			if((Air_nread=read(fd,airbuff,7))>0)
			{
				Air_con_alarm_flag=0;
				for(air_i=0;air_i<Air_nread;air_i++)
				{ 
					if((airbuff[air_i]==0x7e)&&(air_START==0))
					{
						air_START=1;
						air_receive_len=1;
						airmergebuff[0]=0x7e;
						continue;
					}
					if(air_START==1&&airbuff[air_i]==0x7d)
					{
						sign7d=1;
						continue;
					}
					if(sign7d==1)
					{
						airmergebuff[air_receive_len++]=(airbuff[air_i]^0x20);
						sign7d=0;
						if(air_receive_len==7) 
						{
							air_END=1;
							air_START=0;
							break;
						}
						continue;
					}
					if((airbuff[air_i]!=0x7d)&&(sign7d==0))
					{
						airmergebuff[air_receive_len++]=airbuff[air_i];
					}
					if(air_receive_len==7) 
					{
						air_END=1;
						air_START=0;
						break;
					}
					else
						continue;
				}
			}
			else
			{
				sleep(1);
				SelfTest.fGetSelftest(5,&feeddog);
				feeddog++;
				if(feeddog>65530)
				{feeddog=0;}
				SelfTest.fSetSelftest(5,&feeddog);
				air_receive_time++;
			}
		}  
		printf("\n");int i;
		for(i=0;i<air_receive_len;i++)
		{
			printf("%x",airmergebuff[i]);
			printf(" ");
		}
		if(air_receive_time<7)
		{
			Airchecksum=0;
			for(Air_ii=1;Air_ii<6;Air_ii++)
			{
				Airchecksum=Airchecksum+airmergebuff[Air_ii];
			}
			if(Airchecksum==airmergebuff[6])
			{
				printf("\nAircon 0xf0 check ok!!!");
				air_receive_buff=0;
				air_receive_buff=airmergebuff[3];
				gs_AirControlMng.AirConSetData(0,&air_receive_buff);
				air_receive_buff=0;//airmergebuff[5];
				gs_AirControlMng.AirConSetData(1,&air_receive_buff);
				if((airmergebuff[4]&0x08)!=0)
				{
					air_receive_buff=0xffff;
					air_receive_buff=(air_receive_buff)&ControlToReport[airmergebuff[4]&0x07];
					//gs_DataMng.fGetData(46,&air_receive_buff1);
					air_receive_buff1=((air_receive_buff1&0xff00) |(air_receive_buff&0x00ff));
					//gs_DataMng.fSetData(46,&air_receive_buff1);
					if((air_receive_buff1&&0x02)==0x02)
					{
						air_receive_buff2=2;
						gs_NewDataMng.fSetNewData(133,&air_receive_buff2);
					}
					else if((air_receive_buff1&&0x02)==0x04)
					{
						air_receive_buff2=3;
						gs_NewDataMng.fSetNewData(133,&air_receive_buff2);
					}
					else
					{
						air_receive_buff2=1;
						gs_NewDataMng.fSetNewData(133,&air_receive_buff2);
					}
				}
				else
				{
					//gs_DataMng.fGetData(46,&air_receive_buff1);
					air_receive_buff=0xff09;
					air_receive_buff1=((air_receive_buff1&0xff00) |(air_receive_buff&0x00ff));
					//gs_DataMng.fSetData(46,&air_receive_buff1);
					air_receive_buff2=0;
					gs_NewDataMng.fSetNewData(133,&air_receive_buff2);
				}
				air_receive_buff=(airmergebuff[4]>>4)+16;
				//gs_DataMng.fGetData(4,&air_receive_buff1);
				air_receive_buff1=((air_receive_buff1&0xff00) |air_receive_buff);
				//gs_DataMng.fSetData(4,&air_receive_buff1);
				air_receive_buff=air_receive_buff*10;
				gs_NewDataMng.fSetNewData(134,&air_receive_buff);
			}
			else
			{
				printf("\nAircon 0xf0 wrong");
			}
		}
		else
		{
			Air_con_alarm_flag=1;
			printf("\nout of time"); 
		}
		air_START=0;
		air_END=0;
		air_receive_buff=0;
		air_receive_buff1=0;
		memset(airbuff,0,20);
		memset(airmergebuff,0,30);
		sleep(5);
		SelfTest.fGetSelftest(5,&feeddog);
		feeddog++;
		printf("~~~~~~~~~~~~~~))))%d",feeddog); 
		if(feeddog>65530)
		{feeddog=0;}
		SelfTest.fSetSelftest(5,&feeddog);
	}
}

