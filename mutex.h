/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : mutex.h
 *  CREATOR  : RTU Team                 DATE: 2008-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/

#ifndef __MUTEX_H_
#define __MUTEX_H_
#include <sys/types.h>
typedef pthread_mutex_t MUTEX_T;
int MutexUnlock(void* mutex);
int MutexLock(void* mutex);
int MutexCreat(void* mutex);
int MutexTrylock(void* mutex);
int MutexDestroy(void* mutex);

#endif //__MUTEX_H_


