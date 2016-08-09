#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "inifile.h"
#include "measure.h"
#include "interface.h" 
#include "typedef.h"


float calculate_temperature(float ad_volt)
{
	int  temp;
	temp=(int)((ad_volt*2.5*10+0)*10);
	return temp;
}
float calculate_humidity(float ad_volt)
{
	int  temp;
	temp=(int)((ad_volt*2.5*20+0)*10);
	return temp;
}
float calculate_air_voltage(float ad_volt)
{
	int  temp;
	temp=(int)((ad_volt*2.5*112.5-112.5)*10);
	return temp;
}
float calculate_air_current(float ad_volt)
{
	int  temp;
	temp=(int)((ad_volt*2.5*7.5-7.5)*10);
	return temp;
}
float calculate_ac_voltage(float ad_volt)
{
	int  temp;
	temp=(int)((ad_volt*2.5*20-112.5)*10);
	return temp;
}

int AIMeasure(void)
{
unsigned short ad_count[AD_REAL_CHANNEL],feeddog;
int data=0;
float ad_volt[AD_CHANNEL_NUMBER];
int ad_handle;
int i;
unsigned char AITask[16];
gs_RTUcfgMng.Getcfg(RTU_AI_NUM,&AITask[0]);
ad_handle = open("/dev/ad", O_RDWR);	
if (ad_handle < 0)
{
	return -1;
}
while(1)
{
	read(ad_handle,ad_count,AD_REAL_CHANNEL*sizeof(unsigned short));
	for(i=0;i<16;i++)
	{
		if(AITask[i]!=255)
		{
			//暂时直接用数字代替
			//ad_volt[i] = Measure[i].vref*((ad_count[i] - ad_count[GND_CHANNEL])/(ad_count[VREF_CHANNEL]-ad_count[GND_CHANNEL]));
			ad_volt[i] = 2.3189*((ad_count[i] - ad_count[GND_CHANNEL])/(ad_count[VREF_CHANNEL]-ad_count[GND_CHANNEL]));
			//data=(int)((ad_volt[i]*Measure[i].Gain*Measure[i].ADK+Measure[i].ADB)*10);
			switch(AITask[i])
			{
				case 0://温度1
					data=calculate_temperature(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,TEMPERATURE_1,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,TEMPERATURE_1,data,AlarmStat.environment_alarm_flag[TEMPERATURE_1],ALARM_ID_TEM_1);
					break;
		   
				case 1://湿度1
					data=calculate_humidity(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,HUMIDITY_1,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,HUMIDITY_1,data,AlarmStat.environment_alarm_flag[HUMIDITY_1],ALARM_ID_HUMIDITY_1);
					break;

				case 2: //空调电流
					data=calculate_air_current(ad_volt[i]);
					gs_NewDataMng.fSetCData(AIRCONDITIONER_DEVICE,AIR_CURRENT_A_1,DATA,&data);
					gs_EventMng.fJudgeAI(AIRCONDITIONER_DEVICE,AIR_CURRENT_A_1,data,AlarmStat.air_alarm_flag[AIR_CURRENT_A_1],ALARM_ID_AIR_CUR_A_1);
					break;
					
				case 3: //空调电压
					data=calculate_air_voltage(ad_volt[i]);
					gs_NewDataMng.fSetCData(AIRCONDITIONER_DEVICE,AIR_VOLTAGE_A_1,DATA,&data);
					gs_EventMng.fJudgeAI(AIRCONDITIONER_DEVICE,AIR_VOLTAGE_A_1,data,AlarmStat.air_alarm_flag[AIR_VOLTAGE_A_1],ALARM_ID_AIR_VOL_A_1);
					break;

				case 8:  // 温度2
					data=calculate_temperature(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,TEMPERATURE_2,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,TEMPERATURE_2,data,AlarmStat.environment_alarm_flag[TEMPERATURE_2],ALARM_ID_TEM_2);
					break;
		   
				case 9:  // 湿度2
					data=calculate_humidity(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,HUMIDITY_2,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,HUMIDITY_2,data,AlarmStat.environment_alarm_flag[HUMIDITY_2],ALARM_ID_HUMIDITY_2);
					break;

				case 10: // 温度3
					data=calculate_temperature(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,TEMPERATURE_3,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,TEMPERATURE_3,data,AlarmStat.environment_alarm_flag[TEMPERATURE_3],ALARM_ID_TEM_3);
					break;

				case 11:  // 湿度3
					data=calculate_humidity(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,HUMIDITY_3,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,HUMIDITY_3,data,AlarmStat.environment_alarm_flag[HUMIDITY_3],ALARM_ID_HUMIDITY_3);
					break;

				case 12:  // 温度4
					data=calculate_temperature(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,TEMPERATURE_4,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,TEMPERATURE_4,data,AlarmStat.environment_alarm_flag[TEMPERATURE_4],ALARM_ID_TEM_4);
					break;
		   
				case 13:  // 湿度4
					data=calculate_humidity(ad_volt[i]);
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,HUMIDITY_4,DATA,&data);
					gs_EventMng.fJudgeAI(ENVIRONMENT_DEVICE,HUMIDITY_4,data,AlarmStat.environment_alarm_flag[HUMIDITY_4],ALARM_ID_HUMIDITY_4);
					break;
		   
				case 14: //交流1
					data=calculate_ac_voltage(ad_volt[i]);
					gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_VOLTAGE_A_1,DATA,&data);
					gs_EventMng.fJudgeAI(ACDU_DEVICE,ACDU_VOLTAGE_A_1,data,AlarmStat.acdu_alarm_flag[ACDU_VOLTAGE_A_1],ALARM_ID_ACDU_A_1);
					break;

				case 15: //交流2
					data=calculate_ac_voltage(ad_volt[i]);
					gs_NewDataMng.fSetCData(ACDU_DEVICE,ACDU_VOLTAGE_A_2,DATA,&data);
					gs_EventMng.fJudgeAI(ACDU_DEVICE,ACDU_VOLTAGE_A_2,data,AlarmStat.acdu_alarm_flag[ACDU_VOLTAGE_A_2],ALARM_ID_ACDU_A_2);
					break;

				default:
					break;
			}
		}
	}
	sleep(1);
	SelfTest.fGetSelftest(3,&feeddog);
	feeddog++;
	if(feeddog>65530)
	{feeddog=0;}
	SelfTest.fSetSelftest(3,&feeddog);
}
}

