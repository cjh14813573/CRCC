
#include "property.h"
#include "typedef.h"
#include "interface.h"




//定义节点ID号结构体

struct completeID id_struct[ID_SIZE];
short int id_number=0;
struct completeID power_struct[POWER_SIZE+1];
short int power_number=0; 
struct completeID air_struct[AIR_SIZE+1];
short int air_number=0;
struct completeID battery_struct[BATTERY_SIZE+1];
short int battery_number=0;
struct completeID environment_struct[ENVIRONMENT_SIZE+1];
short int environment_number=0;
struct completeID acdu_struct[ACDU_SIZE+1];
short int acdu_number=0;
struct completeID spd_struct[SPD_SIZE+1];
short int spd_number=0;
struct completeID ups_struct[UPS_SIZE+1];
short int ups_number=0;
struct completeID device_struct[DEVICE_SIZE+1];
short int device_number=0;

int light_to_DO[3]={-1,-1,-1};  //light_to_DO 和 buzzer_to_DO是全局变量，用于向 DOmeasure中传递某个设备使用的 DO口
int buzzer_to_DO[3]={-1,-1,-1};//初始化值为-1，表示没有该设备
int read_property_ini_string(char *section,char *key,char *buf,char *value)
{
	int sec_s;
	int sec_e;
	int key_s;
	int key_e;
	int value_s;
	int value_e;
	if(!parse_file(section,key,buf,&sec_s,&sec_e,&key_s,&key_e,&value_s,&value_e))
	{
		memset(value, 0, 256);
		return 0; //not find the key
	}
	else
	{
		int cpcount = value_e -value_s;
		if( 255 < cpcount)
		{
			cpcount =  255;
		}
		memset(value, 0, 256);
		memcpy(value,buf+value_s, cpcount );
		value[cpcount] = '\0';
		return 1;
	}
}


//初始化id结构体,ss初始化为1，point初始化为-1，只有有效的点才会赋值为正数
void init_struct(struct completeID *device_struct,short int rtu_address, short int deviceID, int size)
{
	int i;
	for(i=0;i<=size;i++)
	{
		(*(device_struct+i)).ss=CENTER_ID;
		(*(device_struct+i)).rtuID=rtu_address;
		(*(device_struct+i)).device=deviceID;
		(*(device_struct+i)).point=-1;
	}
}

//写入下一个id结构体
void write_next_id_struct(struct completeID *device_struct,short int *number, short int deviceID, short int pointID)
{
	(*number)++;
	(*(device_struct+(*number)-1)).device=deviceID;
	(*(device_struct+(*number)-1)).point=pointID;
}
void write_next_struct(struct completeID *device_struct,short int *number,short int pointID)
{
	(*number)++;
	(*(device_struct+(*number)-1)).point=pointID;
}

void write_property(char *buf,short int device,short int point)
{	
	char *sections;
	char *keys;
	char value[256];
	char temp_section[10];
	sprintf(temp_section,"%d",point);	
	sections=temp_section;	 //  节点ID
	keys="Type";
	read_property_ini_string(sections,keys,buf,value);
	gs_ProMng.Pro[device][point].Type=atoi(value);
	keys="Name";
	read_property_ini_string(sections,keys,buf,value);
	memset(&(gs_ProMng.Pro[device][point].Name[0]), 0x20, 30);
	unicode_to_char(value,&(gs_ProMng.Pro[device][point].Name[0]));
	keys="Des";
	read_property_ini_string(sections,keys,buf,value);
	memset(&(gs_ProMng.Pro[device][point].Des[0]), 0x20, 40);
	unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des[0]));
	switch(gs_ProMng.Pro[device][point].Type)
	{
		case 0://station
			break;
	
		case 1://device
			keys="DeviceType";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].DeviceType=atoi(value);
			keys="Productor";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Productor[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Productor[0]));
			keys="Version";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Version[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Version[0]));
			break;
	
		case 2://DI
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].AlarmEnable=atoi(value);
			keys="AlarmThresbhold";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].AlarmThresbhold=atoi(value);
			keys="Des0";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des0[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des0[0]));
			keys="Des1";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des1[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des1[0]));
			break;
	
		case 3://AI
			keys="MaxVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MaxVal=atof(value);
			keys="MinVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MinVal=atof(value);
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].AlarmEnable=atoi(value);
			keys="HiLimit1";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].HiLimit1=atof(value);
			keys="HiLimit2";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].HiLimit2=atof(value);
			keys="HiLimit3";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].HiLimit3=atof(value);
			keys="LoLimit1";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].LoLimit1=atof(value);
			keys="LoLimit2";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].LoLimit2=atof(value);
			keys="LoLimit3";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].LoLimit3=atof(value);
			keys="Stander";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Stander=atof(value);
			keys="Percision";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Percision=atof(value);
			keys="Unit";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Unit[0]), 0x20, 5);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Unit[0]));
			break;
	
		case 4://DO
			keys="Des0";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des0[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des0[0]));
			keys="Des1";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des1[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des1[0]));
			break;
	
		case 5://AO
			keys="MaxVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MaxVal=atof(value);
			keys="MinVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MinVal=atof(value);
			keys="Stander";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Stander=atof(value);
			keys="Percision";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Percision=atof(value);
			keys="Unit";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Unit[0]), 0x20, 5);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Unit[0]));
			break;
	
		default:
			break;
	}
}

