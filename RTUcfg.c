#include "inifile.h"
#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "interface.h"
#include "typedef.h"

#define BUF_SIZE 256
void B10strread(char *str1, unsigned char *charResult,int n)
{
	int i=0,ii=0,iii;
	char *q;
	char qq[30]={0};//qqq[10];
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

void B16strread(char *str1, unsigned char *charResult,int n)   
{
	int i=0,ii=0,iii,r=0;
	char *q;
	char qq[30]={0};//qqq[10];
	q=qq;
	char *p=str1;
	for(iii=0;iii<n;iii++)
	{
	ii=0;memset(qq,0,30);
	 while( p[i]!=',' && p[i]!='\0'&&p[i]!='.'&&p[i]!=':'&&p[i]!='-')
	 {q[ii++]=p[i];i++;}
	 i+=1;
	 if(q)
	 {
	 	 sscanf(q,"%x",&r);
	    *(charResult++)=r;
	 }
    }
}


void comread(char *str,unsigned char *charResult)
{
int i=0,ii=0;
char *q;
char qq[20]={0};
q=qq;
char *p=str;
 while( p[i]!=',' && p[i]!='\0')
 {q[ii++]=p[i];i++;}
*(charResult)=atoi(q);
memset(qq,0,20);
i=i+1;
ii=0;
while( p[i]!=',' && p[i]!='\0')
 {q[ii++]=p[i];i++;}
switch(atoi(q))
{
case 600:
*(charResult+1)=0;
break;
case 1200:
*(charResult+1)=1;
break;
case 2400:
*(charResult+1)=2;
break;
case 4800:
*(charResult+1)=3;
break;
case 9600:
*(charResult+1)=4;
break;
case 19200:
*(charResult+1)=5;
break;
case 38400:
*(charResult+1)=6;
break;
default :
break;
}
memset(qq,0,20);
i=i+1;
ii=0;
while( p[i]!=',' && p[i]!='\0')
 {q[ii++]=p[i];i++;}
switch(atoi(q))
{
case 7:
*(charResult+2)=0;
break;
case 8:
*(charResult+2)=1;
break;
case 9:
*(charResult+2)=2;
break;
default:
break;
}
memset(qq,0,20);
i=i+1;
ii=0;
while( p[i]!=',' && p[i]!='\0')
 {q[ii++]=p[i];i++;}
if(*q=='o')
*(charResult+3)=0;	
else if(*q=='e')
{
*(charResult+3)=1;	
}
else if(*q=='n')
{
*(charResult+3)=2;	
}
memset(qq,0,20);
i=i+1;
ii=0;
while( p[i]!=',' && p[i]!='\0')
 {q[ii++]=p[i];i++;}
if(*q=='1')
{
*(charResult+4)=0;
}
else if(*q=='2')
{
*(charResult+4)=2;	
}
memset(qq,0,20);
i=i+1;
ii=0;
while( p[i]!=',' && p[i]!='\0')
 {q[ii++]=p[i];i++;}
*(charResult+5)=*q-'0';
memset(qq,0,20);
i=i+1;
ii=0;
while( p[i]!=',' && p[i]!='\0')
 {q[ii++]=p[i];i++;}
*(charResult+6)=*q-'0';
}



void comset(char *s,unsigned char *pDatabuf)
{
 int u1=0,u2=0;char *u3,*u4; char uu3[3]={0},uu4[3]={0};
 u3=uu3;u4=uu4;
 switch(*((char *)(pDatabuf+1)))
 {
 case 0:
  u1=600;
  break;
 case 1:
  u1=1200;
  break;
 case 2:
  u1=2400;
  break;
 case 3:
  u1=4800;
  break;
 case 4:
  u1=9600;
  break;
 case 5:
  u1=19200;
  break;
 case 6:
  u1=38400;
  break;
 default:
   break;
 }
 switch(*((char *)(pDatabuf+2)))
 {
 case 0:
  u2=7;
  break;
 case 1:
  u2=8;
  break;
 case 2:
  u2=5;
  break;
 default:
   break;
 }
 switch(*((char *)(pDatabuf+3)))
 {
 case 0:
  u3="o";
  break;
 case 1:
  u3="e";
  break;
 case 2:
  u3="n";
  break;
 default:
  break;
 }
 switch(*((char *)(pDatabuf+4)))
 {
 case 0:
  u4="1";
  break;
 case 1:
  u4="1.5";
  break;
 case 2:
  u4="2";
  break;
 default:
  break;
  }
 sprintf(s,"%d,%d,%d,%s,%s,%d,%d",*((unsigned char *)(pDatabuf)),u1,u2,u3,u4,*((char *)(pDatabuf+5)),*((char *)(pDatabuf+6)));
}

static MUTEX_T hMutexReadWritecfg=PTHREAD_MUTEX_INITIALIZER;
unsigned char SetCFG(unsigned short i,void *pDataBuf)
{
 char *files ="/app/RTUcfg.ini";
char *sections;
char *keys; 
 char u[70];int ii;
 int addr;  
 MutexLock(&hMutexReadWritecfg);
 if(i == RTU_addr_NUM)
 {
files ="/app/RTUcfg.ini";
 sections="RTUAddrdelaytime";
 keys="Address";
 memset(u,0,70);
 gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[0]= *((char *)pDataBuf);
 gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[1]= *((char *)(pDataBuf+1));
  addr= gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[1];
  addr=((addr<<8)| gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[0]);
sprintf(u,"%d",addr);

 if(!write_profile_string(sections,keys,u,files))
 	{
 		printf("!!!write to ini file fail\n");
 		return 1;
 	}
  }
 else if(i == RTU_startdelaytime_NUM)  // RTU地址扩大， 地址低位
 {
 files ="/app/RTUcfg.ini";
 sections="RTUAddrdelaytime";
 keys="Startdelaytime";
 memset(u,0,70);
  gs_RTUcfgMng.RTUcfg.Addrdelaytime.startdelaytime= *((char *)pDataBuf);
  itoa(gs_RTUcfgMng.RTUcfg.Addrdelaytime.startdelaytime,u);
  if(!write_profile_string(sections,keys,u,files))
  	{
  		printf("write to ini file fail\n");
  		return 1;
  	}
   }
 else if(i == RTU_enddelaytime_NUM) //  RTU 地址扩大， 地址高位
 {
 files ="/app/RTUcfg.ini";
 sections="RTUAddrdelaytime";
 keys="Enddelaytime";
 memset(u,0,70);
   gs_RTUcfgMng.RTUcfg.Addrdelaytime.enddelaytime= *((char *)pDataBuf);
   itoa(gs_RTUcfgMng.RTUcfg.Addrdelaytime.enddelaytime,u);
   if(!write_profile_string(sections,keys,u,files))
   	{
   		printf("write to ini file fail\n");
   		return 1;
   	}
    }
 else if(i == RTU_Tel_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUStandbychannel";
 keys="Tel";
 memset(gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmTel,0,15);
  strncpy(gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmTel,(char *)pDataBuf,15);
   if(!write_profile_string(sections,keys,gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmTel,files))
    	{
    		printf("write to ini file fail\n");
    		return 1;
    	}
     }
 else if(i == RTU_AlarmReport_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUStandbychannel";
 keys="AlarmReport";
 gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmReport= *((char *)pDataBuf);
 itoa(gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmReport,u);
    if(!write_profile_string(sections,keys,u,files))
    	{
    		printf("write to ini file fail\n");
    		return 1;
    	}
     }
 else if(i == RTU_COM1_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUCOMSet";
 keys="com1";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.ComSet.com1[ii]=*((char *)(pDataBuf+ii));
 }
 comset(u,&gs_RTUcfgMng.RTUcfg.ComSet.com1[0]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
else if(i == RTU_COM2_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUCOMSet";
 keys="com2";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.ComSet.com2[ii]=*((char *)(pDataBuf+ii));
 }
 comset(u,&gs_RTUcfgMng.RTUcfg.ComSet.com2[0]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
else if(i == RTU_COM3_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUCOMSet";
 keys="com3";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.ComSet.com3[ii]=*((char *)(pDataBuf+ii));
 }
 comset(u,&gs_RTUcfgMng.RTUcfg.ComSet.com3[0]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
else if(i == RTU_COM4_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUCOMSet";
 keys="com4";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.ComSet.com4[ii]=*((char *)(pDataBuf+ii));
 }
 comset(u,&gs_RTUcfgMng.RTUcfg.ComSet.com4[0]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
 else if(i == RTU_COM5_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUCOMSet";
 keys="com5";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.ComSet.com5[ii]=*((char *)(pDataBuf+ii));
 }
 comset(u,&gs_RTUcfgMng.RTUcfg.ComSet.com5[0]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
  else if(i == RTU_COM6_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUCOMSet";
 keys="com6";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.ComSet.com6[ii]=*((char *)(pDataBuf+ii));
 }
 comset(u,&gs_RTUcfgMng.RTUcfg.ComSet.com6[0]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
   else if(i == RTU_COM7_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUCOMSet";
 keys="com7";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.ComSet.com7[ii]=*((char *)(pDataBuf+ii));
 }
 comset(u,&gs_RTUcfgMng.RTUcfg.ComSet.com7[0]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
else if(i == RTU_DI_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUDISet";
 keys="DI";
 for(ii=0;ii<16;ii++)
 {
	 gs_RTUcfgMng.RTUcfg.DIset[ii]=*((char *)(pDataBuf+ii));
 }
 memset(u,0,70);
 sprintf(u,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[0],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[1],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[2],
		 (unsigned char)gs_RTUcfgMng.RTUcfg.DIset[3],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[4],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[5],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[6],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[7],
		 (unsigned char)gs_RTUcfgMng.RTUcfg.DIset[8],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[9],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[10],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[11],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[12],
		 (unsigned char)gs_RTUcfgMng.RTUcfg.DIset[13],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[14],(unsigned char)gs_RTUcfgMng.RTUcfg.DIset[15]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
else if(i == RTU_AI_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUAISet";
 keys="AI";
 for(ii=0;ii<16;ii++)
  {
 	 gs_RTUcfgMng.RTUcfg.AIset[ii]=*((char *)(pDataBuf+ii));
  }
  memset(u,0,70);
  sprintf(u,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[0],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[1],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[2],
   		 (unsigned char)gs_RTUcfgMng.RTUcfg.AIset[3],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[4],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[5],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[6],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[7],
   		 (unsigned char)gs_RTUcfgMng.RTUcfg.AIset[8],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[9],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[10],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[11],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[12],
   		 (unsigned char)gs_RTUcfgMng.RTUcfg.AIset[13],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[14],(unsigned char)gs_RTUcfgMng.RTUcfg.AIset[15]);
  if(!write_profile_string(sections,keys,u,files))
 	{
 		return 1;
 	}
  }
else if(i == RTU_DB_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUDBSet";
 keys="DB";
 memset(u,0,70);
 for(ii=0;ii<7;ii++)
   {
  	 gs_RTUcfgMng.RTUcfg.DBset[ii]=*((char *)(pDataBuf+ii));
   }
 sprintf(u,"%d,%d,%d,%d,%d,%d,%d",gs_RTUcfgMng.RTUcfg.DBset[0],gs_RTUcfgMng.RTUcfg.DBset[1],gs_RTUcfgMng.RTUcfg.DBset[2],
  		 gs_RTUcfgMng.RTUcfg.DBset[3],gs_RTUcfgMng.RTUcfg.DBset[4],gs_RTUcfgMng.RTUcfg.DBset[5],gs_RTUcfgMng.RTUcfg.DBset[6]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 }
 else if(i == RTU_IP_NUM)
 {
 files ="/app/RTUcfg.ini";
 sections="RTUNetset";
 keys="IP";
 memset(u,0,70);
  for(ii=0;ii<4;ii++)
    {
	  if(*((char *)pDataBuf)==0&&*((char *)(pDataBuf+1))==0&&*((char *)(pDataBuf+2))==0&&*((char *)(pDataBuf+3))!=0)
	  {
		  ii=4;
	  }
	  else  gs_RTUcfgMng.RTUcfg.NetcardSet.IPAddress[ii]=*((char *)(pDataBuf+ii));

    }
 sprintf(u,"%d.%d.%d.%d",gs_RTUcfgMng.RTUcfg.NetcardSet.IPAddress[0],gs_RTUcfgMng.RTUcfg.NetcardSet.IPAddress[1],gs_RTUcfgMng.RTUcfg.NetcardSet.IPAddress[2],gs_RTUcfgMng.RTUcfg.NetcardSet.IPAddress[3]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
 files="/etc/rc.sh";
       	 //files="123";
 keys="eth0";
 if(writesysfile(files,keys,u)==0)
 	{
 	return 1;
 	}
 }
 else if(i == RTU_netmask_NUM)
 {
 files="/app/RTUcfg.ini";
 sections="RTUNetset";
 keys="Netmask"; 
 memset(u,0,70);
 for(ii=0;ii<4;ii++)
   {
  	 gs_RTUcfgMng.RTUcfg.NetcardSet.NetMask[ii]=*((char *)(pDataBuf+ii));
   }
sprintf(u,"%d.%d.%d.%d",gs_RTUcfgMng.RTUcfg.NetcardSet.NetMask[0],gs_RTUcfgMng.RTUcfg.NetcardSet.NetMask[1],gs_RTUcfgMng.RTUcfg.NetcardSet.NetMask[2],gs_RTUcfgMng.RTUcfg.NetcardSet.NetMask[3]);
if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
	 files="/etc/rc.sh";
	 //files="123";
	 keys="netmask";
 if(writesysfile(files,keys,u)==0)
 	{
 	return 1;
 	}
}
else if(i == RTU_gateway_NUM)
 {
 files="/app/RTUcfg.ini";
 sections="RTUNetset";
 keys="Gateway";
 memset(u,0,70);
  for(ii=0;ii<4;ii++)
    {
   	 gs_RTUcfgMng.RTUcfg.NetcardSet.Gateway[ii]=*((char *)(pDataBuf+ii));
    }
 sprintf(u,"%d.%d.%d.%d",gs_RTUcfgMng.RTUcfg.NetcardSet.Gateway[0],gs_RTUcfgMng.RTUcfg.NetcardSet.Gateway[1],gs_RTUcfgMng.RTUcfg.NetcardSet.Gateway[2],gs_RTUcfgMng.RTUcfg.NetcardSet.Gateway[3]);
 if(!write_profile_string(sections,keys,u,files))
 	{
 		return 1;
 	}
	 files="/etc/rc.sh";
	 //files="123";
	 keys="/sbin/route add default gw";
 if(writesysfile(files,keys,u)==0)
 	{
 	return 1;
 	}
 }
/*  else if(i == RTU_mac_NUM)
 { 
 files="RTUcfg.ini";
 sections="RTUNetset";
 keys="MAC";
 memset(u,0,50);
 for(ii=0;ii<6;ii++)
     {
    	 gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[ii]=*((char *)(pDataBuf+ii));
     }
 sprintf(u,"%x,%x,%x,%x,%x,%x", gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[0],gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[1],gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[2],gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[3],
		 gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[4],gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[5]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return -1;
	}
 }*/
  else if(i == RTU_pwmodel_NUM)
   {
   files="/app/RTUcfg.ini";
   sections="RTUPWModel";
   keys="pwmodel";
   memset(u,0,70);
   gs_RTUcfgMng.RTUcfg.pwModel=*(char *)(pDataBuf);
   sprintf(u,"%d", gs_RTUcfgMng.RTUcfg.pwModel);
   if(!write_profile_string(sections,keys,u,files))
  	{
  		return 1;
  	}
   }
  else if(i == RTU_pwaddr_NUM)
   {
   files="/app/RTUcfg.ini";
   sections="RTUPWModel";
   keys="pwaddress";
   memset(u,0,70);
   gs_RTUcfgMng.RTUcfg.pwaddr=*(char *)(pDataBuf);
   sprintf(u,"%d", gs_RTUcfgMng.RTUcfg.pwaddr);
   if(!write_profile_string(sections,keys,u,files))
  	{
  		return 1;
  	}
   }

  else if(i == RTU_acmodel_NUM)
   {
   files="/app/RTUcfg.ini";
   sections="RTUAirControlModel";
   keys="ACmodel";
   memset(u,0,70);
   gs_RTUcfgMng.RTUcfg.acModel=*(unsigned char *)(pDataBuf);
   sprintf(u,"%d", gs_RTUcfgMng.RTUcfg.acModel);
   if(!write_profile_string(sections,keys,u,files))
  	{
  		return 1;
  	}
   }

  else if(i == RTU_videolinkage_NUM)
   {
   files="/app/RTUcfg.ini";
   sections="RTUVideoLinkage";
   keys="time";
   memset(u,0,70);
   gs_RTUcfgMng.RTUcfg.time=*(unsigned char *)(pDataBuf);
   sprintf(u,"%d", gs_RTUcfgMng.RTUcfg.time);
   if(!write_profile_string(sections,keys,u,files))
  	{
  		return 1;
  	}
   }

  else if(i == RTU_stat_NUM)
   {
   files="/app/RTUcfg.ini";
   sections="RTUstat";
   keys="stat";
   memset(u,0,70);
   gs_RTUcfgMng.RTUcfg.RTUstat=*(unsigned char *)(pDataBuf);
   sprintf(u,"%d", gs_RTUcfgMng.RTUcfg.RTUstat);
   if(!write_profile_string(sections,keys,u,files))
  	{
  		return 1;
  	}
   }
  
else if(i == RTU_DO_NUM)  //DO
   {
   files="/app/RTUcfg.ini";
   sections="RTUDOSet";
   keys="DO";
   memset(u,0,70);
  for(ii=0;ii<6;ii++)
  {
 	 gs_RTUcfgMng.RTUcfg.DOset[ii]=*((char *)(pDataBuf+ii));
	  printf("\n SET DODODODOD %x\n",gs_RTUcfgMng.RTUcfg.DOset[ii]);
  }
  
 sprintf(u,"%d,%d,%d,%d,%d,%d",(unsigned char)gs_RTUcfgMng.RTUcfg.DOset[0],(unsigned char)gs_RTUcfgMng.RTUcfg.DOset[1],(unsigned char)gs_RTUcfgMng.RTUcfg.DOset[2],
		 (unsigned char)gs_RTUcfgMng.RTUcfg.DOset[3],(unsigned char)gs_RTUcfgMng.RTUcfg.DOset[4],(unsigned char)gs_RTUcfgMng.RTUcfg.DOset[5]);
 if(!write_profile_string(sections,keys,u,files))
	{
		return 1;
	}
}


else
  {
    MutexUnlock(&hMutexReadWritecfg);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWritecfg);
  return  TRUE;
}

static MUTEX_T hMutexReadWritecfg1=PTHREAD_MUTEX_INITIALIZER;
unsigned char GetCFG(unsigned short i,void *pDataBuf)
{
 MutexLock(&hMutexReadWritecfg1);
 int ii;
 if(i == RTU_addr_NUM)
 {
    *((char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[0];
     *((char *)(pDataBuf+1))=gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[1];

 }
 else if(i == RTU_startdelaytime_NUM)
 {
	 *((char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.Addrdelaytime.startdelaytime;
 }
 else if(i == RTU_enddelaytime_NUM)
 {
	 *((char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.Addrdelaytime.enddelaytime;
 }
 else if(i == RTU_Tel_NUM)
 {
	 for(ii=0;ii<14;ii++)
	 {
    *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmTel[ii];
	 }
 }
 else if(i == RTU_AlarmReport_NUM)
 {
	  *((char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmReport;
 }
 else if(i == RTU_COM1_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((unsigned char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.ComSet.com1[ii];
	 }
 }
else if(i == RTU_COM2_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((unsigned char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.ComSet.com2[ii];
	 }
 }
else if(i == RTU_COM3_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((unsigned char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.ComSet.com3[ii];
	 }
 }
else if(i == RTU_COM4_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((unsigned char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.ComSet.com4[ii];
	 }
 }
else if(i == RTU_COM5_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((unsigned char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.ComSet.com5[ii];
	 }
 }
else if(i == RTU_COM6_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((unsigned char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.ComSet.com6[ii];
	 }
 }
else if(i == RTU_COM7_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((unsigned char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.ComSet.com7[ii];
	 }
 }
else if(i == RTU_DI_NUM)
 {
	 for(ii=0;ii<16;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.DIset[ii];
	 }
 }
else if(i == RTU_DO_NUM)    // DO
 {
	 for(ii=0;ii<6;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.DOset[ii];
	 }
 }

else if(i == RTU_AI_NUM)
 {
	 for(ii=0;ii<16;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.AIset[ii];
	 }
 }
else if(i == RTU_DB_NUM)
 {
	 for(ii=0;ii<7;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.DBset[ii];
	 }
 }
 else if(i == RTU_IP_NUM)
 {
	 for(ii=0;ii<4;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.NetcardSet.IPAddress[ii];
	 }
 }
else if(i == RTU_netmask_NUM)
 {
	 for(ii=0;ii<4;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.NetcardSet.NetMask[ii];
	 }
 } 
else if(i == RTU_gateway_NUM)
 {
	 for(ii=0;ii<4;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.NetcardSet.Gateway[ii];
	 }
}
else if(i == RTU_mac_NUM)
 {
	 for(ii=0;ii<6;ii++)
	 {
	 *((char *)(pDataBuf+ii))=gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[ii];
	 }
 }
else if(i == RTU_pwmodel_NUM)
 {
	*((char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.pwModel;
 }
else if(i == RTU_pwaddr_NUM)
 {
	*((char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.pwaddr;
 }
else if(i == RTU_acmodel_NUM)
 {
	*((unsigned char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.acModel;
 }
else if(i == RTU_videolinkage_NUM)
 {
	*((unsigned char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.time;
 }
else if(i == RTU_stat_NUM)
 {
	*((unsigned char *)pDataBuf)=gs_RTUcfgMng.RTUcfg.RTUstat;
 }

else
  {
    MutexUnlock(&hMutexReadWritecfg1);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWritecfg1);
  return  TRUE;
}

static MUTEX_T hMutexReadWritecfgp2=PTHREAD_MUTEX_INITIALIZER;
unsigned char SetPro(short int device, short int point)
{	
	char *filedp;
	char *sectionp;
	char *keyp;
	char cfgp[BUF_SIZE]={0};
	char p[64];

	sprintf(p,"%d",point);	
	sectionp=p;   //  节点ID
	switch(device)
	{
		case 0:
			filedp="rtu.pro.ini";
		case POWER_DEVICE:
			filedp="power.pro.ini";
			break;
		case UPS_DEVICE:
			filedp="ups.pro.ini";
			break;
		case ACDU_DEVICE:
			filedp="acdu.pro.ini";
			break;
		case ENVIRONMENT_DEVICE:
			filedp="environment.pro.ini";
			break;
		case AIRCONDITIONER_DEVICE:
			filedp="air.pro.ini";
			break;
		case SPD_DEVICE:
			filedp="spd.pro.ini";
			break;
		case BATTERY_DEVICE:
			filedp="db.pro.ini";
			break;
		default:
			break;
	}
	switch(gs_ProMng.Pro_to_modify.Type)
	{
		case 2://DI
			keyp="Alarmlevel";
			sprintf(cfgp,"%d",gs_ProMng.Pro_to_modify.Alarmlevel);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].Alarmlevel=gs_ProMng.Pro_to_modify.Alarmlevel;
			
			keyp="AlarmEnable";
			sprintf(cfgp,"%d",gs_ProMng.Pro_to_modify.AlarmEnable);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].AlarmEnable=gs_ProMng.Pro_to_modify.AlarmEnable;
			break;
			
		case 3://AI
			keyp="Alarmlevel";
			sprintf(cfgp,"%d",gs_ProMng.Pro_to_modify.Alarmlevel);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].Alarmlevel=gs_ProMng.Pro_to_modify.Alarmlevel;
			
			keyp="AlarmEnable";
			sprintf(cfgp,"%d",gs_ProMng.Pro_to_modify.AlarmEnable);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].AlarmEnable=gs_ProMng.Pro_to_modify.AlarmEnable;

			keyp="HiLimit1";
			sprintf(cfgp,"%f",gs_ProMng.Pro_to_modify.HiLimit1);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].HiLimit1=gs_ProMng.Pro_to_modify.HiLimit1;

			keyp="HiLimit2";
			sprintf(cfgp,"%f",gs_ProMng.Pro_to_modify.HiLimit2);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].HiLimit2=gs_ProMng.Pro_to_modify.HiLimit2;

			keyp="HiLimit3";
			sprintf(cfgp,"%f",gs_ProMng.Pro_to_modify.HiLimit3);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].HiLimit3=gs_ProMng.Pro_to_modify.HiLimit3;

			keyp="LoLimit1";
			sprintf(cfgp,"%f",gs_ProMng.Pro_to_modify.LoLimit1);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].LoLimit1=gs_ProMng.Pro_to_modify.LoLimit1;

			keyp="LoLimit2";
			sprintf(cfgp,"%f",gs_ProMng.Pro_to_modify.LoLimit2);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].LoLimit2=gs_ProMng.Pro_to_modify.LoLimit2;

			keyp="LoLimit3";
			sprintf(cfgp,"%f",gs_ProMng.Pro_to_modify.LoLimit3);
			if(!write_profile_string(sectionp, keyp, cfgp,filedp))
			{
				MutexUnlock(&hMutexReadWritecfgp2);
				return 0xff;
			}
			gs_ProMng.Pro[device][point].LoLimit3=gs_ProMng.Pro_to_modify.LoLimit3;
			break;

		default:
			break;
	}
	switch(device)//将告警标志重置为0，重新上告告警
	{
		case POWER_DEVICE:
			AlarmStat.power_alarm_flag[point][0]=ALARM_FLAG_END;
			AlarmStat.power_alarm_flag[point][1]=ALARM_FLAG_END;
			AlarmStat.power_alarm_flag[point][2]=ALARM_FLAG_END;
			break;

		case UPS_DEVICE:
			AlarmStat.ups_alarm_flag[point][0]=ALARM_FLAG_END;
			AlarmStat.ups_alarm_flag[point][1]=ALARM_FLAG_END;
			AlarmStat.ups_alarm_flag[point][2]=ALARM_FLAG_END;
			break;

		case ACDU_DEVICE:
			AlarmStat.acdu_alarm_flag[point][0]=ALARM_FLAG_END;
			AlarmStat.acdu_alarm_flag[point][1]=ALARM_FLAG_END;
			AlarmStat.acdu_alarm_flag[point][2]=ALARM_FLAG_END;
			break;

		case ENVIRONMENT_DEVICE:
			AlarmStat.environment_alarm_flag[point][0]=ALARM_FLAG_END;
			AlarmStat.environment_alarm_flag[point][1]=ALARM_FLAG_END;
			AlarmStat.environment_alarm_flag[point][2]=ALARM_FLAG_END;
			break;

		case AIRCONDITIONER_DEVICE:
			AlarmStat.air_alarm_flag[point][0]=ALARM_FLAG_END;
			AlarmStat.air_alarm_flag[point][1]=ALARM_FLAG_END;
			AlarmStat.air_alarm_flag[point][2]=ALARM_FLAG_END;
			break;

		case SPD_DEVICE:
			AlarmStat.spd_alarm_flag[point][0]=ALARM_FLAG_END;
			AlarmStat.spd_alarm_flag[point][1]=ALARM_FLAG_END;
			AlarmStat.spd_alarm_flag[point][2]=ALARM_FLAG_END;
			break;

		case BATTERY_DEVICE:
			AlarmStat.battery_alarm_flag[point][0]=ALARM_FLAG_END;
			AlarmStat.battery_alarm_flag[point][1]=ALARM_FLAG_END;
			AlarmStat.battery_alarm_flag[point][2]=ALARM_FLAG_END;
			break;
	}
	return TRUE;
}
int GetPro(unsigned char device,unsigned char point, void *pDataBuf,int ID)
{
	int i;

	*((char *)(pDataBuf))=0;
	*((char *)(pDataBuf+1))=0;
	*((char *)(pDataBuf+2))=0;
	*((char *)(pDataBuf+3))=gs_ProMng.Pro[device][point].Type;
	switch(gs_ProMng.Pro[device][point].Type)
	{
		case 0://station
			ltochar((char *)(pDataBuf+4),ID); // 节点ID
			ID=ID&0xF8000000;
			ltochar((char *)(pDataBuf+8),ID); //  父节点ID
			return 220;
			
		case 1:   //  TDEVICE
			ltochar((char *)(pDataBuf+4),ID); // 节点ID
			ID=ID&0xFF7F0000;
			ltochar((char *)(pDataBuf+8),ID); //  父节点ID

			for(i=0;i<30;i++)
			{
				*((char *)(pDataBuf+12+i))=gs_ProMng.Pro[device][point].Name[i];
			}
			
			for(i=0;i<40;i++)
			{
				*((char *)(pDataBuf+52+i))=gs_ProMng.Pro[device][point].Des[i];
			}
				
			*((char *)(pDataBuf+212))=0;
			*((char *)(pDataBuf+213))=0;
			*((char *)(pDataBuf+214))=0;
			*((char *)(pDataBuf+215))=gs_ProMng.Pro[device][point].DeviceType;

			for(i=0;i<10;i++)
			{
				*((char *)(pDataBuf+216+i))=gs_ProMng.Pro[device][point].Productor[i];
			}
			
			for(i=0;i<10;i++)
			{
				*((char *)(pDataBuf+256+i))=gs_ProMng.Pro[device][point].Version[i];
			}

			//投入运行 时间  00-0-0-0-0-0
			for(i=0;i<7;i++)
			{
				*((char *)(pDataBuf+296+i))=0;
			}
			return 303;

		case 2:  //  TDIC
			ltochar((char *)(pDataBuf+4),ID); // 节点ID
			ID=ID&0xFFFFF800;
			ltochar((char *)(pDataBuf+8),ID); //  父节点ID
			
			for(i=0;i<30;i++)
			{
				*((char *)(pDataBuf+12+i))=gs_ProMng.Pro[device][point].Name[i];
			}

			for(i=0;i<40;i++)
			{
				*((char *)(pDataBuf+52+i))=gs_ProMng.Pro[device][point].Des[i];
			}

			//告警触发值
			for(i=0;i<4;i++)
			{
				*((char *)(pDataBuf+212+i))=0;
			}

			*((char *)(pDataBuf+216))=0;
			*((char *)(pDataBuf+217))=0;
			*((char *)(pDataBuf+218))=0;
			*((char *)(pDataBuf+219))=gs_ProMng.Pro[device][point].Alarmlevel;
			
			*((char *)(pDataBuf+220))=0;
			*((char *)(pDataBuf+221))=0;
			*((char *)(pDataBuf+222))=0;
			*((char *)(pDataBuf+223))=gs_ProMng.Pro[device][point].AlarmEnable;

			for(i=0;i<10;i++)
			{
				*((char *)(pDataBuf+224+i))=gs_ProMng.Pro[device][point].Des0[i];
			}

			for(i=0;i<10;i++)
			{
				*((char *)(pDataBuf+384+i))=gs_ProMng.Pro[device][point].Des1[i];
			}

			//是否保存
			for(i=0;i<4;i++)
			{
				*((char *)(pDataBuf+544+i))=0;
			}
			return 548;

		case 3:  //  TAIC
			ltochar((char *)(pDataBuf+4),ID); // 节点ID
			ID=ID&0xFFFFF800;
			ltochar((char *)(pDataBuf+8),ID); //  父节点ID
			
			for(i=0;i<30;i++)
			{
				*((char *)(pDataBuf+12+i))=gs_ProMng.Pro[device][point].Name[i];
			}

			for(i=0;i<40;i++)
			{
				*((char *)(pDataBuf+52+i))=gs_ProMng.Pro[device][point].Des[i];
			}

			//有效上下限
			for(i=0;i<8;i++)
			{
				*((char *)(pDataBuf+212+i))=0;
			}

			*((char *)(pDataBuf+220))=0;
			*((char *)(pDataBuf+221))=0;
			*((char *)(pDataBuf+222))=0;
			*((char *)(pDataBuf+223))=gs_ProMng.Pro[device][point].Alarmlevel;
				
			*((char *)(pDataBuf+224))=0;
			*((char *)(pDataBuf+225))=0;
			*((char *)(pDataBuf+226))=0;
			*((char *)(pDataBuf+227))=gs_ProMng.Pro[device][point].AlarmEnable;

			float_to_char(gs_ProMng.Pro[device][point].HiLimit1,((char *)(pDataBuf+228)));	 
				
			float_to_char(gs_ProMng.Pro[device][point].LoLimit1,((char *)(pDataBuf+232)));	 
			
			float_to_char(gs_ProMng.Pro[device][point].HiLimit2,((char *)(pDataBuf+236)));	 
		
			float_to_char(gs_ProMng.Pro[device][point].LoLimit2,((char *)(pDataBuf+240)));	 
		
			float_to_char(gs_ProMng.Pro[device][point].HiLimit3,((char *)(pDataBuf+244)));	 
		
			float_to_char(gs_ProMng.Pro[device][point].LoLimit3,((char *)(pDataBuf+248)));	 
			
			float_to_char(gs_ProMng.Pro[device][point].Stander,((char *)(pDataBuf+252)));	 

			float_to_char(gs_ProMng.Pro[device][point].Percision,((char *)(pDataBuf+256)));

			//是否保存历史
			for(i=0;i<12;i++)
			{
				*((char *)(pDataBuf+260+i))=0;
			}

			for(i=0;i<5;i++)
			{
				*((char *)(pDataBuf+264+i))=gs_ProMng.Pro[device][point].Unit[i];
			}
			return 272;

		case 4://TDOC
			ltochar((char *)(pDataBuf+4),ID); // 节点ID
			ID=ID&0xFFFFF800;
			ltochar((char *)(pDataBuf+8),ID); //  父节点ID
			
			for(i=0;i<30;i++)
			{
				*((char *)(pDataBuf+12+i))=gs_ProMng.Pro[device][point].Name[i];
			}

			for(i=0;i<40;i++)
			{
				*((char *)(pDataBuf+52+i))=gs_ProMng.Pro[device][point].Des[i];
			}

			//可否控制标志
			for(i=0;i<4;i++)
			{
				*((char *)(pDataBuf+212+i))=0;
			}

			for(i=0;i<10;i++)
			{
				*((char *)(pDataBuf+216+i))=gs_ProMng.Pro[device][point].Des0[i];
			}
			
			for(i=0;i<10;i++)
			{
				*((char *)(pDataBuf+376+i))=gs_ProMng.Pro[device][point].Des1[i];
			}

			//是否保存
			for(i=0;i<4;i++)
			{
				*((char *)(pDataBuf+536+i))=0;
			}
			return 540;

		case 5://TAOC
			ltochar((char *)(pDataBuf+4),ID); // 节点ID
			ID=ID&0xFFFFF800;
			ltochar((char *)(pDataBuf+8),ID); //  父节点ID
			
			for(i=0;i<30;i++)
			{
				*((char *)(pDataBuf+12+i))=gs_ProMng.Pro[device][point].Name[i];
			}

			for(i=0;i<40;i++)
			{
				*((char *)(pDataBuf+52+i))=gs_ProMng.Pro[device][point].Des[i];
			}

			float_to_char(gs_ProMng.Pro[device][point].MaxVal,((char *)(pDataBuf+212)));

			float_to_char(gs_ProMng.Pro[device][point].MinVal,((char *)(pDataBuf+216)));

			//可否控制标志
			for(i=0;i<4;i++)
			{
				*((char *)(pDataBuf+220+i))=0;
			}

			float_to_char(gs_ProMng.Pro[device][point].Stander,((char *)(pDataBuf+224)));	 

			float_to_char(gs_ProMng.Pro[device][point].Percision,((char *)(pDataBuf+228)));

			//是否保存
			for(i=0;i<4;i++)
			{
				*((char *)(pDataBuf+232+i))=0;
			}

			for(i=0;i<5;i++)
			{
				*((char *)(pDataBuf+236+i))=gs_ProMng.Pro[device][point].Unit[i];
			}
			return 244;

		default:
			return 0;
	}
	 	
}


RTUcfgMng_TypeDef gs_RTUcfgMng;
ProMng_TypeDef gs_ProMng;

void init_gs_cfgMng(void)
{
	printf("\nnow the cfg initializing is started\n");
	char *files ="/app/RTUcfg.ini";
	char *sections;
	char *keys;
	int addrint=1;
	///////CRCC
	gs_ProMng.fSetPro = SetPro;
	gs_ProMng.fGetPro = GetPro;
	/////
	gs_RTUcfgMng.Setcfg = SetCFG;
	gs_RTUcfgMng.Getcfg = GetCFG;
	sections="RTUAddrdelaytime";
	keys="Address";
	char cfg[BUF_SIZE]={0};
	if(!read_profile_string(sections, keys, cfg, BUF_SIZE,"",files))
	{
		sections="RTUAddrdelaytime";
		keys="Enddelaytime";
		write_profile_string(sections,keys,"10",files);
		sections="RTUAddrdelaytime";
		keys="Startdelaytime";
		write_profile_string(sections,keys,"10",files);
		sections="RTUAddrdelaytime";
		keys="Address";
		write_profile_string(sections,keys,"1",files);
		sections="RTUStandbychannel";
		keys="AlarmReport";
		write_profile_string(sections,keys,"0",files);
		sections="RTUStandbychannel";
		keys="Tel";
		write_profile_string(sections,keys,"",files);
		sections="RTUCOMSet";
		keys="com7";
		write_profile_string(sections,keys,"255,9600,8,n,1,0,1",files);
		sections="RTUCOMSet";
		keys="com6";
		write_profile_string(sections,keys,"255,9600,8,n,1,0,1",files);
		sections="RTUCOMSet";
		keys="com5";
		write_profile_string(sections,keys,"255,9600,8,n,1,1,1",files);
		sections="RTUCOMSet";
		keys="com4";
		write_profile_string(sections,keys,"255,1200,8,n,1,0,1",files);
		sections="RTUCOMSet";
		keys="com3";
		write_profile_string(sections,keys,"255,9600,8,n,1,0,1",files);
		sections="RTUCOMSet";
		keys="com2";
		write_profile_string(sections,keys,"255,1200,8,n,1,0,1",files);
		sections="RTUCOMSet";
		keys="com1";
		write_profile_string(sections,keys,"255,9600,8,n,1,0,1",files);
		sections="RTUDBSet";
		keys="DB";
		write_profile_string(sections,keys,"1,1,0,0,0,0,0",files);
		sections="RTUAISet";
		keys="AI";
		write_profile_string(sections,keys,"0,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255",files);
		sections="RTUDISet";
		keys="DI";
		write_profile_string(sections,keys,"0,1,2,255,255,255,255,255,255,255,255,255,255,255,255,255",files);

		/* sections="RTUDOSet";
		keys="DO";
		write_profile_string(sections,keys,"1,255,255,255,255,255",files);*/

		system("ifconfig >>/app/mac.txt");
		files="/app/mac.txt";
		keys="HWaddr";
		readsysfile(files,keys,cfg);
		files="/app/RTUcfg.ini";
		sections="RTUNetset";
		keys="MAC";
		write_profile_string(sections,keys,cfg,files);

		files="/app/RTUcfg.ini";
		sections="RTUNetset";
		keys="Gateway";
		write_profile_string(sections,keys,"192.168.0.1",files);
		files="/etc/rc.sh";
		keys="/sbin/route add default gw";
		writesysfile(files,keys,"192.168.0.1");

		files="/app/RTUcfg.ini";
		sections="RTUNetset";
		keys="Netmask";
		write_profile_string(sections,keys,"255.255.255.0",files);
		files="/etc/rc.sh";
		keys="netmask";
		writesysfile(files,keys,"255.255.255.0");

		files="/app/RTUcfg.ini";
		sections="RTUNetset";
		keys="IP";
		write_profile_string(sections,keys,"192.168.0.123",files);
		files="/etc/rc.sh";
		keys="eth0";
		writesysfile(files,keys,"192.168.0.123");

		files="/app/RTUcfg.ini";
		sections="RTUPWModel";
		keys="pwaddress";
		write_profile_string(sections,keys,"1",files);

		files="/app/RTUcfg.ini";
		sections="RTUPWModel";
		keys="pwmodel";
		write_profile_string(sections,keys,"3",files);

		files="/app/RTUcfg.ini";
		sections="RTUAirControlModel";
		keys="ACmodel";
		write_profile_string(sections,keys,"0",files);

		files="/app/RTUcfg.ini";
		sections="RTUVideoLinkage";
		keys="time";
		write_profile_string(sections,keys,"9",files);

		files="/app/RTUcfg.ini";
		sections="RTUstat";
		keys="stat";
		write_profile_string(sections,keys,"0",files);
		printf("\ncreat RTUcfg.ini default ini files ok\n"); 
	}
	else
		printf("\ncfg ini files exist\n");
	sections="RTUAddrdelaytime";
	keys="Address";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	addrint=atoi(cfg);
	gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[0]=(addrint&0xff);
	gs_RTUcfgMng.RTUcfg.Addrdelaytime.address[1]=((addrint>>8)&0xff);

	sections="RTUAddrdelaytime";
	keys="Startdelaytime";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.Addrdelaytime.startdelaytime=(char)atoi(cfg);
	sections="RTUAddrdelaytime";
	keys="Enddelaytime";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.Addrdelaytime.enddelaytime=(char)atoi(cfg);
	sections="RTUStandbychannel";
	keys="Tel";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	strncpy(gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmTel,cfg,14);
	sections="RTUStandbychannel";
	keys="AlarmReport";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.Standbychannelset.AlarmReport=atoi(cfg);
	sections="RTUCOMSet";
	keys="com1";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	comread(&cfg[0],&gs_RTUcfgMng.RTUcfg.ComSet.com1[0]);
	sections="RTUCOMSet";
	keys="com2";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	comread(&cfg[0],&gs_RTUcfgMng.RTUcfg.ComSet.com2[0]);
	sections="RTUCOMSet";
	keys="com3";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	comread(&cfg[0],&gs_RTUcfgMng.RTUcfg.ComSet.com3[0]);
	sections="RTUCOMSet";
	keys="com4";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	comread(&cfg[0],&gs_RTUcfgMng.RTUcfg.ComSet.com4[0]);
	sections="RTUCOMSet";
	keys="com5";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	comread(&cfg[0],&gs_RTUcfgMng.RTUcfg.ComSet.com5[0]);
	sections="RTUCOMSet";
	keys="com6";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	comread(&cfg[0],&gs_RTUcfgMng.RTUcfg.ComSet.com6[0]);
	sections="RTUCOMSet";
	keys="com7";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	comread(&cfg[0],&gs_RTUcfgMng.RTUcfg.ComSet.com7[0]);
	sections="RTUDISet";
	keys="DI";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	B10strread(cfg,&gs_RTUcfgMng.RTUcfg.DIset[0],16);

	/*sections="RTUDOSet";
	keys="DO";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	B10strread(cfg,&gs_RTUcfgMng.RTUcfg.DOset[0],6);*/

	sections="RTUAISet";
	keys="AI";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	B10strread(cfg,&gs_RTUcfgMng.RTUcfg.AIset[0],16);

	sections="RTUDBSet";
	keys="DB";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	B10strread(cfg,&gs_RTUcfgMng.RTUcfg.DBset[0],7);


	sections="RTUNetset";
	keys="IP";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	files="/etc/rc.sh";
	keys="eth0";
	writesysfile(files,keys,cfg);
	B10strread(cfg,&gs_RTUcfgMng.RTUcfg.NetcardSet.IPAddress[0],4);

	files="/app/RTUcfg.ini";
	sections="RTUNetset";
	keys="Netmask";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	files="/etc/rc.sh";
	keys="netmask";
	writesysfile(files,keys,cfg);
	B10strread(cfg,&gs_RTUcfgMng.RTUcfg.NetcardSet.NetMask[0],4);

	files="/app/RTUcfg.ini";
	sections="RTUNetset";
	keys="Gateway";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	files="/etc/rc.sh";
	keys="broadcast";
	writesysfile(files,keys,"192.168.0.255");
	keys="/sbin/route add default gw";
	writesysfile(files,keys,cfg);

	keys="mount -o nolock";
	writesysfile(files,keys,"123");
	B10strread(cfg,&gs_RTUcfgMng.RTUcfg.NetcardSet.Gateway[0],4);

	files="/app/mac.txt";
	keys="HWaddr";
	if(readsysfile(files,keys,cfg)==0)
	{
	system("ifconfig >>/app/mac.txt");
	readsysfile(files,keys,cfg);
	}
	files="/app/RTUcfg.ini";
	sections="RTUNetset";
	keys="MAC";
	write_profile_string(sections,keys,cfg,files);
	B16strread(cfg,&gs_RTUcfgMng.RTUcfg.NetcardSet.MACAddress[0],6);
	files="/app/RTUcfg.ini";
	sections="RTUPWModel";
	keys="pwmodel";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.pwModel=atoi(cfg);

	files="/app/RTUcfg.ini";
	sections="RTUPWModel";
	keys="pwaddress";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.pwaddr=atoi(cfg);

	files="/app/RTUcfg.ini";
	sections="RTUAirControlModel";
	keys="ACmodel";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.acModel=atoi(cfg);

	files="/app/RTUcfg.ini";
	sections="RTUVideoLinkage";
	keys="time";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.time=atoi(cfg); 

	files="/app/RTUcfg.ini";
	sections="RTUstat";
	keys="stat";
	if(!read_profile_string(sections, keys, cfg, BUF_SIZE,"",files))
	{
	write_profile_string(sections,keys,"0",files);  	
	}
	files="/app/RTUcfg.ini";
	sections="RTUstat";
	keys="stat";
	read_profile_string(sections, keys, cfg, BUF_SIZE,"",files);
	gs_RTUcfgMng.RTUcfg.RTUstat=atoi(cfg); 

	printf("\nnow the cfg initializing is completed\n");
}

void init_gs_DOMng(void)
{
	char *fileds ="/app/RTUcfg.ini";
	char *sectionds;
	char *keyds;
	char cfgd[BUF_SIZE]={0};
	sectionds="RTUDOSet";
	keyds="DO";
	if(!read_profile_string(sectionds, keyds, cfgd, BUF_SIZE,"",fileds))
	{
		sectionds="RTUDOSet";
		keyds="DO";
		write_profile_string(sectionds,keyds,"255,255,255,255,255,255",fileds);
	}
	sectionds="RTUDOSet";
	keyds="DO";
	read_profile_string(sectionds, keyds, cfgd, BUF_SIZE,"",fileds);
	B10strread(cfgd,&gs_RTUcfgMng.RTUcfg.DOset[0],6);
}

