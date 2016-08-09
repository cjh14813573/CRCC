#include "typedef.h"
#include "stdsys.h"
#include "basetype.h"
/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : mutex.c
 *  CREATOR  : RTU Team                 DATE: 2008-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/
#include "mutex.h"

int MutexCreat(void* mutex)
{
	pthread_mutex_init((MUTEX_T *)mutex, NULL);
	return SUCCESS;
}
int MutexLock(void* mutex)
{
	if(pthread_mutex_lock((MUTEX_T *)mutex))
		return FAILURE;
	else
		return SUCCESS;
}
int MutexUnlock(void* mutex)
{
	if(pthread_mutex_unlock((MUTEX_T *)mutex))
		return FAILURE;
	else
		return SUCCESS;
}
int MutexTrylock(void* mutex)
{
	return pthread_mutex_trylock((MUTEX_T *)mutex);
}
int MutexDestroy(void* mutex)
{
	if(pthread_mutex_destroy((MUTEX_T *)mutex))
		return FAILURE;
	else
		return SUCCESS;
}
