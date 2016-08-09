/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : ser.c
 *  CREATOR  : RTU Team                 DATE: 2008-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/
#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "interface.h"
#include<stdlib.h>
#include<time.h>
#include <stdio.h>
#include "property.h"


int Tcpipser(void)  
{
int select_flag;
struct timeval tv;
unsigned short lantest;
unsigned short crc1=0;
char *timebuf,timebuffer[30];	
timebuf=timebuffer;
Event_TypeDef SendEvent;
SendEvent.Type = 0;
int sockfd,newsockfd,is_connected[MAXSOCKFD],fd;
int EventCount=0,alarm_count=0;//EventCount是所有报警的数目，alarm_count是当前包的告警数
struct sockaddr_in addr,addr1;
struct completeID temp_id_struct,id_pro_to_modify;
fd_set readfds;
fd_set writefds;
unsigned char buffer[4096],new_command[4096]={0};
int addr_len,send1=0,option=1,sockstatus;
long control_data;
long cnt=0;
int pp;
int pp_alarm;//用于告警
unsigned char sendbuf[1024*300]={0},buff[2048]={0},loginbuf[128],CRCH,CRCL;
unsigned char eventbuf[1024*2]={0};//告警包缓冲
unsigned char modify_pro_buf[30]={0};//属性修改通知缓冲1501
long i_command=0, t=0,length=0,i=0,j=0,data_count=0,sum=0,ID,xuhao;
long temp_id_long;
unsigned char data[8],back[3]={0};   //  0 - 年H    1 - 年L   2 - 月 3- 日 4- 时  5 -分 6 - 秒
int year,cmdback=0,access=0,alarmlock=0,prolock=0;
int alarm_flag=0;
unsigned short setdataback=0;
int device_flag=0;
long typelen=26,pronum;

memset(sendbuf,0x20,61000);

sendbuf[0]=0x23;
sendbuf[1]=0x64;
sendbuf[2]=0x6c;
sendbuf[3]=0x68;
sendbuf[4]=0x6a;
sendbuf[5]=0x74;
sendbuf[6]=0x78;
sendbuf[7]=0x78;    
sendbuf[8]=0x79;
sendbuf[9]=0x23;          //协议头  #dlhjtxxy#

eventbuf[0]=0x23;
eventbuf[1]=0x64;
eventbuf[2]=0x6c;
eventbuf[3]=0x68;
eventbuf[4]=0x6a;
eventbuf[5]=0x74;
eventbuf[6]=0x78;
eventbuf[7]=0x78;    
eventbuf[8]=0x79;
eventbuf[9]=0x23;          //协议头  #dlhjtxxy#

modify_pro_buf[0]=0x23;
modify_pro_buf[1]=0x64;
modify_pro_buf[2]=0x6c;
modify_pro_buf[3]=0x68;
modify_pro_buf[4]=0x6a;
modify_pro_buf[5]=0x74;
modify_pro_buf[6]=0x78;
modify_pro_buf[7]=0x78;    
modify_pro_buf[8]=0x79;
modify_pro_buf[9]=0x23;          //协议头  #dlhjtxxy#



loginbuf[0]=0x61;
loginbuf[1]=0x64;
loginbuf[2]=0x6d;
loginbuf[3]=0x69;
loginbuf[4]=0x6e;
loginbuf[5]=0x61;
loginbuf[6]=0x64;
loginbuf[7]=0x6d;
loginbuf[8]=0x69;
loginbuf[9]=0x6e;           // 用户名  密码  admin            
		
//SocketStart:
if((sockfd=socket (AF_INET,SOCK_STREAM,0))<0)
{
	perror("socket");
	exit(1);
}
bzero (&addr,sizeof (struct sockaddr_in));
addr.sin_family=AF_INET;
addr.sin_port=htons(PORT);
addr.sin_addr.s_addr=htonl(INADDR_ANY);


sockstatus=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(char*)&option,sizeof(option));
if (sockstatus==-1)
{
	perror("setsockopt");
}  
if(bind (sockfd,(struct sockaddr *)(&addr),sizeof(addr))<0)
{
	perror("connect");
	exit(1);
}
if(listen(sockfd,3)<0)
{
	perror("listen");
	exit(1);
}

