/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : typedef.h
 *  CREATOR  : RTU Team                 DATE: 2009-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/
#include "stdsys.h"

//#define DI_test_NUM           254	


#define IC_NUM       50

//Version
#define LcdVersion  "   V6.61   CRCC   @0424 "
#define LanServerVersion  "V6.61  ZXDU58 IR@CRCC_0424"


//////////////////////////////////////
//“‘œ¬Œ™ Ù–‘”√µƒ∫Í

//÷––ƒµÿ÷∑
#define CENTER_ID               1
//…Ë±∏∫≈
#define POWER_DEVICE            1
#define UPS_DEVICE              2
#define ACDU_DEVICE             3
#define ENVIRONMENT_DEVICE      4
#define AIRCONDITIONER_DEVICE   5
#define SPD_DEVICE              6
#define BATTERY_DEVICE          7
#define SMART_LOCK_DEVICE       8
#define DCDU_DEVICE             9
#define GENERATOR_DEVICE        10

//∏˜…Ë±∏◊Ó∂‡ø…ƒ‹Ω⁄µ„ ˝
#define ID_SIZE              800
#define POWER_SIZE           103
#define UPS_SIZE             39
#define BATTERY_SIZE         500
#define ENVIRONMENT_SIZE     72
#define ACDU_SIZE            8
#define SPD_SIZE             17
#define AIR_SIZE             39
#define DEVICE_SIZE          10

//∑¿¿◊∆˜
#define SPD_LAST_LIGHTNING_TIME_YEAR        1
#define SPD_LAST_LIGHTNING_TIME_MONTH       2
#define SPD_LAST_LIGHTNING_TIME_DAY         3
#define SPD_LAST_LIGHTNING_TIME_HOUR        4
#define SPD_LAST_LIGHTNING_TIME_MINUTE      5
#define SPD_LAST_LIGHTNING_TIME_SECOND      6
#define SPD_LAST_LIGHTNING_PEAK             7
#define SPD_CUMULATIVE_NUMBER               8
#define SPD_CONNECTION                      9
#define SPD_INVALID_1_ALARM                 10
#define SPD_INVALID_2_ALARM                 11
#define SPD_SWITCH_TRIP_1_ALARM             12
#define SPD_SWITCH_TRIP_2_ALARM             13
#define SPD_POWER_OFF_1_ALARM               14
#define SPD_POWER_OFF_2_ALARM               15
#define SPD_ERROR_1                         16
#define SPD_ERROR_2                         17

//µÁ‘¥∏˜œÓ
#define POWER_A_VOLTAGE_1               1
#define POWER_B_VOLTAGE_1               2
#define POWER_C_VOLTAGE_1               3
#define POWER_A_VOLTAGE_2               4
#define POWER_B_VOLTAGE_2               5
#define POWER_C_VOLTAGE_2               6
#define POWER_DC_CURRENT                7
#define POWER_DC_VOLTAGE                8
#define POWER_BATTERY_VOLTAGE_1         9
#define POWER_BATTERY_VOLTAGE_2         10
#define POWER_BATTERY_CURRENT_1         11
#define POWER_BATTERY_CURRENT_2         12
#define POWER_BATTERY_TEM_1             13
#define POWER_BATTERY_TEM_2             14
#define POWER_BATTERY_CAP_1             15
#define POWER_BATTERY_CAP_2             16
#define POWER_CONNECTION                17
#define POWER_RECTIFIER_CURRENT_1       18
//18-33Œ™’˚¡˜∆˜1-16µÁ¡˜
#define POWER_RECTIFIER_SWITCH_1        34
//34-49Œ™’˚¡˜∆˜1-16ø™πÿª˙◊¥Ã¨
#define POWER_RECTIFIER_STATUS_1        50
//50-65Œ™’˚¡˜∆˜1-16‘À––◊¥Ã¨
#define POWER_RECTIFIER_CHARGE_1        66
//66-81Œ™’˚¡˜∆˜1-16æ˘∏°≥‰◊¥Ã¨
#define POWER_DC_STATUS_1               82
//82-91Œ™÷±¡˜∑÷¬∑1-10◊¥Ã¨
#define POWER_AC_OFF_ALARM              92
#define POWER_LOAD_BREAK_ALARM          93
#define POWER_CITY_OFF_1                94
#define POWER_CITY_OFF_2                95
#define POWER_CITY_STATUS               96
#define POWER_SPD_STATUS                97
#define POWER_AC_IN_STATUS              98
#define POWER_AC_OUT_STATUS             99
#define POWER_BATTERY_STATUS_1          100
#define POWER_BATTERY_STATUS_2          101
#define POWER_BATTERY_CHARGE_1          102
#define POWER_BATTERY_CHARGE_2          103




