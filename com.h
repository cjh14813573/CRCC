#ifndef _COM_H_
#define _COM_H_
void set_speed(int fd, int speedNUM);
int set_Parity(int fd,int databitsNUM,int stopbitsNUM,int parityNUM);
int OpenDev(char dev);

#endif //end of _COM_H_

