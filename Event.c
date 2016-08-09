#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "typedef.h"
#include "/home/lizh/mnt/yaffs/sqlite3/include/sqlite3.h"
char u[48];
char uu[140]={0},tt[140]={0};
unsigned char GetAlarmStat(unsigned short i, void *pDataBuf);

static int select_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
 
    for (i=0; i < argc; i ++)
    {
   //   printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		u[i]=(atoi(argv[i]));
    }
    
    printf("\n");
    return 0;
}
  
static MUTEX_T hMutexReadWriteEventArray=PTHREAD_MUTEX_INITIALIZER;
static unsigned char  SetEvent(void *pDataBuf)
{
	char temp[512]={0};
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char select=0;
	Event_TypeDef *pEvent;
	Event_TypeDef *pEventArray;  
	time_t timep;
	struct tm *p;
	time(&timep);
	int eve_num=0;
	char *s,ss[100]={0};//*alarm;
	s=ss;
	rc = sqlite3_open("/app/timealarm.db", &db); 
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	MutexLock(&hMutexReadWriteEventArray);
	p=localtime(&timep); 
	pEvent = (Event_TypeDef*)pDataBuf;
	
	pEventArray = &gs_EventMng.EventArray[gs_EventMng.SetEventNum];
	pEventArray->Type= 1;
	pEventArray->ID = pEvent->ID;
	pEventArray->Name = pEvent->Name;
	pEventArray->Flag = pEvent->Flag;
	pEventArray->Value= pEvent->Value;
	pEventArray->Device= pEvent->Device;
	pEventArray->Point= pEvent->Point;
	pEventArray->level= pEvent->level;
	pEventArray->AlarmLevel= pEvent->AlarmLevel;
	pEventArray->Content= pEvent->Content;
	printf("\nnow device=%d,point=%d,SetEventNum=%d,FUUUUUUUUCK the alarm event!!!!!!!!!!!!!!\n",pEventArray->Device,pEventArray->Point,gs_EventMng.SetEventNum);
	if(pEvent->Flag!=0)
	{
		pEventArray->SYearHigh =((int)((1900+p->tm_year)/100)); //pEvent->YearHigh;
		pEventArray->SYearLow =((1900+p->tm_year)%100); // pEvent->YearLow;
		pEventArray->SMonth =1+p->tm_mon;// pEvent->Month;
		pEventArray->SDay = p->tm_mday;//pEvent->Day;
		pEventArray->SHour = p->tm_hour;//pEvent->Hour;
		pEventArray->SMinute =p->tm_min;// pEvent->Minute;
		pEventArray->SSecond =p->tm_sec;// pEvent->Second;
		pEventArray->EYearHigh =0;
		pEventArray->EYearLow =0;
		pEventArray->EMonth =0;
		pEventArray->EDay =0;
		pEventArray->EHour =0;
		pEventArray->EMinute =0;  
		pEventArray->ESecond =0;
		sprintf(temp,"select count(*) from T1 where id=%d and device=%d and point=%d ",(pEvent->ID),(pEvent->Device),(pEvent->Point));
		rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		} 
		else
		{
			select=u[0];
		}
		if(select==0)
		{
			sprintf(temp,"insert into T1 values(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",(pEventArray->ID),(pEventArray->SYearHigh),(pEventArray->SYearLow),(pEventArray->SMonth),(pEventArray->SDay),(pEventArray->SHour),(pEventArray->SMinute),(pEventArray->SSecond),(pEventArray->Device),(pEventArray->Point));
			rc = sqlite3_exec(db, temp, 0, 0, &zErrMsg);
			if (rc == SQLITE_OK)
			{
				printf("\nOne record inserted SETEVENT T1 id=%d device=%d point=%d time=%d-%d-%d-%d-%d-%d-%d\n",(pEventArray->ID),(pEventArray->Device),(pEventArray->Point),(pEventArray->SYearHigh),(pEventArray->SYearLow),(pEventArray->SMonth),(pEventArray->SDay),(pEventArray->SHour),(pEventArray->SMinute),(pEventArray->SSecond));
			}
			else
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
		}
		else if(select==1)
		{
			sprintf(temp,"update T1 set yearh=%d,yearl=%d,month=%d,day=%d,hour=%d,minute=%d,sec=%d where id=%d and device=%d and point=%d",(pEventArray->SYearHigh),(pEventArray->SYearLow),(pEventArray->SMonth),(pEventArray->SDay),(pEventArray->SHour),(pEventArray->SMinute),(pEventArray->SSecond),(pEventArray->ID),(pEventArray->Device),(pEventArray->Point));
			rc = sqlite3_exec(db, temp, 0, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			} 
			else
			{
				printf("\n UPDATE SET EVENT OK --=- id=%d device=%d point=%d time=%d-%d-%d-%d-%d-%d-%d\n",(pEventArray->ID),(pEventArray->Device),(pEventArray->Point),(pEventArray->SYearHigh),(pEventArray->SYearLow),(pEventArray->SMonth),(pEventArray->SDay),(pEventArray->SHour),(pEventArray->SMinute),(pEventArray->SSecond));
			}
		}
	}
	else if(pEvent->Flag==0)
	{
		sprintf(temp,"select yearh,yearl,month,day,hour,minute,sec from T1 where id=%d and device=%d and point=%d",(pEvent->ID),(pEvent->Device),(pEvent->Point));
		rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			//	printf("\n START TIME SELECT WRONG!!!   %d\n",(pEvent->ID));
			pEventArray->SYearHigh =0;
			pEventArray->SYearLow =0;
			pEventArray->SMonth =0;
			pEventArray->SDay =0;
			pEventArray->SHour =0;
			pEventArray->SMinute =0;
			pEventArray->SSecond =0;
		} 
		else
		{
			pEventArray->SYearHigh =u[0];
			pEventArray->SYearLow =u[1];
			pEventArray->SMonth =u[2];
			pEventArray->SDay =u[3];
			pEventArray->SHour =u[4];
			pEventArray->SMinute =u[5];
			pEventArray->SSecond =u[6];
			printf("\n get the time form db:::::id=%d device=%d point=%d time=%d-%d-%d-%d-%d-%d-%d\n",(pEventArray->ID),(pEventArray->Device),(pEventArray->Point),(pEventArray->SYearHigh),(pEventArray->SYearLow),(pEventArray->SMonth),(pEventArray->SDay),(pEventArray->SHour),(pEventArray->SMinute),(pEventArray->SSecond));
		}
		pEventArray->EYearHigh =((int)((1900+p->tm_year)/100)); //pEvent->YearHigh;
		pEventArray->EYearLow =((1900+p->tm_year)%100); // pEvent->YearLow;
		pEventArray->EMonth =1+p->tm_mon;// pEvent->Month;
		pEventArray->EDay = p->tm_mday;//pEvent->Day;
		pEventArray->EHour = p->tm_hour;//pEvent->Hour;
		pEventArray->EMinute =p->tm_min;// pEvent->Minute;
		pEventArray->ESecond =p->tm_sec;// pEvent->Second;
	}
  
	gs_pwalarmMng.Getthre_val(RTU_log_NUM,&eve_num);
	if(eve_num>=EVENT_NUM)
	{
		eve_num=1;
		system("rm /app/log.txt");
		gs_pwalarmMng.Setthre_val(RTU_log_NUM,&eve_num);
	}
  
	gs_EventMng.SetEventNum++;
	if(gs_EventMng.SetEventNum >= EVENT_NUM)
	{
		gs_EventMng.SetEventNum = 0;
	}
  	
	sqlite3_close(db); 

	MutexUnlock(&hMutexReadWriteEventArray);
	return  TRUE;

}


