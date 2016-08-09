#include "stdsys.h"
#include "basetype.h"
#include "typedef.h"
int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300, 
B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400, 19200, 9600, 4800, 2400, 1200, 300,
38400, 19200, 9600, 4800, 2400, 1200, 300, };
void set_speed(int fd, int speedNUM)
{
	int i,speed;
	int status;
switch(speedNUM)
{
case 0:
speed=600;
break;
case 1:
speed=1200;
break;
case 2:
speed=2400;
break;
case 3:
speed=4800;
break;
case 4:
speed=9600;
break;
case 5:
speed=19200;
break;
case 6:
speed=38400;
break;
}

      struct termios Opt; 
      tcgetattr(fd, &Opt); 
      for (i= 0;i < sizeof(speed_arr)/sizeof(int);i++)
       {
      if  (speed == name_arr[i]) 
       { 
      tcflush(fd, TCIOFLUSH); 
      cfsetispeed(&Opt, speed_arr[i]); 
      cfsetospeed(&Opt, speed_arr[i]);
      status = tcsetattr(fd, TCSADRAIN, &Opt); 
      if (status != 0)
       {
      perror("tcsetattr fd1"); 
      return;
       }
      tcflush(fd,TCIOFLUSH);
       }   
       }
}
int set_Parity(int fd,int databitsNUM,int stopbitsNUM,int parityNUM)
{ 
	struct termios options; 
	char databits,stopbits,parity;
switch(databitsNUM)
{
case 0:
   databits=7;
 break;
case 1:
   databits=8;
 break;
case 2:
	databits=5;
 break;
default:
  break;
}
switch(parityNUM)
{
case 0:
 parity='O';
 break;
case 1:
 parity='E';
 break;
case 2:
 parity='N';
 break;
default:
 break;
}
 switch(stopbitsNUM)
 {
 case 0:
  stopbits=1;
  break;
 case 2:
  stopbits=2;
  break;
 default:
  break;
  }  
     if (tcgetattr(fd,&options)!=0) 
      { 
      perror("SetupSerial 1");     
      return(FALSE);  
      }
      options.c_cflag &= ~CSIZE; 
      switch (databits) 
      {   
	case 7:		
	options.c_cflag |= CS7; 
	break;
	case 8:     
	options.c_cflag |= CS8;
	break;   
	default:    
	fprintf(stderr,"Unsupported data size\n"); 
       return (FALSE);  
	}


 switch (parity) 
{   
       case 'n':
	case 'N':    
	options.c_cflag &= ~PARENB;  
	options.c_iflag &= ~INPCK;   
	break;  
	case 'o':   
	case 'O':     
	options.c_cflag |= (PARODD | PARENB); 
	options.c_iflag |= INPCK;             
	break;  
	case 'e':  
	case 'E':   
	options.c_cflag |= PARENB;   
	options.c_cflag &= ~PARODD;  
	options.c_iflag |= INPCK;       
	break;
	case 'S': 
	case 's':  
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;break;  
	default:   
	fprintf(stderr,"Unsupported parity\n");    
	return (FALSE);  
	}  
  
switch (stopbits)
        {   
	case 1:    
       options.c_cflag &= ~CSTOPB;  
	break;  
	case 2:    
	options.c_cflag |= CSTOPB;  
	break;
       fprintf(stderr,"Unsupported stop bits\n");  
       return (FALSE); 
        } 
 
       if (parity != 'n')   
    	   options.c_iflag |= INPCK; 
    	          tcflush(fd,TCIFLUSH);
    	          options.c_cc[VTIME] = 100; 
    	          options.c_cc[VMIN] = 8; 
    	          options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    	          options.c_oflag  &= ~OPOST;   /*Output*/
    	          options.c_iflag   &= ~ IXON;
		   options.c_iflag   &= ~ICRNL;
    	          //options.c_cflag  &= ~(CRTSCTS);
    	          //options.c_cflag  |= (CREAD);
    	          //options.c_cflag  |= (CLOCAL);
    	          
       if (tcsetattr(fd,TCSADRAIN,&options) != 0)   
        { 
	perror("SetupSerial 3");   
	return (FALSE);  
        } 
       return (TRUE);  
 
       }
