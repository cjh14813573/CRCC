#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

signed int DBMaxVot[6]={0};
signed int DBMinVot[6]={0};

void calculate_each_group(int groupNum,int maxNum,signed int *DBMaxVot,signed int *DBMinVot,int voltage,int dbaddr)
{
	DBMaxVot[groupNum-1]=(DBMaxVot[groupNum-1]>voltage)?DBMaxVot[groupNum-1]:voltage;
	DBMinVot[groupNum-1]=(DBMinVot[groupNum-1]<voltage)?DBMinVot[groupNum-1]:voltage;
	if(dbaddr==maxNum-1)
	{
		int data=DBMaxVot[groupNum-1]-DBMinVot[groupNum-1];
		gs_NewDataMng.fSetCData(BATTERY_DEVICE,groupNum,DATA,&data);
		gs_EventMng.fJudgeAI(BATTERY_DEVICE,groupNum,data,AlarmStat.battery_alarm_flag[groupNum],500);
	}
}

void calculate_voltage_difference(int voltage,int dbaddr,unsigned char *DBcfg)
{
	if(dbaddr<DBcfg[1])//第一组
	{
		calculate_each_group(1,DBcfg[1],DBMaxVot,DBMinVot,voltage,dbaddr);
	}
	else if(dbaddr<DBcfg[1]+DBcfg[2])//第二组
	{
		calculate_each_group(2,DBcfg[1]+DBcfg[2],DBMaxVot,DBMinVot,voltage,dbaddr);
	}
	else if(dbaddr<DBcfg[1]+DBcfg[2]+DBcfg[3])//第三组
	{
		calculate_each_group(3,DBcfg[1]+DBcfg[2]+DBcfg[3],DBMaxVot,DBMinVot,voltage,dbaddr);
	}
	else if(dbaddr<DBcfg[1]+DBcfg[2]+DBcfg[3]+DBcfg[4])//第四组
	{
		calculate_each_group(4,DBcfg[1]+DBcfg[2]+DBcfg[3]+DBcfg[4],DBMaxVot,DBMinVot,voltage,dbaddr);
	}
	else if(dbaddr<DBcfg[1]+DBcfg[2]+DBcfg[3]+DBcfg[4]+DBcfg[5])//第五组
	{
		calculate_each_group(5,DBcfg[1]+DBcfg[2]+DBcfg[3]+DBcfg[4]+DBcfg[5],DBMaxVot,DBMinVot,voltage,dbaddr);
	}
	else if(dbaddr<DBcfg[1]+DBcfg[2]+DBcfg[3]+DBcfg[4]+DBcfg[5]+DBcfg[6])//第六组
	{
		calculate_each_group(6,DBcfg[1]+DBcfg[2]+DBcfg[3]+DBcfg[4]+DBcfg[5]+DBcfg[6],DBMaxVot,DBMinVot,voltage,dbaddr);
	}
}


