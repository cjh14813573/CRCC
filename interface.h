
#ifndef  _INTERFACE_H_
#define _INTERFACE_H_
unsigned short  cal_crc( unsigned char   *buf, unsigned short n);
void send_message(unsigned char *buf,unsigned char *sendbuf,unsigned short len,void *sendlen);
void floattochar(float n,char *floatResult);
void float_to_char(float float_number,unsigned char *char_result);
void char_to_float(unsigned char *charbuf,float *floatbuf,int head,int end);
void chartofloat(unsigned char *charbuf,float *floatbuf,int head,int end);
char *itoa( int n,char *strResult);
char FtoS(double f,char *str);
int chksum(unsigned char *chkbuff,unsigned char *chkbuff1,unsigned int chklen);
int len_chksum(unsigned char *len_chkbuff);
void floattoint(unsigned char *charbuf, int *floatbuf,int head,int end);
void ASCIItoH(unsigned char *ASCIIbuff,unsigned char *Hbuff,unsigned int ASCIIlen);
void Hebing(unsigned char *Hbuff,unsigned char *Abuff,unsigned int Hlen);
unsigned short crccode(char *strbuf,int buf_len);
unsigned int crc16(unsigned char *buf, unsigned long len);
void NUMASCIItoH(unsigned char *ASCIIbuff,unsigned char *Hbuff,unsigned int ASCIIlen);
void chartolg(long *lgint,char *charResult);
void ltochar(unsigned char *charbuf,long lnum);
void string_to_char(char *str1, unsigned char *charResult);
void unicode_to_char(char *str1, unsigned char *charResult);
void inttofloat(unsigned char *charbuf,float *floatbuf);
int size_of_unicode(unsigned char *unicodeString);
void set_alarm_des(int flag,unsigned char *Des);
int write_data_buffer(unsigned char *buffer,short int device,short int point,int id_long);
int write_alarm_buffer(unsigned char * buffer, void *Event,int EventCount);
#endif //__INTERFACE_H_