long IDstruct_to_long(struct completeID device_struct)
{
	int a=device_struct.ss*134217728;
	int b=device_struct.rtuID*131072;
	int c=device_struct.device*2048;
	int d=device_struct.point;
	int whole_id=a+b+c+d;
	return whole_id;
}

struct completeID long_to_IDstruct(long whole_id)
{
	struct completeID device_struct;
	device_struct.ss=(short int)(whole_id>>27);
	device_struct.rtuID=(short int)((whole_id<<5)>>22);
	device_struct.device=(short int)(whole_id&0x01f800)/2048;
	device_struct.point=(short int)(whole_id&0x07ff);
	return device_struct;
}

void ini_to_array(char *str1, unsigned char *charResult,int n)
{
	int i=0,ii=0,iii;
	char *q;
	char qq[30]={0};
	q=qq;
	char *p=str1;
	for(iii=0;iii<n;iii++)
	{
	ii=0;memset(qq,0,30);
	 while( p[i]!=',' && p[i]!='\0'&&p[i]!='.'&&p[i]!=':'&&p[i]!='-')
	 {q[ii++]=p[i];i++;}
	 i+=1;
    *(charResult++)=atoi(qq);
    }
}


void init_property(void)
{	
	char *inifile;
	int file_size;
	inifile="/app/RTUcfg.ini";
	char *sections;
	char *keys;
	char key[20];
	char cfg[256]={0};
	int light_flag=0;
	int smoke_flag=0;
	unsigned char temp[16];
	int i=0;
	int m=0,n=0;//mn用于电池属性初始化循环
	int power_flag[3]={0,0,0};//若串口有电源，则赋值为1，并进行电源节点初始化
	int ups_flag[3]={0,0,0};//若串口有ups，则。。。
	int air_flag[3]={0,0,0};//若串口有空调，则。。。
	int acdu_flag[3]={0,0,0};//交流配电
	int spd_flag[3]={0,0,0};//SPD
	int smart_access_flag[3]={0,0,0};//智能门禁
	int battery_flag[3]={0};//电池
	//int dcdu_flag[3]={0,0,0};//直流配电柜
	//int generator_flag[3]={0,0,0};//发电机
	//以上数组中，第一个数字表示是否有该设备，第二个数字表示串口号，第三个表示设备数
	unsigned char battery_num[7];
	//取rtu地址
	short int rtu_address;
	unsigned char rtu_temp_address[2];
	gs_RTUcfgMng.Getcfg(RTU_addr_NUM,&rtu_temp_address);
	rtu_address=rtu_temp_address[1];
	rtu_address=((rtu_address<<8)|rtu_temp_address[0]);

	//初始化id结构体
	init_struct(id_struct,rtu_address,-1,800);
	init_struct(power_struct,rtu_address,POWER_DEVICE,POWER_SIZE);
	init_struct(ups_struct,rtu_address,UPS_DEVICE,UPS_SIZE);
	init_struct(battery_struct,rtu_address,BATTERY_DEVICE,BATTERY_SIZE);
	init_struct(acdu_struct,rtu_address,ACDU_DEVICE,ACDU_SIZE);
	init_struct(air_struct,rtu_address,AIRCONDITIONER_DEVICE,AIR_SIZE);
	init_struct(spd_struct,rtu_address,SPD_DEVICE,SPD_SIZE);
	init_struct(environment_struct,rtu_address,ENVIRONMENT_DEVICE,ENVIRONMENT_SIZE);
	init_struct(device_struct,rtu_address,-1,DEVICE_SIZE);
	
//  RTU station 节点号
	id_number++;
	(*(id_struct+id_number-1)).device=0;
	(*(id_struct+id_number-1)).point=0;
	
	
	//读取AI量
	sections="RTUAISet";
	keys="AI";
	read_profile_string(sections, keys, cfg, 256,"",inifile);
	ini_to_array(cfg,temp,16);
	for(i=0;i<16;i++)
	{
		if(temp[i]!=255)
		{
			switch(temp[i])
			{
				case 0:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,TEMPERATURE_1);
					write_next_struct(environment_struct,&environment_number,TEMPERATURE_1);
					break;
				case 1:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,HUMIDITY_1);
					write_next_struct(environment_struct,&environment_number,HUMIDITY_1);
					break;
				case 2:
					write_next_id_struct(id_struct,&id_number,AIRCONDITIONER_DEVICE,AIR_CURRENT_A_1);
					write_next_struct(air_struct,&air_number,AIR_CURRENT_A_1);
					break;
				case 3:
					write_next_id_struct(id_struct,&id_number,AIRCONDITIONER_DEVICE,AIR_VOLTAGE_A_1);
					write_next_struct(air_struct,&air_number,AIR_VOLTAGE_A_1);
					break;
				case 4:
					write_next_id_struct(id_struct,&id_number,POWER_DEVICE,POWER_A_VOLTAGE_1);
					write_next_struct(power_struct,&power_number,POWER_A_VOLTAGE_1);
					break;
				case 8:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,TEMPERATURE_2);
					write_next_struct(environment_struct,&environment_number,TEMPERATURE_2);
					break;
				case 9:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,HUMIDITY_2);
					write_next_struct(environment_struct,&environment_number,HUMIDITY_2);
					break;
				case 10:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,TEMPERATURE_3);
					write_next_struct(environment_struct,&environment_number,TEMPERATURE_3);
					break;
				case 11:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,HUMIDITY_3);
					write_next_struct(environment_struct,&environment_number,HUMIDITY_3);
					break;
				case 12:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,TEMPERATURE_4);
					write_next_struct(environment_struct,&environment_number,TEMPERATURE_4);
					break;
				case 13:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,HUMIDITY_4);
					write_next_struct(environment_struct,&environment_number,HUMIDITY_4);
					break;
				case 14:
					write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,ACDU_VOLTAGE_A_1);
					write_next_struct(acdu_struct,&acdu_number,ACDU_VOLTAGE_A_1);
					break;
				case 15:
					write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,ACDU_VOLTAGE_A_2);
					write_next_struct(acdu_struct,&acdu_number,ACDU_VOLTAGE_A_2);
					break;

				default:
					break;
			}
		}				
	}


	//读取DI量
	sections="RTUDISet";
	keys="DI";
	read_profile_string(sections,keys,cfg,256,"",inifile);
	ini_to_array(cfg,temp,16);
	for(i=0;i<16;i++)
	{
		if(temp[i]!=255)
		{
			switch(temp[i])
			{
				case 0:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,ACCESS_1);
					write_next_struct(environment_struct,&environment_number,ACCESS_1);
					break;
				case 1:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,WATER_1);
					write_next_struct(environment_struct,&environment_number,WATER_1);
					break;
				case 2:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,SMOKE_1);
					write_next_struct(environment_struct,&environment_number,SMOKE_1);
					smoke_flag=1;
					break;
				case 3:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,GLASS_1);
					write_next_struct(environment_struct,&environment_number,GLASS_1);
					break;
				case 4:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,INFRARED_1);
					write_next_struct(environment_struct,&environment_number,INFRARED_1);
					break;
				case 5:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,GLASS_1);
					write_next_struct(environment_struct,&environment_number,GLASS_1);
					break;
				case 6:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,ACCESS_2);
					write_next_struct(environment_struct,&environment_number,ACCESS_2);
					break;
				case 7:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,ACCESS_3);
					write_next_struct(environment_struct,&environment_number,ACCESS_3);
					break;
				case 8:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,ACCESS_4);
					write_next_struct(environment_struct,&environment_number,ACCESS_4);
					break;
				case 9:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,GLASS_2);
					write_next_struct(environment_struct,&environment_number,GLASS_2);
					break;
				case 10:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,GLASS_3);
					write_next_struct(environment_struct,&environment_number,GLASS_3);
					break;
				case 11:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,GLASS_4);
					write_next_struct(environment_struct,&environment_number,GLASS_4);
					break;
				case 12:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,WATER_2);
					write_next_struct(environment_struct,&environment_number,WATER_2);
					break;
				case 13:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,WATER_3);
					write_next_struct(environment_struct,&environment_number,WATER_3);
					break;
				case 14:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,WATER_4);
					write_next_struct(environment_struct,&environment_number,WATER_4);
					break;
				case 15:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,SMOKE_2);
					write_next_struct(environment_struct,&environment_number,SMOKE_2);
					smoke_flag=1;
					break;
				case 16:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,SMOKE_3);
					write_next_struct(environment_struct,&environment_number,SMOKE_3);
					smoke_flag=1;
					break;
				case 17:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,SMOKE_4);
					write_next_struct(environment_struct,&environment_number,SMOKE_4);
					smoke_flag=1;
					break;
				case 19:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,INFRARED_2);
					write_next_struct(environment_struct,&environment_number,INFRARED_2);
					break;
				case 20:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,INFRARED_3);
					write_next_struct(environment_struct,&environment_number,INFRARED_3);
					break;
				case 21:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,INFRARED_4);
					write_next_struct(environment_struct,&environment_number,INFRARED_4);
					break;
				case 22:
					write_next_id_struct(id_struct,&id_number,SPD_DEVICE,SPD_ERROR_1);
					write_next_struct(spd_struct,&spd_number,SPD_ERROR_1);
					break;
				case 23:
					write_next_id_struct(id_struct,&id_number,SPD_DEVICE,SPD_ERROR_2);
					write_next_struct(spd_struct,&spd_number,SPD_ERROR_2);
					break;
				default:
					break;
			}
		}				
	}
	if(smoke_flag==1)
	{
		write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,SMOKE_RESET);
		write_next_struct(environment_struct,&environment_number,SMOKE_RESET);
	}

	
	//读取DO量
	sections="RTUDOSet";
	keys="DO";
	read_profile_string(sections,keys,cfg,256,"",inifile);
	ini_to_array(cfg,temp,16);
	for(i=0;i<8;i++)
	{
		if(temp[i]!=255)
		{
			switch(temp[i])
			{
				case 1:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,LIGHT_CONTROL_1);
					write_next_struct(environment_struct,&environment_number,LIGHT_CONTROL_1);
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,LIGHT_1);
					write_next_struct(environment_struct,&environment_number,LIGHT_1);
					light_flag=1;
					light_to_DO[0]=i;
					break;
				case 2:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,LIGHT_CONTROL_2);
					write_next_struct(environment_struct,&environment_number,LIGHT_CONTROL_2);
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,LIGHT_2);
					write_next_struct(environment_struct,&environment_number,LIGHT_2);
					light_flag=1;
					light_to_DO[1]=i;
					break;
				case 3:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,LIGHT_CONTROL_3);
					write_next_struct(environment_struct,&environment_number,LIGHT_CONTROL_3);
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,LIGHT_3);
					write_next_struct(environment_struct,&environment_number,LIGHT_3);
					light_flag=1;
					light_to_DO[2]=i;
					break;
				case 4:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,BUZZER_1);
					write_next_struct(environment_struct,&environment_number,BUZZER_1);
					buzzer_to_DO[0]=i;
					break;
				case 5:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,BUZZER_2);
					write_next_struct(environment_struct,&environment_number,BUZZER_2);
					buzzer_to_DO[1]=i;
					break;
				case 6:
					write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,BUZZER_3);
					write_next_struct(environment_struct,&environment_number,BUZZER_3);
					buzzer_to_DO[2]=i;
					break;
				default:
					break;
			}
		}
	}
	if(light_flag==1)
	{
		write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,LIGHT_DELAY);
		write_next_struct(environment_struct,&environment_number,LIGHT_DELAY);
	}
	
	//读取串口数据
	unsigned char temp_com[7];
	sections="RTUCOMSet";      
	for(i=1;i<=7;i++)
	{
		//先将ini文件中的各串口功能读取到temp_com_task中
		sprintf(key,"com%d",i);
		read_profile_string(sections,key,cfg,256,"",inifile);
		ini_to_array(cfg,temp_com,7);
		//判断串口功能
		if(temp_com[0]!=255)
		{
			switch(temp_com[0])
			{
				case 2:
					power_flag[0]=1;
					power_flag[1]=i;
					power_flag[2]=temp_com[6];
					break;
				case 3:
					air_flag[0]=1;
					air_flag[1]=i;
					air_flag[2]=temp_com[6];
					break;
				case 4:
					battery_flag[0]=1;
					battery_flag[1]=i;
					battery_flag[2]=temp_com[6];
					break;
				case 6:
					acdu_flag[0]=1;
					acdu_flag[1]=i;
					acdu_flag[2]=temp_com[6];
					break;
				case 7:
					ups_flag[0]=1;
					ups_flag[1]=i;
					ups_flag[2]=temp_com[6];
					break;
				case 8:
					smart_access_flag[0]=1;
					smart_access_flag[1]=i;
					smart_access_flag[2]=temp_com[6];
					break;
				case 9:
					spd_flag[0]=1;
					spd_flag[1]=i;
					spd_flag[2]=temp_com[6];
					break;
				default:
					break;
			}	
		}
	}
	
	//初始化电源节点
	//暂时未区分有几个整流器
	if(power_flag[0]==1)
	{
		for(i=1;i<=POWER_SIZE;i++)
		{
			write_next_id_struct(id_struct,&id_number,POWER_DEVICE,i);
			write_next_struct(power_struct,&power_number,i);
		}
	}