static MUTEX_T hMutexReadWriteEventArray1=PTHREAD_MUTEX_INITIALIZER;
static unsigned  char  GetEvent(void *pDataBuf)
{
	
	char temp[512]={0};
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc,select=0;
	Event_TypeDef *pEvent;
	Event_TypeDef *pEventArray;
	MutexLock(&hMutexReadWriteEventArray1);
	pEvent = (Event_TypeDef*)pDataBuf;
	pEventArray = &gs_EventMng.EventArray[gs_EventMng.GetEventNum];
	if(pEventArray->Type == 0)
	{
		MutexUnlock(&hMutexReadWriteEventArray1);
		sqlite3_close(db); 
		return  FALSE;
	} 
	rc = sqlite3_open("/app/alarmlock.db", &db); 
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	printf("\n GET EVENT BEGIN ====---==-==%d, %d\n",(pEventArray->ID),(pEventArray->Name));

	sprintf(temp,"select count(*) from T3 where device=%d and point=%d and level=%d",(pEventArray->Device),(pEventArray->Point),(pEventArray->level));
	rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		printf("\n GET EVENT SELECT WRONG!!!   %d %d\n",(pEvent->Device),(pEventArray->Point));
	} 
	else
	{
		select=u[0];
		//	printf("\n GET SELECT RESULT -=====-==- %x\n",select);
	}
	if(select==0)
	{
		sprintf(temp,"insert into T3 values(%d,%d,%d,%d)",(pEventArray->Device),(pEventArray->Point),(pEventArray->level),(pEventArray->Flag));
		rc = sqlite3_exec(db, temp, 0, 0, &zErrMsg);
		if (rc == SQLITE_OK)
		{
			printf("One record inserted get EVENT T3 %d %d %d, %d",(pEventArray->Device),(pEventArray->Point),(pEventArray->level),(pEventArray->Flag));
		}
		else
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			printf("\n GET EVENT INSERT FAILD! -=====-==-\n");			
		}
	}
	else if(select==1)
	{
		sprintf(temp,"update T3 set flag=%d where device=%d and point=%d and level=%d",(pEventArray->Flag),(pEventArray->Device),(pEventArray->Point),(pEventArray->level));
		rc = sqlite3_exec(db, temp, 0, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		} 
		else
		{
			printf("\n UPDATE GET EVENT OK ---------=-==- %d %d %d %d\n",(pEventArray->Device),(pEventArray->Point),(pEventArray->level),(pEventArray->Flag));
		}
	}

	sqlite3_close(db); 

	pEvent->ID = pEventArray->ID;
	pEvent->Name= pEventArray->Name;
	pEvent->SYearHigh = pEventArray->SYearHigh;
	pEvent->SYearLow = pEventArray->SYearLow;
	pEvent->SMonth = pEventArray->SMonth;
	pEvent->SDay = pEventArray->SDay;
	pEvent->SHour = pEventArray->SHour;
	pEvent->SMinute = pEventArray->SMinute;
	pEvent->SSecond = pEventArray->SSecond;
	pEvent->EYearHigh = pEventArray->EYearHigh;
	pEvent->EYearLow = pEventArray->EYearLow;
	pEvent->EMonth = pEventArray->EMonth;
	pEvent->EDay = pEventArray->EDay;
	pEvent->EHour = pEventArray->EHour;
	pEvent->EMinute = pEventArray->EMinute;
	pEvent->ESecond = pEventArray->ESecond;
	pEvent->Flag = pEventArray->Flag;
	pEvent->Value= pEventArray->Value;
	pEvent->Device= pEventArray->Device;
	pEvent->Point= pEventArray->Point;
	pEvent->Content= pEventArray->Content;
	pEventArray->level= pEvent->level;
	pEvent->AlarmLevel= pEventArray->AlarmLevel;
	pEventArray->Type= 0; 

	printf("\nnow device=%d,point=%d,GETeventnum=%d,FUUUUUUUUUUCK the alarmEvent\n",pEvent->Device,pEvent->Point,gs_EventMng.GetEventNum);
	gs_EventMng.GetEventNum++;
	if(gs_EventMng.GetEventNum >= EVENT_NUM)
	{
		gs_EventMng.GetEventNum = 0;
	}

	MutexUnlock(&hMutexReadWriteEventArray1);

	return  TRUE;
}


