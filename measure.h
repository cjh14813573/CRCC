/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : cfgdata.h
 *  CREATOR  : RTU Team                 DATE: 2008-09-19 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *  HISTORY  :
 *
 *==========================================================================*/
#ifndef __MEASURE_H_
#define __MEASURE_H_
 
#define GND_CHANNEL 18
#define VREF_CHANNEL 17
#define AD_CHANNEL_NUMBER 16
#define AD_REAL_CHANNEL (AD_CHANNEL_NUMBER+3)
extern int light_to_DO[];
extern int buzzer_to_DO[];

#endif //__MEASURE_H_

