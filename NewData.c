/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : data.c
 *  CREATOR  : RTU Team                 DATE: 2008-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/
#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "typedef.h"


//extern DataMng_TypeDef gs_DataMng;
static MUTEX_T hMutexReadWriteNewData=PTHREAD_MUTEX_INITIALIZER;
unsigned char SetNewData(unsigned short i, void *pDataBuf)
{
  MutexLock(&hMutexReadWriteNewData);

  if(i <=230)
  {
    gs_NewDataMng.NewData.Data[i]= *((int *)pDataBuf);   
  }
  else
  {
    MutexUnlock(&hMutexReadWriteNewData);
    return  FALSE; 
  }
  MutexUnlock(&hMutexReadWriteNewData);
  return  TRUE;
}
unsigned char SetCData(short int device, short int point,int i,void *pDataBuf)
{
	MutexLock(&hMutexReadWriteNewData);
	if(device<=10&&point<=500)
	{
		gs_NewDataMng.NewData.CData[device][point][i]=*((int *)pDataBuf);
	}
	else
	{
		MutexUnlock(&hMutexReadWriteNewData);
		return  FALSE; 
	}
	MutexUnlock(&hMutexReadWriteNewData);
	return  TRUE;
}
static MUTEX_T hMutexReadWriteNewData1=PTHREAD_MUTEX_INITIALIZER;
unsigned char GetCData(short int device, short int point,int i,void *pDataBuf)
{
	MutexLock(&hMutexReadWriteNewData1);
	if(device<=10&&point<=500)
	{
		*((int *)pDataBuf)=gs_NewDataMng.NewData.CData[device][point][i];
	}
	else
	{
		MutexUnlock(&hMutexReadWriteNewData1);
		return  FALSE; 
	}
	MutexUnlock(&hMutexReadWriteNewData1);
	return  TRUE;
}


NewDataMng_TypeDef gs_NewDataMng;

void init_gs_NewDataMng(void)
{
	int i;
	int j;
	for(i=0;i<230;i++)
	{
		gs_NewDataMng.NewData.Data[i]=0;
	}
	for(i=0;i<=10;i++)
	{
		for(j=0;j<=500;j++)
		{
			gs_NewDataMng.NewData.CData[i][j][DATA]=0;
			gs_NewDataMng.NewData.CData[i][j][STATUS]=0xff;
		}
	}
/////////////////////////////////
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_CONNECTION_1][DATA]=0;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_CONNECTION_1][STATUS]=2;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_CONNECTION_2][DATA]=1;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_CONNECTION_2][STATUS]=0;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_POWER_SWITCH_I_2][DATA]=1;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_POWER_SWITCH_I_2][STATUS]=0;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_MODE_I_2][DATA]=10;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_MODE_I_2][STATUS]=0;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_TEM_SET_I_2][DATA]=250;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_TEM_SET_I_2][STATUS]=0;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_A_2][DATA]=2222;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_A_2][STATUS]=0;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_B_2][DATA]=2322;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_B_2][STATUS]=0;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_C_2][DATA]=2243;
gs_NewDataMng.NewData.CData[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_C_2][STATUS]=0;

/////////////////////////////////



	gs_NewDataMng.fSetNewData = SetNewData; 
	gs_NewDataMng.fSetCData = SetCData;
	gs_NewDataMng.fGetCData = GetCData; 

}


