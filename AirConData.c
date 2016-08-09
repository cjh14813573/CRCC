/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : AirControl.c
 *  CREATOR  : RTU Team                 DATE: 2008-10-17 10:00
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
static MUTEX_T hMutexReadWriteAirControl=PTHREAD_MUTEX_INITIALIZER;

unsigned char AirControl_SetData(unsigned short Air_i, void *pDataBuf)
{

  MutexLock(&hMutexReadWriteAirControl);

  if(Air_i == AirCon_Address_NUM)
  {
   gs_AirControlMng.AirConData.Address = *((unsigned char *)pDataBuf);
  }
  else if(Air_i == Aircon_Model_NUM)
  {
    gs_AirControlMng.AirConData.Model= *((unsigned char *)pDataBuf);
  }
  else if(Air_i == Aircon_Version_NUM)
  {
    gs_AirControlMng.AirConData.Version= *((unsigned short *)pDataBuf);
  }
  else if(Air_i == Aircon_SetPara_NUM)
  {
    gs_AirControlMng.AirConData.SetPara= *((unsigned char *)pDataBuf);
  }
  else if(Air_i == Aircon_SetTemperature_NUM  )
  {
    gs_AirControlMng.AirConData.SetTemperature= *((unsigned char *)pDataBuf);
  }
  else if(Air_i ==  Aircon_SetAddress_NUM)
  {
    gs_AirControlMng.AirConData.SetAddress= *((unsigned char *)pDataBuf);
  }
  else if(Air_i == Aircon_SetModel_NUM )
  {
    gs_AirControlMng.AirConData.SetModel= *((unsigned char *)pDataBuf);
  }
  else if(Air_i == Aircon_Controlflag_NUM  )
  {
    gs_AirControlMng.AirConData.Controlflag= *((unsigned char *)pDataBuf);
  }
  
  else
  {
    MutexUnlock(&hMutexReadWriteAirControl);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWriteAirControl);
  return  TRUE;
}

static MUTEX_T hMutexReadWriteAirControl1=PTHREAD_MUTEX_INITIALIZER;
unsigned char AirControl_GetData(unsigned short Air_i, void *pDataBuf)
{

  MutexLock(&hMutexReadWriteAirControl1);


  if(Air_i == AirCon_Address_NUM)
  {
    *((unsigned char *)pDataBuf) = gs_AirControlMng.AirConData.Address;
  }
  else if(Air_i ==  Aircon_Model_NUM)
  {
    *((unsigned char *)pDataBuf) = gs_AirControlMng.AirConData.Model;
  }
  else if(Air_i == Aircon_Version_NUM)
  {
    *((unsigned short *)pDataBuf) = gs_AirControlMng.AirConData.Version;
  }
  else if(Air_i == Aircon_SetPara_NUM)
  {
     *((unsigned char *)pDataBuf)=gs_AirControlMng.AirConData.SetPara;
  }
  else if(Air_i == Aircon_SetTemperature_NUM  )
  {
     *((unsigned char *)pDataBuf)=gs_AirControlMng.AirConData.SetTemperature;
  }
  else if(Air_i ==  Aircon_SetAddress_NUM)
  {
    *((unsigned char *)pDataBuf)=gs_AirControlMng.AirConData.SetAddress;
  }
  else if(Air_i == Aircon_SetModel_NUM )
  {
     *((unsigned char *)pDataBuf)=gs_AirControlMng.AirConData.SetModel;
  }
  else if(Air_i == Aircon_Controlflag_NUM  )
  {
   *((unsigned char *)pDataBuf)= gs_AirControlMng.AirConData.Controlflag;
  }
  
  else
  {
    MutexUnlock(&hMutexReadWriteAirControl1);
    return  FALSE;
  }

  MutexUnlock(&hMutexReadWriteAirControl1);
  return  TRUE;
}

AirControlDataMng_TypeDef gs_AirControlMng;

void init_gs_AirControlDataMng(void)
{
  gs_AirControlMng.AirConData.Address=0;;
  gs_AirControlMng.AirConData.Model=0;
  gs_AirControlMng.AirConData.Version=0;
  gs_AirControlMng.AirConData.SetPara=0;
  gs_AirControlMng.AirConData.SetTemperature=0;
  gs_AirControlMng.AirConData.SetAddress=0;
  gs_AirControlMng.AirConData.SetModel=0;
  gs_AirControlMng.AirConData.Controlflag=0xf1;

  gs_AirControlMng.AirConSetData = AirControl_SetData;
  gs_AirControlMng.AirConGetData = AirControl_GetData;
}



