/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : task.h
 *  CREATOR  : RTU Team                 DATE: 2008-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/
 #ifndef __TASK_H_
#define __TASK_H_
#include "pthread.h"
struct task
{
	char name[20];
	pthread_t id;
	void *(*func)(void *arg);
};

int TaskCreat(struct task *ptask, const char *name, void *funcname(void *arg));
#endif
