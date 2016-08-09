#include "stdsys.h"
int pw_time_flag=0;
unsigned char pw_set_flag;
signed short pw_scan_flag=10;
signed short pw_db_flag;
int receive_time=0;
int read_flag=0;
int len=0;
int pw_flag=1;
unsigned char settype;
unsigned char setaction;
unsigned char bcc1;
unsigned char hw_poll[21];
unsigned char hw_poll1[21];
unsigned char hw_poll2[20];
unsigned char hw_poll3[20];
unsigned char hw_poll4[20];
unsigned char hw_poll5[20];
unsigned char hw_poll6[20];
unsigned char hw_poll7[20];
unsigned char hw_poll8[20];
unsigned char hw_poll9[20];
unsigned char hw_ctr_cmd[60];
void  buf_init(char hw_addr)
{	 
	unsigned int sum;
	int ii;
	int check;

	hw_poll[0]=0x7e;
	hw_poll[1]=0x32;
	hw_poll[2]=0x30;
	hw_poll[3]=0x30+((unsigned char)(hw_addr&0xf0)>>4);
	hw_poll[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll[5]=0x34;
	hw_poll[6]=0x30;
	hw_poll[7]=0x34;
	hw_poll[8]=0x31;
	sum=2;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll[9]=0x30+sum;
	else hw_poll[9]=0x41+(sum-10);

	hw_poll[10]=0x30;
	hw_poll[11]=0x30;
	hw_poll[12]=0x32;
	hw_poll[13]=0x30;
	hw_poll[14]=0x30;
	check=0;
	for (ii=1;ii<15;ii++) check=hw_poll[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll[17]=0x30+sum;
	else hw_poll[17]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll[18]=0x30+sum;
	else hw_poll[18]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll[16]=0x30+sum;
	else hw_poll[16]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll[15]=0x30+sum;
	else hw_poll[15]=0x41+(sum-10);
	hw_poll[19]=0x0d;

	hw_poll1[0]=0x7e;
	hw_poll1[1]=0x32;
	hw_poll1[2]=0x30;
	hw_poll1[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll1[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll1[5]=0x34;
	hw_poll1[6]=0x30;
	hw_poll1[7]=0x34;
	hw_poll1[8]=0x33;
	sum=2;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll1[9]=0x30+sum;
	else hw_poll1[9]=0x41+(sum-10);

	hw_poll1[10]=0x30;
	hw_poll1[11]=0x30;
	hw_poll1[12]=0x32;
	hw_poll1[13]=0x30;
	hw_poll1[14]=0x30;

	check=0;
	for (ii=1;ii<15;ii++) check=hw_poll1[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll1[17]=0x30+sum;
	else hw_poll1[17]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll1[18]=0x30+sum;
	else hw_poll1[18]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll1[16]=0x30+sum;
	else hw_poll1[16]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll1[15]=0x30+sum;
	else hw_poll1[15]=0x41+(sum-10);
	hw_poll1[19]=0x0d;

	hw_poll2[0]=0x7e;
	hw_poll2[1]=0x32;
	hw_poll2[2]=0x30;
	hw_poll2[3]=0x30+((unsigned char)((hw_addr&0xf0)>>4));
	hw_poll2[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll2[5]=0x34;
	hw_poll2[6]=0x30;
	hw_poll2[7]=0x34;
	hw_poll2[8]=0x34;
	sum=2;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll2[9]=0x30+sum;
	else hw_poll2[9]=0x41+(sum-10);

	hw_poll2[10]=0x30;
	hw_poll2[11]=0x30;
	hw_poll2[12]=0x32;
	hw_poll2[13]=0x30;
	hw_poll2[14]=0x30;

	check=0;
	for (ii=1;ii<15;ii++) check=hw_poll2[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll2[17]=0x30+sum;
	else hw_poll2[17]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll2[18]=0x30+sum;
	else hw_poll2[18]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll2[16]=0x30+sum;
	else hw_poll2[16]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll2[15]=0x30+sum;
	else hw_poll2[15]=0x41+(sum-10);
	hw_poll2[19]=0x0d;

	hw_poll3[0]=0x7e;
	hw_poll3[1]=0x32;
	hw_poll3[2]=0x30;
	hw_poll3[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll3[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll3[5]=0x34;
	hw_poll3[6]=0x31;
	hw_poll3[7]=0x34;
	hw_poll3[8]=0x31;
	sum=0;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll3[9]=0x30+sum;
	else hw_poll3[9]=0x41+(sum-10);

	hw_poll3[10]=0x30;
	hw_poll3[11]=0x30;
	hw_poll3[12]=0x30;
	//  hw_poll3[13]=0x30;
	//  hw_poll3[14]=0x30;

	check=0;
	for (ii=1;ii<13;ii++) check=hw_poll3[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll3[15]=0x30+sum;
	else hw_poll3[15]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll3[16]=0x30+sum;
	else hw_poll3[16]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll3[14]=0x30+sum;
	else hw_poll3[14]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll3[13]=0x30+sum;
	else hw_poll3[13]=0x41+(sum-10);
	hw_poll3[17]=0x0d;

	hw_poll4[0]=0x7e;
	hw_poll4[1]=0x32;
	hw_poll4[2]=0x30;
	hw_poll4[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll4[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll4[5]=0x34;
	hw_poll4[6]=0x31;
	hw_poll4[7]=0x34;
	hw_poll4[8]=0x33;
	sum=0;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll4[9]=0x30+sum;
	else hw_poll4[9]=0x41+(sum-10);

	hw_poll4[10]=0x30;
	hw_poll4[11]=0x30;
	hw_poll4[12]=0x30;
	//  hw_poll3[13]=0x30;
	//  hw_poll3[14]=0x30;

	check=0;
	for (ii=1;ii<13;ii++) check=hw_poll4[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll4[15]=0x30+sum;
	else hw_poll4[15]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll4[16]=0x30+sum;
	else hw_poll4[16]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll4[14]=0x30+sum;
	else hw_poll4[14]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll4[13]=0x30+sum;
	else hw_poll4[13]=0x41+(sum-10);
	hw_poll4[17]=0x0d;

	hw_poll5[0]=0x7e;
	hw_poll5[1]=0x32;
	hw_poll5[2]=0x30;
	hw_poll5[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll5[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll5[5]=0x34;
	hw_poll5[6]=0x31;
	hw_poll5[7]=0x34;
	hw_poll5[8]=0x34;
	sum=0;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll5[9]=0x30+sum;
	else hw_poll5[9]=0x41+(sum-10);

	hw_poll5[10]=0x30;
	hw_poll5[11]=0x30;
	hw_poll5[12]=0x30;
	//  hw_poll3[13]=0x30;
	//  hw_poll3[14]=0x30;

	check=0;
	for (ii=1;ii<13;ii++) check=hw_poll5[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll5[15]=0x30+sum;
	else hw_poll5[15]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll5[16]=0x30+sum;
	else hw_poll5[16]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll5[14]=0x30+sum;
	else hw_poll5[14]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll5[13]=0x30+sum;
	else hw_poll5[13]=0x41+(sum-10);
	hw_poll5[17]=0x0d;

	hw_poll6[0]=0x7e;
	hw_poll6[1]=0x32;
	hw_poll6[2]=0x30;
	hw_poll6[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll6[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll6[5]=0x34;
	hw_poll6[6]=0x32;
	hw_poll6[7]=0x34;
	hw_poll6[8]=0x31;
	sum=0;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll6[9]=0x30+sum;
	else hw_poll6[9]=0x41+(sum-10);

	hw_poll6[10]=0x30;
	hw_poll6[11]=0x30;
	hw_poll6[12]=0x30;
	//  hw_poll3[13]=0x30;
	//  hw_poll3[14]=0x30;

	check=0;
	for (ii=1;ii<13;ii++) check=hw_poll6[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll6[15]=0x30+sum;
	else hw_poll6[15]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll6[16]=0x30+sum;
	else hw_poll6[16]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll6[14]=0x30+sum;
	else hw_poll6[14]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll6[13]=0x30+sum;
	else hw_poll6[13]=0x41+(sum-10);
	hw_poll6[17]=0x0d;

	hw_poll7[0]=0x7e;
	hw_poll7[1]=0x32;
	hw_poll7[2]=0x30;
	hw_poll7[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll7[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll7[5]=0x34;
	hw_poll7[6]=0x32;
	hw_poll7[7]=0x34;
	hw_poll7[8]=0x34;
	sum=0;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll7[9]=0x30+sum;
	else hw_poll7[9]=0x41+(sum-10);

	hw_poll7[10]=0x30;
	hw_poll7[11]=0x30;
	hw_poll7[12]=0x30;
	//  hw_poll3[13]=0x30;
	//  hw_poll3[14]=0x30;



	check=0;
	for (ii=1;ii<13;ii++) check=hw_poll7[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll7[15]=0x30+sum;
	else hw_poll7[15]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll7[16]=0x30+sum;
	else hw_poll7[16]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll7[14]=0x30+sum;
	else hw_poll7[14]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll7[13]=0x30+sum;
	else hw_poll7[13]=0x41+(sum-10);
	hw_poll7[17]=0x0d;

	hw_poll8[0]=0x7e;
	hw_poll8[1]=0x32;
	hw_poll8[2]=0x30;
	hw_poll8[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll8[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll8[5]=0x34;
	hw_poll8[6]=0x30;
	hw_poll8[7]=0x34;
	hw_poll8[8]=0x36;
	sum=0;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll8[9]=0x30+sum;
	else hw_poll8[9]=0x41+(sum-10);

	hw_poll8[10]=0x30;
	hw_poll8[11]=0x30;
	hw_poll8[12]=0x30;
	//  hw_poll3[13]=0x30;
	//  hw_poll3[14]=0x30;

	check=0;
	for (ii=1;ii<13;ii++) check=hw_poll8[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll8[15]=0x30+sum;
	else hw_poll8[15]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll8[16]=0x30+sum;
	else hw_poll8[16]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll8[14]=0x30+sum;
	else hw_poll8[14]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll8[13]=0x30+sum;
	else hw_poll8[13]=0x41+(sum-10);
	hw_poll8[17]=0x0d;

	hw_poll9[0]=0x7e;
	hw_poll9[1]=0x32;
	hw_poll9[2]=0x30;
	hw_poll9[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_poll9[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_poll9[5]=0x34;
	hw_poll9[6]=0x32;
	hw_poll9[7]=0x34;
	hw_poll9[8]=0x36;
	sum=0;
	sum=(~sum+1)%16;
	sum=sum&0x000f;
	if(sum<0x0a) hw_poll9[9]=0x30+sum;
	else hw_poll9[9]=0x41+(sum-10);

	hw_poll9[10]=0x30;
	hw_poll9[11]=0x30;
	hw_poll9[12]=0x30;
	//  hw_poll9[13]=0x30;
	//  hw_poll9[14]=0x30;

	check=0;
	for (ii=1;ii<13;ii++) check=hw_poll9[ii]+check;
	check=check%0xffff;
	check=~check+1;

	sum=(check&0x00f0)>>4;
	if(sum<0x0a) hw_poll9[15]=0x30+sum;
	else hw_poll9[15]=0x41+(sum-10);
	sum=check&0x000f;
	if(sum<0x0a) hw_poll9[16]=0x30+sum;
	else hw_poll9[16]=0x41+(sum-10);
	sum=(check&0x0f00)>>8;
	if(sum<0x0a) hw_poll9[14]=0x30+sum;
	else hw_poll9[14]=0x41+(sum-10);
	sum=(check&0xf000)>>12;
	if(sum<0x0a) hw_poll9[13]=0x30+sum;
	else hw_poll9[13]=0x41+(sum-10);
	hw_poll9[17]=0x0d;
}
void ctrl_buf_init(char hw_addr,unsigned char power_type,unsigned char power_action)
{
	unsigned int sum, i, check;
	hw_ctr_cmd[0]=0x7e;
	hw_ctr_cmd[1]=0x32;
	hw_ctr_cmd[2]=0x30;
	hw_ctr_cmd[3]=0x30+(unsigned char)((hw_addr&0xf0)>>4);
	hw_ctr_cmd[4]=0x30+(unsigned char)(hw_addr&0x0f);
	hw_ctr_cmd[5]=0x34;
	hw_ctr_cmd[6]=0x31;
	hw_ctr_cmd[7]=0x34;
	hw_ctr_cmd[8]=0x35;
	if(power_type==0)            //均浮充
	{
		sum=4;                       // 长度校验计算
		sum=(~sum+1)%16;
		sum=sum&0x000f;
		if(sum<0x0a) hw_ctr_cmd[9]=0x30+sum;
		else hw_ctr_cmd[9]=0x41+(sum-10);

		hw_ctr_cmd[10]=0x30;
		hw_ctr_cmd[11]=0x30;
		hw_ctr_cmd[12]=0x34;
  
		if(power_action==0x1)           //均充
		{
			hw_ctr_cmd[13]='1';
			hw_ctr_cmd[14]='0';
		}
		else if(power_action==0x0)     //浮充
		{ 
			hw_ctr_cmd[13]='1';
			hw_ctr_cmd[14]='F';
		}
		hw_ctr_cmd[15]='0';
		hw_ctr_cmd[16]='0';
		check=0;                        //数据区域校验

		for (i=1;i<17;i++) check=hw_ctr_cmd[i]+check;
		check=check%0xffff;
		check=~check+1;
		sum=(check&0x00f0)>>4;
		if(sum<0x0a)
			hw_ctr_cmd[19]=0x30+sum;
		else
			hw_ctr_cmd[19]=0x41+(sum-10);
		sum=check&0x000f;
		if(sum<0x0a)
			hw_ctr_cmd[20]=0x30+sum;
		else
			hw_ctr_cmd[20]=0x41+(sum-10);
		sum=(check&0x0f00)>>8;
		if(sum<0x0a)
			hw_ctr_cmd[18]=0x30+sum;
		else
			hw_ctr_cmd[18]=0x41+(sum-10);
		sum=(check&0xf000)>>12;
		if(sum<0x0a)
			hw_ctr_cmd[17]=0x30+sum;
		else
			hw_ctr_cmd[17]=0x41+(sum-10);
		hw_ctr_cmd[21]=0x0d;

		//pw_ctr_flag=1;      //置控制命令标志
		//pw_cmd_len=22;

		//break;
	}

	else                       //模块控制
	{
		sum=4;
		sum=(~sum+1)%16;
		sum=sum&0x000f;
		if(sum<0x0a) hw_ctr_cmd[9]=0x30+sum;
		else hw_ctr_cmd[9]=0x41+(sum-10);

		hw_ctr_cmd[10]=0x30;
		hw_ctr_cmd[11]=0x30;
		hw_ctr_cmd[12]=0x34;


		if(power_action==0x0)           //关机
		{
			hw_ctr_cmd[13]='2';
			hw_ctr_cmd[14]='F';
		}
		else if(power_action==0x1)     //开机
		{
			hw_ctr_cmd[13]='2';
			hw_ctr_cmd[14]='0';
		}

		sum=(unsigned short)(power_type&0xf0)>>4;
		if(sum<0x0a) hw_ctr_cmd[15]=0x30+sum;
		else hw_ctr_cmd[15]=0x41+(sum-10);
		sum=(unsigned short)power_type&0x0f;
		if(sum<0x0a) hw_ctr_cmd[16]=0x30+sum;
		else hw_ctr_cmd[16]=0x41+(sum-10);

		check=0;
			
		for (i=1;i<17;i++) check=hw_ctr_cmd[i]+check;
		check=check%0xffff;
		check=~check+1;

		sum=(check&0x00f0)>>4;
		if(sum<0x0a)
			hw_ctr_cmd[19]=0x30+sum;
		else
			hw_ctr_cmd[19]=0x41+(sum-10);
		sum=check&0x000f;
		if(sum<0x0a)
			hw_ctr_cmd[20]=0x30+sum;
		else
			hw_ctr_cmd[20]=0x41+(sum-10);
		sum=(check&0x0f00)>>8;
		if(sum<0x0a)
			hw_ctr_cmd[18]=0x30+sum;
		else
			hw_ctr_cmd[18]=0x41+(sum-10);
		sum=(check&0xf000)>>12;
		if(sum<0x0a)
			hw_ctr_cmd[17]=0x30+sum;
		else
			hw_ctr_cmd[17]=0x41+(sum-10);
		hw_ctr_cmd[21]=0x0d;

		//pw_ctr_flag=1;
		//pw_cmd_len=22;											
	}	  
}