for(fd=0;fd<MAXSOCKFD;fd++) 
is_connected[fd]=0;
while(1)
{
	tv.tv_sec = 40;
	tv.tv_usec = 0;    
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(sockfd,&readfds);
	FD_SET(sockfd,&writefds);
	for(fd=0;fd<MAXSOCKFD;fd++)
	{
		if(is_connected[fd])
		{
			FD_SET(fd, &readfds);
			FD_SET(fd, &writefds);
		}
	}
	select_flag=select(MAXSOCKFD,&readfds,&writefds,NULL,&tv);
	if(select_flag==-1)
	{
		printf("\n select error select=%d\n",select_flag);
		exit(-1);
	}
	else if(select_flag==0)
	{
		printf("\n rec non select=%d\n",select_flag);
		for(fd=0;fd<MAXSOCKFD;fd++)
		if(fd==sockfd)
		{
			//printf("\nConnection sockfd=%d.is_connect[%d]=%d\n",sockfd,fd,is_connected[fd]);
			continue;
		}
		else
		{
			//printf("\nConnection fd=%d.is_connect[%d]=%d\n",fd,fd,is_connected[fd]);
			if(is_connected[fd]==1)
			{
				is_connected[fd]=0;
				close(fd);
				printf("\nConnection fd=%d time out and  closed.\n",fd);
			}
		}
	}
	else
	{	
		for(fd=0;fd<MAXSOCKFD;fd++)
		{
			if(FD_ISSET(fd,&readfds))
			{
				if(sockfd==fd)
				{ 
					addr_len=(int)sizeof(struct sockaddr_in);
					if((newsockfd=accept(sockfd,(struct sockaddr *)(&addr1),&addr_len))<0)
						perror("accept");
					is_connected[newsockfd]=1;
					printf("\nConnection newsockfd=%d sockfd=%d\n",newsockfd,sockfd);
					printf("Connect from %s\n",inet_ntoa(addr1.sin_addr));
					// jesse=1;     // 开始定时
					break;
				}
				else
				{
					length=0;
					i_command=0;
					i=0;
					bzero(buffer,sizeof(buffer));
					printf("\nfdtest  newsockfd=%d fd=%d\n",newsockfd,fd);
					if(read(fd,buffer,sizeof(buffer))<=0)
					{
						printf("Connection closed.\n");
						is_connected[fd]=0; 
						close(fd);
					}
					else
					{
						printf("\nbuffer[0]=%d buffer[1]=%d\n",buffer[0],buffer[1]);
						if((buffer[0]==0x23)&&(buffer[1]==0x64))
						{
							//   p=0;
							//   gs_DataMng.fSetData(47,&p);   // 重新计心跳
							//    connectflag=0;         // 消除连接计次
							SelfTest.fGetSelftest(9,&lantest);
							lantest++;
							if( lantest>65530)
								lantest=0;
							SelfTest.fSetSelftest(9,&lantest);	  
							chartolg(&length,&buffer[10]);
							printf("\n socket rec length = %ld\n",length);
							length=length+2;
							for(i_command=0;i_command<length;i_command++)
							{
								new_command[i_command]=buffer[i_command+10];  
							}
							for(t=0;t<=length;t++)
							{
								printf("%x",new_command[t]);
								printf(" ");
							} 
							printf("\n");
							CRCH=new_command[length-2];
							CRCL=new_command[length-1];
							new_command[length-2]=0;
							new_command[length-1]=0;
							crc1=crccode(&new_command[0],length-2);
							printf("\n CRC CRC ===== %d\n",crc1);
							if(crc1!=0&&((crc1&0xff)==CRCL)&&(((crc1>>8)&0xff)==CRCH))
							{
								chartolg(&sum,&new_command[8]);
								chartolg(&xuhao,&new_command[4]);
								memset(&sendbuf[10],0x20,61000);
								printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~##~~~~~~~~~~~~~~~~~~~%ld  %ld\n",sum,xuhao);
								switch(sum)
								{
									case 101:     //登录 登录响应
										pp=0;
										i=0;
										cmdback=0;
										for(t=12;t<52;t++)
										{
											if(new_command[t]!=0x20)
											{
												buff[i]=new_command[t];
												i++;
											}
											else
											{
												for(t=0;t<i;t++)
												{
													printf("#### username = \n");
													printf("%x , %x",buff[t],loginbuf[pp]);
													printf(" ");
													if(buff[t]==loginbuf[pp])
													{
														cmdback++;
														printf("\n LOGIN USER NAME right  %ld , %d\n",i,cmdback);
													}
													pp++;
												} 
												if(cmdback==5)
												{
													printf("\n name go\n");
													back[0]=2;
												}
												else
												{
													back[0]=0;
												}
												printf("\n");
												i=0;
												break;
											}
										}
										i=0;
										cmdback=0;
										for(t=52;t<71;t++)
										{
											if(new_command[t]!=0x20)
											{
												buff[i]=new_command[t];
												i++;
											}
											else
											{
												for(t=0;t<i;t++)
												{
													printf("#^ password = \n");
													printf("%x , %x",buff[t],loginbuf[pp]);                     
													printf(" ");
													if(buff[t]==loginbuf[pp])
													{
														cmdback++;
														printf("\n LOGIN USER password right  %ld , %d\n",i,cmdback);
													}
													pp++;
												} 
												if(cmdback==5)
												{
													printf("\n password go\n");
													back[1]=2;
												}
												else
												{
													back[1]=0;
												}
												printf("\n");
												i=0;
												break;
											}
										}
										if((back[1]==2)&&(back[0]==2))
										{
											back[2]=2;
											// jesse=1;     // 开始定时
											printf("\n LOGIN IN OKOKOKOK %x %x  GOGOG!!\n",back[0],back[1]);
										}
										else
											back[2]=0;
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x10;	
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										printf("\n NO.NUM ======= %x,%x,%x,%x\n",sendbuf[14],sendbuf[15],sendbuf[16],sendbuf[17]);
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x00;
										sendbuf[21]=0x66;    	
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;  
										sendbuf[24]=0x00;
										sendbuf[25]=back[2];
										sendbuf[26]=0;
										sendbuf[27]=0;
										crc1=crccode(&sendbuf[10],16);	
										printf("\nLOGIN SEND CRC === %d\n",crc1);
										sendbuf[26]=((crc1>>8)&0xff);
										sendbuf[27]=(crc1&0xff);
										printf(" ^^^ login \n");
										for(t=0;t<=28;t++)
										{
											printf("%x",sendbuf[t]);
											printf(" ");
										} 
										if((send1=send(newsockfd, sendbuf,28,0))<0)
										{
											perror("send");
										}
										break;

									case 103:     //登出
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x10;
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x00;
										sendbuf[21]=0x68;	
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;  
										sendbuf[24]=0x00;
										sendbuf[25]=0x01;
										sendbuf[26]=0;
										sendbuf[27]=0;
										crc1=crccode(&sendbuf[10],16);	
										printf("\nLOGIN SEND CRC === %d\n",crc1);
										sendbuf[26]=((crc1>>8)&0xff);
										sendbuf[27]=(crc1&0xff);
										printf(" ^^^ login \n");
										for(t=0;t<=28;t++)
										{
											printf("%x",sendbuf[t]);
											printf(" ");
										} 
										if((send1=send(newsockfd, sendbuf,28,0))<0)
										{
											perror("send");
										}						  
										//	   printf("\n logout  Connection closed.\n");
										//      is_connected[fd]=0;
										//      close(fd);
										//     jesse=0;  //关闭定时器
										break;

							/*		case 1201:   // 心跳相应

										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x0c;
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										printf("\n NO.NUM ======= %x,%x,%x,%x\n",sendbuf[14],sendbuf[15],sendbuf[16],sendbuf[17]);	
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x04;
										sendbuf[21]=0xB2;
										sendbuf[22]=0;
										sendbuf[23]=0;	
										crc1=crccode(&sendbuf[10],12);	
										printf("\n  heartbit SEND CRC === %d\n",crc1);
										sendbuf[22]=((crc1>>8)&0xff);
										sendbuf[23]=(crc1&0xff);
										for(t=0;t<=24;t++)
										{
										printf("%x",sendbuf[t]);
										printf(" ");
										} 
										printf(" \n");
										if((send1=send(newsockfd, sendbuf,24,0))<0)
										{
										perror("send");
										}

										break;

										case 1202:
										printf("\n get heartbit back OKOKOKOK!\n");
										break;*/

					
									case 201://树请求响应
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x00; 
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);    //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x00;
										sendbuf[21]=0xca;  //  CMD
										chartolg(&sum,&new_command[12]);
										temp_id_struct=long_to_IDstruct(sum);
										//判断id号是否有错误
										for(i=0;i<device_number;i++)
										{
											if(device_struct[i].device==temp_id_struct.device)
												device_flag=1;
										}
										if(sum==0||(temp_id_struct.rtuID==id_struct[0].rtuID&&temp_id_struct.device==0))
										{//返回全站id
											sendbuf[22]=0x00;
											sendbuf[23]=0x00;
											sendbuf[24]=(unsigned char)((id_number>>8)&0xff);
											sendbuf[25]=(unsigned char)(id_number&0xff);
											
											for(i=0;i<id_number;i++)
											{
												//节点号
												ltochar(&sendbuf[26+i*8],IDstruct_to_long(*(id_struct+i)));
												//父节点号
												struct completeID temp_father_id;
												temp_father_id.ss=(*(id_struct+i)).ss;
												temp_father_id.rtuID=(*(id_struct+i)).rtuID;
												temp_father_id.device=(*(id_struct+i)).device;
												temp_father_id.point=0;
												if((*(id_struct+i)).point==0)   //判断节点是否有point
												{
													temp_father_id.device=0;
												}
												if((*(id_struct+i)).device==0)//判断节点是否有device
												{
													temp_father_id.rtuID=0;
												}
												ltochar(&sendbuf[30+i*8],IDstruct_to_long(temp_father_id));
											}
											pp=26+id_number*8;
											sendbuf[12]=(((pp-10)>>8)&0xff);
											sendbuf[13]=((pp-10)&0xff);
											sendbuf[pp]=0;
											sendbuf[pp+1]=0;
											crc1=crccode(&sendbuf[10],(pp-10)); 
											sendbuf[pp]=((crc1>>8)&0xff);
											sendbuf[pp+1]=(crc1&0xff);
											for(t=0;t<=(pp+2);t++)
											{
												printf("%x ",sendbuf[t]);
											}
											printf(" \n");
											if((send1=send(newsockfd, sendbuf,(pp+2),0))<0)
											{
												perror("send");
											}
											break;
										}
										else if(temp_id_struct.rtuID==id_struct[0].rtuID&&device_flag==1)
										{//返回设备id
											break;
										}
										else
										{//id号错误，返回-2
											sendbuf[22]=0xff;
											sendbuf[23]=0xff;
											sendbuf[24]=0xff;
											sendbuf[25]=0xfe;
											pp=26;
											sendbuf[10]=(((pp-10)>>24)&0xff);
											sendbuf[11]=(((pp-10)>>16)&0xff);
											sendbuf[12]=(((pp-10)>>8)&0xff);
											sendbuf[13]=((pp-10)&0xff);
											sendbuf[pp]=0;
											sendbuf[pp+1]=0;
											crc1=crccode(&sendbuf[10],(pp-10)); 
											sendbuf[pp]=((crc1>>8)&0xff);
											sendbuf[pp+1]=(crc1&0xff);
											if((send1=send(newsockfd, sendbuf,(pp+2),0))<0)
											{
												perror("send");
											}
											break;
										}
										break;

									case 301: //请求数据属性
										printf("MIANGE IS RIGHT!!!!!!!!!!!\n");
										typelen=26;
										pronum=0;
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x00; 
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);    //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x01;
										sendbuf[21]=0x2e;  //  CMD
										chartolg(&cnt,&new_command[12]);

										if(cnt<1000)
										{
											for(i=0;i<cnt;i++)
											{
												chartolg(&ID,&new_command[16+i*4]);
												printf("\n PRO PRO ID NUM ============= %ld\n",ID);
												if((ID&0x1ffff)==0x1ffff)   //  整个站所有节点属性
												{
													pronum=pronum+id_number;
													for(i=0;i<id_number;i++)
													{
														ID=IDstruct_to_long(id_struct[i]);
														typelen=typelen+gs_ProMng.fGetPro(id_struct[i].device,id_struct[i].point,&sendbuf[typelen],ID);
													}
													// 计算CNT  跳出FOR循环
												}
												else if((ID&0x7ff)==0x7ff)  //取设备下所有点
												{
													temp_id_struct=long_to_IDstruct(ID);
													switch(temp_id_struct.device)
													{
														case POWER_DEVICE:
															pronum=pronum+power_number;
															for(i=0;i<power_number;i++)
															{
																ID=IDstruct_to_long(power_struct[i]);
																typelen=typelen+gs_ProMng.fGetPro(power_struct[i].device,power_struct[i].point,&sendbuf[typelen],ID);
															}
															break;

														case UPS_DEVICE:
															pronum=pronum+ups_number;
															for(i=0;i<ups_number;i++)
															{
																ID=IDstruct_to_long(ups_struct[i]);
																typelen=typelen+gs_ProMng.fGetPro(ups_struct[i].device,ups_struct[i].point,&sendbuf[typelen],ID);
															}
															break;

														case ACDU_DEVICE:
															pronum=pronum+acdu_number;
															for(i=0;i<acdu_number;i++)
															{
																ID=IDstruct_to_long(acdu_struct[i]);
																typelen=typelen+gs_ProMng.fGetPro(acdu_struct[i].device,acdu_struct[i].point,&sendbuf[typelen],ID);
															}
															break;
												
														case ENVIRONMENT_DEVICE:
															pronum=pronum+environment_number;
															for(i=0;i<environment_number;i++)
															{
																ID=IDstruct_to_long(environment_struct[i]);
																typelen=typelen+gs_ProMng.fGetPro(environment_struct[i].device,environment_struct[i].point,&sendbuf[typelen],ID);
															}
															break;

														case AIRCONDITIONER_DEVICE:
															pronum=pronum+air_number;
															for(i=0;i<air_number;i++)
															{
																ID=IDstruct_to_long(air_struct[i]);
																typelen=typelen+gs_ProMng.fGetPro(air_struct[i].device,air_struct[i].point,&sendbuf[typelen],ID);
															}
															break;

														case SPD_DEVICE:
															pronum=pronum+spd_number;
															for(i=0;i<spd_number;i++)
															{
																ID=IDstruct_to_long(spd_struct[i]);
																typelen=typelen+gs_ProMng.fGetPro(spd_struct[i].device,spd_struct[i].point,&sendbuf[typelen],ID);
															}
															break;

														case BATTERY_DEVICE:
															pronum=pronum+battery_number;
															for(i=0;i<battery_number;i++)
															{
																ID=IDstruct_to_long(battery_struct[i]);
																typelen=typelen+gs_ProMng.fGetPro(battery_struct[i].device,battery_struct[i].point,&sendbuf[typelen],ID);
															}
															break;
													}
												}
												else   //  按单一节点取
												{
													pronum++;  //计算 CNT
													temp_id_struct=long_to_IDstruct(ID);
													typelen=typelen+gs_ProMng.fGetPro(temp_id_struct.device,temp_id_struct.point,&sendbuf[typelen],ID);
												}
									        }
										}
										else
										{
											printf(" too many point \n");   //  最后再加处理
										}

										ltochar(&sendbuf[22],pronum);   // CNT
										pp=typelen;       //报文总长度
										sendbuf[10]=(((pp-10)>>24)&0xff);
										sendbuf[11]=(((pp-10)>>16)&0xff);
										sendbuf[12]=(((pp-10)>>8)&0xff);
										sendbuf[13]=((pp-10)&0xff);
										sendbuf[pp]=0;
										sendbuf[pp+1]=0;
										crc1=crccode(&sendbuf[10],(pp-10)); 
										sendbuf[pp]=((crc1>>8)&0xff);
										sendbuf[pp+1]=(crc1&0xff);
										if((send1=send(newsockfd, sendbuf,(pp+2),0))<0)
										{
											perror("send");
										}
										/*for(t=0;t<=(pp+2);t++)
										{
											printf("%x ",sendbuf[t]);
										}*/
										printf("\n****a property package has been uploaded***\n");
										break;
					
					 				case 1301:     // 校时
										year=((new_command[12]<<8)|new_command[13]);
										data[0]=year/100;
										data[1]=year%100;
										printf("\n timecheck YEAR ====%d %x,%x\n",year,data[0],data[1]);                                         	
										sprintf(timebuf,"date %02d%02d%02d%02d%02d%02d.%02d",new_command[14],new_command[15],new_command[16],new_command[17],data[0],data[1],new_command[18]);
										printf("\n%s\n",timebuf);
										system(timebuf);
										system("hwclock -w");
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x10;
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x05;
										sendbuf[21]=0x16;
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;  
										sendbuf[24]=0x00;
										sendbuf[25]=1;
										sendbuf[26]=0;
										sendbuf[27]=0;
										crc1=crccode(&sendbuf[10],16);	
										printf("\n timeSEND CRC === %d\n",crc1);
										sendbuf[26]=((crc1>>8)&0xff);
										sendbuf[27]=(crc1&0xff);
										if((send1=send(newsockfd, sendbuf,28,0))<0)
										{
											perror("send");
										}
										break;

					 				case 501:       // 请求报警方式
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x14;
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x01;
										sendbuf[21]=0xf6;
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;
										sendbuf[24]=0x00;
										sendbuf[25]=0x00;
										sendbuf[26]=0x00;
										sendbuf[27]=0x00;
										sendbuf[28]=0x00;
										sendbuf[29]=0x01;
										sendbuf[30]=0;
										sendbuf[31]=0;	
										crc1=crccode(&sendbuf[10],20);	
										sendbuf[30]=((crc1>>8)&0xff);
										sendbuf[31]=(crc1&0xff);
										for(t=0;t<=32;t++)
										{
											printf("%x",sendbuf[t]);
											printf(" ");
										} 
										printf(" \n");
										if((send1=send(newsockfd, sendbuf,32,0))<0)
										{
											perror("send");
										}
										alarmlock=1;     // 启动报警自动上报
										break;


									case 1001:       // 请求写数据  
										setdataback=0;
										chartolg(&ID,&new_command[16]);
										temp_id_struct=long_to_IDstruct(ID);
										//空调1温度控制
										if(temp_id_struct.device==AIRCONDITIONER_DEVICE&&temp_id_struct.point==AIR_TEM_SET_O_1)
										{
											chartolg(&control_data,&new_command[20]);
											gs_NewDataMng.fSetCData(AIRCONDITIONER_DEVICE,AIR_TEM_SET_O_1,DATA,&control_data);
											setdataback=1;
										}
										//空调1模式控制
										else if(temp_id_struct.device==AIRCONDITIONER_DEVICE&&temp_id_struct.point==AIR_MODE_O_1)
										{
											chartolg(&control_data,&new_command[20]);
											gs_NewDataMng.fSetCData(AIRCONDITIONER_DEVICE,AIR_MODE_O_1,DATA,&control_data);
											setdataback=1;
										}
										// 烟雾复位
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==SMOKE_RESET)
										{
											control_data=1;
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,SMOKE_RESET,DATA,&control_data);
											setdataback=1;
										}
										// 灯控1
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==LIGHT_CONTROL_1)
										{
											control_data=new_command[20];
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_1,DATA,&control_data);
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_1,DATA,&control_data);
											setdataback=1;
										}
										// 灯控2
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==LIGHT_CONTROL_2)
										{
											control_data=new_command[20];
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_2,DATA,&control_data);
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_2,DATA,&control_data);
											setdataback=1;
										}
										// 灯控3
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==LIGHT_CONTROL_3)
										{
											control_data=new_command[20];
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_3,DATA,&control_data);
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_3,DATA,&control_data);
											setdataback=1;
										}
										// 灯控4
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==LIGHT_CONTROL_4)
										{
											control_data=new_command[20];
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_CONTROL_4,DATA,&control_data);
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_4,DATA,&control_data);
											setdataback=1;
										}
										// 蜂鸣器1
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==BUZZER_1)
										{
											control_data=0;
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_1,DATA,&control_data);
											setdataback=1;
										}
										// 蜂鸣器2
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==BUZZER_2)
										{
											control_data=0;
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_2,DATA,&control_data);
											setdataback=1;
										}
										// 蜂鸣器3
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==BUZZER_3)
										{
											control_data=0;
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_3,DATA,&control_data);
											setdataback=1;
										}
										// 蜂鸣器4
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==BUZZER_4)
										{
											control_data=0;
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_4,DATA,&control_data);
											setdataback=1;
										}
										//灯控延时
										else if(temp_id_struct.device==ENVIRONMENT_DEVICE&&temp_id_struct.point==LIGHT_DELAY)
										{
											chartolg(&control_data,&new_command[20]);
											gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,LIGHT_DELAY,DATA,&control_data);
											setdataback=1;
										}
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x10;		
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x03;
										sendbuf[21]=0xEA;
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;
										sendbuf[24]=0x00;
										sendbuf[25]=setdataback;
										sendbuf[26]=0;
										sendbuf[27]=0;	
										crc1=crccode(&sendbuf[10],16);	
										sendbuf[26]=((crc1>>8)&0xff);
										sendbuf[27]=(crc1&0xff);
										for(t=0;t<=28;t++)
										{
											printf("%x",sendbuf[t]);
											printf(" ");
										} 
										if((send1=send(newsockfd, sendbuf,28,0))<0)
										{
											perror("send");
										}
										break;
						
									case 401:  // 实时数据响应
										//alarmlock=1;//要实时数据时进入告警自动上告模式
										chartolg(&sum,&new_command[16]);
										if(sum==1)
										{
											access=1;
										}
										else
										{
											access=0;
										}
										data_count=0;
										chartolg(&cnt,&new_command[24]);//请求的节点数量
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x00;	
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x01;
										sendbuf[21]=0x92;  //  CMD
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;
										sendbuf[24]=0x00;
										sendbuf[25]=0x00;        //  group ID
										sendbuf[26]=0x00;
										sendbuf[27]=0x00;
										sendbuf[28]=0x00;
										sendbuf[29]=0x01;       //方式设定成功
										sendbuf[30]=0x00;
										sendbuf[31]=0x00;       //数据个数的前两个字节
										pp=34;
										if(cnt==1)
										{//只要一个设备的实时数据
											chartolg(&sum,&new_command[28]);//请求的id号
											temp_id_long=sum;
											temp_id_struct=long_to_IDstruct(sum);
											for(i=0;i<device_number;i++)            //判断设备id是否存在
											{
												if(device_struct[i].device==temp_id_struct.device)
													device_flag=1;
											}
											if(temp_id_struct.rtuID==id_struct[0].rtuID&&device_flag==1)
											{
												//正常返回设备下所有节点数据
												switch(temp_id_struct.device)
												{
													case POWER_DEVICE:
														data_count=power_number;
														for(i=0;i<power_number;i++)
														{
															temp_id_long=IDstruct_to_long(power_struct[i]);
															pp=pp+write_data_buffer(&sendbuf[pp],power_struct[i].device,power_struct[i].point,temp_id_long);
														}
														break;
													case UPS_DEVICE:
														data_count=ups_number;
														for(i=0;i<ups_number;i++)
														{
															temp_id_long=IDstruct_to_long(ups_struct[i]);
															pp=pp+write_data_buffer(&sendbuf[pp],ups_struct[i].device,ups_struct[i].point,temp_id_long);
														}
														break;
													case ENVIRONMENT_DEVICE:
														data_count=environment_number;
														for(i=0;i<environment_number;i++)
														{
															temp_id_long=IDstruct_to_long(environment_struct[i]);
															pp=pp+write_data_buffer(&sendbuf[pp],environment_struct[i].device,environment_struct[i].point,temp_id_long);;
														}
														break;
													case BATTERY_DEVICE:
														data_count=battery_number;
														for(i=0;i<battery_number;i++)
														{
															temp_id_long=IDstruct_to_long(battery_struct[i]);
															pp=pp+write_data_buffer(&sendbuf[pp],battery_struct[i].device,battery_struct[i].point,temp_id_long);
														}
														break;
													case ACDU_DEVICE:
														data_count=acdu_number;
														for(i=0;i<acdu_number;i++)
														{
															temp_id_long=IDstruct_to_long(acdu_struct[i]);
															pp=pp+write_data_buffer(&sendbuf[pp],acdu_struct[i].device,acdu_struct[i].point,temp_id_long);
														}
														break;
													case AIRCONDITIONER_DEVICE:
														data_count=air_number;
														for(i=0;i<air_number;i++)
														{
															temp_id_long=IDstruct_to_long(air_struct[i]);
															pp=pp+write_data_buffer(&sendbuf[pp],air_struct[i].device,air_struct[i].point,temp_id_long);
														}
														break;
													case SPD_DEVICE:
														data_count=spd_number;
														for(i=0;i<spd_number;i++)
														{
															temp_id_long=IDstruct_to_long(spd_struct[i]);
															pp=pp+write_data_buffer(&sendbuf[pp],spd_struct[i].device,spd_struct[i].point,temp_id_long);
														}
														break;
													default:
														break;
												}
											}
											else
											{//id号错误，返回-2
												sendbuf[30]=0xff;
												sendbuf[31]=0xff;
												sendbuf[32]=0xff;
												sendbuf[33]=0xfe;
											}
										}
										else
										{
											//要多个设备的实时数据
											for(j=1;j<=cnt;j++)
											{
												chartolg(&sum,&new_command[28+(j-1)*4]);//请求的id号
												temp_id_long=sum;
												temp_id_struct=long_to_IDstruct(sum);
												for(i=0;i<device_number;i++)            //判断设备id是否存在
												{
													if(device_struct[i].device==temp_id_struct.device)
														device_flag=1;
												}
												if(temp_id_struct.rtuID==id_struct[0].rtuID&&device_flag==1)
												{//正常返回设备下所有节点数据
													switch(temp_id_struct.device)
													{
														case POWER_DEVICE:
															data_count+=power_number;
															for(i=0;i<power_number;i++)
															{
																temp_id_long=IDstruct_to_long(power_struct[i]);
																pp=pp+write_data_buffer(&sendbuf[pp],power_struct[i].device,power_struct[i].point,temp_id_long);
															}
															break;
														case UPS_DEVICE:
															data_count+=ups_number;
															for(i=0;i<ups_number;i++)
															{
																temp_id_long=IDstruct_to_long(ups_struct[i]);
																pp=pp+write_data_buffer(&sendbuf[pp],ups_struct[i].device,ups_struct[i].point,temp_id_long);
															}
															break;
														case ENVIRONMENT_DEVICE:
															data_count+=environment_number;
															for(i=0;i<environment_number;i++)
															{
																temp_id_long=IDstruct_to_long(environment_struct[i]);
																pp=pp+write_data_buffer(&sendbuf[pp],environment_struct[i].device,environment_struct[i].point,temp_id_long);;
															}
															break;
														case BATTERY_DEVICE:
															data_count+=battery_number;
															for(i=0;i<battery_number;i++)
															{
																temp_id_long=IDstruct_to_long(battery_struct[i]);
																pp=pp+write_data_buffer(&sendbuf[pp],battery_struct[i].device,battery_struct[i].point,temp_id_long);
															}
															break;
														case ACDU_DEVICE:
															data_count+=acdu_number;
															for(i=0;i<acdu_number;i++)
															{
																temp_id_long=IDstruct_to_long(acdu_struct[i]);
																pp=pp+write_data_buffer(&sendbuf[pp],acdu_struct[i].device,acdu_struct[i].point,temp_id_long);
															}
															break;
														case AIRCONDITIONER_DEVICE:
															data_count+=air_number;
															for(i=0;i<air_number;i++)
															{
																temp_id_long=IDstruct_to_long(air_struct[i]);
																pp=pp+write_data_buffer(&sendbuf[pp],air_struct[i].device,air_struct[i].point,temp_id_long);
															}
															break;
														case SPD_DEVICE:
															data_count+=spd_number;
															for(i=0;i<spd_number;i++)
															{
																temp_id_long=IDstruct_to_long(spd_struct[i]);
																pp=pp+write_data_buffer(&sendbuf[pp],spd_struct[i].device,spd_struct[i].point,temp_id_long);
															}
															break;
														default:
															break;
													}
												}
											}
										}
										sendbuf[10]=(((pp-10)>>24)&0xff);
										sendbuf[11]=(((pp-10)>>16)&0xff);
										sendbuf[12]=(((pp-10)>>8)&0xff);//长度后两个字节
										sendbuf[13]=((pp-10)&0xff);
										printf("data_count=%ld\n",data_count);
										sendbuf[32]=((data_count>>8)&0xff);//节点数量后两个字节
										sendbuf[33]=(data_count&0xff);
										sendbuf[pp]=0;
										sendbuf[pp+1]=0;
										crc1=crccode(&sendbuf[10],(pp-10));
										sendbuf[pp]=((crc1>>8)&0xff);
										sendbuf[pp+1]=(crc1&0xff);
										for(t=0;t<=(pp+2);t++)
										{
											printf("%x ",sendbuf[t]);
										}
										printf(" \n");
										if((send1=send(newsockfd, sendbuf,(pp+2),0))<0)
										{
											perror("send");
										}
										break;

									case 1601:       // 告警确认请求
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x10;	
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x06;
										sendbuf[21]=0x42;
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;
										sendbuf[24]=0x00;
										sendbuf[25]=0x01;
										sendbuf[26]=0;
										sendbuf[27]=0;	
										crc1=crccode(&sendbuf[10],16);	
										sendbuf[26]=((crc1>>8)&0xff);
										sendbuf[27]=(crc1&0xff);
										for(t=0;t<=28;t++)
										{
											printf("%x",sendbuf[t]);
											printf(" ");
										} 
										printf(" \n");
										if((send1=send(newsockfd, sendbuf,28,0))<0)
										{
											perror("send");
										}
										break;

									case 504:       // 告警确认返回
										alarm_flag=0;
										break;

									case 1502:
										prolock=0;
										break;

									case 1401:       // 请求修改属性
										gs_ProMng.Pro_to_modify.Type=new_command[15];
										chartolg(&ID,&new_command[16]);
										id_pro_to_modify=long_to_IDstruct(ID);
										switch(gs_ProMng.Pro_to_modify.Type)
										{
											case 2://DI
												gs_ProMng.Pro_to_modify.Alarmlevel=new_command[231];
												gs_ProMng.Pro_to_modify.AlarmEnable=new_command[235];
												break;

											case 3://AI
												gs_ProMng.Pro_to_modify.Alarmlevel=new_command[235];
												gs_ProMng.Pro_to_modify.AlarmEnable=new_command[239];
												char_to_float(&new_command[0],&gs_ProMng.Pro_to_modify.HiLimit1,240,243);
												char_to_float(&new_command[0],&gs_ProMng.Pro_to_modify.LoLimit1,244,247);
												char_to_float(&new_command[0],&gs_ProMng.Pro_to_modify.HiLimit2,248,251);
												char_to_float(&new_command[0],&gs_ProMng.Pro_to_modify.LoLimit2,252,255);
												char_to_float(&new_command[0],&gs_ProMng.Pro_to_modify.HiLimit3,256,259);
												char_to_float(&new_command[0],&gs_ProMng.Pro_to_modify.LoLimit3,260,263);
												break;

											default:
												break;
										}
										gs_ProMng.fSetPro(id_pro_to_modify.device,id_pro_to_modify.point);
										prolock=1;
										sendbuf[10]=0x00;
										sendbuf[11]=0x00;
										sendbuf[12]=0x00;
										sendbuf[13]=0x10;
										sendbuf[14]=(unsigned char)((xuhao>>24)&0xff);
										sendbuf[15]=(unsigned char)((xuhao>>16)&0xff);
										sendbuf[16]=(unsigned char)((xuhao>>8)&0xff);
										sendbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
										sendbuf[18]=0x00;
										sendbuf[19]=0x00;
										sendbuf[20]=0x05;
										sendbuf[21]=0x7A;//命令
										sendbuf[22]=0x00;
										sendbuf[23]=0x00;
										sendbuf[24]=0x00;
										sendbuf[25]=0x01;
										sendbuf[26]=0;
										sendbuf[27]=0;	
										crc1=crccode(&sendbuf[10],16);	
										sendbuf[26]=((crc1>>8)&0xff);
										sendbuf[27]=(crc1&0xff);
										for(t=0;t<=28;t++)
										{
											printf("%x",sendbuf[t]);
											printf(" ");
										} 
										printf(" \n");
										if((send1=send(newsockfd, sendbuf,28,0))<0)
										{
											perror("send");
										}
										break;
						
									default:
										break;
								}
							}
							else
							{
								printf("\n CRC CHECK WRONG!!!\n");
							}
						}
						else
						{
							printf("\n WRONG HEAD!!!!\n");
							for(t=0;t<=100;t++)
							{
								printf("%x",buffer[t]);
								printf(" * ");
							} 
							printf("\n");
						}
					}
				}
			}
			else
			{
				if(fd==sockfd)
				{		 
					continue;
				}
			}
			if(FD_ISSET(fd,&writefds))
			{
				//告警主动上报
				if(alarmlock==1)
				{
					if(alarm_flag==0)//报警已被确认，找下一条告警
					{
						alarm_count=0;
						pp_alarm=26;
						for(i=0;i<10;i++)//每包最多十条
						{
							if(gs_EventMng.fGetEvent(&SendEvent)==TRUE)
							{
								alarm_flag=1;
								alarm_count++;
								EventCount++;
								if(EventCount==1000)
									EventCount=0;
								pp_alarm=pp_alarm+write_alarm_buffer(&eventbuf[pp_alarm],&SendEvent,EventCount);
							}
							else
								break;
						}
					}
					if(alarm_flag!=0)
					{
						eventbuf[10]=0x00;
						eventbuf[11]=0x00;
						eventbuf[12]=0x00;
						eventbuf[13]=0x00;
						eventbuf[14]=(unsigned char)((xuhao>>24)&0xff);
						eventbuf[15]=(unsigned char)((xuhao>>16)&0xff);
						eventbuf[16]=(unsigned char)((xuhao>>8)&0xff);
						eventbuf[17]=(unsigned char)(xuhao&0xff);     //报文序号
						eventbuf[18]=0x00;
						eventbuf[19]=0x00;
						eventbuf[20]=0x01;
						eventbuf[21]=0xf7;  //  CMD
						eventbuf[22]=0x00;
						eventbuf[23]=0x00;
						eventbuf[24]=(alarm_count>>8)&0xff;
						eventbuf[25]=alarm_count&0xff;        // cnt 报警数量
						
						eventbuf[10]=(((pp_alarm-10)>>24)&0xff);
						eventbuf[11]=(((pp_alarm-10)>>16)&0xff);
						eventbuf[12]=(((pp_alarm-10)>>8)&0xff); 
						eventbuf[13]=((pp_alarm-10)&0xff); 
						eventbuf[pp_alarm]=0;
						eventbuf[pp_alarm+1]=0;
						crc1=crccode(&eventbuf[10],(pp_alarm-10));	
						eventbuf[pp_alarm]=((crc1>>8)&0xff);
						eventbuf[pp_alarm+1]=(crc1&0xff);
						if((send1=send(newsockfd, eventbuf,(pp_alarm+2),0))<0)
						{
							perror("send");
						}
						for(t=0;t<=(pp_alarm+2);t++)
						{
							printf("%x",eventbuf[t]);
							printf(" ^ ");
						} 
						printf(" \n");	
					}
					usleep(500000);
				}
				if(prolock==1)    //修改数据属性通知
				{
					modify_pro_buf[10]=0x00;
					modify_pro_buf[11]=0x00;
					modify_pro_buf[12]=0x00;
					modify_pro_buf[13]=0x10;
					modify_pro_buf[14]=(unsigned char)((xuhao>>24)&0xff);
					modify_pro_buf[15]=(unsigned char)((xuhao>>16)&0xff);
					modify_pro_buf[16]=(unsigned char)((xuhao>>8)&0xff);
					modify_pro_buf[17]=(unsigned char)(xuhao&0xff);     //报文序号
					modify_pro_buf[18]=0x00;
					modify_pro_buf[19]=0x00;
					modify_pro_buf[20]=0x05;
					modify_pro_buf[21]=0xDD;//命令
					ltochar(&modify_pro_buf[22],IDstruct_to_long(id_pro_to_modify));
					modify_pro_buf[26]=0;
					modify_pro_buf[27]=0;	
					crc1=crccode(&modify_pro_buf[10],16);	
					modify_pro_buf[26]=((crc1>>8)&0xff);
					modify_pro_buf[27]=(crc1&0xff);
					for(t=0;t<=28;t++)
					{
						printf("%x",modify_pro_buf[t]);
						printf(" ");
					} 
					printf(" \n");
					if((send1=send(newsockfd, modify_pro_buf,28,0))<0)
					{
						perror("send");
					}
				}
			}
			else
			{
				//printf("\n no fd write!!! %d\n",fd);
				if(is_connected[fd]==1)
				{
					is_connected[fd]=0;
					close(fd);
					printf("\n send Connection fd=%d no data ### \n",fd);
				}
			}
		}
	}
}
}


