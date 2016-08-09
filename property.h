
#include "stdsys.h"
#include "inifile.h"

struct completeID
{
	short int ss;//AA,5位,最多32个
	short int rtuID;//BBB,10位,最多1022个
	short int device;//CC,6位,最多62个
	short int point;//DDD,11位,最多2046个
};

long IDstruct_to_long(struct completeID device_struct);
void ini_to_array(char *str1, unsigned char *charResult,int n);
void init_property(void);
struct completeID long_to_IDstruct(long whole_id);


extern struct completeID id_struct[];
extern short int id_number;
extern struct completeID power_struct[];
extern short int power_number; 
extern struct completeID air_struct[];
extern short int air_number;
extern struct completeID battery_struct[];
extern short int battery_number;
extern struct completeID environment_struct[];
extern short int environment_number;
extern struct completeID acdu_struct[];
extern short int acdu_number;
extern struct completeID spd_struct[];
extern short int spd_number;
extern struct completeID ups_struct[];
extern short int ups_number;
extern struct completeID device_struct[];
extern short int device_number;
extern int light_to_DO[];
extern int buzzer_to_DO[];



