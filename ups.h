#include "stdsys.h"
int UPS_time_flag=0;
int UPS_alarm=0;
int UPS_set_flag;
int UPS_pw_flag=10;
signed short UPS_scan_flag=9;
signed short UPS_db_flag;
int UPS_receive_time=0;
int UPS_read_flag=0;
int UPSlen=0;
int UPS_flag1=11;

unsigned char UPS_pol[21];
unsigned char UPS_poll[21];
unsigned char UPS_poll1[21];
unsigned char UPS_poll2[23];
unsigned char UPS_poll3[20];
unsigned char UPS_poll4[20];
unsigned char UPS_poll5[20];
unsigned char UPS_poll6[20];
unsigned char UPS_poll7[20];
unsigned char UPS_poll8[20];
unsigned char UPS_poll9[20];

void  UPSbuf_init()   
{	 
	  unsigned int sum;   
	  int ii;
          int check;
		  
		  // ~ 0 0 P 0 0 3 S T B A A 
      UPS_poll[0]=0x7e;
      UPS_poll[1]=0x30;
      UPS_poll[2]=0x30;
      UPS_poll[3]=0x50;
      UPS_poll[4]=0x30;
      UPS_poll[5]=0x30;
      UPS_poll[6]=0x33;
      UPS_poll[7]=0x53;
      UPS_poll[8]=0x54;
      UPS_poll[9]=0x42;
     // UPS_poll[10]=0x41;
   //   UPS_poll[11]=0x41; 

	 //UPS_poll[12]=0x0D;
    
	//  ~ 0 0 P 0 0 3 S T I B 1 
      UPS_pol[0]=0x7e;
      UPS_pol[1]=0x30;
      UPS_pol[2]=0x30;
      UPS_pol[3]=0x50;
      UPS_pol[4]=0x30;
      UPS_pol[5]=0x30;
      UPS_pol[6]=0x33;
      UPS_pol[7]=0x53;
      UPS_pol[8]=0x54;
      UPS_pol[9]=0x49;
   //   UPS_pol[10]=0x42;
   //   UPS_pol[11]=0x31;

  // UPS_pol[12]=0x0D;
	// ~ 0 0 P 0 0 3 S T O B 7  

      UPS_poll1[0]=0x7e;
      UPS_poll1[1]=0x30;
      UPS_poll1[2]=0x30;
      UPS_poll1[3]=0x50;
      UPS_poll1[4]=0x30;
      UPS_poll1[5]=0x30;
      UPS_poll1[6]=0x33;
      UPS_poll1[7]=0x53;
      UPS_poll1[8]=0x54;
      UPS_poll1[9]=0x4F;
     // UPS_poll1[10]=0x42;
     // UPS_poll1[11]=0x37;

	//  UPS_poll1[12]=0x0D;

     // ~ 0 0 P 0 0 3 S T P B 8
     
      UPS_poll2[0]=0x7e;
      UPS_poll2[1]=0x30;
      UPS_poll2[2]=0x30;
      UPS_poll2[3]=0x50;
      UPS_poll2[4]=0x30;
      UPS_poll2[5]=0x30;
      UPS_poll2[6]=0x33;
      UPS_poll2[7]=0x53;
      UPS_poll2[8]=0x54;
      UPS_poll2[9]=0x50;
     // UPS_poll2[10]=0x42;
    //  UPS_poll2[11]=0x38;

	 // UPS_poll2[12]=0x0D;

    // ~ 0 0 P 0 0 3 S T A A 9
    
      UPS_poll3[0]=0x7e;
      UPS_poll3[1]=0x30;
      UPS_poll3[2]=0x30;
      UPS_poll3[3]=0x50;
      UPS_poll3[4]=0x30;
      UPS_poll3[5]=0x30;
      UPS_poll3[6]=0x33;
      UPS_poll3[7]=0x53;
      UPS_poll3[8]=0x54;
      UPS_poll3[9]=0x41;
   //   UPS_poll3[10]=0x41;
   //   UPS_poll3[11]=0x39;

	 // UPS_poll3[12]=0x0D;


}

