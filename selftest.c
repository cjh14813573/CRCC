#include "wdog.h"
#include "typedef.h"
#include "stdsys.h"
#include "mutex.h"
#include "basetype.h"
static MUTEX_T hMutexReadWriteSelfTest=PTHREAD_MUTEX_INITIALIZER;
unsigned char SetSelfTest(unsigned short i, void *pDataBuf)
{
 MutexLock(&hMutexReadWriteSelfTest);

  if(i == 0)
  {
    SelfTest.mn= *((unsigned short *)pDataBuf);
  }
  else if(i == 1)
  {
    SelfTest.sb= *((unsigned short *)pDataBuf);
  }
  else if(i == 2)
  {
    SelfTest.pw= *((unsigned short *)pDataBuf);
  }
   else if(i == 3)
  {
    SelfTest.ai= *((unsigned short *)pDataBuf);
  } 
   else if(i == 4)
  {
    SelfTest.di= *((unsigned short *)pDataBuf);
  }
   else if(i == 5)
  {
    SelfTest.ac= *((unsigned short *)pDataBuf);
  }
   else if(i == 6)
  {
    SelfTest.db= *((unsigned short *)pDataBuf);
  }
    else if(i == 7)
  {
    SelfTest.lan= *((unsigned short *)pDataBuf);
  }
     else if(i == 8)
  {
    SelfTest.lcd= *((unsigned short *)pDataBuf);
  }  
     else if(i == 9)
  {
    LanTEST= *((unsigned short *)pDataBuf);
  }  
	 else
  {
    MutexUnlock(&hMutexReadWriteSelfTest);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWriteSelfTest);
  return  TRUE;
}

static MUTEX_T hMutexReadWriteSelfTest1=PTHREAD_MUTEX_INITIALIZER;
unsigned char GetSelfTest(unsigned short i, void *pDataBuf)
{
 MutexLock(&hMutexReadWriteSelfTest1);

  if(i == 0)
  {
    *((unsigned short *)pDataBuf)=SelfTest.mn;
  }
  else if(i == 1)
  {
     *((unsigned short *)pDataBuf)=SelfTest.sb;
  }
  else if(i == 2)
  {
    *((unsigned short *)pDataBuf)=SelfTest.pw;
  }
   else if(i == 3)
  {
     *((unsigned short *)pDataBuf)=SelfTest.ai;
  }
   else if(i == 4)
  {
     *((unsigned short *)pDataBuf)=SelfTest.di;
  }
   else if(i == 5)
  {
     *((unsigned short *)pDataBuf)=SelfTest.ac;
  }
   else if(i == 6)
  {
     *((unsigned short *)pDataBuf)=SelfTest.db;
  }
    else if(i == 7)
  {
     *((unsigned short *)pDataBuf)=SelfTest.lan;
  }
	    else if(i == 8)
  {
     *((unsigned short *)pDataBuf)=SelfTest.lcd;
  }
     else if(i == 9)
  {
     *((unsigned short *)pDataBuf)=LanTEST;
  }
     else
  {
    MutexUnlock(&hMutexReadWriteSelfTest1);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWriteSelfTest1);
  return  TRUE;
}
SelfTest_TypeDef SelfTest;
void init_SelfTest(void)
{
	SelfTest.fSetSelftest=SetSelfTest;
	SelfTest.fGetSelftest=GetSelfTest;
	SelfTest.mn=1;
	SelfTest.sb=1;
	SelfTest.pw=1;
	SelfTest.ai=1; 
	SelfTest.di=1; 
	SelfTest.db=1;
	SelfTest.lan=1;
	SelfTest.ac=1;
	SelfTest.lcd=1;
	LanTEST=1;
}
void Self_Test(void)
{
	int hd_wdog;
	unsigned char time=100;
	int wdog_flag=0;
	struct st
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
	}selftest,temp;
	selftest.mn=0;
	selftest.sb=0;
	selftest.pw=0;
	selftest.ai=0; 
	selftest.di=0; 
	selftest.db=0;
	selftest.lan=0;
	selftest.lcd=0;
	selftest.ac=0;
	temp.mn=0;
	temp.sb=0;
	temp.pw=0;
	temp.ai=0; 
	temp.di=0; 
	temp.db=0;
	temp.lan=0;
	temp.lcd=0;
	hd_wdog = open("/dev/wd", O_RDWR);
	ioctl(hd_wdog, IOCTL_SET_TIMER, time);
	ioctl(hd_wdog, IOCTL_EN_WD, NULL);
	while(wdog_flag==0)
	{
		if(comTASK.ACDU[0]!=0xff)
		{
			SelfTest.fGetSelftest(0,&selftest.mn);
			if(selftest.mn!=temp.mn)
			{
				temp.mn=selftest.mn;
			}
			else
				wdog_flag++;
			printf("\n+++++++++++ACDU%d\n",wdog_flag);
		}

		if(comTASK.pw[0]!=0xff)
		{
			SelfTest.fGetSelftest(2,&selftest.pw);
			if(selftest.pw!=temp.pw)
			{
				temp.pw=selftest.pw;
			}
			else
				wdog_flag++;
			printf("\n+++++++++++%dpw\n",wdog_flag);
		}

		if(comTASK.ac[0]!=0xff)
		{
			SelfTest.fGetSelftest(5,&selftest.ac);
			if(selftest.ac!=temp.ac)
			{
				temp.ac=selftest.ac;
			}
			else
				wdog_flag=1;
			printf("\n+++++++++++%dac\n",wdog_flag);
		}

		if(comTASK.db[0]!=0xff)
		{
			SelfTest.fGetSelftest(6,&selftest.db);
			if(selftest.db!=temp.db)
			{
				temp.db=selftest.db;
			}
			else
				wdog_flag=1;
			printf("\n+++++++++++%ddb\n",wdog_flag);
		}

		if(comTASK.IC[0]!=0xff)
		{
			SelfTest.fGetSelftest(7,&selftest.lan);
			if(selftest.lan!=temp.lan)
			{
				temp.lan=selftest.lan;
			}
			else
				wdog_flag++;
		}

		SelfTest.fGetSelftest(3,&selftest.ai);
		if(selftest.ai!=temp.ai)
		{
			temp.ai=selftest.ai;
		}
		else
			wdog_flag++;
		printf("\n+++++++++++ai%d\n",wdog_flag);		

		SelfTest.fGetSelftest(4,&selftest.di);
		if(selftest.di!=temp.di)
		{
			temp.di=selftest.di;
		}
		else
			wdog_flag++;
		printf("\n+++++++++++di%d\n",wdog_flag);
		if(LCDTASK==1)
		{
			SelfTest.fGetSelftest(8,&selftest.lcd);
			if(selftest.lcd!=temp.lcd)
			{
				temp.lcd=selftest.lcd;
			}
			else
				wdog_flag++;
			printf("\n+++++++++++lcd%d\n",wdog_flag);
		}
		if(wdog_flag==0)
		{
			ioctl(hd_wdog, IOCTL_FEED_WD, NULL);
		}
		sleep(25);
	}
}
