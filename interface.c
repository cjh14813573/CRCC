#include "stdsys.h"
#include "typedef.h"
#include "inifile.h"
#include "property.h"
/*unsigned short crccode(char *strbuf,int buf_len)
   {
		 unsigned long tx;
		 unsigned char crc;
		 unsigned short code;
		 unsigned long gx=0x11021;
		 unsigned char ii,jj;

		  tx=*strbuf*256;
		  strbuf++;
		  tx=tx+*strbuf;
		  strbuf++;
		  for(ii=2;ii<buf_len;ii++)
		  {
			  crc=*strbuf;
			   for(jj=0;jj<8;jj++)
			   {
				 if((crc&0x80)==0x80)
				 tx=tx*2+1;
				 else tx=tx*2;

			   crc=crc*2;
			   if((tx&0x10000)==0x10000)
			   tx=tx^gx;
			}
			   strbuf++;

		  }

	   code=tx;
	  return(code);

   }*/

unsigned short  crccode ( unsigned char   *buf, unsigned long n)
{
unsigned int crc_table[] = {
    0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
  } ;
	unsigned short  crc;
	crc = 0xffff;
	while (n > 0)
	{
		crc = ((crc >> 8) & 0xff) ^ crc_table[(crc ^ *(buf++)) & 0xff];
 		
	n--;

	}
	return( (crc >> 8) | (crc << 8) );

}


//////门锁CRC16-1021校验

unsigned int crc16(unsigned char *buf, unsigned long len) /*产生16位CRC码的程序*/
{
   unsigned char i;
   unsigned int crc=0;
   unsigned int ccitt=0x1021;

   while(len--!=0)
   {
	  for(i=0x80; i!=0; i/=2)
	  {
	      if((crc&0x8000)!=0)
	      {
		crc*=2;
		crc^=ccitt;
	      } /* 余式CRC乘以2再求CRC */

	      else crc*=2;

	      if((*buf&i)!=0) crc^=ccitt; /* 再加上本位的CRC */
	  }
	  buf++;
   }
   return(crc);
}

unsigned short  cal_crcrtu( char   *buf, unsigned long n)
{
unsigned int crc_table[] = {
    0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
  } ;
	unsigned short  crc;
	crc = 0xffff;
	while (n > 0)
	{
		crc = ((crc >> 8) & 0xff) ^ crc_table[(crc ^ *(buf++)) & 0xff];
 		
	n--;

	}
	return( (crc >> 8) | (crc << 8) );

}

unsigned short  cal_crc( unsigned char   *buf, unsigned long n)
{
unsigned int crc_table[] = {
    0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
  } ;
	unsigned short  crc;
	crc = 0xffff;
	while (n > 0)
	{
		crc = ((crc >> 8) & 0xff) ^ crc_table[(crc ^ *(buf++)) & 0xff];
 		
	n--;

	}
	return( (crc >> 8) | (crc << 8) );

}



void send_message(unsigned char *buf,unsigned char *sendbuf,unsigned short len,void *sendlen)
{
   unsigned short  i,ii;
   *sendbuf=0x7e;
   ii=1;
   for(i=0;i<len;i++)
   {
      if((buf[i]==0x7d)||(buf[i]==0X7e)||(buf[i]<0x20))
        {
        sendbuf[ii++]=0x7d;
        sendbuf[ii++]=buf[i]^0x20;
        }
      else
        {
        sendbuf[ii++]=buf[i];
        }
    }
   sendbuf[ii]=0x7e;
   *(unsigned short *)(sendlen)=ii+1;
}

void floattochar(float n,char *floatResult)
{
	union fl_val
	{
		unsigned char ch[4];
		float fl;
	}itof;
	itof.fl=n;
	*(floatResult)=itof.ch[0];
	*(floatResult+1)=itof.ch[1];
	*(floatResult+2)=itof.ch[2];
	*(floatResult+3)=itof.ch[3];
}

void float_to_char(float float_number,unsigned char *char_result)
{
	union fl_val
	{
		unsigned char ch[4];
		float fl;
	}itof;
	itof.fl=float_number;
	*(char_result)=itof.ch[3];
	*(char_result+1)=itof.ch[2];
	*(char_result+2)=itof.ch[1];
	*(char_result+3)=itof.ch[0];
}//crcc用，顺序和之前的相反