EventMng_TypeDef gs_EventMng;
int Event_i;
void judgeAI(short int device, short int point,int value, signed char *alarm_status, int alarmId)
{
	Event_TypeDef event;
	alarmId=(alarmId-1)*6;
	int alarm_level=gs_ProMng.Pro[device][point].Alarmlevel;
	int alarm_enable=gs_ProMng.Pro[device][point].AlarmEnable;
	if(*(alarm_status+1-1)==ALARM_FLAG_HIGH_START)//一级过高告警中
	{
		if(value<gs_ProMng.Pro[device][point].HiLimit1*10)//一级过高告警恢复
		{
			event.ID=alarmId;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_END;
		}
		if(value<gs_ProMng.Pro[device][point].HiLimit2*10)//二级过高告警恢复
		{
			event.ID=alarmId+1;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_END;
		}
		if(value<gs_ProMng.Pro[device][point].HiLimit3*10)//三级过高告警恢复
		{
			event.ID=alarmId+2;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_END;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit3*10&&alarm_enable)//三级过低告警
		{
			event.ID=alarmId+3;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit2*10&&alarm_enable)//二级过低告警
		{
			event.ID=alarmId+4;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit1*10&&alarm_enable)//一级过低告警
		{
			event.ID=alarmId+5;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_LOW_START;
		}
	}
	else if(*(alarm_status+2-1)==ALARM_FLAG_HIGH_START)//二级过高告警中
	{
		if(value>=gs_ProMng.Pro[device][point].HiLimit1*10&&alarm_enable)//一级过高告警
		{
			event.ID=alarmId;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_HIGH_START;
		}
		if(value<gs_ProMng.Pro[device][point].HiLimit2*10)//二级过高告警恢复
		{
			event.ID=alarmId+1;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_END;
		}
		if(value<gs_ProMng.Pro[device][point].HiLimit3*10)//三级过高告警恢复
		{
			event.ID=alarmId+2;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_END;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit3*10&&alarm_enable)//三级过低告警
		{
			event.ID=alarmId+3;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit2*10&&alarm_enable)//二级过低告警
		{
			event.ID=alarmId+4;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit1*10&&alarm_enable)//一级过低告警
		{
			event.ID=alarmId+5;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_LOW_START;
		}
	}
	else if(*(alarm_status+3-1)==ALARM_FLAG_HIGH_START)//三级过高告警中
	{
		if(value>=gs_ProMng.Pro[device][point].HiLimit1*10&&alarm_enable)//一级过高告警
		{
			event.ID=alarmId;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit2*10&&alarm_enable)//二级过高告警
		{
			event.ID=alarmId+1;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_HIGH_START;
		}
		if(value<gs_ProMng.Pro[device][point].HiLimit3*10)//三级过高告警恢复
		{
			event.ID=alarmId+2;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_END;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit3*10&&alarm_enable)//三级过低告警
		{
			event.ID=alarmId+3;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit2*10&&alarm_enable)//二级过低告警
		{
			event.ID=alarmId+4;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit1*10&&alarm_enable)//一级过低告警
		{
			event.ID=alarmId+5;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_LOW_START;
		}
	}
	else if(*(alarm_status+3-1)==ALARM_FLAG_END)//正常状态
	{
		if(value>=gs_ProMng.Pro[device][point].HiLimit1*10&&alarm_enable)//一级过高告警
		{
			event.ID=alarmId;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit2*10&&alarm_enable)//二级过高告警
		{
			event.ID=alarmId+1;
			event.Flag=ALARM_FLAG_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit3*10&&alarm_enable)//三级过高告警
		{
			event.ID=alarmId+2;
			event.Flag=ALARM_FLAG_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_HIGH_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit3*10&&alarm_enable)//三级过低告警
		{
			event.ID=alarmId+3;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit2*10&&alarm_enable)//二级过低告警
		{
			event.ID=alarmId+4;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit1*10&&alarm_enable)//一级过低告警
		{
			event.ID=alarmId+5;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_LOW_START;
		}
	}
	else if(*(alarm_status+1-1)==ALARM_FLAG_LOW_START)//一级过低告警中
	{
		if(value>=gs_ProMng.Pro[device][point].HiLimit1*10&&alarm_enable)//一级过高告警
		{
			event.ID=alarmId;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit2*10&&alarm_enable)//二级过高告警
		{
			event.ID=alarmId+1;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit3*10&&alarm_enable)//三级过高告警
		{
			event.ID=alarmId+2;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>gs_ProMng.Pro[device][point].LoLimit3*10)//三级过低告警恢复
		{
			event.ID=alarmId+3;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_END;
		}
		if(value>gs_ProMng.Pro[device][point].LoLimit2*10)//二级过低告警恢复
		{
			event.ID=alarmId+4;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_END;
		}
		if(value>gs_ProMng.Pro[device][point].LoLimit1*10)//一级过低告警恢复
		{
			event.ID=alarmId+5;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_END;
		}
	}
	else if(*(alarm_status+2-1)==ALARM_FLAG_LOW_START)//二级过低告警中
	{
		if(value>=gs_ProMng.Pro[device][point].HiLimit1*10&&alarm_enable)//一级过高告警
		{
			event.ID=alarmId;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit2*10&&alarm_enable)//二级过高告警
		{
			event.ID=alarmId+1;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit3*10&&alarm_enable)//三级过高告警
		{
			event.ID=alarmId+2;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>gs_ProMng.Pro[device][point].LoLimit3*10)//三级过低告警恢复
		{
			event.ID=alarmId+3;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_END;
		}
		if(value>gs_ProMng.Pro[device][point].LoLimit2*10)//二级过低告警恢复
		{
			event.ID=alarmId+4;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_END;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit1*10&&alarm_enable)//一级过低告警
		{
			event.ID=alarmId+5;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_LOW_START;
		}
	}
	else if(*(alarm_status+3-1)==ALARM_FLAG_LOW_START)//三级过低告警中
	{
		if(value>=gs_ProMng.Pro[device][point].HiLimit1*10&&alarm_enable)//一级过高告警
		{
			event.ID=alarmId;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit2*10&&alarm_enable)//二级过高告警
		{
			event.ID=alarmId+1;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>=gs_ProMng.Pro[device][point].HiLimit3*10&&alarm_enable)//三级过高告警
		{
			event.ID=alarmId+2;
			event.Flag=ALARM_FLAG_HIGH_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_HIGH_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_HIGH_START;
		}
		if(value>gs_ProMng.Pro[device][point].LoLimit3*10)//三级过低告警恢复
		{
			event.ID=alarmId+3;
			event.Flag=ALARM_FLAG_END;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=3;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_3;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+3-1)=ALARM_FLAG_END;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit2*10&&alarm_enable)//二级过低告警
		{
			event.ID=alarmId+4;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=2;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_2;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+2-1)=ALARM_FLAG_LOW_START;
		}
		if(value<=gs_ProMng.Pro[device][point].LoLimit1*10&&alarm_enable)//一级过低告警
		{
			event.ID=alarmId+5;
			event.Flag=ALARM_FLAG_LOW_START;
			event.Device=device;
			event.Point=point;
			event.Value=value;
			event.level=1;
			event.AlarmLevel=alarm_level;
			event.Content=ALARM_CONTENT_LOW_1;
			if(gs_EventMng.fSetEvent(&event)==TRUE)
				printf("right");
			else
				printf("wrong");
			*(alarm_status+1-1)=ALARM_FLAG_LOW_START;
		}
	}
	///////////////////
	//以上为告警判断，以下为相应数据状态
	int data_status;
	if(*(alarm_status+1-1)!=ALARM_FLAG_END||*(alarm_status+2-1)!=ALARM_FLAG_END||*(alarm_status+3-1)!=ALARM_FLAG_END)
	{
		data_status=alarm_level;
		gs_NewDataMng.fSetCData(device,point,STATUS,&data_status);
	}
	else
	{
		data_status=0;
		gs_NewDataMng.fSetCData(device,point,STATUS,&data_status);
	}
}
void judgeDI(short int device, short int point,int value, signed char *alarm_status, int alarmId,int content)
{
	Event_TypeDef *event;
	Event_TypeDef event_di;
	event=&event_di;
	int data_status;
	int alarm_level=gs_ProMng.Pro[device][point].Alarmlevel;
	if(value==gs_ProMng.Pro[device][point].AlarmThresbhold&&gs_ProMng.Pro[device][point].AlarmEnable==1)
	{
		//告警
		data_status=gs_ProMng.Pro[device][point].Alarmlevel;
		gs_NewDataMng.fSetCData(device,point,STATUS,&data_status);
		if(*alarm_status==ALARM_FLAG_END)
		{
			event->ID=alarmId;
			event->Flag=ALARM_FLAG_START;
			event->Value=value;
			event->Device=device;
			event->Point=point;
			event->Content=content;
			event->level=1;
			event->AlarmLevel=alarm_level;
			if(gs_EventMng.fSetEvent(event)==TRUE)
				printf("right");
			else
				printf("wrong"); 
			*alarm_status=ALARM_FLAG_START;
		}
	}
	if(value!=gs_ProMng.Pro[device][point].AlarmThresbhold)
	{
		//恢复
		data_status=0;
		gs_NewDataMng.fSetCData(device,point,STATUS,&data_status);
		if(*alarm_status==ALARM_FLAG_START)
		{
			event->ID=alarmId;
			event->Flag=ALARM_FLAG_END;
			event->Value=value;
			event->Device=device;
			event->Point=point;
			event->Content=content;
			event->level=1;
			event->AlarmLevel=alarm_level;
			if(gs_EventMng.fSetEvent(event)==TRUE)
				printf("right");
			else
				printf("wrong"); 
			*alarm_status=ALARM_FLAG_END;
		}
	}
}