//ª∑æ≥¡ø
#define TEMPERATURE_1      1
#define HUMIDITY_1         2
#define TEMPERATURE_2      3
#define HUMIDITY_2         4
#define TEMPERATURE_3      5
#define HUMIDITY_3         6
#define TEMPERATURE_4      7
#define HUMIDITY_4         8
#define TEMPERATURE_5      9
#define HUMIDITY_5         10
#define ACCESS_1           11
#define WATER_1            12
#define SMOKE_1            13
#define GLASS_1            14
#define INFRARED_1         15
#define LIGHT_1            16
#define BUZZER_1           17
#define SPD_1              18
#define ACCESS_2           19
#define WATER_2            20
#define SMOKE_2            21
#define GLASS_2            22
#define INFRARED_2         23
#define LIGHT_2            24
#define BUZZER_2           25
#define SPD_2              26
#define ACCESS_3           27
#define WATER_3            28
#define SMOKE_3            29
#define GLASS_3            30
#define INFRARED_3         31
#define LIGHT_3            32
#define BUZZER_3           33
#define SPD_3              34
#define ACCESS_4           35
#define WATER_4            36
#define SMOKE_4            37
#define GLASS_4            38
#define INFRARED_4         39
#define LIGHT_4            40
#define BUZZER_4           41
#define SPD_4              42
#define SMOKE_RESET        67
#define LIGHT_CONTROL_1    68
#define LIGHT_CONTROL_2    69
#define LIGHT_CONTROL_3    70
#define LIGHT_CONTROL_4    71
#define LIGHT_DELAY        72

//ups
#define UPS_BATTERY_VOLTAGE             1
#define UPS_BATTERY_CAPACITY            2
#define UPS_BATTERY_TIME_LEFT           3
#define UPS_INPUT_FREQUENCY             4
#define UPS_OUTPUT_FREQUENCY            5
#define UPS_BYPASS_FREQUENCY            6
#define UPS_INPUT_VOLTAGE_A             7
#define UPS_INPUT_VOLTAGE_B             8
#define UPS_INPUT_VOLTAGE_C             9
#define UPS_OUTPUT_VOLTAGE_A            10
#define UPS_OUTPUT_VOLTAGE_B            11
#define UPS_OUTPUT_VOLTAGE_C            12
#define UPS_BYPASS_VOLTAGE_A            13
#define UPS_BYPASS_VOLTAGE_B            14
#define UPS_BYPASS_VOLTAGE_C            15
#define UPS_OUTPUT_CURRENT_A            16
#define UPS_OUTPUT_CURRENT_B            17
#define UPS_OUTPUT_CURRENT_C            18
#define UPS_LOAD_A                      19
#define UPS_LOAD_B                      20
#define UPS_LOAD_C                      21
#define UPS_TEMPERATURE                 22
#define UPS_CONNECTION_ALARM            30
#define UPS_STATUS                      31
#define UPS_CHARGE_STATUS               32
#define UPS_CITY_VOLTAGE_LOW_ALARM      33
#define UPS_CITY_VOLTAGE_HIGH_ALARM     34
#define UPS_BYPASS_VOLTAGE_LOW_ALARM    35
#define UPS_BYPASS_VOLTAGE_HIGH_ALARM   36
#define UPS_OUTPUT_OVERLOAD_ALARM       37
#define UPS_BATTERY_VOLTAGE_LOW_ALARM   38
#define UPS_BATTERY_VOLTAGE_HIGH_ALARM  39