void chartofloat(unsigned char *charbuf,float *floatbuf,int head,int end)
{
	int iii=0,fi;
	union fl_value
	{ 
		unsigned char cch[4];
		float fv;
	}fl_hw;
	for(fi=head;fi<end;fi+=4)
	{
		fl_hw.cch[0]=*(charbuf+fi);
		fl_hw.cch[1]=*(charbuf+fi+1);
		fl_hw.cch[2]=*(charbuf+fi+2);
		fl_hw.cch[3]=*(charbuf+fi+3);
		*(floatbuf+iii)=(float)(fl_hw.fv);
		iii++;
	}
}
void char_to_float(unsigned char *charbuf,float *floatbuf,int head,int end)
{
	int iii=0,fi;
	union fl_value
	{ 
		unsigned char cch[4];
		float fv;
	}fl_hw;
	for(fi=head;fi<end;fi+=4)
	{
		fl_hw.cch[3]=*(charbuf+fi);
		fl_hw.cch[2]=*(charbuf+fi+1);
		fl_hw.cch[1]=*(charbuf+fi+2);
		fl_hw.cch[0]=*(charbuf+fi+3);
		*(floatbuf+iii)=(float)(fl_hw.fv);
		iii++;
	}
}


char *itoa( int n,char *strResult)
{
	char *p=strResult;
	if(n/10!=0)
		p=itoa(n/10,p);
		*p=n%10+'0';
		++p;
		*p='\0';
		//printf("%s\n",*p);
		return p;
}

char FtoS(double f,char *str)
{
	char *p;
	sprintf(str,"%f",f);
	p=str+strlen(str)-1;
	while(*p=='0')
		p--;
	*(p+1)='\0';
	if(*p=='.')
		*p='\0';
   return(*str);
}

int chksum(unsigned char *chkbuff,unsigned char *chkbuff1,unsigned int chklen)
{
unsigned long sum=0,i;
unsigned char sum1[2]={0};
for (i=1;i<(chklen-5);i++)
               {
	           sum=sum+*(chkbuff+i);
	           }
               sum=(~(sum%65536))+1;
               sum1[0]=(sum>>8)&0x000000ff;
               sum1[1]=sum&0x000000ff;
               
               //printf("\n%x,%x",sum1[0],sum1[1]);
             
               if ((sum1[0]==*(chkbuff1+(chklen-2)/2-2))&&(sum1[1]==*(chkbuff1+(chklen-2)/2-1)))
                 return 1;
               else
                 return 0;
}
               


int len_chksum(unsigned char *len_chkbuff)
{
int ii;unsigned char lchksum=0;

         
          for(ii=9;ii<12;ii++)
            { 
           lchksum=lchksum+(*(len_chkbuff+ii));
            }
            
          lchksum=(~(lchksum%16))+1;
            lchksum=lchksum&0x0f;
           if (lchksum==*(len_chkbuff+8))
            {
            
            return 1;
            }
           else 
           {
           
           return 0;
           }
         
}




void floattoint(unsigned char *charbuf,int *floatbuf,int head,int end)
{
 int iii=0,fi;
  union fl_value
  { 
  unsigned char cch[4];
  float fv;
  }fl_hw;
for(fi=head;fi<end;fi+=4)
{
fl_hw.cch[0]=*(charbuf+fi);
fl_hw.cch[1]=*(charbuf+fi+1);
fl_hw.cch[2]=*(charbuf+fi+2);
fl_hw.cch[3]=*(charbuf+fi+3);
*(floatbuf+iii)=(int)(fl_hw.fv*10);

iii++;


}
printf("\n");

}

void NUMASCIItoH(unsigned char *ASCIIbuff,unsigned char *Hbuff,unsigned int ASCIIlen)    //只转移ASCii 中 数字部分
{
unsigned int Hlen=0,len1;
for(len1=1;len1<(ASCIIlen-1);len1++)
           {    
              if ((*(ASCIIbuff+len1)<0x3A)&& (*(ASCIIbuff+len1)>0x2F))
              	{
               *(Hbuff+Hlen)=*(ASCIIbuff+len1)&0x0f;
              	}
               else if ((*(ASCIIbuff+len1)<0x47)&& (*(ASCIIbuff+len1)>0x40))
               	{
               *(Hbuff+Hlen)=*(ASCIIbuff+len1)-0x41+10;
               	}
	        else
	        {*(Hbuff+Hlen)=*(ASCIIbuff+len1); }
                 Hlen++;
}
                 
}
void ASCIItoH(unsigned char *ASCIIbuff,unsigned char *Hbuff,unsigned int ASCIIlen)
{
unsigned int Hlen=0,len1;
for(len1=1;len1<(ASCIIlen-1);len1++)
           {    if (*(ASCIIbuff+len1)<0x41)
               *(Hbuff+Hlen)=*(ASCIIbuff+len1)&0x0f;
               else
               *(Hbuff+Hlen)=*(ASCIIbuff+len1)-0x41+10;
                 Hlen++;}
                 
}

