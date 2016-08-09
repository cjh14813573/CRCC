#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "typedef.h"
#include "inifile.h"
#include "interface.h"
const char *file ="/app/ThreVal.ini";
char *section; 
char *key;
static MUTEX_T hMutexReadWritepwthreval=PTHREAD_MUTEX_INITIALIZER;


unsigned char SetPWAlarmVal(unsigned char i, void *pDataBuf)
{ 
 MutexLock(&hMutexReadWritepwthreval);
 section="pwalarm";
 char u[20];
 if(i == AC_higt_volt_NUM)
 {
 key="ACHighVolt";
 memset(u,0,20);
 gs_pwalarmMng.thre_val.AC_high_volt= *((int *)pDataBuf);
 itoa(gs_pwalarmMng.thre_val.AC_high_volt,u);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}   
 }
else if(i == AC_low_volt_NUM)
 {
 key="ACLowVolt";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.AC_low_volt= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == AC_higt_curr_NUM)
 {
 key="ACHighCurr";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.AC_high_curr= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == AC_low_curr_NUM)
 {
 key="ACLowCurr";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.AC_low_curr= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == DC_higt_volt_NUM)
 {
 key="DCHighVolt";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.DC_high_volt= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == DC_low_volt_NUM)
 {
 key="DCLowVolt";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.DC_low_volt= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == high_temp_NUM)
 {
 key="HighTemp";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.Temp_high= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == low_temp_NUM)
 {
 key="LowTemp";
 memset(u,0,20);
  itoa(*((int *)pDataBuf),u);
  gs_pwalarmMng.thre_val.Temp_low= *((int *)pDataBuf);
  if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == high_humidity_NUM)
 {
 key="HighHumidity";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.Humidity_high= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
	
 }
else if(i == low_humidity_NUM)
 {
 key="LowHumidity";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.thre_val.Humidity_low= *((int *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
}
    else if(i == RTU_log_NUM)
 {
 section="RTUlog";
 key="EventNum";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.log= *((unsigned short *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
}
    else if(i == RTU_lcd_NUM)
 {
 section="lcd";
 key="LCD";
 memset(u,0,20);
 itoa(*((int *)pDataBuf),u);
 gs_pwalarmMng.lcd= *((unsigned char *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
}

    else if(i == RTU_backlight_NUM)
 {
 section="lcd";
 key="backlight";
 memset(u,0,20);
 itoa(*((unsigned char *)pDataBuf),u);
 gs_pwalarmMng.backlight= *((unsigned char *)pDataBuf);
 if(!write_profile_string(section,key,u,file))
	{
		printf("write to ini file fail\n");
		return FALSE;
	}
}

	
else if(i == Set_AlarmThreVal_NUM)
{
	gs_pwalarmMng.threval_flag=*((char *)pDataBuf);
}
else
  {
    MutexUnlock(&hMutexReadWritepwthreval);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWritepwthreval);
  return  TRUE;
}



static MUTEX_T hMutexReadWritepwthreval1=PTHREAD_MUTEX_INITIALIZER;
unsigned char GetPWAlarmVal(unsigned char i, void *pDataBuf)
{
 MutexLock(&hMutexReadWritepwthreval1);
 if(i == AC_higt_volt_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.AC_high_volt;
 }
else if(i == AC_low_volt_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.AC_low_volt;
 }
else if(i == AC_higt_curr_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.AC_high_curr;
 }
else if(i == AC_low_curr_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.AC_low_curr;
 }
else if(i == DC_higt_volt_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.DC_high_volt;
 }
else if(i == DC_low_volt_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.DC_low_volt;
 }
else if(i == high_temp_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.Temp_high;
 }
else if(i == low_temp_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.Temp_low;
 }
else if(i == high_humidity_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.Humidity_high;
 }
else if(i == low_humidity_NUM)
 {
 *((int *)pDataBuf)=gs_pwalarmMng.thre_val.Humidity_low;
 }
else if(i == Set_AlarmThreVal_NUM)
{
	*((char*)pDataBuf)=gs_pwalarmMng.threval_flag;
}
else if(i == RTU_log_NUM)
{
	*((int *)pDataBuf)=gs_pwalarmMng.log;
}
else if(i == RTU_lcd_NUM)
{
	*((int *)pDataBuf)=gs_pwalarmMng.lcd;
}
else if(i == RTU_backlight_NUM)
{
	*((unsigned char *)pDataBuf)=gs_pwalarmMng.backlight;
}
else
  {
    MutexUnlock(&hMutexReadWritepwthreval1);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWritepwthreval1);
  return  TRUE;
}


pw_alarm_thre_valMng_TypeDef gs_pwalarmMng;
void init_gs_pwalarmMng(void)
{ 
	section="pwalarm";
	gs_pwalarmMng.Setthre_val = SetPWAlarmVal;
	gs_pwalarmMng.Getthre_val = GetPWAlarmVal;
	gs_pwalarmMng.threval_flag=0;

	char thre_val[BUF_SIZE]={0};
	char *key="ACHighVolt";
	if(!read_profile_string(section, key, thre_val, BUF_SIZE,"",file))
	{
		section="RTUlog";
		key="EventNum";
		write_profile_string(section,key,"0",file);
		
		section="lcd";
		key="LCD";
		write_profile_string(section,key,"1",file);
		
		key="backlight";
		write_profile_string(section,key,"45",file);
		
		section="pwalarm";
		key="LowHumidity";
		write_profile_string(section,key,"100",file);
		
		key="HighHumidity";
		write_profile_string(section,key,"900",file);
		
		key="LowTemp";
		write_profile_string(section,key,"100",file);
		
		key="HighTemp";
		write_profile_string(section,key,"400",file);
		
		key="DCLowVolt";
		write_profile_string(section,key,"480",file);
		
		key="DCHighVolt";
		write_profile_string(section,key,"600",file);
		
		key="ACLowCurr";
		write_profile_string(section,key,"10",file);
		
		key="ACHighCurr";
		write_profile_string(section,key,"100",file);
		
		key="ACLowVolt";
		write_profile_string(section,key,"1800",file);
		
		key="ACHighVolt";
		write_profile_string(section,key,"2800",file);
		printf("\ncreat default ini file ok\n"); 
	}
	else printf("\npw ini file exist\n");
	section="pwalarm";
	key="ACHighVolt";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.AC_high_volt=atoi(thre_val);
	key="ACLowVolt";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.AC_low_volt=atoi(thre_val);
	key="ACHighCurr";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.AC_high_curr=atoi(thre_val);
	key="ACLowCurr";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.AC_low_curr=atoi(thre_val);
	key="DCHighVolt";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.DC_high_volt=atoi(thre_val);
	key="DCLowVolt";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.DC_low_volt=atoi(thre_val);	
	key="HighTemp";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.Temp_high=atoi(thre_val);
	key="LowTemp";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.Temp_low=atoi(thre_val);
	key="HighHumidity";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.Humidity_high=atoi(thre_val);
	key="LowHumidity";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.thre_val.Humidity_low=atoi(thre_val);
	section="RTUlog";
	key="EventNum";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.log=atoi(thre_val);
	section="lcd";
	key="LCD";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.lcd=atoi(thre_val);
	key="backlight";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file);
	gs_pwalarmMng.backlight=atoi(thre_val);				   
	/*		    key="PWaddress";
	read_profile_string(section, key, thre_val, BUF_SIZE,"",file); 
	gs_pwalarmMng.thre_val.pw_addr=atoi(thre_val);*/
}


