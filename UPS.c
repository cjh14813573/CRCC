#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"
#include "ups.h"
unsigned char GetAlarmStat();
int UPS_flag=10;

extern int flag16;
extern int flag27;
extern int com7;

int readUPSbuf(char fd,unsigned char *mergebuff,int *length,int *time)
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
               {//printf("\n~~~~~~~~~nread=%d,%d,%d",nread,buff[i]&0x0f,i);
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
	          SelfTest.fGetSelftest(1,&feeddog);
		   feeddog++;
		   if(feeddog>65530)
		   	{feeddog=0;}
		   SelfTest.fSetSelftest(1,&feeddog);
		   
           }
         }
*length=len;
*time=time_rec;
return(read_flag);
}


void UPS(void)      // 中达 Delta UPS Protocol Version 1.55  
{

unsigned short feeddog;
int i,ii,fd, nwrite,sum,pp=0,UPS_time_flagplus=0,nread;
unsigned char UPSbuff[256]={0};
unsigned char bytebuff[256]={0};
unsigned char ch[256]={0};
Event_TypeDef *MarkEvent;
Event_TypeDef Port_Alarm_Table[1];
MarkEvent=Port_Alarm_Table;
unsigned char  nomal_alarm_status[64];
memset(nomal_alarm_status,0,64);

fd = OpenDev(comTASK.UPS[0]);
printf("ups~~~~~~~~~%d~~~~",fd);
set_speed(fd,comTASK.UPS[1]);
set_Parity(fd,comTASK.UPS[2],comTASK.UPS[4],comTASK.UPS[3]);

UPS_time_flag=nomal_alarm_status[0];//超时标记与告警标记同步
UPSbuf_init();
while(UPS_flag1!=0)
{
if(UPS_flag!=0)
{
if(UPS_time_flag==0)
            {
              UPS_time_flagplus=0;
               gs_NewDataMng.fSetNewData(81,&sum); // UPS 通断恢复
               if(nomal_alarm_status[0]==1)
               	{   
	    				                 MarkEvent->ID=36; 
                                  			   MarkEvent->Name=1;
                          				   MarkEvent->Flag=0;
                                  			   MarkEvent->Value=0;
						if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
	                                    printf("right");
	                                    else printf("wrong"); 
                               nomal_alarm_status[0]=0;
               	}
               }	
if(UPS_time_flag==1)   
            {
            UPS_time_flagplus++;
	    if(UPS_time_flagplus>=6)
	    	{
	    	UPS_time_flagplus=6;
	       sum=1;
		  gs_NewDataMng.fSetNewData(81,&sum); // UPS 通断
	      if(nomal_alarm_status[0]!=1)
		         {
                              nomal_alarm_status[0]=1;
	                                              MarkEvent->ID=36; 
                                  			   MarkEvent->Name=1;
                          				   MarkEvent->Flag=1;
                                  			   MarkEvent->Value=10;
                               if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                          	            printf("\nset event Ok");
                               else printf("set event nok");
                       }	  	  
	    	}
            }    
switch (UPS_scan_flag)
					{
					  case 9:   //  电池
				              nwrite=write(fd,UPS_poll,10);
                                
						UPS_db_flag=9;
					   break;                                    

					  case 10:    // 输入
				              nwrite=write(fd,UPS_pol,10);
                                       
						UPS_db_flag=10;
					   break;
					   case 11:   // 输出
					       nwrite=write(fd,UPS_poll1,10);
                                        
						UPS_db_flag=11;
					  break;
					  
					   case 12:   // 旁路
					    nwrite=write(fd,UPS_poll2,10);
                                       
						UPS_db_flag=12;
					  break;

					  case 13:   // 告警 
					    nwrite=write(fd,UPS_poll3,10);
                                     
						UPS_db_flag=13;
					  break;
					  
					   default:
                                      UPS_scan_flag=9;
					   break;	  
                                }
			   printf("\nUPSFlag=%d\n",UPS_scan_flag);
			   sleep(1);
			   
        	      nread=read(fd,UPSbuff,255);
			 
			  if(nread>5)
                        {
        	                 UPS_time_flag=0;	
                              ASCIItoH(&UPSbuff[0],&bytebuff[0],(nread+1));
							  
                             for(i=0;i<UPSlen;i++)
			     {
			       printf("%x, ",bytebuff[i]);
		    	       printf("^ ");
			     }
				  printf("\n");
				  
					 if(bytebuff[2]==13)
						 {
                                           switch (UPS_db_flag)
                                           {
                                               case 9:     //  电池  
                                                pp=6;
							for(i=0;i<2;i++)
								{
               					                if(bytebuff[pp]!=11)
               					                	{
               					                	   pp=pp+2;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
								}
							if(bytebuff[pp]!=11)   // 均浮充状态
					                	{
					                	   printf(" \n JUN FU CHONG  ^^^^^^ %x\n",bytebuff[pp]);
								   if(bytebuff[pp]==0)   
								   	{
								   	   sum=0xE2;
								   	  // gs_UPSDataMng.fSetUPS(1,17,&sum);
								         gs_NewDataMng.fSetNewData(76,&sum);
								   	}
								   else if(bytebuff[pp]==1)   
								   	{
								   	   sum=0xE3;
								   	  //gs_UPSDataMng.fSetUPS(1,17,&sum);
								         gs_NewDataMng.fSetNewData(76,&sum);
								   	}
								   else
								   	{
								   	     sum=0xEA;
								   	  // gs_UPSDataMng.fSetUPS(1,17,&sum);
								         gs_NewDataMng.fSetNewData(76,&sum);
								   	}

								   pp=pp+2;
					                	}
                                                     else
                                                     	{
                                                     	   pp=pp+1;
                                                     	}
                                                  if(bytebuff[pp]!=11)
               					                	{
               					                	   pp=pp+6;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
							if(bytebuff[pp]!=11)
               					                	{
               					                	   pp=pp+5;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
							if(bytebuff[pp]!=11)
               					                	{
               					                	   pp=pp+4;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
							if(bytebuff[pp]!=11)      // 电池电压
               					                	{
               					                	  sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2];
													   //  sum=sum*10;
               					                	   //gs_UPSDataMng.fSetUPS(1,13,&sum);
								                gs_NewDataMng.fSetNewData(71,&sum);
													   printf(" \n DIANCHI DIANYA ^^^^^^ %d\n",sum);
               					                 	   pp=pp+4;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
							if(bytebuff[pp]!=11)
               					                	{
               					                	   pp=pp+5;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
							if(bytebuff[pp]!=11)      // 电池温度
               					                	{
               					                	  sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2];
										   sum=sum*10;
               					            //    	   gs_UPSDataMng.fSetUPS(1,14,&sum);
								                gs_NewDataMng.fSetNewData(77,&sum);
												   printf(" \n DIANCHI wendu ^^^^^^ %d\n",sum);
               					                 	   pp=pp+4;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
							if(bytebuff[pp]!=11)      // 电池容量
               					                	{
               					                	  sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2];
													     sum=sum*10;
               					          //      	   gs_UPSDataMng.fSetUPS(1,13,&sum);
								                gs_NewDataMng.fSetNewData(70,&sum);
												   printf(" \n DIANCHI rongliang  ^^^^^^ %d\n",sum);
               					                 	   pp=pp+4;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}

							 UPS_scan_flag++;
							// UPS_scan_flag=9;
						     break;
										     
                                               case 10:       // 输入
                                                              pp=6;
							    ii=bytebuff[pp];
								  pp=pp+2;
							//	   printf(" \n shuru geshu   ^^^^^^ %x\n",ii);
								  if(ii==11)
								  	{
								  //	  printf("\n !!!!! \n");
								  	}
								  else
								  	{
								  	if(ii<4)
								  		{
								  	   for(i=0;i<ii;i++)    // ii 路输入
								  	   	{
    								  	   	   if(bytebuff[pp]!=11)     // 输入频率 
                   					                    	{
                   					                    	    sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2];
										   // sum=sum*10;
									//		   printf(" \n pinlv    ^^^^^^ %d\n",sum);
               					          //      	   gs_UPSDataMng.fSetUPS(1,11,&sum);
								                 gs_NewDataMng.fSetNewData(69,&sum);
                   					                   	   pp=pp+4;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}

										     if(bytebuff[pp]!=11)     // 输入电压
                   					                    	{
                   					                    	    sum=bytebuff[pp]*1000+bytebuff[pp+1]*100+bytebuff[pp+2]*10+bytebuff[pp+3];
											// sum=sum*10;
									//		  printf(" \n SHURU  DIANYA    ^^^^^^ %d\n",sum);
               					          //      	   gs_UPSDataMng.fSetUPS(1,i,&sum);
								                 gs_NewDataMng.fSetNewData((66+i),&sum);
                   					                   	   pp=pp+5;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
										if(bytebuff[pp]!=11)
               					                	{
               					                	   pp=pp+5;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
										if(bytebuff[pp]!=11)
               					                	{
               					                	   pp=pp+6;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
								  	   	}
								  	}
								  	}
						
							 UPS_scan_flag++;
						     break;
							 
						     case 11:
							 	   pp=6;
							    if(bytebuff[pp]!=11)
               					                	{
               					                	   if(bytebuff[pp]==0)   // UPS 状态
               					                	   	{
               					                	   	  sum=0x01;
               					          //      	   	   gs_UPSDataMng.fSetUPS(1,15,&sum);
								                        gs_NewDataMng.fSetNewData(75,&sum);
               					                	   	}
										   else  if(bytebuff[pp]==1)
										   	{
										   	   sum=0x03;
								                        gs_NewDataMng.fSetNewData(75,&sum);
										   	}
										    else  if(bytebuff[pp]==2)
										   	{
										   	    sum=0x02;
               					              //  	   	   gs_UPSDataMng.fSetUPS(1,15,&sum);
								                        gs_NewDataMng.fSetNewData(75,&sum);
										   	}
											 else  if(bytebuff[pp]==5)
										   	{
										   	    sum=0x04;
               					                	   	   //gs_UPSDataMng.fSetUPS(1,15,&sum);
								                        gs_NewDataMng.fSetNewData(75,&sum);
										   	}
											  else  if(bytebuff[pp]==7)
										   	{
										   	    sum=0;
               					                	   	   //gs_UPSDataMng.fSetUPS(1,15,&sum);
								                        gs_NewDataMng.fSetNewData(75,&sum);
										   	}
               					                	   pp=pp+2;
               					                	}
                                                                    else
                                                                    	{
                                                                    	   pp=pp+1;
                                                                    	}
									 if(bytebuff[pp]!=11)     // 输出频率
                   					                    	{
                   					                    	    sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2]*1;
											printf(" \n SHUcU  PINLV    ^^^^^^ %d\n",sum);
               					            //    	   gs_UPSDataMng.fSetUPS(1,10,&sum);
								                 gs_NewDataMng.fSetNewData(61,&sum);
                   					                   	   pp=pp+4;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
																		
                                                           ii=bytebuff[pp];
								  pp=pp+2;
								   printf(" \n shucu  geshu   ^^^^^^ %x\n",ii);
								  if(ii==11)
								  	{
								  	 printf("\n !!!!! \n");
								  	}
								  else
								  	{
								  	  if(ii<4)
								  		{
								  	   for(i=0;i<ii;i++)    // ii 路输出
								  	   	 {
								  	           if(bytebuff[pp]!=11)     // 输出电压
                   					                    	{
                   					                    	    sum=bytebuff[pp]*1000+bytebuff[pp+1]*100+bytebuff[pp+2]*10+bytebuff[pp+3];
																 //  sum=sum*10;
																    printf(" \n SHUcU  DIANYA    ^^^^^^ %d\n",sum);
               					         //       	   gs_UPSDataMng.fSetUPS(1,(3+i),&sum);
								                 gs_NewDataMng.fSetNewData((58+i),&sum);
                   					                   	   pp=pp+5;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
                                                                           if(bytebuff[pp]!=11)     // 输出电流
                   					                    	{
                   					                    	    sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2];
											gs_NewDataMng.fSetNewData((78+i),&sum);
                   					                   	   pp=pp+4;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
										   if(bytebuff[pp]!=11)     // 输出功率
                   					                    	{
                   					                   	   pp=pp+5;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
										   if(bytebuff[pp]!=11)     // 输出负载
                   					                    	{
                   					                    	       sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2];
												     sum=sum*10;
               					                	               //gs_UPSDataMng.fSetUPS(1,(3+i),&sum);
								                 gs_NewDataMng.fSetNewData((72+i),&sum);
                   					                   	   pp=pp+4;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}							
								  	    	 }
								  	  	}
								  	}
								
								
							 UPS_scan_flag++;
						     break;

							 case 12:  // 旁路
							 	   pp=6;
							    if(bytebuff[pp]!=11)        // 旁路频率
               					        {
               					               sum=bytebuff[pp]*100+bytebuff[pp+1]*10+bytebuff[pp+2];
											  //    sum=sum*10;
								                 gs_NewDataMng.fSetNewData(65,&sum);
                   					                   	   pp=pp+4;
							    	}
								else
									{
									  pp=pp+1;
									}
                                                       ii=bytebuff[pp];
								  pp=pp+2;
								  if(ii==11)
								  	{
								  	 printf("\n !!!!! \n");
								  	}
								  else
								  	{
								  	     if(ii<4)
 								  		{
     								  	   for(i=0;i<ii;i++)    // ii 路输出
     								  	      	 {
     								  	      	    if(bytebuff[pp]!=11)     // 旁路电压
                   					                    	{
                   					                    	    sum=bytebuff[pp]*1000+bytebuff[pp+1]*100+bytebuff[pp+2]*10+bytebuff[pp+3];
																//   sum=sum*10;
																    printf(" \n PANGLU DIANYA    ^^^^^^ %d\n",sum);
               					                	  // gs_UPSDataMng.fSetUPS(1,(3+i),&sum);
								                 gs_NewDataMng.fSetNewData((62+i),&sum);
                   					                   	   pp=pp+5;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
										  if(bytebuff[pp]!=11)     // 旁路电流
                   					                    	{
                   					                   	   pp=pp+4;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
										   if(bytebuff[pp]!=11)     // 旁路功率
                   					                    	{
                   					                   	   pp=pp+5;
                   					                    	}
                                                                        else
                                                                        	{
                                                                        	   pp=pp+1;
                                                                        	}
																		
     								  	   	}
								  	   	}
								  	}


								 UPS_scan_flag++;
						     break;

								
                                               case 13:       //  告警
                                               
                                                       pp=6;
							   if(bytebuff[pp]!=11)    //  UPS 散热器温度过高  --- Alarm Over Temperature
							    	{
							    	 printf(" \n ups SANREQI TEMP   ^^^^^^ %x\n",bytebuff[pp]);
							    	   if(bytebuff[pp]==1)
							    	   	{
							    	   	
							    	   	}
								else  if(bytebuff[pp]==0)
							    	   	{
							    	   
							    	   	}
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }


							  if(bytebuff[pp]!=11)    //  UPS 市电电压高  --- Alarm Input Out Of Range
							    	{
							    	printf(" \n ups AC HIGH   ^^^^^^ %x\n",bytebuff[pp]);
							    	   if(bytebuff[pp]==1)
							    	   	{
							    	   	    if(nomal_alarm_status[12]==0) 
                                                                {
                                                                   MarkEvent->ID=39; 
                                                            	 MarkEvent->Name=1;
                                                    		        MarkEvent->Flag=1;
                                                                    MarkEvent->Value=10;
               									  printf("\nfuckfuckfuck\n");
               								   if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");  
                                                                   nomal_alarm_status[12]=1;
                                                                }
							    	   	}
								else  if(bytebuff[pp]==0)
							    	   	{
							    	       if(nomal_alarm_status[12]==1) 
                                                                {
                                                                   MarkEvent->ID=39; 
                                             			   MarkEvent->Name=1;
                                     				   MarkEvent->Flag=0;
                                             			   MarkEvent->Value=0;
										  if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");  
                                                                   nomal_alarm_status[12]=0;
                                                                }
							    	   	}
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }

								 if(bytebuff[pp]!=11)    
							    	{
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }
								
								   if(bytebuff[pp]!=11)    //  UPS输出过载 --- Alarm Overload
							    	{
							    	printf(" \n ups OUTPUT OVER   ^^^^^^ %x\n",bytebuff[pp]);
							    	   if(bytebuff[pp]==1)
							    	   	{
							    	   	    if(nomal_alarm_status[32]==0) 
                                                                {
                                                                   MarkEvent->ID=133; 
                                                            	 MarkEvent->Name=1;
                                                    		        MarkEvent->Flag=1;
                                                                    MarkEvent->Value=10;
               								   if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");  
                                                                   nomal_alarm_status[32]=1;
                                                                }
							    	   	}
								else  if(bytebuff[pp]==0)
							    	   	{
							    	   	      if(nomal_alarm_status[32]==1) 
                                                                {
                                                                   MarkEvent->ID=133; 
                                                            	 MarkEvent->Name=1;
                                                    		        MarkEvent->Flag=0;
                                                                    MarkEvent->Value=0;
               								   if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");  
                                                                   nomal_alarm_status[32]=0;
                                                                }
							    	   	}
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }

							  if(bytebuff[pp]!=11)    //  UPS 旁路过高  -- Alarm Bypass Out Of Range
							    	{
							    	printf(" \n ups BYPASS OVER   ^^^^^^ %x\n",bytebuff[pp]);
							    	   if(bytebuff[pp]==1)
							    	   	{
							    	 if(nomal_alarm_status[16]!=1) 
                                                                {
                                                                    MarkEvent->ID=40; 
                                             			   MarkEvent->Name=1;
                                     				   MarkEvent->Flag=1;
                                             			   MarkEvent->Value=10;
										  if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");  
                                                                  nomal_alarm_status[16]=1;
                                                                }
							    	   	}
								else  if(bytebuff[pp]==0)
							    	   	{
							    	 if(nomal_alarm_status[16]!=0) 
                                                                {
                                                                    MarkEvent->ID=40; 
                                             			   MarkEvent->Name=1;
                                     				   MarkEvent->Flag=0;
                                             			   MarkEvent->Value=0;
										  if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");  
                                                                   nomal_alarm_status[16]=0;
                                                                }
							    	   	}
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }

								 if(bytebuff[pp]!=11)    
							    	{
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }
									 if(bytebuff[pp]!=11)    
							    	{
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }

							/*   if(bytebuff[pp]!=11)    //  UPS 充电器故障 --Alarm Charger Fail
							    	{
							    	printf(" \n ups CHARGE FAIL   ^^^^^^ %x\n",bytebuff[pp]);
							    	   if(bytebuff[pp]==1)
							    	   	{
							    	   	    if(notify_alarm_status[118]!=1) 
                                                                {
                                                                   MarkEvent->Type=((3<<6)+58); 
                                                                   MarkEvent->Para=1; 
									     if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");  
                                                                   notify_alarm_status[118]=1;
                                                                }
							    	   	}
								else  if(bytebuff[pp]==0)
							    	   	{
							    	   	    if(notify_alarm_status[118]==1) 
                                                                {
                                                                   MarkEvent->Type=((3<<6)+59); 
                                                                   MarkEvent->Para=0;
									      if(gs_EventMng.fSetEvent(MarkEvent)==TRUE)
                                               	                   printf("right");
                                                                   else printf("wrong");   
                                                                   notify_alarm_status[118]=0;
                                                                }
							    	   	}
							    	    pp=pp+2;
							    	}
								else
                                                                    {
                                                                         pp=pp+1;
                                                                     }*/

                                                 UPS_scan_flag=9;
						     break;
							 
						     default:
						     break;

                                           }
						 }
                              	  
				else printf("\nUPS check %d wrong",UPS_scan_flag);
			}
			     	else 
	                     {
		                printf("\nUPS case %d out of time!!!",UPS_scan_flag);
		                UPS_time_flag=1;
						                                                 
	                     }
	          sleep(2);
	          SelfTest.fGetSelftest(1,&feeddog);
		   feeddog++;
		   if(feeddog>65530)
		   	{feeddog=0;}
		   SelfTest.fSetSelftest(1,&feeddog);
		   if(com7==1)
		   	{
		   flag27=1;
		   UPS_flag=0;
		   	}
}   
              }

}