void Hebing(unsigned char *Hbuff,unsigned char *Abuff,unsigned int Hlen)
{
unsigned int Alen=0,len2;
for(len2=0;len2<Hlen;len2+=2)
                 {
               *(Abuff+Alen)=(((*(Hbuff+len2))<<4)|(  *(Hbuff+(len2+1))));
              
               Alen++;
                 }

}

/////CRCC

void chartolg(long *lgint,char *charResult)
{
	long lg,lgH,lgL;
	lgH=*charResult;
	lgL=*(charResult+2);
	lgH=((lgH<<8)|*(charResult+1));
	lgL=((lgL<<8)|*(charResult+3));
	lg=((lgH<<16)|lgL);
	*lgint=lg;
}

void ltochar(unsigned char *charbuf,long lnum)
{
   *charbuf=((lnum>>24)&0xff);
   *(charbuf+1)=((lnum>>16)&0xff);
   *(charbuf+2)=((lnum>>8)&0xff);
   *(charbuf+3)=(lnum&0xff);
}

void unicode_to_char(char *str1, unsigned char *charResult)
{
	int i=0,ii=0;
	char *q;
	char qq[256]={0};
	q=qq;
	char *p=str1;
	while( p[i]!='\0')
	{
		memset(qq,0,256);
		ii=0;
		while((p[i]!=',' )&&(p[i]!=0x20)&&(p[i]!='-')&&(p[i]!='\0'))
		{
			q[ii++]=p[i];
			i++;
		}
		if(p[i]!='\0')
		{
			i+=1;
		}
		else
		{
			*(charResult++)=atoi(qq);
			break;
		}
		*(charResult++)=atoi(qq);
	}
}


void inttofloat(unsigned char *charbuf,float *floatbuf)
{
union fl_value
{ 
	unsigned char cch[4];
	float fv;
}fl_hw;
fl_hw.fv=*floatbuf;
*charbuf=fl_hw.cch[3];
*(charbuf+1)=fl_hw.cch[2];
*(charbuf+2)=fl_hw.cch[1];
*(charbuf+3)=fl_hw.cch[0];
}

int size_of_unicode(unsigned char *unicodeString)
{
	//用于判断存于数组中的汉字字符串长度，数组被初始时全部填了0x20
	int i=0;
	while(*(unicodeString+i)!=0x20)
	{
		i++;
	}
	return i;
}