void init_gs_EventMng(void)
{
	gs_EventMng.GetEventNum = 0;
	gs_EventMng.SetEventNum = 0;

	for(Event_i = 0; Event_i < EVENT_NUM; Event_i++)
	{
		gs_EventMng.EventArray[Event_i].Type= 0; 
		gs_EventMng.Eventnum[Event_i]=0; 
	}
	gs_EventMng.fSetEvent = SetEvent;
	gs_EventMng.fGetEvent = GetEvent;
	gs_EventMng.fJudgeAI=judgeAI;
	gs_EventMng.fJudgeDI=judgeDI;
}

Alarmstat_TypeDef AlarmStat;
void init_alarm(void)
{
	printf("\nsqlite task started\n");
	char temp[1024];
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	rc = sqlite3_open("/app/alarmlock.db", &db);  // will create a new db if not existing
	int i,ii;
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else
	{
		///////////////////////////////////////////////////
		//////新表T3，用device和point找点，level找级别，flag取值-1、0、1，表过低正常过高
		char *sql = "create table T3(device integer,point integer,level integer,flag integer)"; 
		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if (rc == SQLITE_OK)
		{
			printf("Alarm Table T3 created. \n");
		}
		else  
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			printf("Alarm Table T3 Failed. \n");
		}	
	}
	for(i=1;i<=POWER_SIZE;i++)
	{
		for(ii=1;ii<=3;ii++)
		{
			
			AlarmStat.power_alarm_flag[i][ii-1]=0;
			sprintf(temp,"select flag from T3 where device=%d and point=%d and level=%d",POWER_DEVICE,i,ii);
			rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
			else
			{
				AlarmStat.power_alarm_flag[i][ii-1]=u[0];	
				u[0]=0;
			}
		}
	}
	
	for(i=1;i<=UPS_SIZE;i++)
	{
		for(ii=1;ii<=3;ii++)
		{
			
			AlarmStat.ups_alarm_flag[i][ii-1]=0;
			sprintf(temp,"select flag from T3 where device=%d and point=%d and level=%d",UPS_DEVICE,i,ii);
			rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
			else
			{
				AlarmStat.ups_alarm_flag[i][ii-1]=u[0];	
				u[0]=0;
			}
		}
	}

	for(i=1;i<=BATTERY_SIZE;i++)
	{
		for(ii=1;ii<=3;ii++)
		{
			
			AlarmStat.battery_alarm_flag[i][ii-1]=0;
			sprintf(temp,"select flag from T3 where device=%d and point=%d and level=%d",BATTERY_DEVICE,i,ii);
			rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
			else
			{
				AlarmStat.battery_alarm_flag[i][ii-1]=u[0];	
				u[0]=0;
			}
		}
	}

	for(i=1;i<=ENVIRONMENT_SIZE;i++)
	{
		for(ii=1;ii<=3;ii++)
		{
			
			AlarmStat.environment_alarm_flag[i][ii-1]=0;
			sprintf(temp,"select flag from T3 where device=%d and point=%d and level=%d",ENVIRONMENT_DEVICE,i,ii);
			rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
			else
			{
				AlarmStat.environment_alarm_flag[i][ii-1]=u[0];	
				u[0]=0;
			}
		}
	}

	for(i=1;i<=ACDU_SIZE;i++)
	{
		for(ii=1;ii<=3;ii++)
		{
			
			AlarmStat.acdu_alarm_flag[i][ii-1]=0;
			sprintf(temp,"select flag from T3 where device=%d and point=%d and level=%d",ACDU_DEVICE,i,ii);
			rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
			else
			{
				AlarmStat.acdu_alarm_flag[i][ii-1]=u[0];	
				u[0]=0;
			}
		}
	}

	for(i=1;i<=SPD_SIZE;i++)
	{
		for(ii=1;ii<=3;ii++)
		{
			
			AlarmStat.spd_alarm_flag[i][ii-1]=0;
			sprintf(temp,"select flag from T3 where device=%d and point=%d and level=%d",SPD_DEVICE,i,ii);
			rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
			else
			{
				AlarmStat.spd_alarm_flag[i][ii-1]=u[0];	
				u[0]=0;
			}
		}
	}

	for(i=1;i<=AIR_SIZE;i++)
	{
		for(ii=1;ii<=3;ii++)
		{
			
			AlarmStat.air_alarm_flag[i][ii-1]=0;
			sprintf(temp,"select flag from T3 where device=%d and point=%d and level=%d",AIRCONDITIONER_DEVICE,i,ii);
			rc = sqlite3_exec(db, temp, select_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			}
			else
			{
				AlarmStat.air_alarm_flag[i][ii-1]=u[0];	
				u[0]=0;
			}
		}
	}

	rc = sqlite3_open("/app/timealarm.db", &db);  // will create a new db if not existing
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else
	{
		char *sql = "create table T1(id integer,yearh tinyint,yearl tinyint,month tinyint,day tinyint,hour tinyint,minute tinyint,sec tinyint,device integer,point integer)"; 
		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if (rc == SQLITE_OK)
		{
			printf("\n timealarm Table T1 created.\n");
		}
		else
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			printf("\n timealarm T1 CREAT FAILD !!!\n");
		}
		sqlite3_close(db);
	}
printf("\nsqlite task completed\n");
}