//ø’µ˜
#define AIR_CONNECTION_1             1
#define AIR_POWER_SWITCH_I_1         2
#define AIR_POWER_SWITCH_O_1         3
#define AIR_MODE_I_1                 4
#define AIR_MODE_O_1                 5
#define AIR_TEM_SET_I_1              6
#define AIR_TEM_SET_O_1              7
#define AIR_VOLTAGE_A_1              8
#define AIR_CURRENT_A_1              9
#define AIR_VOLTAGE_B_1              10
#define AIR_CURRENT_B_1              11
#define AIR_VOLTAGE_C_1              12
#define AIR_CURRENT_C_1              13
#define AIR_CONNECTION_2             14
#define AIR_POWER_SWITCH_I_2         15
#define AIR_POWER_SWITCH_O_2         16
#define AIR_MODE_I_2                 17
#define AIR_MODE_O_2                 18
#define AIR_TEM_SET_I_2              19
#define AIR_TEM_SET_O_2              20
#define AIR_VOLTAGE_A_2              21
#define AIR_CURRENT_A_2              22
#define AIR_VOLTAGE_B_2              23
#define AIR_CURRENT_B_2              24
#define AIR_VOLTAGE_C_2              25
#define AIR_CURRENT_C_2              26
#define AIR_CONNECTION_3             27
#define AIR_POWER_SWITCH_I_3         28
#define AIR_POWER_SWITCH_O_3         29
#define AIR_MODE_I_3                 30
#define AIR_MODE_O_3                 31
#define AIR_TEM_SET_I_3              32
#define AIR_TEM_SET_O_3              33
#define AIR_VOLTAGE_A_3              34
#define AIR_CURRENT_A_3              35
#define AIR_VOLTAGE_B_3              36
#define AIR_CURRENT_B_3              37
#define AIR_VOLTAGE_C_3              38
#define AIR_CURRENT_C_3              39


//Ωª¡˜≈‰µÁ
#define ACDU_VOLTAGE_A_1          1
#define ACDU_VOLTAGE_B_1          2
#define ACDU_VOLTAGE_C_1          3
#define ACDU_CONNECTION_1         4
#define ACDU_VOLTAGE_A_2          5
#define ACDU_VOLTAGE_B_2          6
#define ACDU_VOLTAGE_C_2          7
#define ACDU_CONNECTION_2         8

//µ•ÃÂµÁ≥ÿ
#define BATTERY_VOLTAGE_DIFFERENTIAL_1     1
#define BATTERY_VOLTAGE_DIFFERENTIAL_2     2
#define BATTERY_VOLTAGE_DIFFERENTIAL_3     3
#define BATTERY_VOLTAGE_DIFFERENTIAL_4     4
#define BATTERY_VOLTAGE_DIFFERENTIAL_5     5
#define BATTERY_VOLTAGE_DIFFERENTIAL_6     6
#define BATTERY_READ_RESISTANCE            7

// ¥”11ø™ º£¨√ø∏ˆµÁ≥ÿ π”√Àƒ∏ˆµ„£¨µÁ—π°¢Œ¬∂»°¢ƒ⁄◊Ë°¢Õ®–≈

////“‘…œŒ™ Ù–‘”√µƒ∫Í
//////////////////////////////////////////////////////////////////////////////////

//alarm
#define ALARM_FLAG_START            1
#define ALARM_FLAG_END              0
#define ALARM_FLAG_HIGH_START       1
#define ALARM_FLAG_LOW_START       -1
#define ALARM_CONTENT_RECOVER       0
#define ALARM_CONTENT_ALARM         1
#define ALARM_CONTENT_HIGH          2
#define ALARM_CONTENT_HIGH_1        3
#define ALARM_CONTENT_HIGH_2        4
#define ALARM_CONTENT_HIGH_3        5
#define ALARM_CONTENT_LOW           6
#define ALARM_CONTENT_LOW_1         7
#define ALARM_CONTENT_LOW_2         8
#define ALARM_CONTENT_LOW_3         9
#define ALARM_CONTENT_POWER_FAIL    10
#define ALARM_CONTENT_ERROR         11
#define ALARM_CONTENT_BREAK         12
#define ALARM_CONTENT_ON            13
#define ALARM_CONTENT_OFF           14
#define ALARM_CONTENT_FUSE_BREAK    15
#define ALARM_CONTENT_DISCHARGE     16