//////////////////////////////////////////////////////
air_flag[0]=1;
air_flag[2]=2;

////////////////////////////////////////////////////////////



	//初始化空调节点
	if(air_flag[0]==1)
	{
		if(air_flag[2]==1)
		{
			for(i=1;i<=13;i++)
			{
				write_next_id_struct(id_struct,&id_number,AIRCONDITIONER_DEVICE,i);
				write_next_struct(air_struct,&air_number,i);
			}
		}
		else if(air_flag[2]==2)
		{
			for(i=1;i<=26;i++)
			{
				write_next_id_struct(id_struct,&id_number,AIRCONDITIONER_DEVICE,i);
				write_next_struct(air_struct,&air_number,i);
			}
		}
		else if(air_flag[2]==3)
		{
			for(i=1;i<=39;i++)
			{
				write_next_id_struct(id_struct,&id_number,AIRCONDITIONER_DEVICE,i);
				write_next_struct(air_struct,&air_number,i);
			}
		}
	}

	//初始化acdu节点
	if(acdu_flag[0]==1)
	{
		if(acdu_flag[2]==1)
		{
			for(i=1;i<=3;i++)
			{
				write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,i);
				write_next_struct(acdu_struct,&acdu_number,i);
			}
			write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,ACDU_CONNECTION_1);
			write_next_struct(acdu_struct,&acdu_number,ACDU_CONNECTION_1);
		}
		else if(acdu_flag[2]==2)
		{
			for(i=1;i<=6;i++)
			{
				write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,i);
				write_next_struct(acdu_struct,&acdu_number,i);
			}
			write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,ACDU_CONNECTION_1);
			write_next_struct(acdu_struct,&acdu_number,ACDU_CONNECTION_1);
			write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,ACDU_CONNECTION_2);
			write_next_struct(acdu_struct,&acdu_number,ACDU_CONNECTION_2);
		}
		
	}

	//初始化UPS节点
	if(ups_flag[0]==1)
	{
		for(i=1;i<=UPS_SIZE;i++)
		{
			write_next_id_struct(id_struct,&id_number,UPS_DEVICE,i);
			write_next_struct(ups_struct,&ups_number,i);
		}
	}   

	//初始化SPD节点
	if(spd_flag[0]==1)
	{
		for(i=0;i<=SPD_SIZE;i++)
		{
			write_next_id_struct(id_struct,&id_number,SPD_DEVICE,i);
			write_next_struct(spd_struct,&spd_number,i);
		}
	}

	//读取并初始化单体电池节点
	if(battery_flag[0]==1)
	{
		sections="RTUDBSet";
		keys="DB";
		read_profile_string(sections,keys,cfg,256,"",inifile);
		ini_to_array(cfg,battery_num,7);
		if(battery_num[0]!=0)
		{
			for(i=1;i<=battery_num[0];i++)
			{
				write_next_id_struct(id_struct,&id_number,BATTERY_DEVICE,i);
				write_next_struct(battery_struct,&battery_number,i);
			}
			write_next_id_struct(id_struct,&id_number,BATTERY_DEVICE,BATTERY_READ_RESISTANCE);
			write_next_struct(battery_struct,&battery_number,BATTERY_READ_RESISTANCE);
			for(i=0;i<(battery_num[1]+battery_num[2]+battery_num[3]+battery_num[4]+battery_num[5]+battery_num[6]);i++)
			{
				write_next_id_struct(id_struct,&id_number,BATTERY_DEVICE,i*4+11);
				write_next_struct(battery_struct,&battery_number,i*4+11);
				write_next_id_struct(id_struct,&id_number,BATTERY_DEVICE,i*4+12);
				write_next_struct(battery_struct,&battery_number,i*4+12);
				write_next_id_struct(id_struct,&id_number,BATTERY_DEVICE,i*4+13);
				write_next_struct(battery_struct,&battery_number,i*4+13);
				write_next_id_struct(id_struct,&id_number,BATTERY_DEVICE,i*4+14);
				write_next_struct(battery_struct,&battery_number,i*4+14);
			}
		}
	}
	printf("\nbattery ended\n");
		
	//初始化设备节点
	//id_struct、device_struct中各添加一份
	if(environment_number>0)
	{
		write_next_id_struct(id_struct,&id_number,ENVIRONMENT_DEVICE,0);
		write_next_id_struct(device_struct,&device_number,ENVIRONMENT_DEVICE,0);
	}
	if(power_number>0)
	{
		write_next_id_struct(id_struct,&id_number,POWER_DEVICE,0);
		write_next_id_struct(device_struct,&device_number,POWER_DEVICE,0);
	}
	if(ups_number>0)
	{
		write_next_id_struct(id_struct,&id_number,UPS_DEVICE,0);
		write_next_id_struct(device_struct,&device_number,UPS_DEVICE,0);
	}
	if(acdu_number>0)
	{
		write_next_id_struct(id_struct,&id_number,ACDU_DEVICE,0);
		write_next_id_struct(device_struct,&device_number,ACDU_DEVICE,0);
	}
	if(air_number>0)
	{
		write_next_id_struct(id_struct,&id_number,AIRCONDITIONER_DEVICE,0);
		write_next_id_struct(device_struct,&device_number,AIRCONDITIONER_DEVICE,0);
	}
	if(spd_number>0)
	{
		write_next_id_struct(id_struct,&id_number,SPD_DEVICE,0);
		write_next_id_struct(device_struct,&device_number,SPD_DEVICE,0);
	}
	if(battery_number>0)
	{
		write_next_id_struct(id_struct,&id_number,BATTERY_DEVICE,0);
		write_next_id_struct(device_struct,&device_number,BATTERY_DEVICE,0);
	}

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//以上为节点初始化，下面为属性初始化
	//将属性从ini读取到结构体数组中
	printf("\n id property initializing is now started\n ");
	char rtu_buf[1024]={0};
	char power_buf[1024*50]={0};
	char ups_buf[1024*50]={0};
	char acdu_buf[1024*50]={0};
	char environment_buf[1024*50]={0};
	char air_buf[1024*50]={0};
	char spd_buf[1024*50]={0};
	char db_buf[1024*50]={0};

	inifile="/app/rtu.pro.ini";
	load_ini_file(inifile,rtu_buf,&file_size);
	printf("\nrtu buffer\n");
	inifile="/app/power.pro.ini";
	load_ini_file(inifile,power_buf,&file_size);
	printf("\npower buffer\n");
	inifile="/app/ups.pro.ini";
	load_ini_file(inifile,ups_buf,&file_size);
	printf("\nups buffer\n");
	inifile="/app/acdu.pro.ini";
	load_ini_file(inifile,acdu_buf,&file_size);
	printf("\nacdu buffer\n");
	inifile="/app/environment.pro.ini";
	load_ini_file(inifile,environment_buf,&file_size);
	printf("\nenvironment buffer\n");
	inifile="/app/air.pro.ini";
	load_ini_file(inifile,air_buf,&file_size);
	printf("\nair buffer\n");
	inifile="/app/spd.pro.ini";
	load_ini_file(inifile,spd_buf,&file_size);
	printf("\nspd buffer\n");
	inifile="/app/db.pro.ini";
	load_ini_file(inifile,db_buf,&file_size);
	printf("\ndb buffer\n");
	for(i=0;i<id_number;i++)
	{
		printf("\nnow is the %dth point\n",i);
		switch(id_struct[i].device)
		{
			case 0:
				write_property(rtu_buf,id_struct[i].device,id_struct[i].point);
				break;
			case POWER_DEVICE:
				write_property(power_buf,id_struct[i].device,id_struct[i].point);
				break;
			case UPS_DEVICE:
				write_property(ups_buf,id_struct[i].device,id_struct[i].point);
				break;
			case ACDU_DEVICE:
				write_property(acdu_buf,id_struct[i].device,id_struct[i].point);
				break;
			case ENVIRONMENT_DEVICE:
				write_property(environment_buf,id_struct[i].device,id_struct[i].point);
				break;
			case AIRCONDITIONER_DEVICE:
				write_property(air_buf,id_struct[i].device,id_struct[i].point);
				break;
			case SPD_DEVICE:
				write_property(spd_buf,id_struct[i].device,id_struct[i].point);
				break;
			case BATTERY_DEVICE:
				if(id_struct[i].point<=7)
					write_property(db_buf,id_struct[i].device,id_struct[i].point);
				break;
			default:
				break;
		}
	}
	printf("\nnow is the battery points\n");
	if(battery_flag[0]==1)//如果有电池
	{
		Pro_TypeDef temp_pro;
		char value[256];
		char temp_section[10];
		char temp_num[2];//用于格式化数字
		
		int battery_before=0;//本组之前的电池节数
		for(i=1;i<=battery_num[0];i++)//电池组数
		{	
			//电压
			sprintf(temp_section,"%d",i*4+7);
			sections=temp_section;
			keys="Name";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Name[0]), 0x20, 30);
			unicode_to_char(value,&(temp_pro.Name[0]));
			keys="MaxVal";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.MaxVal=atof(value);
			keys="MinVal";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.MinVal=atof(value);
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.AlarmEnable=atoi(value);
			keys="HiLimit1";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit1=atof(value);
			keys="HiLimit2";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit2=atof(value);
			keys="HiLimit3";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit3=atof(value);
			keys="LoLimit1";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit1=atof(value);
			keys="LoLimit2";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit2=atof(value);
			keys="LoLimit3";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit3=atof(value);
			keys="Stander";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Stander=atof(value);
			keys="Percision";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Percision=atof(value);
			keys="Unit";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Unit[0]), 0x20, 5);
			unicode_to_char(value,&(temp_pro.Unit[0]));
			for(m=1;m<=battery_num[i];m++)//每组中各节电池
			{
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Type=3;
				//名称格式为i组j节电压
				for(n=0;n<30;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Name[n]=temp_pro.Name[n];
				}
				sprintf(temp_num,"%02d",m);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Name[3]=temp_num[0];
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Name[4]=temp_num[1];
				memset(&(gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Des[0]), 0x20, 40);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].MaxVal=temp_pro.MaxVal;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].MinVal=temp_pro.MinVal;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Alarmlevel=temp_pro.Alarmlevel;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].AlarmEnable=temp_pro.AlarmEnable;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].HiLimit1=temp_pro.HiLimit1;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].HiLimit2=temp_pro.HiLimit2;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].HiLimit3=temp_pro.HiLimit3;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].LoLimit1=temp_pro.LoLimit1;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].LoLimit2=temp_pro.LoLimit2;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].LoLimit3=temp_pro.LoLimit3;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Stander=temp_pro.Stander;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Percision=temp_pro.Percision;
				for(n=0;n<5;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+7].Unit[n]=temp_pro.Unit[n];
				}
			}
			
			//温度
			sprintf(temp_section,"%d",i*4+8);
			sections=temp_section;
			keys="Name";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Name[0]), 0x20, 30);
			unicode_to_char(value,&(temp_pro.Name[0]));
			keys="MaxVal";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.MaxVal=atof(value);
			keys="MinVal";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.MinVal=atof(value);
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.AlarmEnable=atoi(value);
			keys="HiLimit1";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit1=atof(value);
			keys="HiLimit2";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit2=atof(value);
			keys="HiLimit3";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit3=atof(value);
			keys="LoLimit1";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit1=atof(value);
			keys="LoLimit2";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit2=atof(value);
			keys="LoLimit3";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit3=atof(value);
			keys="Stander";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Stander=atof(value);
			keys="Percision";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Percision=atof(value);
			keys="Unit";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Unit[0]), 0x20, 5);
			unicode_to_char(value,&(temp_pro.Unit[0]));
			for(m=1;m<=battery_num[i];m++)//每组中各节电池
			{
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Type=3;
				//名称格式为i组j节电压
				for(n=0;n<30;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Name[n]=temp_pro.Name[n];
				}
				sprintf(temp_num,"%02d",m);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Name[3]=temp_num[0];
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Name[4]=temp_num[1];
				memset(&(gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Des[0]), 0x20, 40);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].MaxVal=temp_pro.MaxVal;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].MinVal=temp_pro.MinVal;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Alarmlevel=temp_pro.Alarmlevel;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].AlarmEnable=temp_pro.AlarmEnable;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].HiLimit1=temp_pro.HiLimit1;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].HiLimit2=temp_pro.HiLimit2;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].HiLimit3=temp_pro.HiLimit3;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].LoLimit1=temp_pro.LoLimit1;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].LoLimit2=temp_pro.LoLimit2;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].LoLimit3=temp_pro.LoLimit3;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Stander=temp_pro.Stander;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Percision=temp_pro.Percision;
				for(n=0;n<5;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+8].Unit[n]=temp_pro.Unit[n];
				}
			}
			
			//内阻
			sprintf(temp_section,"%d",i*4+9);
			sections=temp_section;
			keys="Name";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Name[0]), 0x20, 30);
			unicode_to_char(value,&(temp_pro.Name[0]));
			keys="MaxVal";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.MaxVal=atof(value);
			keys="MinVal";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.MinVal=atof(value);
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.AlarmEnable=atoi(value);
			keys="HiLimit1";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit1=atof(value);
			keys="HiLimit2";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit2=atof(value);
			keys="HiLimit3";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.HiLimit3=atof(value);
			keys="LoLimit1";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit1=atof(value);
			keys="LoLimit2";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit2=atof(value);
			keys="LoLimit3";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.LoLimit3=atof(value);
			keys="Stander";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Stander=atof(value);
			keys="Percision";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Percision=atof(value);
			keys="Unit";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Unit[0]), 0x20, 5);
			unicode_to_char(value,&(temp_pro.Unit[0]));
			for(m=1;m<=battery_num[i];m++)//每组中各节电池
			{
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Type=3;
				//名称格式为i组j节电压
				for(n=0;n<30;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Name[n]=temp_pro.Name[n];
				}
				sprintf(temp_num,"%02d",m);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Name[3]=temp_num[0];
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Name[4]=temp_num[1];
				memset(&(gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Des[0]), 0x20, 40);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].MaxVal=temp_pro.MaxVal;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].MinVal=temp_pro.MinVal;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Alarmlevel=temp_pro.Alarmlevel;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].AlarmEnable=temp_pro.AlarmEnable;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].HiLimit1=temp_pro.HiLimit1;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].HiLimit2=temp_pro.HiLimit2;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].HiLimit3=temp_pro.HiLimit3;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].LoLimit1=temp_pro.LoLimit1;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].LoLimit2=temp_pro.LoLimit2;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].LoLimit3=temp_pro.LoLimit3;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Stander=temp_pro.Stander;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Percision=temp_pro.Percision;
				for(n=0;n<5;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+9].Unit[n]=temp_pro.Unit[n];
				}
			}
			
			//通断
			sprintf(temp_section,"%d",i*4+10);
			sections=temp_section;
			keys="Name";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Name[0]), 0x20, 30);
			unicode_to_char(value,&(temp_pro.Name[0]));
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.AlarmEnable=atoi(value);
			keys="AlarmThresbhold";
			read_property_ini_string(sections,keys,db_buf,value);
			temp_pro.AlarmThresbhold=atoi(value);
			keys="Des0";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Des0[0]), 0x20, 10);
			unicode_to_char(value,&(temp_pro.Des0[0]));
			keys="Des1";
			read_property_ini_string(sections,keys,db_buf,value);
			memset(&(temp_pro.Des1[0]), 0x20, 10);
			unicode_to_char(value,&(temp_pro.Des1[0]));
			for(m=1;m<=battery_num[i];m++)//每组中各节电池
			{
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Type=2;
				//名称格式为i组j节电压
				for(n=0;n<30;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Name[n]=temp_pro.Name[n];
				}
				sprintf(temp_num,"%02d",m);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Name[3]=temp_num[0];
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Name[4]=temp_num[1];
				memset(&(gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Des[0]), 0x20, 40);
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Alarmlevel=temp_pro.Alarmlevel;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].AlarmEnable=temp_pro.AlarmEnable;
				gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].AlarmThresbhold=temp_pro.AlarmThresbhold;
				for(n=0;n<10;n++)
				{
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Des0[n]=temp_pro.Des0[n];
					gs_ProMng.Pro[BATTERY_DEVICE][(battery_before+m)*4+10].Des1[n]=temp_pro.Des1[n];
				}
			}
			battery_before+=battery_num[i];
		}
	}
	printf("\nnow the battery property is completed\n");
	//灯控延时数值从属性中取出(标称值)
	int delay_time=(int)(gs_ProMng.Pro[ENVIRONMENT_DEVICE][LIGHT_DELAY].Stander*10);
	gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_DELAY,DATA,&delay_time);
	printf("\nid property initializing completed\n");
}