int dio_handle;//DImeasure和 DOmeasure都用到的句柄，所以做成全部变量
char DI_val[16];//lcd程序中需要用到开关量状态，所以做成全局变量,并在lcd.c中extern一下
int DIMeasure(void)
{
unsigned short feeddog;
int data;
unsigned char DITask[16];
gs_RTUcfgMng.Getcfg(RTU_DI_NUM,&DITask[0]);
int i;
unsigned short input;
dio_handle = open("/dev/dio", O_RDWR);	
if (dio_handle < 0)
{
	return -1;
}
while(1)
{	
	for(i=0;i<16;i++)
	{
		read(dio_handle, &input, sizeof(unsigned short));
		if(input&(0x1<<i)) 
			DI_val[i]=1;
		else
			DI_val[i]=0;
		switch(DITask[i])
		{
			case 0://门禁1
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,ACCESS_1,DATA,&DI_val[i]);
				//在未告警状态下如果门开就开灯开蜂鸣，其中开灯数据置为2以区别于遥控动作
				//data置为2后,若data=2且status=0,触发延时开灯动作
				//若data=2且status=1,说明处于遥控开灯状态,不触发任何动作
				//此段需要放在judgeDI产生告警之前
				if(DI_val[i]==gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_1].AlarmThresbhold&&AlarmStat.environment_alarm_flag[ACCESS_1][0]==0)
				{
					data=2;//灯控
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_1,DATA,&data);
					data=1;//蜂鸣器
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_1,DATA,&data);
					
				}
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,ACCESS_1,DI_val[i],AlarmStat.environment_alarm_flag[ACCESS_1],200,ALARM_CONTENT_ALARM);
				break;

			case 1://水浸
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,WATER_1,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,WATER_1,DI_val[i],AlarmStat.environment_alarm_flag[WATER_1],201,ALARM_CONTENT_ALARM);
				break;

			case 2:   // 烟雾 
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SMOKE_1,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,SMOKE_1,DI_val[i],AlarmStat.environment_alarm_flag[SMOKE_1],201,ALARM_CONTENT_ALARM);
				break;
				
			case 4:    //红外
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,INFRARED_1,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,INFRARED_1,DI_val[i],AlarmStat.environment_alarm_flag[INFRARED_1],201,ALARM_CONTENT_ALARM);
				break;

			case 5:    // 玻璃破碎
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,GLASS_1,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,GLASS_1,DI_val[i],AlarmStat.environment_alarm_flag[GLASS_1],201,ALARM_CONTENT_ALARM);
				break;

			case 6:   //门禁2
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,ACCESS_2,DATA,&DI_val[i]);
				//注释见门禁1
				if(DI_val[i]==gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_2].AlarmThresbhold&&AlarmStat.environment_alarm_flag[ACCESS_2][0]==0)
				{
					data=2;//灯控
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_2,DATA,&data);
					data=1;//蜂鸣器
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_2,DATA,&data);
					
				}
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,ACCESS_2,DI_val[i],AlarmStat.environment_alarm_flag[ACCESS_2],201,ALARM_CONTENT_ALARM);
				break;

			case 7:   //门禁3
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,ACCESS_3,DATA,&DI_val[i]);
				//注释见门禁1
				if(DI_val[i]==gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_3].AlarmThresbhold&&AlarmStat.environment_alarm_flag[ACCESS_3][0]==0)
				{
					data=2;//灯控
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_3,DATA,&data);
					data=1;//蜂鸣器
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_3,DATA,&data);
					
				}
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,ACCESS_3,DI_val[i],AlarmStat.environment_alarm_flag[ACCESS_3],201,ALARM_CONTENT_ALARM);
				break;
				
			case 8:   //门禁4
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,ACCESS_4,DATA,&DI_val[i]);
				//注释见门禁1
				if(DI_val[i]==gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_4].AlarmThresbhold&&AlarmStat.environment_alarm_flag[ACCESS_4][0]==0)
				{
					data=2;//灯控
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_4,DATA,&data);
					data=1;//蜂鸣器
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_4,DATA,&data);
					
				}
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,ACCESS_4,DI_val[i],AlarmStat.environment_alarm_flag[ACCESS_4],201,ALARM_CONTENT_ALARM);
				break;

			case 9:    // 玻璃破碎2
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,GLASS_2,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,GLASS_2,DI_val[i],AlarmStat.environment_alarm_flag[GLASS_2],201,ALARM_CONTENT_ALARM);
				break;

			case 10:    // 玻璃破碎3
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,GLASS_3,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,GLASS_3,DI_val[i],AlarmStat.environment_alarm_flag[GLASS_3],201,ALARM_CONTENT_ALARM);
				break;

			case 11:    // 玻璃破碎4
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,GLASS_4,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,GLASS_4,DI_val[i],AlarmStat.environment_alarm_flag[GLASS_4],201,ALARM_CONTENT_ALARM);
				break;

			case 12:   //水禁2
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,WATER_2,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,WATER_2,DI_val[i],AlarmStat.environment_alarm_flag[WATER_2],201,ALARM_CONTENT_ALARM);
				break;
			
			case 13:  // 水禁3
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,WATER_3,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,WATER_3,DI_val[i],AlarmStat.environment_alarm_flag[WATER_3],201,ALARM_CONTENT_ALARM);
				break;

			case 14:   //水禁4
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,WATER_4,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,WATER_4,DI_val[i],AlarmStat.environment_alarm_flag[WATER_4],201,ALARM_CONTENT_ALARM);
				break;

			case 15:   // 烟雾2
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SMOKE_2,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,SMOKE_2,DI_val[i],AlarmStat.environment_alarm_flag[SMOKE_2],201,ALARM_CONTENT_ALARM);
				break;
			
			case 16:   // 烟雾 3
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SMOKE_3,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,SMOKE_3,DI_val[i],AlarmStat.environment_alarm_flag[SMOKE_3],201,ALARM_CONTENT_ALARM);
				break;
			
			case 17:   // 烟雾4
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SMOKE_4,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,SMOKE_4,DI_val[i],AlarmStat.environment_alarm_flag[SMOKE_4],201,ALARM_CONTENT_ALARM);
				break;

			case 19:    //红外2
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,INFRARED_2,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,INFRARED_2,DI_val[i],AlarmStat.environment_alarm_flag[INFRARED_2],201,ALARM_CONTENT_ALARM);
				break;

			case 20:    //红外3
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,INFRARED_3,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,INFRARED_3,DI_val[i],AlarmStat.environment_alarm_flag[INFRARED_3],201,ALARM_CONTENT_ALARM);
				break;

			case 21:    //红外4
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,INFRARED_4,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,INFRARED_4,DI_val[i],AlarmStat.environment_alarm_flag[INFRARED_4],201,ALARM_CONTENT_ALARM);
				break;
			
			case 22:   //防雷1   (常闭)
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SPD_1,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,SPD_1,DI_val[i],AlarmStat.environment_alarm_flag[SPD_1],201,ALARM_CONTENT_ALARM);
				break;

			case 23:   //防雷2   
				gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SPD_2,DATA,&DI_val[i]);
				gs_EventMng.fJudgeDI(ENVIRONMENT_DEVICE,SPD_2,DI_val[i],AlarmStat.environment_alarm_flag[SPD_2],201,ALARM_CONTENT_ALARM);
				break;

			default:
				break;
		}
	}
	sleep(1);
	SelfTest.fGetSelftest(4,&feeddog);
	feeddog++;
	if(feeddog>65530)
	{feeddog=0;}
	SelfTest.fSetSelftest(4,&feeddog);
}
}   

    
int DOMeasure(void)
{
	unsigned char output=0;
	unsigned char temp=0;
	int data=0;
	int status=0;
	int i=0;
	int delaytime=0;//灯控延时时间
	gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,LIGHT_DELAY,DATA,&delaytime);
	//烟感继电器在板上被固定为DO^0,因此其他DO量在实际使用时置位应多移一位(temp<<+1)
	while(1)
	{
		//灯控
		for(i=0;i<4;i++)
		{
			if(light_to_DO[i]!=-1)
			{
				gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_1+i,DATA,&data);
				gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_1+i,STATUS,&status);
				if(data==1&&status==0xff)//遥控开灯,动作后data=1,status=0,遥控时只对data操作，不更改status
				{
					status=0;
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_1+i,STATUS,&status);
					temp=1<<light_to_DO[i]+1;
					output|=temp;
					write(dio_handle, &output, sizeof(unsigned char));
				}
				else if(data==0&&status==0)//遥控关灯,动作后data=0,status=0xff
				{
					status=0xff;
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_1+i,STATUS,&status);
					temp=1<<light_to_DO[i]+1;
					output&=~temp;
					write(dio_handle, &output, sizeof(unsigned char));
				}
				else if(data==2&&status==0xff)//开门开灯,动作后data=0,status=0xff
				{
					data=0;
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_1+i,DATA,&data);
					temp=1<<light_to_DO[i]+1;
					output|=temp;
					write(dio_handle, &output, sizeof(unsigned char));
					sleep(delaytime);
					output&=~temp;
					write(dio_handle, &output, sizeof(unsigned char));
				}
			}
		}

		//烟感复位
		//烟感是瞬间动作，只有一个命令，不需要status作为另一个标志
		gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,SMOKE_RESET,DATA,&data);
		if(data==1)
		{	
			data=0;
			gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SMOKE_RESET,DATA,&data);	
			temp=1;
			output|=temp;
			write(dio_handle, &output, sizeof(unsigned char));
			sleep(1);
			output&=~temp;
			write(dio_handle, &output, sizeof(unsigned char));
		}

		//蜂鸣器
		for(i=0;i<4;i++)
		{
			if(buzzer_to_DO[i]!=-1)
			{
				gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,BUZZER_1+i*8,DATA,&data);
				gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,BUZZER_1+i*8,STATUS,&status);
				if(data==1&&status==0xff)//开门开蜂鸣,动作后data=1,status=0
				{
					status=0;
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_1+i*8,STATUS,&status);
					temp=1<<buzzer_to_DO[i]+1;
					output|=temp;
					write(dio_handle, &output, sizeof(unsigned char));
				}
				else if(data==0&&status==0)//遥控关蜂鸣,动作后data=0,status=0xff
				{
					status=0xff;
					gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_1+i*8,STATUS,&status);
					temp=1<<buzzer_to_DO[i]+1;
					output&=~temp;
					write(dio_handle, &output, sizeof(unsigned char));
				}
			}
		}
	}
}

