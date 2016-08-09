#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

#define MIDDATASIZE 256
#define MAXDATASIZE 512
extern void buf_init(void);

int cmpchar(unsigned char *a,char *b,int len)
{
	int i,c=0;
	for(i=0;i<len;i++)
	{
		if(*(a+i)!=*(b+i))
		{
			c=1;
		}
	}
	return c;
}
int cmpi(char *a,int b,int len)
{
	int i,c=0;
	for(i=0;i<len;i++)
		{
			if(*(a+i)!=b)
			{
				c=1;
			}
		}
		return c;
}


void Modem(void)
{ 

}