void set_alarm_des(int flag,unsigned char *Des)
{
	switch(flag)
	{
		case ALARM_CONTENT_RECOVER://恢复
			*Des=187;
			*(Des+1)=214;
			*(Des+2)=184;
			*(Des+3)=180;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_ALARM://告警
			*Des=184;
			*(Des+1)=230;
			*(Des+2)=190;
			*(Des+3)=175;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_HIGH://过高
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=184;
			*(Des+3)=223;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_LOW://过低
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=181;
			*(Des+3)=205;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_POWER_FAIL://停电
			*Des=205;
			*(Des+1)=163;
			*(Des+2)=181;
			*(Des+3)=231;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_ERROR://故障
			*Des=185;
			*(Des+1)=202;
			*(Des+2)=213;
			*(Des+3)=207;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_BREAK://断开
			*Des=182;
			*(Des+1)=207;
			*(Des+2)=191;
			*(Des+3)=170;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_HIGH_1://过高(一级)
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=184;
			*(Des+3)=223;
			*(Des+4)=40;//(
			*(Des+5)=210;
			*(Des+6)=187;
			*(Des+7)=188;
			*(Des+8)=182;
			*(Des+9)=41;//)
			*(Des+10)=58;//":"
			*(Des+11)=214;
			*(Des+12)=181;//值
			*(Des+13)=61;//"="
			break;
			
		case ALARM_CONTENT_HIGH_2://过高(二级)
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=184;
			*(Des+3)=223;
			*(Des+4)=40;//(
			*(Des+5)=182;
			*(Des+6)=254;
			*(Des+7)=188;
			*(Des+8)=182;
			*(Des+9)=41;//)
			*(Des+10)=58;//":"
			*(Des+11)=214;
			*(Des+12)=181;//值
			*(Des+13)=61;//"="
			break;

		case ALARM_CONTENT_HIGH_3://过高(三级)
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=184;
			*(Des+3)=223;
			*(Des+4)=40;//(
			*(Des+5)=200;
			*(Des+6)=253;
			*(Des+7)=188;
			*(Des+8)=182;
			*(Des+9)=41;//)
			*(Des+10)=58;//":"
			*(Des+11)=214;
			*(Des+12)=181;//值
			*(Des+13)=61;//"="
			break;

		case ALARM_CONTENT_LOW_1://过低(一级)
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=181;
			*(Des+3)=205;
			*(Des+4)=40;//(
			*(Des+5)=210;
			*(Des+6)=187;
			*(Des+7)=188;
			*(Des+8)=182;
			*(Des+9)=41;//)
			*(Des+10)=58;//":"
			*(Des+11)=214;
			*(Des+12)=181;//值
			*(Des+13)=61;//"="
			break;

		case ALARM_CONTENT_LOW_2://过低(二级)
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=181;
			*(Des+3)=205;
			*(Des+4)=40;//(
			*(Des+5)=182;
			*(Des+6)=254;
			*(Des+7)=188;
			*(Des+8)=182;
			*(Des+9)=41;//)
			*(Des+10)=58;//":"
			*(Des+11)=214;
			*(Des+12)=181;//值
			*(Des+13)=61;//"="
			break;

		case ALARM_CONTENT_LOW_3://过低(三级)
			*Des=185;
			*(Des+1)=253;
			*(Des+2)=181;
			*(Des+3)=205;
			*(Des+4)=40;//(
			*(Des+5)=200;
			*(Des+6)=253;
			*(Des+7)=188;
			*(Des+8)=182;
			*(Des+9)=41;//)
			*(Des+10)=58;//":"
			*(Des+11)=214;
			*(Des+12)=181;//值
			*(Des+13)=61;//"="
			break;

		case ALARM_CONTENT_OFF://关机
			*Des=185;
			*(Des+1)=216;
			*(Des+2)=187;
			*(Des+3)=250;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		case ALARM_CONTENT_DISCHARGE://放电
			*Des=183;
			*(Des+1)=197;
			*(Des+2)=181;
			*(Des+3)=231;
			*(Des+4)=58;//":"
			*(Des+5)=214;
			*(Des+6)=181;//值
			*(Des+7)=61;//"="
			break;

		default:
			break;
	}
}

void last_byte_of_int_to_char(unsigned char *buffer, int number)
{
	union fl_value
	{ 
		unsigned char cch[4];
		int fv;
	}fl_hw;
	fl_hw.fv=number;
	*buffer=fl_hw.cch[0];
}

int write_data_buffer(unsigned char *buffer,short int device,short int point,long id_long)
{ 
	unsigned char type=gs_ProMng.Pro[device][point].Type;
	int temp_data;
	//Num和Type在读取不到时赋值为-1
	ltochar(buffer,type);
	ltochar(buffer+4,id_long);
	if(type==3||type==5)//模拟量
	{
		ltochar(buffer,type);
		ltochar(buffer+4,id_long);
		gs_NewDataMng.fGetCData(device,point,DATA,&temp_data);
		float_to_char(((float)temp_data)/10,buffer+8);
		gs_NewDataMng.fGetCData(device,point,STATUS,&temp_data);
		ltochar(buffer+12,temp_data);
		return 16;
	}
	else if(type==2||type==4)//数字量
	{
		ltochar(buffer,type);
		ltochar(buffer+4,id_long);
		gs_NewDataMng.fGetCData(device,point,DATA,&temp_data);
		last_byte_of_int_to_char(buffer+8,temp_data);
		gs_NewDataMng.fGetCData(device,point,STATUS,&temp_data);
		ltochar(buffer+9,temp_data);
		return 13;
	}
	else return 0;
}