int OpenDev(char dev)
{
char *Dev;
switch(dev)
{
case 1:
Dev="/dev/ttyAT0";
break;
case 2:
Dev="/dev/ttyAT1";
break;
case 3:
Dev="/dev/ttyS1";
break;
case 4:
Dev="/dev/ttyS2";
break;
case 5:
Dev="/dev/ttyS3";
break;
case 6:
Dev=Dev="/dev/ttyAT2";
break;
case 7:
Dev=Dev="/dev/ttyAT3";
break;
}
int fd = open( Dev, O_RDWR|O_NOCTTY|O_NDELAY);


if (-1 == fd)
{
perror("Can't Open Serial Port");
return -1;
}
else
return fd;
}

void copyCh(unsigned char *a,unsigned char *b1,unsigned char *b2,unsigned char *b3,unsigned char *b4,unsigned char *b5,unsigned char *b6,unsigned char *b7,int len)
{
	int i;
switch(*a)
{
case 1:
for(i=1;i<=len;i++)
	{
		*(a+i)=*(b1+i);
	}
break;
case 2:
for(i=1;i<=len;i++)
	{
		*(a+i)=*(b2+i);
	}
break;
case 3:
for(i=1;i<=len;i++)
	{
		*(a+i)=*(b3+i);
	}
break;
case 4:
for(i=1;i<=len;i++)
	{
		*(a+i)=*(b4+i);
	}
break;
case 5:
for(i=1;i<=len;i++)
	{
		*(a+i)=*(b5+i);
	}
break;
case 6:
for(i=1;i<=len;i++)
	{
		*(a+i)=*(b6+i);
	}
break;
case 7:
for(i=1;i<=len;i++)
	{
		*(a+i)=*(b7+i);
	}
break;
default:
	break;
}
}

//comtask_TypeDef comTASK;
void init_serialport()
{   
	 int i;
	 unsigned char com1[7]={0},com2[7]={0},com3[7]={0},com4[7]={0},com5[7]={0},temp[6]={0},com6[7]={0},com7[7]={0};
	 gs_RTUcfgMng.Getcfg(5,&com1[0]);
	 gs_RTUcfgMng.Getcfg(6,&com2[0]);
	 gs_RTUcfgMng.Getcfg(7,&com3[0]);
	 gs_RTUcfgMng.Getcfg(8,&com4[0]);
	 gs_RTUcfgMng.Getcfg(9,&com5[0]);
	  gs_RTUcfgMng.Getcfg(23,&com6[0]);
	 gs_RTUcfgMng.Getcfg(24,&com7[0]);
	 temp[1]=com1[0];
	 temp[2]=com2[0];   
	 temp[3]=com3[0];
	 temp[4]=com4[0];
	 temp[5]=com5[0];
	 temp[6]=com6[0];
	 temp[7]=com7[0];
	 comTASK.mn[0]=255;
	 comTASK.sb[0]=255;
	 comTASK.pw[0]=255;
	 comTASK.ac[0]=255;
	 comTASK.db[0]=255;
	 comTASK.IC[0]=255;
	 comTASK.UPS[0]=255;
	  comTASK.ACDU[0]=255;
	// comTASK.modemmn[0]=255;
 for(i=1;i<=7;i++)
 {
	 if(temp[i]==2)
	 {
		  comTASK.pw[0]=i;
	 }
	 else if(temp[i]==3)
	 {
              comTASK.ac[0]=i;
	 }
	 else if(temp[i]==6)
	 {
		 comTASK.ACDU[0]=i;
	 }
	 else if(temp[i]==4)
	 {
		 comTASK.db[0]=i;
	 }
	 else if(temp[i]==5)
	 {
		 comTASK.mn[0]=i;
	 }
	 else if(temp[i]==7)
	 {
		 comTASK.UPS[0]=i;
	 }
	 else if(temp[i]==9)  //  ·ÀÀ× ÓÃ ÖÇÄÜÃÅ½û
	 {
		 comTASK.IC[0]=i;
	 }
}
copyCh(&comTASK.mn[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
copyCh(&comTASK.sb[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
copyCh(&comTASK.pw[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
copyCh(&comTASK.ac[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
copyCh(&comTASK.db[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
copyCh(&comTASK.IC[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
copyCh(&comTASK.UPS[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
copyCh(&comTASK.ACDU[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],&com6[0],&com7[0],6);
//copyCh(&comTASK.modemmn[0],&com1[0],&com2[0],&com3[0],&com4[0],&com5[0],6);
//printf("%d,%d,%d",comTASK.pw[0],comTASK.db[0],comTASK.ac[0]);
gs_pwalarmMng.Getthre_val(20,&LCDTASK);
}

 