#define ALARM_ID_TEM_1             1
#define ALARM_ID_HUMIDITY_1        2
#define ALARM_ID_TEM_2             3
#define ALARM_ID_HUMIDITY_2        4
#define ALARM_ID_TEM_3             5
#define ALARM_ID_HUMIDITY_3        6
#define ALARM_ID_TEM_4             7
#define ALARM_ID_HUMIDITY_4        8
#define ALARM_ID_TEM_5             9
#define ALARM_ID_HUMIDITY_5        10
#define ALARM_ID_ACDU_A_1          11
#define ALARM_ID_ACDU_B_1          12
#define ALARM_ID_ACDU_C_1          13
#define ALARM_ID_ACDU_A_2          14
#define ALARM_ID_ACDU_B_2          15
#define ALARM_ID_ACDU_C_2          16
#define ALARM_ID_AIR_CUR_A_1       17
#define ALARM_ID_AIR_VOL_A_1       18


//pw_PARA
#define PARA_PowerModel_NUM                        0
#define PARA_FloatVoltLow_NUM                      1
#define PARA_FloatVoltHigh_NUM                     2
#define PARA_ConstantVoltLow_NUM               3
#define PARA_ConstantVoltHigh_NUM                  4
#define PARA_ACVoltLow_NUM                         5
#define PARA_ACVoltHigh_NUM                        6
#define PARA_DCVoltLow_NUM                         7
#define PARA_DCVoltHigh_NUM                        8
#define PARA_BattThresholdTemperature_NUM          9
#define PARA_ConstantTime_NUM                      10
#define PARA_ConstantCycle_NUM                     11
#define PARA_LVDRelinkVolt_NUM                     12
#define PARA_LVDLeaveVolt_NUM                      13
#define PARA_TemperatureModulus_NUM                14
#define PARA_ReferenceTemperature_NUM              15
#define PARA_BattGroupLowAlarmVolt_NUM             16
#define PARA_BattGroupProtectVolt_NUM              17
#define PARA_SMROverVoltShutDown_NUM               18
#define PARA_SMRLimitingAlarm_NUM                  19       
#define PARA_ModultTotal_NUM                       20
#define PARA_Switch_NUM                            21
#define PARA_ConstantVolt_NUM                      22
#define PARA_FloatVolt_NUM                        23
#define SET_PARA_TYPE_NUM                      24
#define SET_PARA_ACTION_NUM                  25
#define SET_PARA_FLAG_NUM                      26

//Aircon
#define AirCon_Address_NUM                     0
#define Aircon_Model_NUM                         1
#define Aircon_Version_NUM                      2
#define Aircon_SetPara_NUM                        3
#define Aircon_SetTemperature_NUM        4
#define Aircon_SetAddress_NUM                5
#define Aircon_SetModel_NUM                    6
#define Aircon_Controlflag_NUM                 7

//DB
#define DataBlock_Volt        1
#define DataBlock_Temp     2
#define DataBlock_BatteryPack1_NUM      0
#define DataBlock_BatteryPack2_NUM      1
#define DataBlock_BatteryPack3_NUM      2
#define DataBlock_BatteryPack4_NUM      3

//set_thre_val_flag
#define Set_AlarmThreVal_NUM 11
//pwalarmthreval
#define AC_higt_volt_NUM 0
#define AC_low_volt_NUM  1
#define AC_higt_curr_NUM 2
#define AC_low_curr_NUM 3
#define DC_higt_volt_NUM 4
#define DC_low_volt_NUM 5
#define high_temp_NUM 6
#define low_temp_NUM 7
#define high_humidity_NUM 8
#define low_humidity_NUM 9
#define RTU_log_NUM  19
#define RTU_lcd_NUM  20
#define RTU_backlight_NUM 21

//dbalarmthreval
#define DB_high_volt_NUM 0
#define DB_low_volt_NUM  1
#define DB_high_temp_NUM 2
#define DB_low_temp_NUM 3
#define DB_high_pressdiffvolt_NUM 4