void DataBlock(void)
{
	unsigned char dbaddr=0;
	unsigned short crc;
	unsigned short feeddog;
	int time_flag;
	int data;
	int data_status;
	unsigned char db_sendbuft[30];
	unsigned char db_time_alarm[192]={0};
	unsigned char DBcfg[7];
	int db_flag=1,fd,DB_nwrite,DB_nread,db_scan_flag=10,db_db_flag;
	unsigned char dbmergebuff[255];
	int status,iRtn;
	gs_RTUcfgMng.Getcfg(RTU_DB_NUM,&DBcfg[0]);

	while(db_flag!=0)
	{
		fd=OpenDev(comTASK.db[0]);
		set_speed(fd,comTASK.db[1]);
		set_Parity(fd,comTASK.db[2],comTASK.db[4],comTASK.db[3]); 
		if(DBcfg[0]>0)
		{
			switch(db_scan_flag)
			{
				case 10:
					ioctl(fd, TIOCSERGETLSR, &iRtn);     
					ioctl(fd,TIOCMGET,&status);
					status&=~TIOCM_RTS;
					ioctl(fd,TIOCMSET,&status);			
					db_sendbuft[0]=(dbaddr+1);
					db_sendbuft[1]=0x03;
					db_sendbuft[2]=0x00;
					db_sendbuft[3]=0x01;
					db_sendbuft[4]=0x00;
					db_sendbuft[5]=0x03;
					crc=cal_crc(&db_sendbuft[0],6);
					db_sendbuft[7]=(crc&0xff); 
					db_sendbuft[6]=((crc>>8)&0xff);
					DB_nwrite=write(fd,db_sendbuft,8);	
					iRtn = 0;
					while(!iRtn)
					{
						ioctl(fd, TIOCSERGETLSR, &iRtn);
					} 
					ioctl(fd,TIOCMGET,&status);
					status|=TIOCM_RTS;
					ioctl(fd,TIOCMSET,&status);
					db_db_flag=10;
					break;
			
				case 11:
					ioctl(fd, TIOCSERGETLSR, &iRtn);     
					ioctl(fd,TIOCMGET,&status);
					status&=~TIOCM_RTS;
					ioctl(fd,TIOCMSET,&status);		
					db_sendbuft[0]=(dbaddr+1);
					db_sendbuft[1]=0x06;
					db_sendbuft[2]=0x00;
					db_sendbuft[3]=0x0C;
					db_sendbuft[4]=0xF0;
					db_sendbuft[5]=0xF0;
					crc=cal_crc(&db_sendbuft[0],6);
					db_sendbuft[7]=(crc&0xff); 
					db_sendbuft[6]=((crc>>8)&0xff);
					DB_nwrite=write(fd,db_sendbuft,8);
					iRtn = 0;
					while(!iRtn)
					{
						ioctl(fd, TIOCSERGETLSR, &iRtn);
						printf("%d",iRtn);
					}
					ioctl(fd,TIOCMGET,&status);
					status|=TIOCM_RTS;
					ioctl(fd,TIOCMSET,&status);
					db_db_flag=11;
					break;
			
				default:
					break;
			}
			sleep(1);
			memset(dbmergebuff,0,255);
			DB_nread=read(fd,dbmergebuff,255);	
			if(DB_nread>6)
			{
				db_time_alarm[dbaddr]=0;
				crc=cal_crc(&dbmergebuff[0],DB_nread-2);
				if(crc!=0&&((crc&0xff)==dbmergebuff[DB_nread-1])&&(((crc>>8)&0xff)==dbmergebuff[DB_nread-2]))
				{
					switch(db_db_flag)
					{
						case 10:
							//电压
							data=(dbmergebuff[3]*256+dbmergebuff[4])/100;
							gs_NewDataMng.fSetCData(BATTERY_DEVICE,11+dbaddr*4,DATA,&data);
							gs_EventMng.fJudgeAI(BATTERY_DEVICE,11+dbaddr*4,data,AlarmStat.battery_alarm_flag[11+dbaddr*4],500);
							calculate_voltage_difference(data,dbaddr,DBcfg);

							//温度
							data=(dbmergebuff[5]*256+dbmergebuff[6]);
							gs_NewDataMng.fSetCData(BATTERY_DEVICE,12+dbaddr*4,DATA,&data);
							gs_EventMng.fJudgeAI(BATTERY_DEVICE,12+dbaddr*4,data,AlarmStat.battery_alarm_flag[12+dbaddr*4],500);

							//内阻
							data=(dbmergebuff[7]*256+dbmergebuff[8])/10;
							gs_NewDataMng.fSetCData(BATTERY_DEVICE,13+dbaddr*4,DATA,&data);
							gs_EventMng.fJudgeAI(BATTERY_DEVICE,13+dbaddr*4,data,AlarmStat.battery_alarm_flag[13+dbaddr*4],500);

							//是否读内阻
							gs_NewDataMng.fGetCData(BATTERY_DEVICE,BATTERY_READ_RESISTANCE,DATA,&data);
							if(data==1)
							{
								data=0;
								gs_NewDataMng.fSetCData(BATTERY_DEVICE,BATTERY_READ_RESISTANCE,DATA,&data);
								db_scan_flag=11;
								dbaddr=0;
							}
							break;
					
						default:
							break;
					}
				}
				else
					printf("\ndb check wrong %d\n",(dbaddr+1));
			}								
			else
			{
				db_time_alarm[dbaddr]++;
				printf("\ndb %d out of time\n",(dbaddr+1));  
			}
		}
		if(db_time_alarm[dbaddr]==0)
		{
			time_flag=0;
			gs_NewDataMng.fSetCData(BATTERY_DEVICE,14+dbaddr*4,DATA,&time_flag);
			gs_EventMng.fJudgeDI(BATTERY_DEVICE,14+dbaddr*4,time_flag,AlarmStat.battery_alarm_flag[14+dbaddr*4],500,ALARM_CONTENT_ALARM);
		}
		if(db_time_alarm[dbaddr]>=3)
		{
			db_time_alarm[dbaddr]=3;
			time_flag=1;
			gs_NewDataMng.fSetCData(BATTERY_DEVICE,14+dbaddr*4,DATA,&time_flag);
			gs_EventMng.fJudgeDI(BATTERY_DEVICE,14+dbaddr*4,time_flag,AlarmStat.battery_alarm_flag[14+dbaddr*4],500,ALARM_CONTENT_ALARM);
			data_status=0xff;
			gs_NewDataMng.fSetCData(BATTERY_DEVICE,11+dbaddr*4,STATUS,&data_status);
			gs_NewDataMng.fSetCData(BATTERY_DEVICE,12+dbaddr*4,STATUS,&data_status);
			gs_NewDataMng.fSetCData(BATTERY_DEVICE,13+dbaddr*4,STATUS,&data_status);
		} 
		dbaddr++;
		if(dbaddr>=(DBcfg[1]+DBcfg[2]+DBcfg[3]+DBcfg[4]+DBcfg[5]+DBcfg[6])) // 全部采集完   重新开始
		{
			dbaddr=0;
			db_scan_flag=10;
		}
		SelfTest.fGetSelftest(6,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{feeddog=0;}
		SelfTest.fSetSelftest(6,&feeddog);
		close(fd);
		sleep(1);	
	}
}	  