int write_alarm_buffer(unsigned char *buffer, void *Event,int EventCount)
{	
	int data_status;
	struct completeID temp_id_struct;
	int i=0;
	Event_TypeDef *SendEvent;
	SendEvent=(Event_TypeDef *)Event;
	
	//	ID
	temp_id_struct=id_struct[0];
	temp_id_struct.device=SendEvent->Device;
	temp_id_struct.point=SendEvent->Point;
	ltochar(buffer,IDstruct_to_long(temp_id_struct));
	
	//数据状态
	gs_NewDataMng.fGetCData(SendEvent->Device,SendEvent->Point,STATUS,&data_status);
	ltochar(buffer+4,data_status);
	
	//"["
	*(buffer+8)=0x5b;
	
	//告警序号，前三位为rtuID,后三位为告警计数
	sprintf(buffer+9,"%03d%03d",id_struct[0].rtuID,EventCount);
	
	//TAB
	*(buffer+15)=0x09;
	
	//对象名称，ss-su-so-sp，ss和su以数字表示，so和sp以文字表示
	for(i=0;i<42;i++)
	{
		*(buffer+16+i)=0x20;//初始化为空格
	}
	sprintf(buffer+16,"%d-%d-%.*s-%.*s",CENTER_ID,id_struct[0].rtuID,size_of_unicode(gs_ProMng.Pro[SendEvent->Device][0].Name),gs_ProMng.Pro[SendEvent->Device][0].Name,size_of_unicode(gs_ProMng.Pro[SendEvent->Device][SendEvent->Point].Name),gs_ProMng.Pro[SendEvent->Device][SendEvent->Point].Name);
	
	//TAB
	*(buffer+58)=0x09;
	
	//时间描述
	sprintf(buffer+59,"%02d%02d-%02d-%02d %02d:%02d:%02d",SendEvent->SYearHigh,SendEvent->SYearLow,SendEvent->SMonth,SendEvent->SDay,SendEvent->SHour,SendEvent->SMinute,SendEvent->SSecond);
	
	//TAB
	*(buffer+78)=0x09;
	
	//ID描述
	sprintf(buffer+79,"%02X.%03X.%02X.%03X",CENTER_ID,id_struct[0].rtuID,SendEvent->Device,SendEvent->Point);
	
	//TAB
	*(buffer+92)=0x09;
	
	//告警级别，汉字表示
	switch(SendEvent->AlarmLevel)
	{
		case 1://紧急 189 244 188 177
			*(buffer+93)=189;
			*(buffer+94)=244;
			*(buffer+95)=188;
			*(buffer+96)=177;
			break;
	
		case 2://重要 214 216 210 170 
			*(buffer+93)=214;
			*(buffer+94)=216;
			*(buffer+95)=210;
			*(buffer+96)=170;
			break;
	
		case 3://一般 210 187 176 227 
			*(buffer+93)=210;
			*(buffer+94)=187;
			*(buffer+95)=176;
			*(buffer+96)=227;
			break;
	}
	
	//TAB
	*(buffer+97)=0x09;
	
	//告警号 alarmlist
	sprintf(buffer+98,"%06d",SendEvent->ID);
	
	//TAB
	*(buffer+104)=0x09;
	
	//告警标志描述和告警标志时间
	switch(SendEvent->Flag)
	{
		case ALARM_FLAG_START://开始 191 170 202 188
			*(buffer+105)=191;
			*(buffer+106)=170;
			*(buffer+107)=202;
			*(buffer+108)=188;
			*(buffer+109)=0x09;//TAB
			sprintf(buffer+110,"%02d%02d-%02d-%02d %02d:%02d:%02d",SendEvent->SYearHigh,SendEvent->SYearLow,SendEvent->SMonth,SendEvent->SDay,SendEvent->SHour,SendEvent->SMinute,SendEvent->SSecond);
			break;
	
		case ALARM_FLAG_END://结束 189 225 202 248
			*(buffer+105)=189;
			*(buffer+106)=225;
			*(buffer+107)=202;
			*(buffer+108)=248;
			*(buffer+109)=0x09;//TAB
			sprintf(buffer+110,"%02d%02d-%02d-%02d %02d:%02d:%02d",SendEvent->EYearHigh,SendEvent->EYearLow,SendEvent->EMonth,SendEvent->EDay,SendEvent->EHour,SendEvent->EMinute,SendEvent->ESecond);
			break;
	}
	
	//TAB
	*(buffer+129)=0x09;
	
	//告警文本
	for(i=0;i<32;i++)
	{
		*(buffer+130+i)=0x20;//初始化为空格
	}
	unsigned char des[20]={0x20};
	set_alarm_des(SendEvent->Content,des);
	if(gs_ProMng.Pro[SendEvent->Device][SendEvent->Point].Type==3)
	{
		sprintf(buffer+130,"%.*s%f",size_of_unicode(des),des,(float)(SendEvent->Value)/10);							
	}
	else if(gs_ProMng.Pro[SendEvent->Device][SendEvent->Point].Type==2)
	{
		sprintf(buffer+130,"%.*s%d",size_of_unicode(des),des,SendEvent->Value);							
	}
	
	//"]"
	*(buffer+162)=0x5d;
	//补5个空格
	*(buffer+163)=0x20;
	*(buffer+164)=0x20;
	*(buffer+165)=0x20;
	*(buffer+166)=0x20;
	*(buffer+167)=0x20;
	return 168;
}