/*
//ADcompensitionfactor
#define  AD1K_NUM               0
#define  AD1B_NUM               1
#define  AD2K_NUM               2
#define  AD2B_NUM               3
#define  AD3K_NUM               4
#define  AD3B_NUM               5
#define  AD4K_NUM               6
#define  AD4B_NUM               7
#define  AD5K_NUM               8
#define  AD5B_NUM               9
#define  AD6K_NUM               10
#define  AD6B_NUM               11
#define  AD7K_NUM               12
#define  AD7B_NUM               13
#define  AD8K_NUM               14
#define  AD8B_NUM               15
#define  AD9K_NUM               16
#define  AD9B_NUM               17
#define  AD10K_NUM              18
#define  AD10B_NUM              19
#define  AD11K_NUM              20
#define  AD11B_NUM              21
#define  AD12K_NUM              22
#define  AD12B_NUM              23
#define  AD13K_NUM              24
#define  AD13B_NUM              25
#define  AD14K_NUM              26
#define  AD14B_NUM              27
#define  AD15K_NUM              28
#define  AD15B_NUM              29
#define  AD16K_NUM              30
#define  AD16B_NUM              31
#define  Set_AD_NUM             32
*/
//cfg
#define RTU_addr_NUM               0 
#define RTU_startdelaytime_NUM     1
#define RTU_enddelaytime_NUM       2
#define RTU_Tel_NUM                3
#define RTU_AlarmReport_NUM        4        
#define RTU_COM1_NUM               5
#define RTU_COM2_NUM               6
#define RTU_COM3_NUM               7
#define RTU_COM4_NUM               8
#define RTU_COM5_NUM               9
#define RTU_DI_NUM                 10
#define RTU_AI_NUM                 11
#define RTU_DB_NUM                 12
#define RTU_IP_NUM                 13
#define RTU_netmask_NUM            14
#define RTU_gateway_NUM            15
#define RTU_mac_NUM                16
#define RTU_pwmodel_NUM            17
#define RTU_pwaddr_NUM             18
#define RTU_acmodel_NUM            19
#define RTU_videolinkage_NUM       20
#define RTU_stat_NUM               21
#define RTU_DO_NUM				   22  
#define RTU_COM6_NUM               23
#define RTU_COM7_NUM               24

#define DATA     0
#define STATUS   1

#define ALARM_NUM 10
#define PORT  10001
#define MAXSOCKFD 20
#define EVENT_NUM 1000
#define BUF_SIZE 256
#define CH_NUM 16
#define USING_CH_NUM 12
typedef	unsigned char (*DATA_INTERFACE_FUNC)(unsigned short i, void *pDataBuf);
typedef	unsigned char (*CDATA_INTERFACE_FUNC)(short int device, short int point,int i,void *pDataBuf);
typedef	unsigned char (*EVENT_INTERFACE_FUNC)(void *pDataBuf);
typedef void (*EVENT_INTERFACE_AI_FUNC)(short int device, short int point, int value,signed char *alarm_status,int alarmID);
typedef void (*EVENT_INTERFACE_DI_FUNC)(short int device, short int point, int value,signed char *alarm_status,int alarmID,int content);
typedef   unsigned char (*DBData_INTERFACE_FUNC)(unsigned char i,unsigned char ii,unsigned char iii,void*pDataBuf);
typedef   unsigned char (*Measure_INTERFACE_FUNC)(unsigned char i, unsigned char ii,void *pDataBuf);
typedef   int (*Property_INTERFACE_FUNC)(unsigned char i, unsigned char ii,void *pDataBuf,int ID);
typedef   unsigned char (*Set_Property_INTERFACE_FUNC)(short int i,short int ii);

