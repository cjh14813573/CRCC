/*==========================================================================*
 *    Copyright(c) 2008-2011, China soft Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *  PRODUCT  : RTU2008
 *
 *  FILENAME : tsak.h
 *  CREATOR  : RTU Team                 DATE: 2008-09-26 10:00
 *  VERSION  : V1.00
 *  PURPOSE  : 
 *
 *
 *  HISTORY  :
 *
 *==========================================================================*/

#include "task.h"
#include "stdsys.h"
int TaskCreat(struct task *ptask, const char *name, void *funcname(void *arg))
{
	if(strlen(name) > sizeof(ptask->name)) return 1;
	strcpy((ptask->name), name);
	if(funcname == NULL) return 1;
	ptask->func = funcname;
	return pthread_create(&(ptask->id), NULL, (ptask->func), NULL);
}


