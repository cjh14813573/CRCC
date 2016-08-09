#include "typedef.h"
#include "M500F.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

int readbuf(char fd,unsigned char *mergebuff,int *length,int *time)
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
					pw_END=1;len++;break;
				}
				len++;
			}
		}
		else    
		{
			sleep(1);
			time_rec++;
			SelfTest.fGetSelftest(2,&feeddog);
			feeddog++;
			if(feeddog>65530)
			{
				feeddog=0;
			}
			SelfTest.fSetSelftest(2,&feeddog);
		}
	}
	*length=len;
	*time=time_rec;
	return(read_flag);
}

void M500F(void)
{
	unsigned short feeddog;
	int i,ll,p,fd,nwrite;
	/*Event_TypeDef *MarkEvent;
	Event_TypeDef power_event;
	MarkEvent=&power_event;*/
	unsigned char hw_addr;
	unsigned char mergebuff[512]={0};
	unsigned char bytebuff[512]={0};
	unsigned char ch[512]={0};
	int sum;
	int data,status;
	fd = OpenDev(comTASK.pw[0]);
	set_speed(fd,comTASK.pw[1]);
	set_Parity(fd,comTASK.pw[2],comTASK.pw[4],comTASK.pw[3]);
	gs_RTUcfgMng.Getcfg(RTU_pwaddr_NUM,&hw_addr);
	buf_init(hw_addr);
	while(pw_flag!=0)
	{
		sum=0;
		switch (pw_scan_flag)
		{
			case 10:
				nwrite=write(fd,hw_poll,20);
				pw_db_flag=10;
				break;
			case 11:
				nwrite=write(fd,hw_poll1,20);
				pw_db_flag=11;
				break;
			case 12:
				nwrite=write(fd,hw_poll2,20);
				pw_db_flag=12;
				break;
			case 13:
				nwrite=write(fd,hw_poll3,20);
				pw_db_flag=13;
				break;
			case 14:
				nwrite=write(fd,hw_poll4,20);
				pw_db_flag=14;
				break;
			case 15:
				nwrite=write(fd,hw_poll5,20);
				pw_db_flag=15;
				break;
			case 16:
				nwrite=write(fd,hw_poll6,20);
				pw_db_flag=16;
				break;
			case 17:
				nwrite=write(fd,hw_poll7,20);
				pw_db_flag=17;
				break;
			case 18:
				nwrite=write(fd,hw_poll8,20);
				pw_db_flag=18;
				break;
			case 19:
				nwrite=write(fd,hw_poll9,20);
				pw_db_flag=19;
				break;
			case 20:
				nwrite=write(fd,hw_ctr_cmd,40);
				pw_db_flag=20;
				break;
			default:
				pw_scan_flag=10;
				break;	  
		}
		printf("\npw_scan_flag=%d\n",pw_scan_flag);
		receive_time=0;
		read_flag=0;
		read_flag=readbuf(fd,&mergebuff[0],&len,&receive_time);
		for(i=0;i<len;i++)
		{
			printf("%x",mergebuff[i]);
			printf(" ");
		}
		printf("\n");
		if(receive_time<6||read_flag==1)
		{
			pw_time_flag=0;	
			ASCIItoH(&mergebuff[0],&bytebuff[0],len);
			Hebing(&bytebuff[0],&ch[0],(len-2));
			if(read_flag==1)//(chksum(&mergebuff[0],&ch[0],len)==1)&&(len_chksum(&bytebuff[0])==1))
			{
				printf("\nCheck %d OK!!!",pw_db_flag);      
				switch (pw_db_flag)
				{
					case 10://����ģ����
						bcc1=ch[7];
						
						//  A���ѹ��һ·
						floattoint(&ch[0],&sum,8,11);
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_A_VOLTAGE_1,DATA,&sum);
						gs_EventMng.fJudgeAI(POWER_DEVICE,POWER_A_VOLTAGE_1,sum,AlarmStat.power_alarm_flag[POWER_A_VOLTAGE_1],11);

						//  A���ѹ�ڶ�·
						floattoint(&ch[0],&sum,25,28);
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_A_VOLTAGE_2,DATA,&sum);
						gs_EventMng.fJudgeAI(POWER_DEVICE,POWER_A_VOLTAGE_2,sum,AlarmStat.power_alarm_flag[POWER_A_VOLTAGE_2],11);

						//  B���ѹ��һ·
						floattoint(&ch[0],&sum,12,15);
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_B_VOLTAGE_1,DATA,&sum);
						gs_EventMng.fJudgeAI(POWER_DEVICE,POWER_B_VOLTAGE_1,sum,AlarmStat.power_alarm_flag[POWER_B_VOLTAGE_1],11);
						
						//  B���ѹ�ڶ�·
						floattoint(&ch[0],&sum,29,32);
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_B_VOLTAGE_2,DATA,&sum);
						gs_EventMng.fJudgeAI(POWER_DEVICE,POWER_B_VOLTAGE_2,sum,AlarmStat.power_alarm_flag[POWER_B_VOLTAGE_2],11);

						//  C���ѹ��һ·
						floattoint(&ch[0],&sum,16,19);
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_C_VOLTAGE_1,DATA,&sum);
						gs_EventMng.fJudgeAI(POWER_DEVICE,POWER_B_VOLTAGE_2,sum,AlarmStat.power_alarm_flag[POWER_B_VOLTAGE_2],11);
						
						//  C���ѹ�ڶ�·
						floattoint(&ch[0],&sum,33,36);
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_C_VOLTAGE_2,DATA,&sum);
						gs_EventMng.fJudgeAI(POWER_DEVICE,POWER_C_VOLTAGE_2,sum,AlarmStat.power_alarm_flag[POWER_C_VOLTAGE_2],11);

						pw_scan_flag++;
						break;

					case 11:  // �е�1  �е�2 �л�
						bcc1=ch[10];
						if(bcc1==0xe4)
							data=0;
						else if(bcc1==0xe5)
							data=1;
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_CITY_STATUS,DATA,&data);
						status=0;
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_CITY_STATUS,STATUS,&status);
						pw_scan_flag++;
						break;		
           
					case 12://�����澯
						//��������տ�
						bcc1=ch[14];
						if(bcc1==0x00)
							data=1;//����
						else if((bcc1==0x04)||(bcc1==0x05))
							data=0;//�Ͽ�
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_AC_IN_STATUS,DATA,&data);
						gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_AC_IN_STATUS,data,AlarmStat.power_alarm_flag[POWER_AC_IN_STATUS],79,ALARM_CONTENT_BREAK);

						//��������տ�
						bcc1=ch[15];
						if(bcc1==0x00)
							data=1;//����
						else if((bcc1==0x04)||(bcc1==0x05))
							data=0;//�Ͽ�
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_AC_OUT_STATUS,DATA,&data);
						gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_AC_OUT_STATUS,data,AlarmStat.power_alarm_flag[POWER_AC_OUT_STATUS],79,ALARM_CONTENT_BREAK);

						//������
						bcc1=ch[16];
						if(bcc1==0x00) 
							data=1;//����
						else if(bcc1==0x05)
							data=0;//����
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_SPD_STATUS,DATA,&data);
						gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_SPD_STATUS,data,AlarmStat.power_alarm_flag[POWER_SPD_STATUS],79,ALARM_CONTENT_ERROR);

						//�е�һ״̬
						bcc1=ch[17];
						if(bcc1==0x00) 
							data=1;//����
						else if(bcc1==0x05)
							data=0;//����
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_CITY_OFF_1,DATA,&data);
						gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_CITY_OFF_1,data,AlarmStat.power_alarm_flag[POWER_CITY_OFF_1],79,ALARM_CONTENT_ERROR);

						//�е��״̬
						bcc1=ch[18];
						if(bcc1==0x00) 
							data=1;//����
						else if(bcc1==0x05)
							data=0;//����
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_CITY_OFF_2,DATA,&data);
						gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_CITY_OFF_2,data,AlarmStat.power_alarm_flag[POWER_CITY_OFF_2],79,ALARM_CONTENT_ERROR);

						//����ͣ��
						bcc1=ch[19];
						if(bcc1==0x00) 
							data=1;//����
						else if(bcc1==0x05)
							data=0;//����
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_AC_OFF_ALARM,DATA,&data);
						gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_AC_OFF_ALARM,data,AlarmStat.power_alarm_flag[POWER_AC_OFF_ALARM],79,ALARM_CONTENT_POWER_FAIL);

						pw_scan_flag++; 
						break;

					case 13://ģ�����
						bcc1=ch[11];//ģ������
						p=ch[16];//�Զ�������
						ll=4*(p+1)+1;//ÿ��ģ�����ݳ���
						for(i=0;i<ch[11];i++)
						{
							floattoint(&ch[0],&data,(12+ll*i),(15+ll*i));
							gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_RECTIFIER_CURRENT_1+i,DATA,&data);
							status=0;
							gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_RECTIFIER_CURRENT_1+i,STATUS,&status);
						}
						pw_scan_flag++; 
						break;				 

					case 14:   //ģ�鿪�ػ��;�����״̬
						bcc1=ch[7];//ģ������
						p=ch[11]+4;
						for(i=0;i<bcc1;i++)
						{
							//ģ�鿪�ػ�
							sum=ch[8+p*i];
							if(sum==0x00)
								data=1;//����
							else if(sum==0x01)
								data=0;//�ػ�
							gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_RECTIFIER_SWITCH_1+i,DATA,&data);
							gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_RECTIFIER_SWITCH_1+i,data,AlarmStat.power_alarm_flag[POWER_RECTIFIER_SWITCH_1+i],79,ALARM_CONTENT_OFF);

							//ģ�������
							sum=ch[10+p*i];
							if(sum==0x00)
								data=1;//����
							else if(sum==0x01)
								data=0;//����
							gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_RECTIFIER_CHARGE_1+i,DATA,&data);
							status=0;
							gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_RECTIFIER_CHARGE_1+i,STATUS,&status);
						}
						pw_scan_flag++; 
						break;	

					case 15: //ģ������״̬
						bcc1=ch[7];	//ģ������
						p=ch[9]+2;
						for(i=0;i<bcc1;i++)
						{
							sum=ch[15+p*i];
							if(sum==0x00)
								data=1;//����
							else if(sum==0xE2)
								data=0;//����
							gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_RECTIFIER_STATUS_1+i,DATA,&data);
							gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_RECTIFIER_STATUS_1+i,data,AlarmStat.power_alarm_flag[POWER_RECTIFIER_STATUS_1+i],79,ALARM_CONTENT_ERROR);
						}
						pw_scan_flag++; 
						break;	

					case 16://ֱ������
						floattoint(&ch[0],&sum,8,11);//ֱ����ѹ
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_DC_VOLTAGE,DATA,&sum);
						gs_EventMng.fJudgeAI(POWER_DEVICE,POWER_DC_VOLTAGE,sum,AlarmStat.power_alarm_flag[POWER_DC_VOLTAGE],11);

						floattoint(&ch[0],&sum,12,15);//ֱ������
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_DC_CURRENT,DATA,&sum);
						status=0;
						gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_DC_CURRENT,STATUS,&status);
						bcc1=ch[16];//�������
						switch (bcc1)
						{
							case 2:
								floattoint(&ch[0],&sum,21,24);//���2����
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CURRENT_2,DATA,&sum);
								if(sum<0)
								{
									data=0;//�ŵ�
									status=gs_ProMng.Pro[POWER_DEVICE][POWER_BATTERY_CURRENT_2].Alarmlevel;
									gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CURRENT_2,STATUS,&status);
								}
								else
								{
									data=1;//���
									status=0;
									gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CURRENT_2,STATUS,&status);
								}
								gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_BATTERY_CHARGE_2,data,AlarmStat.power_alarm_flag[POWER_BATTERY_CHARGE_2],79,ALARM_CONTENT_DISCHARGE);
								floattoint(&ch[0],&sum,ch[25]*4+31,ch[25]*4+34);//���2��ѹ
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_VOLTAGE_2,DATA,&sum);
								floattoint(&ch[0],&sum,ch[25]*4+39,ch[25]*4+42);//���2����
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CAP_2,DATA,&sum);
								floattoint(&ch[0],&sum,ch[25]*4+47,ch[25]*4+50);//���2�¶�
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_TEM_2,DATA,&sum);
								
							case 1: // 1·���
								floattoint(&ch[0],&sum,17,20);//���1����
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CURRENT_1,DATA,&sum);
								if(sum<0)
								{
									data=0;//�ŵ�
									status=gs_ProMng.Pro[POWER_DEVICE][POWER_BATTERY_CURRENT_1].Alarmlevel;
									gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CURRENT_1,STATUS,&status);
								}
								else
								{
									data=1;//���
									status=0;
									gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CURRENT_1,STATUS,&status);
								}
								gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_BATTERY_CHARGE_1,data,AlarmStat.power_alarm_flag[POWER_BATTERY_CHARGE_1],79,ALARM_CONTENT_DISCHARGE);
								floattoint(&ch[0],&sum,ch[25]*4+27,ch[25]*4+30);//���1��ѹ
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_VOLTAGE_1,DATA,&sum);
								floattoint(&ch[0],&sum,ch[25]*4+35,ch[25]*4+38);//���1����
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_CAP_1,DATA,&sum);
								floattoint(&ch[0],&sum,ch[25]*4+43,ch[25]*4+46);//���1�¶�
								gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_TEM_1,DATA,&sum);

							default:
								break;
						}
						pw_scan_flag++; 
						break;

					case 17:   //��ر���
						bcc1=ch[9];
						for(i=0;i<bcc1;i++)
						{
							sum=ch[10+i];
							if(sum==0x00)
								data=1;//����
							else if(sum==0x03)
								data=0;//��˿��
							gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_BATTERY_STATUS_1+i,DATA,&data);
							gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_BATTERY_STATUS_1+i,data,AlarmStat.power_alarm_flag[POWER_BATTERY_STATUS_1+i],79,ALARM_CONTENT_FUSE_BREAK);
						}
						pw_scan_flag=10; 
						break;

				/*	case 18:  //����������ȡ
						floattoint(&ch[0],&sum,6,9);
						gs_ParaMng.fSetPara(6,&sum);//��������
						floattoint(&ch[0],&sum,10,13);
						gs_ParaMng.fSetPara(5,&sum);//��������
						pw_scan_flag++; 
						break;

					case 19:   //ֱ��������ȡ			
						floattoint(&ch[0],&sum,6,9);
						gs_ParaMng.fSetPara(8,&sum);//ֱ������
						floattoint(&ch[0],&sum,10,13);
						gs_ParaMng.fSetPara(7,&sum);//ֱ������	
						floattoint(&ch[0],&sum,19,22);
						gs_ParaMng.fSetPara(9,&sum);
						pw_scan_flag=10; 
						break;*/

					default:
						break;
				}
			}
			else
				printf("\ncheck %d wrong",pw_scan_flag);
		}
		else 
		{
			printf("\ncase %d out of time!!!",pw_scan_flag);
			pw_time_flag=1;
		}
		if(pw_time_flag==0)
		{
			data=1;//���Դͨ������
		}
		else if(pw_time_flag==1)
		{
			data=0;//���Դͨ�Ŷ�
			status=0xff;
			for(i=1;i<=16;i++)
			{
				gs_NewDataMng.fSetCData(POWER_DEVICE,i,STATUS,&status);
			}
			for(i=18;i<=103;i++)
			{
				gs_NewDataMng.fSetCData(POWER_DEVICE,i,STATUS,&status);
			}
		}
		gs_NewDataMng.fSetCData(POWER_DEVICE,POWER_CONNECTION,DATA,&data);
		gs_EventMng.fJudgeDI(POWER_DEVICE,POWER_CONNECTION,data,AlarmStat.power_alarm_flag[POWER_CONNECTION],79,ALARM_CONTENT_ALARM);
		sleep(1);
		SelfTest.fGetSelftest(2,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{
			feeddog=0;
		}
		SelfTest.fSetSelftest(2,&feeddog);
	}
}