typedef struct tagData
{
	int CData[230];
  signed short  Temperature;//ÁéØÂ¢ÉÊ∏©Â∫¶
  signed short  Humidity;//ÁéØÂ¢ÉÊπøÂ∫¶
  signed short  KTVolt;//Á©∫Ë∞ÉÁîµÂéã
  signed short  KTCurr;//Á©∫Ë∞ÉÁîµÊµÅ
  signed short  KTTempandPSModel;//Á©∫Ë∞ÉËÆæÂÆöÊ∏©Â∫¶+ÁîµÊ∫êÁ±ªÂûã
  signed short  ACVoltA;//‰∫§ÊµÅAÁõ∏ÁîµÂéã
  signed short  ACVoltB;//‰∫§ÊµÅBÁõ∏ÁîµÂéã
  signed short  ACVoltC;//‰∫§ÊµÅCÁõ∏ÁîµÂéã
  signed short  ACCurrA;//‰∫§ÊµÅAÁõ∏ÁîµÊµÅ
  signed short  ACCurrB;//‰∫§ÊµÅBÁõ∏ÁîµÊµÅ
  signed short  ACCurrC;//‰∫§ÊµÅCÁõ∏ÁîµÊµÅ
  signed short  LoadCurr;//Áõ¥ÊµÅË¥üËΩΩÊÄªÁîµÊµÅ
  signed short  RectCurr[16];//Ê®°Âùó1-16ËæìÂá∫ÁîµÊµÅ
  signed short  DCVolt;//Áõ¥ÊµÅËæìÂá∫ÊÄªÁîµÂéã
  signed short  Batt1Volt;//ÁîµÊ±†1ÁîµÂéã
  signed short  Batt2Volt;//ÁîµÊ±†2ÁîµÂéã
  signed short  Batt1Curr;//ËìÑÁîµÊ±†ÁªÑ1ÂÖÖÊîæÁîµÊµÅ
  signed short  Batt2Curr;//ËìÑÁîµÊ±†ÁªÑ2ÂÖÖÊîæÁîµÊµÅ
  signed short  Batt1Temp;//ËìÑÁîµÊ±†ÁªÑ1Ê∏©Â∫¶
  signed short  Batt2Temp;//ËìÑÁîµÊ±†ÁªÑ2Ê∏©Â∫¶
  signed short  Batt1Cap;//ËìÑÁîµÊ±†ÁªÑ1ÂÆπÈáè
  signed short  Batt2Cap;//ËìÑÁîµÊ±†ÁªÑ2ÂÆπÈáè
  unsigned short  Switch[11];//ÈÅ•‰ø°Èáè1-11
} Data_TypeDef;//ÂêàËÆ°		96Â≠óËäÇ//gs_DataMng;//ÂêàËÆ°		96Â≠óËäÇ


typedef struct tagDataMng
{
  Data_TypeDef Data;
  DATA_INTERFACE_FUNC       fSetData;
  DATA_INTERFACE_FUNC       fGetData;
} DataMng_TypeDef;
extern DataMng_TypeDef gs_DataMng;
//Event
typedef struct tagEvent
{
    			 int Value; 
	unsigned     int ID;
	unsigned 	char Name;
	unsigned 	char SYearHigh;
	unsigned 	char SYearLow;
	unsigned 	char SMonth;
	unsigned 	char SDay;
	unsigned 	char SHour;
	unsigned 	char SMinute;
	unsigned 	char SSecond;
	unsigned 	char EYearHigh;
	unsigned 	char EYearLow;
	unsigned 	char EMonth;
	unsigned 	char EDay;
	unsigned 	char EHour;
	unsigned 	char EMinute;
	unsigned 	char ESecond;  
	  signed 	char Flag;
	unsigned     int Device;
	unsigned     int Point;
	unsigned    char level;
	unsigned    char AlarmLevel;
	unsigned    char Content;
	unsigned 	char Type;   //  «∑Ò…œ±® 
}Event_TypeDef;

typedef struct tagEventMng
{
	int GetEventNum;
	int SetEventNum;
	Event_TypeDef   EventArray[EVENT_NUM];
	int Eventnum[EVENT_NUM]; 
	EVENT_INTERFACE_FUNC        fSetEvent;
	EVENT_INTERFACE_FUNC        fGetEvent;
	EVENT_INTERFACE_AI_FUNC     fJudgeAI;
	EVENT_INTERFACE_DI_FUNC     fJudgeDI;
}EventMng_TypeDef;
extern EventMng_TypeDef gs_EventMng;

//Aircon
typedef struct tagAirControlData
{
	unsigned char Address;
	unsigned char Model;
	unsigned short Version;
	unsigned char SetPara;
	unsigned char SetTemperature;
	unsigned char SetAddress;
	unsigned char SetModel;
	unsigned char Controlflag;
}AirControlData_TypeDef;

typedef struct tagAirControlDataMng
{
	AirControlData_TypeDef  AirConData;
	DATA_INTERFACE_FUNC       AirConSetData;
	DATA_INTERFACE_FUNC       AirConGetData;
} AirControlDataMng_TypeDef;
extern AirControlDataMng_TypeDef gs_AirControlMng;
//DB
typedef struct tagDataBlockData
{
	int Bat1Volt[24];
	int Bat2Volt[24];
	int Bat3Volt[24];
	int Bat4Volt[24];
	int Bat1Temp[24];
	int Bat2Temp[24];
	int Bat3Temp[24];
	int Bat4Temp[24];
	int Bat1Resistance[24];
	int Bat2Resistance[24];
	int Bat3Resistance[24];
	int Bat4Resistance[24];
	int GetBATRS;
}DataBlockData_TypeDef;
typedef struct tagBlockDataDataMng
{
	DataBlockData_TypeDef DBData;
	DBData_INTERFACE_FUNC    DBSetData;
	DBData_INTERFACE_FUNC    DBGetData;
}DataBlockDataMng_TypeDef;
extern DataBlockDataMng_TypeDef gs_DBDataMng;

//PW
typedef struct pw_alarm_thre_val
{
	int AC_high_volt;
	int AC_low_volt;
	int AC_high_curr;
	int AC_low_curr;
	int DC_high_volt;
	int DC_low_volt;
	int Temp_high;
	int Temp_low;
	int Humidity_high;
	int Humidity_low;
}pw_alarm_thre_val_TypeDef;
typedef struct tagpw_alarm_thre_valMng
{
	int threval_flag;
	unsigned short log;
	unsigned char lcd;
	unsigned char backlight;
	pw_alarm_thre_val_TypeDef  thre_val;
	DATA_INTERFACE_FUNC  Setthre_val;
	DATA_INTERFACE_FUNC  Getthre_val;
}pw_alarm_thre_valMng_TypeDef;
extern pw_alarm_thre_valMng_TypeDef gs_pwalarmMng;
//DB
typedef struct db_alarm_thre_val
{
	int DB_high_volt;
	int DB_low_volt;
	int DB_high_temp;
	int DB_low_temp;
	int DB_highpressdiffVolt;
	int DB2_high_volt;
	int DB2_low_volt;
	int DB2_highpressdiffVolt;
	int DB3_high_volt;
	int DB3_low_volt;
	int DB3_highpressdiffVolt;
	int DB4_high_volt;
	int DB4_low_volt;
	int DB4_highpressdiffVolt;
}db_alarm_thre_val_TypeDef;
typedef struct tagdb_alarm_thre_valMng
{
	int threval_flag;
	db_alarm_thre_val_TypeDef  thre_val;
	DATA_INTERFACE_FUNC  Setthre_val;
	DATA_INTERFACE_FUNC  Getthre_val;
}db_alarm_thre_valMng_TypeDef;
extern db_alarm_thre_valMng_TypeDef gs_dbalarmMng;

//cfg
typedef struct tagrtuaddrtime
{
	char address[2];
	char startdelaytime;
	char enddelaytime;
}AddrDelay_TypeDef;
typedef struct tagcomset
{
	unsigned char com1[7];
	unsigned char com2[7];
	unsigned char com3[7];
	unsigned  char com4[7];
	unsigned  char com5[7];
	unsigned  char com6[7];
	unsigned  char com7[7];
}SerialPortSetup_TypeDef;

typedef struct tagnetset
{
	unsigned   char IPAddress[4];
	unsigned   char  NetMask[4];
	unsigned    char Gateway[4];
	unsigned  char MACAddress[6];
}NetCardSetup_TypeDef;
typedef struct tagstandbychannelset
{
	char AlarmTel[16];
	char AlarmReport;
}Sbchannelset_TypeDef;
typedef struct tagRTUcfg
{
	AddrDelay_TypeDef        Addrdelaytime;
	Sbchannelset_TypeDef     Standbychannelset;
	SerialPortSetup_TypeDef  ComSet;
	unsigned   char DIset[17];
	unsigned  char AIset[17];
	unsigned char DBset[7];
	unsigned char DOset[7];    

	int pwModel;
	unsigned char pwaddr;
	unsigned char acModel;
	unsigned char time;
	unsigned char RTUstat;
	NetCardSetup_TypeDef     NetcardSet;
}RTUcfg_TypeDef;

typedef struct tagRTUcfgMng
{
	RTUcfg_TypeDef RTUcfg;
	DATA_INTERFACE_FUNC       Setcfg;
	DATA_INTERFACE_FUNC       Getcfg;
}RTUcfgMng_TypeDef;
extern RTUcfgMng_TypeDef gs_RTUcfgMng;

struct comtask
{
	unsigned char UPS[7];
	unsigned char ACDU[7];
	unsigned char IC[7];
	unsigned char pw[7];
	unsigned char db[7];
	unsigned char ac[7];
	unsigned char mn[7];
	unsigned char sb[7];
}comTASK;//task_TypeDef;


typedef struct channelPara
{
	float vref;
	float Gain;
	float ADK;
	float ADB;
}ChannelPara_TypeDef;

typedef struct tagselftest
{
	unsigned short mn;
	unsigned short sb;
	unsigned short pw;
	unsigned short ai;
	unsigned short di;
	unsigned short ac;
	unsigned short db;
	unsigned short lan;
	unsigned short lcd;
    DATA_INTERFACE_FUNC       fSetSelftest;
	DATA_INTERFACE_FUNC       fGetSelftest;
} SelfTest_TypeDef;
extern SelfTest_TypeDef SelfTest;

unsigned short LanTEST;
unsigned char LCDTASK;
typedef struct tagalarmstat
{
	unsigned char notify_alarm_status[165];   
	unsigned char agent_alarm_status[100];  
	unsigned char nomal_alarm_status[65];
	unsigned char aircon_alarm_status[170];
	unsigned char module_alarm_status[7][16];
	unsigned char VoltageOfBatWarning[8][140];
	unsigned char TempOfBatWarning[8][140];
	unsigned char ConectOfBatWarning[4][140];

	signed char power_alarm_flag[POWER_SIZE][3];
	signed char ups_alarm_flag[UPS_SIZE][3];
	signed char acdu_alarm_flag[ACDU_SIZE][3];
	signed char environment_alarm_flag[ENVIRONMENT_SIZE][3];
	signed char air_alarm_flag[AIR_SIZE][3];
	signed char spd_alarm_flag[SPD_SIZE][3];
	signed char battery_alarm_flag[BATTERY_SIZE][3];
}Alarmstat_TypeDef;
extern Alarmstat_TypeDef AlarmStat;


typedef struct tagNewData
{
  int  Data[230];
  int  CData[11][500][2];//“ªŒ¨ «device£¨∂˛Œ¨ «point£¨»˝Œ¨ « ˝æ›∫Õ◊¥Ã¨
} NewData_TypeDef;
typedef struct tagNewDataMng
{
	NewData_TypeDef NewData;
	DATA_INTERFACE_FUNC       fSetNewData;
	CDATA_INTERFACE_FUNC      fSetCData;
	CDATA_INTERFACE_FUNC      fGetCData;
} NewDataMng_TypeDef;
extern NewDataMng_TypeDef gs_NewDataMng;


///// CRCC

typedef struct tagPro
{
  	unsigned char Type;
	unsigned char Alarmlevel;
   	unsigned char AlarmEnable;
	unsigned char AlarmThresbhold;
	unsigned char DeviceType;
  	unsigned char Name[30];
   	unsigned char Des[40];
	unsigned char Des0[10];
	unsigned char Des1[10];
	unsigned char Unit[5];
	unsigned char Productor[10];
	unsigned char Version[10];
 	float Stander;
	float Percision;
	float MaxVal;
	float MinVal;
  	float HiLimit1;
 	float LoLimit1;
	float HiLimit2;
	float LoLimit2;
	float HiLimit3;
	float LoLimit3;
} Pro_TypeDef;  //  CRCC  ˝æ› Ù–‘Ω·ππ
typedef struct tagProMng
{
  Pro_TypeDef Pro[11][500];
  Pro_TypeDef Pro_to_modify;
  Set_Property_INTERFACE_FUNC    fSetPro;
  Property_INTERFACE_FUNC    fGetPro;
} ProMng_TypeDef;
extern ProMng_TypeDef gs_ProMng;
