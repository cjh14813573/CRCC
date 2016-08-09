#include "stdsys.h"
#include "lcd.h"
#include "en_dot.h"
#include "ch_dot.h"
#include "basetype.h"
#include "typedef.h"
#include "interface.h"
#include "inifile.h"

int hd_lcd;
extern char DI_val[16];//直接使用 DI的数据

void set_lcd_cursor(void)
{
}
void change(unsigned char num,unsigned char *resnum)
{
  *resnum=num%10;
  *(resnum+1)=(num/10)%10;
  *(resnum+2)=(num/100)%10;
}
void changeaddr(unsigned int num,unsigned char *resnum)
{
  *resnum=num%10;
  *(resnum+1)=(num/10)%10;
  *(resnum+2)=(num/100)%10;
}

void SendOneChar(unsigned char Row,unsigned char Col,unsigned char *ch, unsigned char chRev) 
{
	unsigned char i;//,dd3;
	unsigned char dsp_buf[100];

	if((Row>MAX_ROW) || (Col>MAX_COL))
		return ;

	dsp_buf[0] = Row;
	dsp_buf[1] = Col;
	for( i=0;i<=15;i++)
	{
		if(chRev==0)  //normal
		{
	 		dsp_buf[i+2] = ascii[*ch][i];
		}
		else
		{
	 		dsp_buf[i+2]= ~ascii[*ch][i];
		}
	}
	write(hd_lcd, dsp_buf, 18);

}
int search_word(unsigned char *pVal)
{
	int i;
	for(i=0; i<202; i++)
		{
		if((ch_maxtric[i].code[0] == pVal[0]) && (ch_maxtric[i].code[1] == pVal[1]))
			return i;
		}
	return -1;
}
void SendOneWord(unsigned char Row,unsigned char Col,unsigned char *pVal, unsigned char chRev) 
{
	unsigned char i;
	int pos;
	unsigned char dsp_buf[100];
	
	if((Row>MAX_ROW) || (Col>MAX_COL))
		return ;
	pos = search_word(pVal);
	if(pos<0)
		return ;
	//printf("\nPOS = %d",pos);
	dsp_buf[0] = Row;
	dsp_buf[1] = Col;
	
	dsp_buf[18] = Row;
	dsp_buf[19] = Col+1;
	for( i=0;i<=15;i++)
	{
		if(chRev==0)  //normal
		{
	 		dsp_buf[i+2] = ch_maxtric[pos].dot[i*2];
			dsp_buf[i+20] = ch_maxtric[pos].dot[i*2+1];
		}
		else
		{
	 		dsp_buf[i+2]= ~ch_maxtric[pos].dot[i*2];
			dsp_buf[i+20]= ~ch_maxtric[pos].dot[i*2+1];
		}
	}
	
	write(hd_lcd, dsp_buf, 18*2);
}
void lcd_print(unsigned char Row,unsigned char Col,char  *pVal,unsigned char chrev) 
{
	//unsigned char dd3,thisCol, *MypVal;
	if((Row>MAX_ROW) || (Col>MAX_COL)) 
		return ;
	while(*pVal != '\0')
	{
		if(*pVal >=128)
		{
		SendOneWord(Row, Col, pVal,chrev);
		}
		else
		SendOneChar(Row, Col, pVal, chrev);
		Col++;
		if(Col>MAX_COL)
			{
			Col = 0;
			Row++;
			}
		if(Row>MAX_ROW)
			Row = 0;
		pVal++;
	}

}
void DBprint(unsigned char Row,unsigned char Col,unsigned char  pVal,unsigned char chrev)
{
	char dbbuf[16];
	sprintf(dbbuf, "%02d",pVal);
	lcd_print(Row, Col, dbbuf, chrev);
}


void AIprint(unsigned char aitask,unsigned char chrev)
{
	if(chrev==0)
	{
		switch(aitask)
	 	{
			case 0:
				lcd_print(1,21,"温度",0);   
				break;
			case 1:
				lcd_print(1,21,"湿度",0);   
				break;
			case 2:
				lcd_print(1,21,"空调电流",0);   
				break;
			case 3:
				lcd_print(1,21,"空调电压",0);   
				break;
			case 4:
				lcd_print(1,21,"交流电压",0);   
				break;
			case 5:
				lcd_print(1,21,"交流电流",0);   
				break;
			case 6:
				lcd_print(1,21,"直流电压",0);   
				break;
			case 7:
				lcd_print(1,21,"直流电流",0);   
				break;
			case 8:
				lcd_print(1,21,"温度2",0);  
				break;
			case 9:
				lcd_print(1,21,"湿度2",0);  
				break;
			case 10:
				lcd_print(1,21,"温度3",0);  
				break;
			case 11:
				lcd_print(1,21,"湿度3",0);  
				break;
			case 12:
				lcd_print(1,21,"温度4",0);  
				break;
			case 13:
				lcd_print(1,21,"湿度4",0);  
				break;
			case 14:
				lcd_print(1,21,"交流 1",0); 
				break;
			case 15:
				lcd_print(1,21,"交流 2",0); 
				break;
			case 255:
				lcd_print(1,21,"保留",0);   
				break;
			default:
				lcd_print(1,21,"保留",0);   
				break;
 		}
	}
	else if(chrev==1)
	{
		switch(aitask)
 		{
			case 0:
				lcd_print(1,21,"温度",1);	 
				break;
			case 1:
				lcd_print(1,21,"湿度",1);	 
				break;
			case 2:
				lcd_print(1,21,"空调电流",1);	 
				break;
			case 3:
				lcd_print(1,21,"空调电压",1);	 
				break;
			case 4:
				lcd_print(1,21,"交流电压",1);	 
				break;
			case 5:
				lcd_print(1,21,"交流电流",1);	 
				break;
			case 6:
				lcd_print(1,21,"直流电压",1);	 
				break;
			case 7:
				lcd_print(1,21,"直流电流",1);	 
				break;
			case 8:
				lcd_print(1,21,"温度2",1);  
				break;
			case 9:
				lcd_print(1,21,"湿度2",1);  
				break;
			case 10:
				lcd_print(1,21,"温度3",1);  
				break;
			case 11:
				lcd_print(1,21,"湿度3",1);  
				break;
			case 12:
				lcd_print(1,21,"温度4",1);  
				break;
			case 13:
				lcd_print(1,21,"湿度4",1);  
				break;
			case 14:
				lcd_print(1,21,"交流 1",1); 
				break;
			case 15:
				lcd_print(1,21,"交流 2",1); 
				break;
			case 255:
				lcd_print(1,21,"保留",1);	 
				break;
			default:
				lcd_print(1,21,"保留",1);	 
				break;
 		}
	}
}

void DIprint(unsigned char ditask,unsigned char chrev)
{
if(chrev==0)
{
	 switch(ditask)
	 	{
			case 0:
				lcd_print(2,21,"门禁",0);	
				break;
			case 1:
				lcd_print(2,21,"水浸",0);	
				break;
			case 2:
				lcd_print(2,21,"烟感",0);	
				break;
			case 3:
				lcd_print(2,21,"窗禁",0);	
				break;
			case 4:
				lcd_print(2,21,"红外",0);	
				break;
			case 5:
				lcd_print(2,21,"玻璃破碎",0);	
				break;
			case 6:
				lcd_print(2,21,"门禁2 ",0);	
				break;
			case 7:
				lcd_print(2,21,"门禁3",0);	
				break;
			case 8:
				lcd_print(2,21,"门禁4",0);	
				break;
			case 9:
				lcd_print(2,21,"玻璃破碎2",0);	
				break;
			case 10:
				lcd_print(2,21,"玻璃破碎3",0);	
				break;
			case 11:
				lcd_print(2,21,"玻璃破碎4",0);	
				break;
			case 12:
				lcd_print(2,21,"水浸2",0);	
				break;
			case 13:
				lcd_print(2,21,"水浸3",0);	
				break;
			case 14:
				lcd_print(2,21,"水浸4",0);	
				break;
			case 15:
				lcd_print(2,21,"烟感2",0);	
				break;
			case 16:
				lcd_print(2,21,"烟感3",0);	
				break;
			case 17:
				lcd_print(2,21,"烟感4",0);	
				break;
			case 18:
				lcd_print(2,21,"视频",0);	
				break;
			case 19:
				lcd_print(2,21,"红外2",0);	
				break;
			case 20:
				lcd_print(2,21,"红外3",0);	
				break;
			case 21:
				lcd_print(2,21,"红外4",0);	
				break;
			case 22:
				lcd_print(2,21,"防雷1",0);	
				break;
			case 23:
				lcd_print(2,21,"防雷2",0);	
				break;
			case 255:
				lcd_print(2,21,"保留",0);	
				break;
 		}
	}
	else if(chrev==1)
	{
		switch(ditask)
	 	{
			case 0:
				lcd_print(2,21,"门禁",1);	 
				break;
			case 1:
				lcd_print(2,21,"水浸",1);	 
				break;
			case 2:
				lcd_print(2,21,"烟感",1);	 
				break;
			case 3:
				lcd_print(2,21,"窗禁",1);	 
				break;
			case 4:
				lcd_print(2,21,"红外",1);	 
				break;
			case 5:
				lcd_print(2,21,"玻璃破碎",1);	 
				break;
			case 6:
				lcd_print(2,21,"门禁2 ",1); 
				break;
			case 7:
				lcd_print(2,21,"门禁3",1);  
				break;
			case 8:
				lcd_print(2,21,"门禁4",1);  
				break;
			case 9:
				lcd_print(2,21,"玻璃破碎2",1);  
				break;
			case 10:
				lcd_print(2,21,"玻璃破碎3",1);  
				break;
			case 11:
				lcd_print(2,21,"玻璃破碎4",1);  
				break;
			case 12:
				lcd_print(2,21,"水浸2",1);  
				break;
			case 13:
				lcd_print(2,21,"水浸3",1);  
				break;
			case 14:
				lcd_print(2,21,"水浸4",1);  
				break;
			case 15:
				lcd_print(2,21,"烟感2",1);  
				break;
			case 16:
				lcd_print(2,21,"烟感3",1);  
				break;
			case 17:
				lcd_print(2,21,"烟感4",1);  
				break;
			case 18:
				lcd_print(2,21,"视频",1);  
				break;
			case 19:
				lcd_print(2,21,"红外2",1);  
				break;
			case 20:
				lcd_print(2,21,"红外3",1);  
				break;
			case 21:
				lcd_print(2,21,"红外4",1); 
				break;
			case 22:
				lcd_print(2,21,"防雷1",1); 
				break;
			case 23:
				lcd_print(2,21,"防雷2",1); 
				break;
			case 255:
				lcd_print(2,21,"保留",1);	 
				break;
	 	}
	}
}

void DOprint(unsigned char dotask,unsigned char chrev)
{
	if(chrev==0)
	{
		switch(dotask)
		{
			case 1:
				lcd_print(1,22,"灯1",0);	
				break;
			case 2:
				lcd_print(1,22,"灯2",0);	
				break;
			case 3:
				lcd_print(1,22,"灯3",0);	
				break;
			case 4:
				lcd_print(1,22,"蜂鸣器",0);	
				break;
			case 7:
				lcd_print(1,22,"视频",0);	
				break;
			case 255:
				lcd_print(1,22,"保留",0);	
				break;
		}
	}
	else if(chrev==1)
	{
		switch(dotask)
		{
			case 1:
				lcd_print(1,22,"灯1",1);	
				break;
			case 2:
				lcd_print(1,22,"灯2",1);	
				break;
			case 3:
				lcd_print(1,22,"灯3",1);	
				break;
			case 4:
				lcd_print(1,22,"蜂鸣器",1);	
				break;
			case 7:
				lcd_print(1,22,"视频",1);	
				break;
			case 255:
				lcd_print(1,22,"保留",1);	
				break;
		}
	}
}


void comprint(unsigned char addr,char *lcdcom)
{
	if(addr==255)
	{
		switch(lcdcom[0])
		{
			case 0:
				lcd_print(0,22," RS232",0);	
				break;														   
			case 1:
				lcd_print(0,22,"专线",0);	
				break;		
			case 2:
				lcd_print(0,22,"电源",0);	
				break;																		 
			case 3:
				lcd_print(0,22,"空调",0);	
				break;	
			case 4:
				lcd_print(0,22,"巡检仪",0);	
				break;	
			case 5:
				lcd_print(0,22,"I C 卡",0);	
				break;	
			case 6:
				lcd_print(0,22,"交流配电",0);	
				break;	
			case 7:
				lcd_print(0,22,"U P S",0);	
				break;	
			case 8:
				lcd_print(0,22,"智能门禁",0);	
				break;	
			case 9:
				lcd_print(0,22,"防雷",0);	
				break;	
			case 255:
				lcd_print(0,22,"保留",0);	
				break;							  
		}	
		switch(lcdcom[1])
		{
                          case 0:
		            lcd_print(1,9,"600",0);	
                          break;														   
                          case 1:
		            lcd_print(1,9,"1200",0);	
                          break;		
                          case 2:
		            lcd_print(1,9,"2400",0);	
                          break;																		 
                          case 3:
		            lcd_print(1,9,"4800",0);	
                          break;	
                          case 4:
		            lcd_print(1,9,"9600",0);	
                          break;	
                          case 5:
		            lcd_print(1,9,"19200",0);	
                          break;	
                          case 6:
		            lcd_print(1,9,"38400",0);	
                          break;	
                     	}
                     switch(lcdcom[2])
                     	{
                          case 0:
		            lcd_print(1,24,"7",0);	
                          break;														   
                          case 1:
		            lcd_print(1,24,"8",0);	
                          break;		
                          case 2:
		            lcd_print(1,24,"5",0);	
                          break;																		 
                     	}
                     switch(lcdcom[3])
                     	{
                          case 0:
		            lcd_print(2,9,"偶",0);	
                          break;														   
                          case 1:
		            lcd_print(2,9,"奇",0);	
                          break;		
                          case 2:
		            lcd_print(2,9,"无",0);	
                          break;																		 
                     	}
                     switch(lcdcom[4])
                     	{
                          case 0:
		            lcd_print(2,24,"1",0);	
                          break;														   
                          case 1:
                          break;		
                          case 2:
		            lcd_print(2,24,"2",0);	
                          break;																		 
                     	}
      }
  if(addr==0)
     {		            
                          switch(lcdcom[0])
                     	{
                          case 0:
		            lcd_print(0,22,"RS232",1);	
                          break;														   
                          case 1:
		            lcd_print(0,22,"专线",1);	
                          break;		
                          case 2:
		            lcd_print(0,22,"电源",1);	
                          break;																		 
                          case 3:
		            lcd_print(0,22,"空调",1);	
                          break;	
                          case 4:
		            lcd_print(0,22,"巡检仪",1);	
                          break;	
                          case 5:
		            lcd_print(0,22,"I C 卡",1);	
                          break;	
                          case 6:
		            lcd_print(0,22,"交流配电",1);	
                          break;	
                          case 7:
		            lcd_print(0,22,"U P S",1);	
                          break;	
                          case 8:
		            lcd_print(0,22,"智能门禁",1);	
                          break;	
				case 9:
				lcd_print(0,22,"防雷",1);	
				break;			  
                          case 255:
		            lcd_print(0,22,"保留",1);	
                          break;							  
                     	}	
                     switch(lcdcom[1])
                     	{
                          case 0:
		            lcd_print(1,9,"600",0);	
                          break;														   
                          case 1:
		            lcd_print(1,9,"1200",0);	
                          break;		
                          case 2:
		            lcd_print(1,9,"2400",0);	
                          break;																		 
                          case 3:
		            lcd_print(1,9,"4800",0);	
                          break;	
                          case 4:
		            lcd_print(1,9,"9600",0);	
                          break;	
                          case 5:
		            lcd_print(1,9,"19200",0);	
                          break;	
                          case 6:
		            lcd_print(1,9,"38400",0);	
                          break;	
                     	}
                     switch(lcdcom[2])
                     	{
                          case 0:
		            lcd_print(1,24,"7",0);	
                          break;														   
                          case 1:
		            lcd_print(1,24,"8",0);	
                          break;		
                          case 2:
		            lcd_print(1,24,"5",0);	
                          break;																		 
                     	}
                     switch(lcdcom[3])
                     	{
                          case 0:
		            lcd_print(2,9,"偶",0);	
                          break;														   
                          case 1:
		            lcd_print(2,9,"奇",0);	
                          break;		
                          case 2:
		            lcd_print(2,9,"无",0);	
                          break;																		 
                     	}
                     switch(lcdcom[4])
                     	{
                          case 0:
		            lcd_print(2,24,"1",0);	
                          break;														   
                          case 1:
                          break;		
                          case 2:
		            lcd_print(2,24,"2",0);	
                          break;																		 
                     	}
      }
  else  if(addr==1)
     {
                          switch(lcdcom[0])
                     	{
                          case 0:
		            lcd_print(0,22,"RS232",0);	
                          break;														   
                          case 1:
		            lcd_print(0,22,"专线",0);	
                          break;		
                          case 2:
		            lcd_print(0,22,"电源",0);	
                          break;																		 
                          case 3:
		            lcd_print(0,22,"空调",0);	
                          break;	
                          case 4:
		            lcd_print(0,22,"巡检仪",0);	
                          break;	
                          case 5:
		            lcd_print(0,22,"I C 卡",0);	
                          break;	
                          case 6:
		            lcd_print(0,22,"交流配电",0);	
                          break;	
                          case 7:
		            lcd_print(0,22,"U P S",0);	
                          break;	
                          case 8:
		            lcd_print(0,22,"智能门禁",0);	
                          break;
			  	case 9:
				lcd_print(0,22,"防雷",0);	
				break;	
                          case 255:
		            lcd_print(0,22,"保留",0);	
                          break;							  
                     	}	
                     switch(lcdcom[1])
                     	{
                          case 0:
		            lcd_print(1,9,"600",1);	
                          break;														   
                          case 1:
		            lcd_print(1,9,"1200",1);	
                          break;		
                          case 2:
		            lcd_print(1,9,"2400",1);	
                          break;																		 
                          case 3:
		            lcd_print(1,9,"4800",1);	
                          break;	
                          case 4:
		            lcd_print(1,9,"9600",1);	
                          break;	
                          case 5:
		            lcd_print(1,9,"19200",1);	
                          break;	
                          case 6:
		            lcd_print(1,9,"38400",1);	
                          break;	
                     	}
                     switch(lcdcom[2])
                     	{
                          case 0:
		            lcd_print(1,24,"7",0);	
                          break;														   
                          case 1:
		            lcd_print(1,24,"8",0);	
                          break;		
                          case 2:
		            lcd_print(1,24,"5",0);	
                          break;																		 
                     	}
                     switch(lcdcom[3])
                     	{
                          case 0:
		            lcd_print(2,9,"偶",0);	
                          break;														   
                          case 1:
		            lcd_print(2,9,"奇",0);	
                          break;		
                          case 2:
		            lcd_print(2,9,"无",0);	
                          break;																		 
                     	}
                     switch(lcdcom[4])
                     	{
                          case 0:
		            lcd_print(2,24,"1",0);	
                          break;														   
                          case 1:
                          break;		
                          case 2:
		            lcd_print(2,24,"2",0);	
                          break;																		 
                     	}
    }
  else  if(addr==2)
   {
                          switch(lcdcom[0])
                     	{
                          case 0:
		            lcd_print(0,22,"RS232",0);	
                          break;														   
                          case 1:
		            lcd_print(0,22,"专线",0);	
                          break;		
                          case 2:
		            lcd_print(0,22,"电源",0);	
                          break;																		 
                          case 3:
		            lcd_print(0,22,"空调",0);	
                          break;	
                          case 4:
		            lcd_print(0,22,"巡检仪",0);	
                          break;	
                          case 5:
		            lcd_print(0,22,"I C 卡",0);	
                          break;	
                          case 6:
		            lcd_print(0,22,"交流配电",0);	
                          break;	
                          case 7:
		            lcd_print(0,22,"U P S",0);	
                          break;	
                          case 8:
		            lcd_print(0,22,"智能门禁",0);	
                          break;
				case 9:
				lcd_print(0,22,"防雷",0);	
				break;	
                          case 255:
		            lcd_print(0,22,"保留",0);	
                          break;							  
                     	}	
                     switch(lcdcom[1])
                     	{
                          case 0:
		            lcd_print(1,9,"600",0);	
                          break;														   
                          case 1:
		            lcd_print(1,9,"1200",0);	
                          break;		
                          case 2:
		            lcd_print(1,9,"2400",0);	
                          break;																		 
                          case 3:
		            lcd_print(1,9,"4800",0);	
                          break;	
                          case 4:
		            lcd_print(1,9,"9600",0);	
                          break;	
                          case 5:
		            lcd_print(1,9,"19200",0);	
                          break;	
                          case 6:
		            lcd_print(1,9,"38400",0);	
                          break;	
                     	}
                     switch(lcdcom[2])
                     	{
                          case 0:
		            lcd_print(1,24,"7",1);	
                          break;														   
                          case 1:
		            lcd_print(1,24,"8",1);	
                          break;		
                          case 2:
		            lcd_print(1,24,"5",1);	
                          break;																		 
                     	}
                     switch(lcdcom[3])
                     	{
                          case 0:
		            lcd_print(2,9,"偶",0);	
                          break;														   
                          case 1:
		            lcd_print(2,9,"奇",0);	
                          break;		
                          case 2:
		            lcd_print(2,9,"无",0);	
                          break;																		 
                     	}
                     switch(lcdcom[4])
                     	{
                          case 0:
		            lcd_print(2,24,"1",0);	
                          break;														   
                          case 1:
                          break;		
                          case 2:
		            lcd_print(2,24,"2",0);	
                          break;																		 
                     	}
  }
  else  if(addr==3)
   {
                          switch(lcdcom[0])
                     	{
                          case 0:
		            lcd_print(0,22,"RS232",0);	
                          break;														   
                          case 1:
		            lcd_print(0,22,"专线",0);	
                          break;		
                          case 2:
		            lcd_print(0,22,"电源",0);	
                          break;																		 
                          case 3:
		            lcd_print(0,22,"空调",0);	
                          break;	
                          case 4:
		            lcd_print(0,22,"巡检仪",0);	
                          break;	
                          case 5:
		            lcd_print(0,22,"I C 卡",0);	
                          break;	
                          case 6:
		            lcd_print(0,22,"交流配电",0);	
                          break;	
                          case 7:
		            lcd_print(0,22,"U P S",0);	
                          break;	
                          case 8:
		            lcd_print(0,22,"智能门禁",0);	
                          break;
				case 9:
				lcd_print(0,22,"防雷",0);	
				break;	
                          case 255:
		            lcd_print(0,22,"保留",0);	
                          break;
                     	}	
                     switch(lcdcom[1])
                     	{
                          case 0:
		            lcd_print(1,9,"600",0);	
                          break;														   
                          case 1:
		            lcd_print(1,9,"1200",0);	
                          break;		
                          case 2:
		            lcd_print(1,9,"2400",0);	
                          break;																		 
                          case 3:
		            lcd_print(1,9,"4800",0);	
                          break;	
                          case 4:
		            lcd_print(1,9,"9600",0);	
                          break;	
                          case 5:
		            lcd_print(1,9,"19200",0);	
                          break;	
                          case 6:
		            lcd_print(1,9,"38400",0);	
                          break;	
                     	}
                     switch(lcdcom[2])
                     	{
                          case 0:
		            lcd_print(1,24,"7",0);	
                          break;														   
                          case 1:
		            lcd_print(1,24,"8",0);	
                          break;		
                          case 2:
		            lcd_print(1,24,"5",0);	
                          break;																		 
                     	}
                     switch(lcdcom[3])
                     	{
                          case 0:
		            lcd_print(2,9,"偶",1);	
                          break;														   
                          case 1:
		            lcd_print(2,9,"奇",1);	
                          break;		
                          case 2:
		            lcd_print(2,9,"无",1);	
                          break;																		 
                     	}
                     switch(lcdcom[4])
                     	{
                          case 0:
		            lcd_print(2,24,"1",0);	
                          break;														   
                          case 1:
                          break;		
                          case 2:
		            lcd_print(2,24,"2",0);	
                          break;																		 
                     	}
   }
  else  if(addr==4)
   {
                          switch(lcdcom[0])
                     	{
                          case 0:
		            lcd_print(0,22,"RS232",0);	
                          break;														   
                          case 1:
		            lcd_print(0,22,"专线",0);	
                          break;		
                          case 2:
		            lcd_print(0,22,"电源",0);	
                          break;																		 
                          case 3:
		            lcd_print(0,22,"空调",0);	
                          break;	
                          case 4:
		            lcd_print(0,22,"巡检仪",0);	
                          break;	
                          case 5:
		            lcd_print(0,22,"I C 卡",0);	
                          break;	
                          case 6:
		            lcd_print(0,22,"交流配电",0);	
                          break;	
                          case 7:
		            lcd_print(0,22,"U P S",0);	
                          break;	
                          case 8:
		            lcd_print(0,22,"智能门禁",0);	
                          break;
				case 9:
				lcd_print(0,22,"防雷",0);	
				break;	
                          case 255:
		            lcd_print(0,22,"保留",0);	
                          break;
                     	}	
                     switch(lcdcom[1])
                     	{
                          case 0:
		            lcd_print(1,9,"600",0);	
                          break;														   
                          case 1:
		            lcd_print(1,9,"1200",0);	
                          break;		
                          case 2:
		            lcd_print(1,9,"2400",0);	
                          break;																		 
                          case 3:
		            lcd_print(1,9,"4800",0);	
                          break;	
                          case 4:
		            lcd_print(1,9,"9600",0);	
                          break;	
                          case 5:
		            lcd_print(1,9,"19200",0);	
                          break;	
                          case 6:
		            lcd_print(1,9,"38400",0);	
                          break;	
                     	}
                     switch(lcdcom[2])
                     	{
                          case 0:
		            lcd_print(1,24,"7",0);	
                          break;														   
                          case 1:
		            lcd_print(1,24,"8",0);	
                          break;		
                          case 2:
		            lcd_print(1,24,"5",0);	
                          break;																		 
                     	}
                     switch(lcdcom[3])
                     	{
                          case 0:
		            lcd_print(2,9,"偶",0);	
                          break;														   
                          case 1:
		            lcd_print(2,9,"奇",0);	
                          break;		
                          case 2:
		            lcd_print(2,9,"无",0);	
                          break;																		 
                     	}
                     switch(lcdcom[4])
                     	{
                          case 0:
		            lcd_print(2,24,"1",1);	
                          break;														   
                          case 1:
                          break;		
                          case 2:
		            lcd_print(2,24,"2",1);	
                          break;																		 
                     	}
   }


}

int lcd(void)
{
unsigned short reset_flag;
FILE *in = NULL;
char *files ="/app/user.txt";
char *keys="RTUPW";
char *s="\nRTUPW=0000";
char password[4],pw[5];
struct setRTU
{
	unsigned char RTUaddr[3];
	unsigned char ip[12];
	unsigned char lcd[3];
	unsigned char mask[12];
	unsigned char gate[12];
}RTUset;
int Temp_RTUaddr,RTUaddr,Temp_RTUip[4],Temp_RTUmask[4],Temp_RTUgate[4],set_check,passwordint;
unsigned char buf,RTUip[4],RTUmask[4],RTUgate[4],SetRow,SetCol,RTUaddress[2];
int key_fd,setflag,setRTUflag,readstatflag,password_flag,check_flag,setpwflag, setRTUparaflag,setRTUCOMflag,comNUM,setRTUAIDIflag,AINUM,DINUM,setRTUDBflag;
int setRTUpage;//设置网络参数的页数
int setAIDIpage;//设置AIDI参数的页数
int readStatePage;//读取输入状态的页数
int DONUM,sum;
unsigned short feeddog;
//char buf[18];
char tempbuf[16];
char lcdbuf[100];
extern char DI_val[16];
signed short u,uu;
float v,vv;
//unsigned char  i,j;
int choose_print_flag=0;
unsigned char backlight;
unsigned char task[4]={0};
int i,ii;
gs_pwalarmMng.Getthre_val(RTU_backlight_NUM,&backlight);
unsigned char LCDCOM[7][7];
unsigned char AITASK[16],DITASK[16],DB[5],DOTASK[10];
gs_RTUcfgMng.Getcfg(RTU_COM1_NUM,&LCDCOM[0][0]);
gs_RTUcfgMng.Getcfg(RTU_COM2_NUM,&LCDCOM[1][0]);
gs_RTUcfgMng.Getcfg(RTU_COM3_NUM,&LCDCOM[2][0]);
gs_RTUcfgMng.Getcfg(RTU_COM4_NUM,&LCDCOM[3][0]);
gs_RTUcfgMng.Getcfg(RTU_COM5_NUM,&LCDCOM[4][0]);
gs_RTUcfgMng.Getcfg(RTU_COM6_NUM,&LCDCOM[5][0]);
gs_RTUcfgMng.Getcfg(RTU_COM7_NUM,&LCDCOM[6][0]);
gs_RTUcfgMng.Getcfg(RTU_AI_NUM,&AITASK[0]);
gs_RTUcfgMng.Getcfg(RTU_DI_NUM,&DITASK[0]);
gs_RTUcfgMng.Getcfg(RTU_DB_NUM,&DB[0]);
gs_RTUcfgMng.Getcfg(RTU_DO_NUM,&DOTASK[0]);
gs_RTUcfgMng.Getcfg(RTU_addr_NUM,&RTUaddress[0]);
gs_RTUcfgMng.Getcfg(RTU_IP_NUM,&RTUip[0]);
gs_RTUcfgMng.Getcfg(RTU_netmask_NUM,&RTUmask[0]);
gs_RTUcfgMng.Getcfg(RTU_gateway_NUM,&RTUgate[0]);
RTUaddr=RTUaddress[1];
RTUaddr=((RTUaddr<<8)|RTUaddress[0]);
if(RTUaddr>999)
	RTUaddr=0;
change(backlight,&RTUset.lcd[0]);                              
changeaddr(RTUaddr,&RTUset.RTUaddr[0]);
change(RTUip[0],&RTUset.ip[0]);
change(RTUip[1],&RTUset.ip[3]);
change(RTUip[2],&RTUset.ip[6]);
change(RTUip[3],&RTUset.ip[9]);
change(RTUmask[0],&RTUset.mask[0]);
change(RTUmask[1],&RTUset.mask[3]);
change(RTUmask[2],&RTUset.mask[6]);
change(RTUmask[3],&RTUset.mask[9]);
change(RTUgate[0],&RTUset.gate[0]);
change(RTUgate[1],&RTUset.gate[3]);
change(RTUgate[2],&RTUset.gate[6]);
change(RTUgate[3],&RTUset.gate[9]);

if(backlight<30)
{
	backlight=45;
	gs_pwalarmMng.Setthre_val(RTU_backlight_NUM,&backlight);
}
for(i=0;i<16;i++)
{
	if(DITASK[i]==0)
	{
		task[0]=1;
	}
	else if(DITASK[i]==1)
	{
		task[1]=1;
	}
	else if(DITASK[i]==2)
	{
		task[2]=1;
	}
	else if(DITASK[i]==5)
	{
		task[3]=1;
	}
}
key_fd=open("/dev/key", O_RDWR); 
printf("++++++++++++++++++++++%d",key_fd);
if((hd_lcd = open(LCD_NAME, O_RDWR))<0)
{
	printf("\n%d\n",hd_lcd);
	printf("\ncan not open %s",LCD_NAME);
	exit(0);
}
//pthread_exit("tasklcd");}
ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);//clear screen
//printf("\n---------------%d\n",hd_lcd);
ioctl(hd_lcd, IOC_SET_BL, (backlight&0xff));	
printf("\n&&&&&&&&&&&%d\n",backlight);	

///////////////////////开始主循环
/////////////buf:上8，下2，左16，右1，中4

while(1)
{
read(key_fd, &buf, 1);
if(buf==4)
{
	setflag=1;
	buf=0;
	goto set;
}
///////////////滚屏显示
lcd_print(0,2, " 通号通信信息集团有限公司",0);
lcd_print(1,9,"动环监控设备",0);

////////////温湿度
if(choose_print_flag==0)
{
	lcd_print(2,0," 								",0);
	gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,TEMPERATURE_1,DATA,&u);
	v=(float)u/10;
	gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,HUMIDITY_1,DATA,&uu);
	vv=(float)uu/10;
	sprintf(lcdbuf,"环境湿度%4.1f % 环境温度%4.1f C    ",vv,v);
	lcd_print(2,0,lcdbuf,0);
	choose_print_flag=1;
	SelfTest.fGetSelftest(8,&feeddog);
	feeddog++;
	if(feeddog>109)
	{
		feeddog=0;
	}
	SelfTest.fSetSelftest(8,&feeddog);
	sleep(1);
	read(key_fd, &buf, 1);
	if(buf==4)
	{
		setflag=1;
		buf=0;
		goto set;
	}
	sleep(1);
}

////////ACDC电压
else if(choose_print_flag==1)
{
	lcd_print(2,0," 								",0);
	gs_NewDataMng.fGetCData(POWER_DEVICE,POWER_A_VOLTAGE_1,DATA,&u);
	u=u/10;
	gs_NewDataMng.fGetCData(POWER_DEVICE,POWER_DC_VOLTAGE,DATA,&uu);
	uu=uu/10;
	sprintf(lcdbuf,"   AC 电压%d V   DC 电压 %d V   ",u,uu);
	lcd_print(2,0,lcdbuf,0);
	choose_print_flag=2;
	SelfTest.fGetSelftest(8,&feeddog);
	feeddog++;
	if(feeddog>109)
	{
		feeddog=0;
	}
	SelfTest.fSetSelftest(8,&feeddog);
	sleep(1);
	read(key_fd, &buf, 1);
	if(buf==4)
	{
		setflag=1;
		buf=0;
		goto set;
	}
	sleep(1);
}

/////////门禁窗禁
else if(choose_print_flag==2)
{
	lcd_print(2,0," 								",0);
	gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,ACCESS_1,DATA,&u);
	gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,GLASS_1,DATA,&uu);
	if((u!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_1].AlarmThresbhold)&& (uu!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][GLASS_1].AlarmThresbhold)&&(task[0]==1)&&(task[3]==1))
	{
		sprintf(lcdbuf,"   门禁:正 常     玻破:正 常     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u==gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_1].AlarmThresbhold)&& (uu!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][GLASS_1].AlarmThresbhold)&&(task[0]==1)&&(task[3]==1))
	{
		sprintf(lcdbuf,"   门禁:报 警     玻破:正 常     ");
		lcd_print(2,0,lcdbuf,0);
	}	
	else if((u!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_1].AlarmThresbhold)&& (uu==gs_ProMng.Pro[ENVIRONMENT_DEVICE][GLASS_1].AlarmThresbhold)&&(task[0]==1)&&(task[3]==1))
	{
		sprintf(lcdbuf,"   门禁:正 常     玻破:报 警     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u==gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_1].AlarmThresbhold)&& (uu==gs_ProMng.Pro[ENVIRONMENT_DEVICE][GLASS_1].AlarmThresbhold)&&(task[0]==1)&&(task[3]==1))
	{ 
		sprintf(lcdbuf,"   门禁:报 警     玻破:报 警     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((uu!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][GLASS_1].AlarmThresbhold)&&(task[0]==0)&&(task[3]==1))
	{
		sprintf(lcdbuf,"   门禁:未 安装   玻破:正 常     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((uu==gs_ProMng.Pro[ENVIRONMENT_DEVICE][GLASS_1].AlarmThresbhold)&&(task[0]==0)&&(task[3]==1))
	{
		sprintf(lcdbuf,"   门禁:未 安装	  玻破:报 警     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_1].AlarmThresbhold)&&(task[0]==1)&&(task[3]==0))
	{
		sprintf(lcdbuf,"   门禁:正 常     玻破:未 安装   ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u==gs_ProMng.Pro[ENVIRONMENT_DEVICE][ACCESS_1].AlarmThresbhold)&&(task[0]==1)&&(task[3]==0))
	{
		sprintf(lcdbuf,"   门禁:报 警     玻破:未 安装   ");
		lcd_print(2,0,lcdbuf,0);
	}
	else
	{
		sprintf(lcdbuf,"   门禁:未 安装   玻破:未 安装    ");
		lcd_print(2,0,lcdbuf,0);
	}
	
	SelfTest.fGetSelftest(8,&feeddog);
	feeddog++;
	if(feeddog>109)
	{
		feeddog=0;
	}
	SelfTest.fSetSelftest(8,&feeddog);
	sleep(1);
	read(key_fd, &buf, 1);
	if(buf==4)
	{
		setflag=1;
		buf=0;
		goto set;
	}
	sleep(1);
	choose_print_flag=3;
}

////////水浸烟感
else if(choose_print_flag==3)
{
	lcd_print(2,0," 								",0);
	gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,WATER_1,DATA,&u);
	gs_NewDataMng.fGetCData(ENVIRONMENT_DEVICE,SMOKE_1,DATA,&uu);
	if((u!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][WATER_1].AlarmThresbhold)&& (uu!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][SMOKE_1].AlarmThresbhold)&&(task[1]==1)&&(task[2]==1))
	{
		sprintf(lcdbuf,"   水浸:正 常     烟感:正 常     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u==gs_ProMng.Pro[ENVIRONMENT_DEVICE][WATER_1].AlarmThresbhold)&& (uu!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][SMOKE_1].AlarmThresbhold)&&((uu&0x01)==0x0)&&(task[1]==1)&&(task[2]==1))
	{
		sprintf(lcdbuf,"   水浸:报 警     烟感:正 常     ");
		lcd_print(2,0,lcdbuf,0);
	}	
	else if((u!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][WATER_1].AlarmThresbhold)&& (uu==gs_ProMng.Pro[ENVIRONMENT_DEVICE][SMOKE_1].AlarmThresbhold)&&(task[1]==1)&&(task[2]==1))
	{
		sprintf(lcdbuf,"   水浸:正 常     烟感:报 警     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u==gs_ProMng.Pro[ENVIRONMENT_DEVICE][WATER_1].AlarmThresbhold)&& (uu==gs_ProMng.Pro[ENVIRONMENT_DEVICE][SMOKE_1].AlarmThresbhold)&&(task[1]==1)&&(task[2]==1))
	{ 
		sprintf(lcdbuf,"   水浸:报 警     烟感:报 警     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((uu!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][SMOKE_1].AlarmThresbhold)&&(task[1]==0)&&(task[2]==1))
	{
		sprintf(lcdbuf,"   水浸:未 安装   烟感:正 常     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((uu==gs_ProMng.Pro[ENVIRONMENT_DEVICE][SMOKE_1].AlarmThresbhold)&&(task[1]==0)&&(task[2]==1))
	{
		sprintf(lcdbuf,"   水浸:未 安装	  烟感:报 警     ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u!=gs_ProMng.Pro[ENVIRONMENT_DEVICE][WATER_1].AlarmThresbhold)&&(task[1]==1)&&(task[2]==0))
	{
		sprintf(lcdbuf,"   水浸:正 常    烟感:未 安装    ");
		lcd_print(2,0,lcdbuf,0);
	}
	else if((u==gs_ProMng.Pro[ENVIRONMENT_DEVICE][WATER_1].AlarmThresbhold)&&(task[1]==1)&&(task[2]==0))
	{
		sprintf(lcdbuf,"   水浸:报 警    烟感:未 安装    ");
		lcd_print(2,0,lcdbuf,0);
	}
	else			   
	{
		sprintf(lcdbuf,"   水浸:未 安装   烟感:未 安装    ");
		lcd_print(2,0,lcdbuf,0);
	}
	SelfTest.fGetSelftest(8,&feeddog);
	feeddog++;
	if(feeddog>109)
	{
		feeddog=0;
	}
	SelfTest.fSetSelftest(8,&feeddog);
	sleep(1);
	read(key_fd, &buf, 1);
	if(buf==4)
	{
		setflag=1;
		buf=0;
		goto set;
	}
	sleep(1);
	choose_print_flag=4;
}

//////////电源通讯报警
else if(choose_print_flag==4)
{
	gs_NewDataMng.fGetCData(POWER_DEVICE,POWER_CONNECTION,DATA,&u);
	if(u==gs_ProMng.Pro[POWER_DEVICE][POWER_CONNECTION].AlarmThresbhold)
	{
		sprintf(lcdbuf,"       电源通讯状态报警         ");
		lcd_print(2,0,lcdbuf,0);
		SelfTest.fGetSelftest(8,&feeddog);
		feeddog++;
		if(feeddog>109)
		{
			feeddog=0;
		}
		SelfTest.fSetSelftest(8,&feeddog);
		sleep(1);
		read(key_fd, &buf, 1);
		if(buf==4)
		{
			setflag=1;
			buf=0;
			goto set;
		}
		sleep(1);
	}
	choose_print_flag=5;
}

//////////空调通讯报警
else if(choose_print_flag==5)
{
	gs_NewDataMng.fGetCData(AIRCONDITIONER_DEVICE,AIR_CONNECTION_1,DATA,&u);	
	if(u==gs_ProMng.Pro[AIRCONDITIONER_DEVICE][AIR_CONNECTION_1].AlarmThresbhold)
	{
		sprintf(lcdbuf,"       空调通讯状态报警        ");
		lcd_print(2,0,lcdbuf,0);
		SelfTest.fGetSelftest(8,&feeddog);
		feeddog++;
		if(feeddog>109)
		{
			feeddog=0;
		}
		SelfTest.fSetSelftest(8,&feeddog);
		sleep(1);
		read(key_fd, &buf, 1);
		if(buf==4)
		{
			setflag=1;
			buf=0;
			goto set;
		}
		sleep(1);
	}
choose_print_flag=0;
}
//memset(lcdbuf,0,100);
//char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
time_t timep;
struct tm *p;
time(&timep);
p=gmtime(&timep);
//printf("\n%s\n",lcdbuf);
/*stream = popen( "hwclock -r", "r" ); 
fread( buff, sizeof(char), sizeof(buff), stream); 
pclose(stream);
memcpy(&clockbuf[0],&buff[20],4);
//	printf("\n+++++++++++%s\n",clockbuf);
//	printf("\n+++++++++++%s\n",buff);*/
if((1900+p->tm_year)<2008)
{
	system("hwclock -s");
	time(&timep);
	p=gmtime(&timep);
}
sprintf(lcdbuf,"%d年%02d月%02d日 %02d时%02d分",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday, p->tm_hour, p->tm_min);//p->tm_sec);
lcd_print(3,4,lcdbuf,0);

set :if(setflag==1)
{
	while(setflag==1)
	{
		if(readfile( files, keys, pw)==0)
		{
			if((in = fopen(files,"a+"))==NULL)
			{
				return FALSE;
			}
			else printf("OpenPasswordfileOK\n");
			if(fwrite(s,strlen(s),1,in)==-1)
			{
				printf("WritePasswordfileFailure\n"); 
				fclose(in);
				return FALSE;
			}  
			printf("WritePasswordfileOK\n"); 
			fclose(in);
		}

		passwordint=atoi(pw);
		ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
		lcd_print(0,2, " 通号通信信息集团有限公司",0);
		lcd_print(1,9,"动环监控设备",0);
		lcd_print(2,2,"请输入密码",0); 
		lcd_print(3,7,"确认",0);     
		lcd_print(3,19,"返回",0);   
		SetCol=16;SetRow=2;	
		memset(password,0,4);
		memset(pw,0,5);
		password_flag=0;
		check_flag=0;
		while(password_flag==0)
		{
			read(key_fd, &buf, 1);               
			switch(SetRow)
			{
				case 2:
					switch(SetCol)
					{
						case 16:
							sprintf(tempbuf,"%d ",password[0]);	                                      
							lcd_print(2,16,tempbuf,1);                        
							lcd_print(2,18,"* * * ",0);
							lcd_print(3,7,"确认",0);      
							lcd_print(3,19,"返回",0); 
							if(buf==8)
							{
								if(password[0]==9)
								{
									password[0]=0;
								}
								else
									password[0]++;
							}   
							else if(buf==2)
							{
								if(password[0]==0)
								{
									password[0]=9;
								}
								else
									password[0]--;
							} 						  
							else if(buf==16)
							{
								SetCol=22;
							}   
							else if(buf==1)
							{
								SetCol=18;
							} 	
							break;

						case 18:
							lcd_print(2,16,"* ",0);
							sprintf(tempbuf,"%d ",password[1]);	                                      
							lcd_print(2,18,tempbuf,1);                        
							lcd_print(2,20,"* * ",0);                        
							lcd_print(3,7,"确认",0);      
							lcd_print(3,19,"返回",0); 
							if(buf==8)
							{
								if(password[1]==9)
								{
									password[1]=0;
								}
								else
									password[1]++;
							}   
							else if(buf==2)
							{
								if(password[1]==0)
								{
									password[1]=9;
								}
								else
									password[1]--;
							} 						  
							else if(buf==16)
							{
								SetCol=16;
							}   
							else if(buf==1)
							{
								SetCol=20;
							} 	
							break;
							
						case 20:
							lcd_print(2,16,"* * ",0);
							sprintf(tempbuf,"%d ",password[2]);	                                      
							lcd_print(2,20,tempbuf,1);                        
							lcd_print(2,22,"* ",0);                        
							lcd_print(3,7,"确认",0);      
							lcd_print(3,19,"返回",0); 
							if(buf==8)
							{
								if(password[2]==9)
								{
									password[2]=0;
								}
								else
									password[2]++;
							}   
							else if(buf==2)
							{
								if(password[2]==0)
								{
									password[2]=9;
								}
								else
									password[2]--;
							} 						  
							else if(buf==16)
							{
								SetCol=18;
							}   
							else if(buf==1)
							{
								SetCol=22;
							} 	
							break;
							
						case 22:
							lcd_print(2,16,"* * * ",0);
							sprintf(tempbuf,"%d ",password[3]);	                                      
							lcd_print(2,22,tempbuf,1);
							lcd_print(3,7,"确认",0);      
							lcd_print(3,19,"返回",0); 
							if(buf==8)
							{
								if(password[3]==9)
								{
									password[3]=0;
								}
								else
									password[3]++;
							}   
							else if(buf==2)
							{
								if(password[3]==0)
								{
									password[3]=9;
								}
								else
									password[3]--;
							} 						  
							else if(buf==16)
							{
								SetCol=20;
							}   
							else if(buf==1)
							{
								SetCol=7;
								SetRow=3;
							} 	
							break;
					}
					break;
					
				case 3:
					switch(SetCol)
					{
						case 7:	
							lcd_print(2,16,"* * * * ",0);
							lcd_print(3,7,"确认",1);      
							lcd_print(3,19,"返回",0);   										 
							if(buf==8)
							{
								SetCol=22;
								SetRow=2;
							}   
							else if(buf==2)
							{
								SetCol=22;
								SetRow=2;
							} 						  
							else if(buf==16)
							{
								SetCol=19;
								SetRow=3;
							}   
							else if(buf==1)
							{
								SetCol=19;
								SetRow=3;
							} 	
							else if(buf==4)
							{
								password_flag=1;
							}
							break;
							
						case 19:	
							lcd_print(2,16,"* * * * ",0);
							lcd_print(3,7,"确认",0);      
							lcd_print(3,19,"返回",1);   										 
							if(buf==8)
							{
								SetCol=22;
								SetRow=2;
							}   
							else if(buf==2)
							{
								SetCol=22;
								SetRow=2;
							} 						  
							else if(buf==16)
							{
								SetCol=7;
								SetRow=3;
							}   
							else if(buf==1)
							{
								SetCol=7;
								SetRow=3;
							} 	
							else if(buf==4)
							{
								password_flag=2;
								ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
								system("hwclock -r");
								system("hwclock -s");
								setflag=0;
							} 	
							break;
					}
					break;
			}
			SelfTest.fGetSelftest(8,&feeddog);
			feeddog++;
			if(feeddog>109)
			{
				feeddog=0;
			}
			SelfTest.fSetSelftest(8,&feeddog);
		}
		if(password_flag==1)
		{
			if((password[0]*1000+password[1]*100+password[2]*10+password[3])==passwordint)
			{
				ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
				lcd_print(0,2, " 通号通信信息集团有限公司",0);
				char pwmodel;   
				gs_RTUcfgMng.Getcfg(RTU_pwmodel_NUM,&pwmodel);
				sprintf(tempbuf,"电源类型    %02X ",pwmodel);	
				lcd_print(1,7,tempbuf,0);	
				check_flag=1;
				SetCol=2;
				SetRow=2;	
			}
			else 
			{
				ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
				lcd_print(0,2, " 通号通信信息集团有限公司",0);
                           lcd_print(1,9,"动环监控设备",0);
				lcd_print(2,7,"密  码  错  误",0); sleep(3);
				memset(password,0,4);
				memset(pw,0,4);
				SetCol=16;SetRow=2;	
				password_flag=0;
			}
		}
		while(setflag==1&&check_flag==1)
		{
			//关蜂鸣器
			sum=0;
			gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_1,DATA,&sum);
			gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_2,DATA,&sum);
			gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_3,DATA,&sum);
			gs_NewDataMng.fSetCData(ENVIRONMENT_DEVICE,BUZZER_4,DATA,&sum);
			
			read(key_fd, &buf, 1);
			switch(SetCol)	
			{
			case 2:
				lcd_print(0,9,"动环监控设备",0);
				lcd_print(1,2,LcdVersion,0);
				lcd_print(3,4,"设置密码",0);		
				lcd_print(3,21,"返回",0);		
				lcd_print(2,2,"设置RTU参数",1);
				lcd_print(2,17,"查看输入状态",0);	 
				if(buf==4)
				{
					ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
					setRTUparaflag=1;               
					SetRow=1;   
					SetCol=2;
					while(setRTUparaflag==1)
					{
						read(key_fd, &buf, 1);
						switch(SetRow)
						{
						case 1:
							switch(SetCol)	
							{
								case 2:
								lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",1);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0); 
								if(buf==4)
								{
									setRTUflag=1;//设置网络参数--标识
									setRTUpage=1;//设置网络参数第一页
									SetRow=0;
									SetCol=13;
									ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
									lcd_print(0,0," 对比度设置",0);
									lcd_print(1,0,"RTU地址设置",0);
									lcd_print(2,0,"I P地址设置",0);
									sprintf(tempbuf,"%d",RTUset.lcd[0]);
									lcd_print(0,15,tempbuf,0);
									sprintf(tempbuf,"%d",RTUset.lcd[1]);
									lcd_print(0,13,tempbuf,0);	
									sprintf(lcdbuf,"%d %d %d",RTUset.RTUaddr[2],RTUset.RTUaddr[1],RTUset.RTUaddr[0]);
									lcd_print(1,13,lcdbuf,0);
									sprintf(lcdbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
									lcd_print(2,13,lcdbuf,0);
									lcd_print(3,11,"下页",0);
									lcd_print(3,17,"确认",0);
									lcd_print(3,23,"放弃",0);
								  	while(setRTUflag==1) 
									{
										//////第一页设置
										if(setRTUpage==1)
										{

											read(key_fd, &buf, 1);
											switch(SetRow)
											{
											case 0:
												switch(SetCol)
												{
												case 13:
													sprintf(tempbuf,"%d",RTUset.lcd[0]);
													lcd_print(0,15,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.lcd[1]);
													lcd_print(0,13,tempbuf,1);										 
													if(buf==8)
													{
														if(RTUset.lcd[1]==5)
														{
															RTUset.lcd[1]=3;
														}
														else RTUset.lcd[1]++;
														backlight=RTUset.lcd[1]*10+RTUset.lcd[0];
														ioctl(hd_lcd, IOC_SET_BL, (backlight&0xff));
													}
													else if(buf==2)
													{
														if(RTUset.lcd[1]==3)
														{
															RTUset.lcd[1]=5;
														}
														else RTUset.lcd[1]--;
														backlight=RTUset.lcd[1]*10+RTUset.lcd[0];
														ioctl(hd_lcd, IOC_SET_BL, (backlight&0xff));
													}
													else if(buf==16)
													{
														SetRow=3;
														SetCol=23;
														sprintf(tempbuf,"%d %d",RTUset.lcd[1],RTUset.lcd[0]);
														lcd_print(0,13,tempbuf,0);
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
													
												case 15:
													sprintf(tempbuf,"%d",RTUset.lcd[1]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.lcd[0]);
													lcd_print(0,15,tempbuf,1);									 
													if(buf==8)
													{
														if(RTUset.lcd[0]==9)
														{
															RTUset.lcd[0]=0;
														}
														else RTUset.lcd[0]++;
														backlight=RTUset.lcd[1]*10+RTUset.lcd[0];
														ioctl(hd_lcd, IOC_SET_BL, (backlight&0xff));
													}
													else if(buf==2)
													{
														if(RTUset.lcd[0]==0)
														{
															RTUset.lcd[0]=9;
														}
														else RTUset.lcd[0]--;
														backlight=RTUset.lcd[1]*10+RTUset.lcd[0];
														ioctl(hd_lcd, IOC_SET_BL, (backlight&0xff));
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;						
													}
													else if(buf==1)
													{
														SetRow=1;
														SetCol=13;
														sprintf(tempbuf,"%d %d",RTUset.lcd[1],RTUset.lcd[0]);
														lcd_print(0,13,tempbuf,0);
													}
													break;
												}
												break;
												
											case 1:
												switch(SetCol)
												{
												case 13:
													sprintf(tempbuf,"%d %d",RTUset.RTUaddr[1],RTUset.RTUaddr[0]);
													lcd_print(1,15,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.RTUaddr[2]);
													lcd_print(1,13,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.RTUaddr[2]==9)
														{
															RTUset.RTUaddr[2]=0;
														}
														else RTUset.RTUaddr[2]++;
													}
													else if(buf==2)
													{
														if(RTUset.RTUaddr[2]==0)
														{
														   RTUset.RTUaddr[2]=9;
														}
														else RTUset.RTUaddr[2]--;
													}
													else if(buf==16)
													{
														SetRow=0;
														SetCol=15;
														sprintf(tempbuf,"%d %d %d",RTUset.RTUaddr[2],RTUset.RTUaddr[1],RTUset.RTUaddr[0]);
														lcd_print(1,13,tempbuf,0);
													}
	                                        		else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
												
												case 15:
													sprintf(tempbuf,"%d",RTUset.RTUaddr[2]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.RTUaddr[1]);
													lcd_print(1,15,tempbuf,1);
													sprintf(tempbuf,"%d",RTUset.RTUaddr[0]);
													lcd_print(1,17,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.RTUaddr[1]==9)
														{
															RTUset.RTUaddr[1]=0;
														}
														else RTUset.RTUaddr[1]++;
													}
													else if(buf==2)
													{
														if(RTUset.RTUaddr[1]==0)
														{
														   RTUset.RTUaddr[1]=9;
														}
														else RTUset.RTUaddr[1]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
													
												case 17:
													sprintf(tempbuf,"%d %d",RTUset.RTUaddr[2],RTUset.RTUaddr[1]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.RTUaddr[0]);
													lcd_print(1,17,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.RTUaddr[0]==9)
														{
															RTUset.RTUaddr[0]=0;
														}
														else RTUset.RTUaddr[0]++;
													}
													else if(buf==2)
													{
														if(RTUset.RTUaddr[0]==0)
														{
														   RTUset.RTUaddr[0]=9;
														}
														else RTUset.RTUaddr[0]--;
													}						
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetRow=2;
														SetCol=13;
														sprintf(tempbuf,"%d %d %d",RTUset.RTUaddr[2],RTUset.RTUaddr[1],RTUset.RTUaddr[0]);
														lcd_print(1,13,tempbuf,0);
													}
													break;
													
												}
												break;
											
											case 2:
												switch(SetCol)
												{
												case 13:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[7],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,14,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[2]);
													lcd_print(2,13,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.ip[2]==2)
														{
															RTUset.ip[2]=0;
														}
														else RTUset.ip[2]++;
													}
													else if(buf==2)
													{
														if(RTUset.ip[2]==0)
														{
															RTUset.ip[2]=2;
														}
														else RTUset.ip[2]--;
													}
													else if(buf==16)
													{
														SetCol=17;
														SetRow=1;
														sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
														lcd_print(2,13,tempbuf,0);
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
													
												case 14:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d",RTUset.ip[2]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[1]);
													lcd_print(2,14,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d.%d%d%d.%d%d%d",RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,15,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[2]==2)
														{
															if(RTUset.ip[1]>=5)
															{
																RTUset.ip[1]=0;
															}
															else RTUset.ip[1]++;
														}
														else 
														{
															if(RTUset.ip[1]==9)
															{
																RTUset.ip[1]=0;
															}
															else RTUset.ip[1]++;
														}

													}
													else if(buf==2)
													{
														if(RTUset.ip[2]==2)
														{
															if(RTUset.ip[1]>5||RTUset.ip[1]==0)
															{
																RTUset.ip[1]=5;
															}
															else RTUset.ip[1]--;
														}
														else
														{
															if(RTUset.ip[1]==0)
															{
																RTUset.ip[1]=9;
															}
															else RTUset.ip[1]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 15:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d",RTUset.ip[2],RTUset.ip[1]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[0]);
													lcd_print(2,15,tempbuf,1);
													sprintf(tempbuf,".%d%d%d.%d%d%d.%d%d%d",RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,16,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[2]==2&&RTUset.ip[1]>=5)
														{
															if(RTUset.ip[0]>=5)
															{
																RTUset.ip[0]=0;
															}
															else RTUset.ip[0]++;
														}
														else 
														{
															if(RTUset.ip[0]==9)
															{
																RTUset.ip[0]=0;
															}
															else RTUset.ip[0]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.ip[2]==2&&RTUset.ip[1]>=5)
														{
															if(RTUset.ip[0]>5||RTUset.ip[0]==0)
															{
																RTUset.ip[0]=5;
															}
															else RTUset.ip[0]--;
														}
														else
														{
															if(RTUset.ip[0]==0)
															{
																RTUset.ip[0]=9;
															}
															else RTUset.ip[0]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
												
												case 17:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[5]);
													lcd_print(2,17,tempbuf,1);
													sprintf(tempbuf,"%d%d.%d%d%d.%d%d%d",RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,18,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[5]==2)
														{
															RTUset.ip[5]=0;
														}
														else RTUset.ip[5]++;
													}
													else if(buf==2)
													{
														if(RTUset.ip[5]==0)
														{
															RTUset.ip[5]=2;
														}
														else RTUset.ip[5]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 18:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[4]);
													lcd_print(2,18,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d.%d%d%d",RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,19,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[5]==2)
														{
															if(RTUset.ip[4]>=5)
															{
																RTUset.ip[4]=0;
															}
															else RTUset.ip[4]++;
														}
														else 
														{
															if(RTUset.ip[4]==9)
															{
																RTUset.ip[4]=0;
															}
															else RTUset.ip[4]++;
														}

													}
													else if(buf==2)
													{
														if(RTUset.ip[5]==2)
														{
															if(RTUset.ip[4]>5||RTUset.ip[4]==0)
															{
																RTUset.ip[4]=5;
															}
															else RTUset.ip[4]--;
														}
														else
														{
															if(RTUset.ip[4]==0)
															{
																RTUset.ip[4]=9;
															}
															else RTUset.ip[4]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 19:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[3]);
													lcd_print(2,19,tempbuf,1);
													sprintf(tempbuf,".%d%d%d.%d%d%d",RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,20,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[5]==2&&RTUset.ip[4]>=5)
														{
															if(RTUset.ip[3]>=5)
															{
																RTUset.ip[3]=0;
															}
															else RTUset.ip[3]++;
														}
														else 
														{
															if(RTUset.ip[3]==9)
															{
																RTUset.ip[3]=0;
															}
															else RTUset.ip[3]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.ip[5]==2&&RTUset.ip[4]>=5)
														{
															if(RTUset.ip[3]>5||RTUset.ip[3]==0)
															{
																RTUset.ip[3]=5;
															}
															else RTUset.ip[3]--;
														}
														else
														{
															if(RTUset.ip[3]==0)
															{
																RTUset.ip[3]=9;
															}
															else RTUset.ip[3]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
												
												case 21:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[8]);
													lcd_print(2,21,tempbuf,1);
													sprintf(tempbuf,"%d%d.%d%d%d",RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,22,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[8]==2)
														{
															RTUset.ip[8]=0;
														}
														else RTUset.ip[8]++;
													}
													else if(buf==2)
													{
														if(RTUset.ip[8]==0)
														{
															RTUset.ip[8]=2;
														}
														else RTUset.ip[8]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												case 22:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[7]);
													lcd_print(2,22,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d",RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,23,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[8]==2)
														{
															if(RTUset.ip[7]>=5)
															{
																RTUset.ip[7]=0;
															}
															else RTUset.ip[7]++;
														}
														else 
														{
															if(RTUset.ip[7]==9)
															{
																RTUset.ip[7]=0;
															}
															else RTUset.ip[7]++;
														}

													}
													else if(buf==2)
													{
														if(RTUset.ip[8]==2)
														{
															if(RTUset.ip[7]>5||RTUset.ip[7]==0)
															{
																RTUset.ip[7]=5;
															}
															else RTUset.ip[7]--;
														}
														else
														{
															if(RTUset.ip[7]==0)
															{
																RTUset.ip[7]=9;
															}
															else RTUset.ip[7]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 23:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[6]);
													lcd_print(2,23,tempbuf,1);
													sprintf(tempbuf,".%d%d%d",RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,24,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[8]==2&&RTUset.ip[7]>=5)
														{
															if(RTUset.ip[6]>=5)
															{
																RTUset.ip[6]=0;
															}
															else RTUset.ip[6]++;
														}
														else 
														{
															if(RTUset.ip[6]==9)
															{
																RTUset.ip[6]=0;
															}
															else RTUset.ip[6]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.ip[8]==2&&RTUset.ip[7]>=5)
														{
															if(RTUset.ip[6]>5||RTUset.ip[6]==0)
															{
																RTUset.ip[6]=5;
															}
															else RTUset.ip[6]--;
														}
														else
														{
															if(RTUset.ip[6]==0)
															{
																RTUset.ip[6]=9;
															}
															else RTUset.ip[6]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
												
												case 25:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[11]);
													lcd_print(2,25,tempbuf,1);
													sprintf(tempbuf,"%d%d",RTUset.ip[10],RTUset.ip[9]);
													lcd_print(2,26,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[11]==2)
														{
															RTUset.ip[11]=0;
														}
														else RTUset.ip[11]++;
													}
													else if(buf==2)
													{
														if(RTUset.ip[11]==0)
														{
															RTUset.ip[11]=2;
														}
														else RTUset.ip[11]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 26:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[10]);
													lcd_print(2,26,tempbuf,1);
													sprintf(tempbuf,"%d",RTUset.ip[9]);
													lcd_print(2,27,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.ip[11]==2)
														{
															if(RTUset.ip[10]>=5)
															{
																RTUset.ip[10]=0;
															}
															else RTUset.ip[10]++;
														}
														else 
														{
															if(RTUset.ip[10]==9)
															{
																RTUset.ip[10]=0;
															}
															else RTUset.ip[10]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.ip[11]==2)
														{
															if(RTUset.ip[10]>5||RTUset.ip[10]==0)
															{
																RTUset.ip[10]=5;
															}
															else RTUset.ip[10]--;
														}
														else
														{
															if(RTUset.ip[10]==0)
															{
																RTUset.ip[10]=9;
															}
															else RTUset.ip[10]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 27:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10]);
													lcd_print(2,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.ip[9]);
													lcd_print(2,27,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.ip[11]==2&&RTUset.ip[10]>=5)
														{
															if(RTUset.ip[9]>=5)
															{
																RTUset.ip[9]=0;
															}
															else RTUset.ip[9]++;
														}
														else 
														{
															if(RTUset.ip[9]==9)
															{
																RTUset.ip[9]=0;
															}
															else RTUset.ip[9]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.ip[11]==2&&RTUset.ip[10]>=5)
														{
															if(RTUset.ip[9]>5)
															{
																RTUset.ip[9]=5;
															}
															else
															{
																if(RTUset.ip[9]==0)
																{
																	RTUset.ip[9]=9;
																}
																else RTUset.ip[9]--;
															}
														}
														else
														{
															if(RTUset.ip[9]==0)
															{
																RTUset.ip[9]=9;
															}
															else RTUset.ip[9]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetRow=3;
														SetCol=11;
														sprintf(lcdbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
														lcd_print(2,13,lcdbuf,0);
													}
													break;
													
												}
												break;
											
											case 3:
												switch(SetCol)
												{
												case 11:
													lcd_print(3,11,"下页",1);
													lcd_print(3,17,"确认",0);  
													lcd_print(3,23,"放弃",0);
												    if(buf==4)
													{
														ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
														lcd_print(0,0,"网关地址设置",0);
														lcd_print(1,0,"子网掩码设置",0);
														sprintf(lcdbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
														lcd_print(0,13,lcdbuf,0);
														sprintf(lcdbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
														lcd_print(1,13,lcdbuf,0);
														lcd_print(3,11,"上页",0);
														lcd_print(3,17,"确认",0);
														lcd_print(3,23,"放弃",0);
														setRTUpage=2;

													}
										   			if(buf==16)
										   			{
														SetCol=27;
														SetRow=2;
														sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10]);
														lcd_print(2,13,tempbuf,0);
														sprintf(tempbuf,"%d",RTUset.ip[9]);
														lcd_print(2,27,tempbuf,1);
														lcd_print(3,11,"下页",0);  
										   			}
										   			if(buf==1)
										   			{
														SetCol=17;
										   			}
										   			break;
													
												case 17:
													lcd_print(3,11,"下页",0);
													lcd_print(3,17,"确认",1);  
													lcd_print(3,23,"放弃",0);
													if(buf==4)
													{
														//RTU地址
													   	if((Temp_RTUaddr=RTUset.RTUaddr[2]*100+RTUset.RTUaddr[1]*10+RTUset.RTUaddr[0])>255)
													   		set_check=1;
														//IP地址
														if((Temp_RTUip[0]=RTUset.ip[2]*100+RTUset.ip[1]*10+RTUset.ip[0])>255)
															set_check=1;
														if((Temp_RTUip[1]=RTUset.ip[5]*100+RTUset.ip[4]*10+RTUset.ip[3])>255)
															set_check=1;
													    if((Temp_RTUip[2]=RTUset.ip[8]*100+RTUset.ip[7]*10+RTUset.ip[6])>255)
															set_check=1;
														if((Temp_RTUip[3]=RTUset.ip[11]*100+RTUset.ip[10]*10+RTUset.ip[9])>255)
															set_check=1;
														//子网掩码
														if((Temp_RTUmask[0]=RTUset.mask[2]*100+RTUset.mask[1]*10+RTUset.mask[0])>255)
															set_check=1;
														if((Temp_RTUmask[1]=RTUset.mask[5]*100+RTUset.mask[4]*10+RTUset.mask[3])>255)
															set_check=1;
													    if((Temp_RTUmask[2]=RTUset.mask[8]*100+RTUset.mask[7]*10+RTUset.mask[6])>255)
															set_check=1;
														if((Temp_RTUmask[3]=RTUset.mask[11]*100+RTUset.mask[10]*10+RTUset.mask[9])>255)
															set_check=1;
														//网关地址
														if((Temp_RTUgate[0]=RTUset.gate[2]*100+RTUset.gate[1]*10+RTUset.gate[0])>255)
															set_check=1;
														if((Temp_RTUgate[1]=RTUset.gate[5]*100+RTUset.gate[4]*10+RTUset.gate[3])>255)
															set_check=1;
													    if((Temp_RTUgate[2]=RTUset.gate[8]*100+RTUset.gate[7]*10+RTUset.gate[6])>255)
															set_check=1;
														if((Temp_RTUgate[3]=RTUset.gate[11]*100+RTUset.gate[10]*10+RTUset.gate[9])>255)
															set_check=1;
														//对比度
														backlight=RTUset.lcd[1]*10+RTUset.lcd[0];
														printf("\n************%d",set_check);
														printf("\n%d   %d.%d.%d.%d",Temp_RTUaddr,Temp_RTUip[0],Temp_RTUip[1],Temp_RTUip[2],Temp_RTUip[3]);
														if(set_check!=1) 
						                                {
						                                	RTUaddr=Temp_RTUaddr;
															RTUmask[0]=(unsigned char)Temp_RTUmask[0];
															RTUmask[1]=(unsigned char)Temp_RTUmask[1];
															RTUmask[2]=(unsigned char)Temp_RTUmask[2];
															RTUmask[3]=(unsigned char)Temp_RTUmask[3];
															RTUgate[0]=(unsigned char)Temp_RTUgate[0];
															RTUgate[1]=(unsigned char)Temp_RTUgate[1];
															RTUgate[2]=(unsigned char)Temp_RTUgate[2];
															RTUgate[3]=(unsigned char)Temp_RTUgate[3];
															RTUip[0]=(unsigned char)Temp_RTUip[0];
															RTUip[1]=(unsigned char)Temp_RTUip[1];
															RTUip[2]=(unsigned char)Temp_RTUip[2];
															RTUip[3]=(unsigned char)Temp_RTUip[3];
			  	                                            ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
											      			setRTUflag=0;
											   				SetCol=255;
		                                                    SetRow=3;
						                                }
				                             		}
										   			if(buf==16)
										   			{
														SetCol=11;
														SetRow=3;
														lcd_print(3,17,"确认",0);  
										   			}
													if(buf==1)
													{
														SetCol=23;
													}
													break;
												
												case 23:
                      	
													lcd_print(3,17,"确认",0);  
													lcd_print(3,23,"放弃",1);
									         		if(buf==4)
									         		{
														ioctl(hd_lcd, IOC_LCD_INIT, NULL);
														setRTUflag=0;
														SetCol=255;
	                                                    SetRow=3;
	                                                    gs_RTUcfgMng.Getcfg(RTU_IP_NUM,&RTUip[0]);
														gs_RTUcfgMng.Getcfg(RTU_gateway_NUM,&RTUgate[0]);
														gs_RTUcfgMng.Getcfg(RTU_netmask_NUM,&RTUmask[0]);
										       			gs_pwalarmMng.Setthre_val(RTU_backlight_NUM,&backlight);
	                                                    gs_RTUcfgMng.Getcfg(RTU_addr_NUM,&RTUaddress[0]);
														RTUaddr=RTUaddress[1];
														RTUaddr=((RTUaddr<<8)|RTUaddress[0]);
														if(RTUaddr>999)
															RTUaddr=0;
		                                                change(backlight,&RTUset.lcd[0]);                              
		                                                changeaddr(RTUaddr,&RTUset.RTUaddr[0]);
														change(RTUip[0],&RTUset.ip[0]);
		                                                change(RTUip[1],&RTUset.ip[3]);
		                                                change(RTUip[2],&RTUset.ip[6]);
		                                                change(RTUip[3],&RTUset.ip[9]);
		                                                change(RTUmask[0],&RTUset.mask[0]);
		                                                change(RTUmask[1],&RTUset.mask[3]);
		                                                change(RTUmask[2],&RTUset.mask[6]);
		                                                change(RTUmask[3],&RTUset.mask[9]);
														change(RTUgate[0],&RTUset.gate[0]);
		                                                change(RTUgate[1],&RTUset.gate[3]);
		                                                change(RTUgate[2],&RTUset.gate[6]);
		                                                change(RTUgate[3],&RTUset.gate[9]);
						                            }
										 			if(buf==16)
										   			{
										   				SetCol=17;
										   			}
										   			if(buf==1)
										   			{
										   				SetRow=0;
	                                                    SetCol=13;
														lcd_print(3,17,"确认",0);  
														lcd_print(3,23,"放弃",0);							  
										   			}
	                                                break;										
	                                        	}
												break;   	
											}	//end switch(setRow)
										}//end if(setRTUpage==1)
										
										////////第二页设置
										else if(setRTUpage==2)
										{

											read(key_fd, &buf, 1);
											switch(SetRow)
											{
											case 0:
												switch(SetCol)
												{
												case 13:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,14,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[2]);
													lcd_print(0,13,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.gate[2]==2)
														{
															RTUset.gate[2]=0;
														}
														else RTUset.gate[2]++;
													}
													else if(buf==2)
													{
														if(RTUset.gate[2]==0)
														{
															RTUset.gate[2]=2;
														}
														else RTUset.gate[2]--;
													}
													else if(buf==16)
													{
														SetCol=23;
														SetRow=3;
														sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
														lcd_print(0,13,tempbuf,0);
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
													
												case 14:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d",RTUset.gate[2]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[1]);
													lcd_print(0,14,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d.%d%d%d.%d%d%d",RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,15,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[2]==2)
														{
															if(RTUset.gate[1]>=5)
															{
																RTUset.gate[1]=0;
															}
															else RTUset.gate[1]++;
														}
														else 
														{
															if(RTUset.gate[1]==9)
															{
																RTUset.gate[1]=0;
															}
															else RTUset.gate[1]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[2]==2)
														{
															if(RTUset.gate[1]>5||RTUset.gate[1]==0)
															{
																RTUset.gate[1]=5;
															}
															else RTUset.gate[1]--;
														}
														else
														{
															if(RTUset.gate[1]==0)
															{
																RTUset.gate[1]=9;
															}
															else RTUset.gate[1]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 15:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d",RTUset.gate[2],RTUset.gate[1]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[0]);
													lcd_print(0,15,tempbuf,1);
													sprintf(tempbuf,".%d%d%d.%d%d%d.%d%d%d",RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,16,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[2]==2&&RTUset.gate[1]>=5)
														{
															if(RTUset.gate[0]>=5)
															{
																RTUset.gate[0]=0;
															}
															else RTUset.gate[0]++;
														}
														else 
														{
															if(RTUset.gate[0]==9)
															{
																RTUset.gate[0]=0;
															}
															else RTUset.gate[0]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[2]==2&&RTUset.gate[1]>=5)
														{
															if(RTUset.gate[0]>5||RTUset.gate[0]==0)
															{
																RTUset.gate[0]=5;
															}
															else RTUset.gate[0]--;
														}
														else
														{
															if(RTUset.gate[0]==0)
															{
																RTUset.gate[0]=9;
															}
															else RTUset.gate[0]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;

												case 17:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[5]);
													lcd_print(0,17,tempbuf,1);
													sprintf(tempbuf,"%d%d.%d%d%d.%d%d%d",RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,18,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[5]==2)
														{
															RTUset.gate[5]=0;
														}
														else RTUset.gate[5]++;
													}
													else if(buf==2)
													{
														if(RTUset.gate[5]==0)
														{
															RTUset.gate[5]=2;
														}
														else RTUset.gate[5]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 18:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[4]);
													lcd_print(0,18,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d.%d%d%d",RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,19,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[5]==2)
														{
															if(RTUset.gate[4]>=5)
															{
																RTUset.gate[4]=0;
															}
															else RTUset.gate[4]++;
														}
														else 
														{
															if(RTUset.gate[4]==9)
															{
																RTUset.gate[4]=0;
															}
															else RTUset.gate[4]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[5]==2)
														{
															if(RTUset.gate[4]>5||RTUset.gate[4]==0)
															{
																RTUset.gate[4]=5;
															}
															else RTUset.gate[4]--;
														}
														else
														{
															if(RTUset.gate[4]==0)
															{
																RTUset.gate[4]=9;
															}
															else RTUset.gate[4]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 19:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[3]);
													lcd_print(0,19,tempbuf,1);
													sprintf(tempbuf,".%d%d%d.%d%d%d",RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,20,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[5]==2&&RTUset.gate[4]>=5)
														{
															if(RTUset.gate[3]>=5)
															{
																RTUset.gate[3]=0;
															}
															else RTUset.gate[3]++;
														}
														else 
														{
															if(RTUset.gate[3]==9)
															{
																RTUset.gate[3]=0;
															}
															else RTUset.gate[3]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[5]==2&&RTUset.gate[4]>=5)
														{
															if(RTUset.gate[3]>5||RTUset.gate[3]==0)
															{
																RTUset.gate[3]=5;
															}
															else RTUset.gate[3]--;
														}
														else
														{
															if(RTUset.gate[3]==0)
															{
																RTUset.gate[3]=9;
															}
															else RTUset.gate[3]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
													
												case 21:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[8]);
													lcd_print(0,21,tempbuf,1);
													sprintf(tempbuf,"%d%d.%d%d%d",RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,22,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[8]==2)
														{
															RTUset.gate[8]=0;
														}
														else RTUset.gate[8]++;
													}
													else if(buf==2)
													{
														if(RTUset.gate[8]==0)
														{
															RTUset.gate[8]=2;
														}
														else RTUset.gate[8]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
													
												case 22:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[7]);
													lcd_print(0,22,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d",RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,23,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[8]==2)
														{
															if(RTUset.gate[7]>=5)
															{
																RTUset.gate[7]=0;
															}
															else RTUset.gate[7]++;
														}
														else 
														{
															if(RTUset.gate[7]==9)
															{
																RTUset.gate[7]=0;
															}
															else RTUset.gate[7]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[8]==2)
														{
															if(RTUset.gate[7]>5||RTUset.gate[7]==0)
															{
																RTUset.gate[7]=5;
															}
															else RTUset.gate[7]--;
														}
														else
														{
															if(RTUset.gate[7]==0)
															{
																RTUset.gate[7]=9;
															}
															else RTUset.gate[7]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 23:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[6]);
													lcd_print(0,23,tempbuf,1);
													sprintf(tempbuf,".%d%d%d",RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,24,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[8]==2&&RTUset.gate[7]>=5)
														{
															if(RTUset.gate[6]>=5)
															{
																RTUset.gate[6]=0;
															}
															else RTUset.gate[6]++;
														}
														else 
														{
															if(RTUset.gate[6]==9)
															{
																RTUset.gate[6]=0;
															}
															else RTUset.gate[6]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[8]==2&&RTUset.gate[7]>=5)
														{
															if(RTUset.gate[6]>5||RTUset.gate[6]==0)
															{
																RTUset.gate[6]=5;
															}
															else RTUset.gate[6]--;
														}
														else
														{
															if(RTUset.gate[6]==0)
															{
																RTUset.gate[6]=9;
															}
															else RTUset.gate[6]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;

												case 25:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[11]);
													lcd_print(0,25,tempbuf,1);
													sprintf(tempbuf,"%d%d",RTUset.gate[10],RTUset.gate[9]);
													lcd_print(0,26,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[11]==2)
														{
															RTUset.gate[11]=0;
														}
														else RTUset.gate[11]++;
													}
													else if(buf==2)
													{
														if(RTUset.gate[11]==0)
														{
															RTUset.gate[11]=2;
														}
														else RTUset.gate[11]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 26:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[10]);
													lcd_print(0,26,tempbuf,1);
													sprintf(tempbuf,"%d",RTUset.gate[9]);
													lcd_print(0,27,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.gate[11]==2)
														{
															if(RTUset.gate[10]>=5)
															{
																RTUset.gate[10]=0;
															}
															else RTUset.gate[10]++;
														}
														else 
														{
															if(RTUset.gate[10]==9)
															{
																RTUset.gate[10]=0;
															}
															else RTUset.gate[10]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[11]==2)
														{
															if(RTUset.gate[10]>5||RTUset.gate[10]==0)
															{
																RTUset.gate[10]=5;
															}
															else RTUset.gate[10]--;
														}
														else
														{
															if(RTUset.gate[10]==0)
															{
																RTUset.gate[10]=9;
															}
															else RTUset.gate[10]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 27:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10]);
													lcd_print(0,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.gate[9]);
													lcd_print(0,27,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.gate[11]==2&&RTUset.gate[10]>=5)
														{
															if(RTUset.gate[9]>=5)
															{
																RTUset.gate[9]=0;
															}
															else RTUset.gate[9]++;
														}
														else 
														{
															if(RTUset.gate[9]==9)
															{
																RTUset.gate[9]=0;
															}
															else RTUset.gate[9]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.gate[11]==2&&RTUset.gate[10]>=5)
														{
															if(RTUset.gate[9]>5)
															{
																RTUset.gate[9]=5;
															}
															else
															{
																if(RTUset.gate[9]==0)
																{
																	RTUset.gate[9]=9;
																}
																else RTUset.mask[9]--;
															}
														}
														else
														{
															if(RTUset.gate[9]==0)
															{
																RTUset.gate[9]=9;
															}
															else RTUset.gate[9]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetRow=1;
														SetCol=13;
														sprintf(lcdbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.gate[2],RTUset.gate[1],RTUset.gate[0],RTUset.gate[5],RTUset.gate[4],RTUset.gate[3],RTUset.gate[8],RTUset.gate[7],RTUset.gate[6],RTUset.gate[11],RTUset.gate[10],RTUset.gate[9]);
														lcd_print(0,13,lcdbuf,0);
													}
													break;
												}
												break;
											
											
											case 1:
												switch(SetCol)
												{
												case 13:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,14,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[2]);
													lcd_print(1,13,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.mask[2]==2)
														{
															RTUset.mask[2]=0;
														}
														else RTUset.mask[2]++;
													}
													else if(buf==2)
													{
														if(RTUset.mask[2]==0)
														{
															RTUset.mask[2]=2;
														}
														else RTUset.mask[2]--;
													}
													else if(buf==16)
													{
														SetCol=27;
														SetRow=0;
														sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
														lcd_print(1,13,tempbuf,0);
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
													
												case 14:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d",RTUset.mask[2]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[1]);
													lcd_print(1,14,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d.%d%d%d.%d%d%d",RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,15,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[2]==2)
														{
															if(RTUset.mask[1]>=5)
															{
																RTUset.mask[1]=0;
															}
															else RTUset.mask[1]++;
														}
														else 
														{
															if(RTUset.mask[1]==9)
															{
																RTUset.mask[1]=0;
															}
															else RTUset.mask[1]++;
														}

													}
													else if(buf==2)
													{
														if(RTUset.mask[2]==2)
														{
															if(RTUset.mask[1]>5||RTUset.mask[1]==0)
															{
																RTUset.mask[1]=5;
															}
															else RTUset.mask[1]--;
														}
														else
														{
															if(RTUset.mask[1]==0)
															{
																RTUset.mask[1]=9;
															}
															else RTUset.mask[1]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 15:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d",RTUset.mask[2],RTUset.mask[1]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[0]);
													lcd_print(1,15,tempbuf,1);
													sprintf(tempbuf,".%d%d%d.%d%d%d.%d%d%d",RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,16,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[2]==2&&RTUset.mask[1]>=5)
														{
															if(RTUset.mask[0]>=5)
															{
																RTUset.mask[0]=0;
															}
															else RTUset.mask[0]++;
														}
														else 
														{
															if(RTUset.mask[0]==9)
															{
																RTUset.mask[0]=0;
															}
															else RTUset.mask[0]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.mask[2]==2&&RTUset.mask[1]>=5)
														{
															if(RTUset.mask[0]>5||RTUset.mask[0]==0)
															{
																RTUset.mask[0]=5;
															}
															else RTUset.mask[0]--;
														}
														else
														{
															if(RTUset.mask[0]==0)
															{
																RTUset.mask[0]=9;
															}
															else RTUset.mask[0]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
												
												case 17:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[5]);
													lcd_print(1,17,tempbuf,1);
													sprintf(tempbuf,"%d%d.%d%d%d.%d%d%d",RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,18,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[5]==2)
														{
															RTUset.mask[5]=0;
														}
														else RTUset.mask[5]++;
													}
													else if(buf==2)
													{
														if(RTUset.mask[5]==0)
														{
															RTUset.mask[5]=2;
														}
														else RTUset.mask[5]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 18:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[4]);
													lcd_print(1,18,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d.%d%d%d",RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,19,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[5]==2)
														{
															if(RTUset.mask[4]>=5)
															{
																RTUset.mask[4]=0;
															}
															else RTUset.mask[4]++;
														}
														else 
														{
															if(RTUset.mask[4]==9)
															{
																RTUset.mask[4]=0;
															}
															else RTUset.mask[4]++;
														}

													}
													else if(buf==2)
													{
														if(RTUset.mask[5]==2)
														{
															if(RTUset.mask[4]>5||RTUset.mask[4]==0)
															{
																RTUset.mask[4]=5;
															}
															else RTUset.mask[4]--;
														}
														else
														{
															if(RTUset.mask[4]==0)
															{
																RTUset.mask[4]=9;
															}
															else RTUset.mask[4]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 19:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[3]);
													lcd_print(1,19,tempbuf,1);
													sprintf(tempbuf,".%d%d%d.%d%d%d",RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,20,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[5]==2&&RTUset.mask[4]>=5)
														{
															if(RTUset.mask[3]>=5)
															{
																RTUset.mask[3]=0;
															}
															else RTUset.mask[3]++;
														}
														else 
														{
															if(RTUset.mask[3]==9)
															{
																RTUset.mask[3]=0;
															}
															else RTUset.mask[3]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.mask[5]==2&&RTUset.mask[4]>=5)
														{
															if(RTUset.mask[3]>5||RTUset.mask[3]==0)
															{
																RTUset.mask[3]=5;
															}
															else RTUset.mask[3]--;
														}
														else
														{
															if(RTUset.mask[3]==0)
															{
																RTUset.mask[3]=9;
															}
															else RTUset.mask[3]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
													
												case 21:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[8]);
													lcd_print(1,21,tempbuf,1);
													sprintf(tempbuf,"%d%d.%d%d%d",RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,22,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[8]==2)
														{
															RTUset.mask[8]=0;
														}
														else RTUset.mask[8]++;
													}
													else if(buf==2)
													{
														if(RTUset.mask[8]==0)
														{
															RTUset.mask[8]=2;
														}
														else RTUset.mask[8]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												case 22:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[7]);
													lcd_print(1,22,tempbuf,1);
													sprintf(tempbuf,"%d.%d%d%d",RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,23,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[8]==2)
														{
															if(RTUset.mask[7]>=5)
															{
																RTUset.mask[7]=0;
															}
															else RTUset.mask[7]++;
														}
														else 
														{
															if(RTUset.mask[7]==9)
															{
																RTUset.mask[7]=0;
															}
															else RTUset.mask[7]++;
														}

													}
													else if(buf==2)
													{
														if(RTUset.mask[8]==2)
														{
															if(RTUset.mask[7]>5||RTUset.mask[7]==0)
															{
																RTUset.mask[7]=5;
															}
															else RTUset.mask[7]--;
														}
														else
														{
															if(RTUset.mask[7]==0)
															{
																RTUset.mask[7]=9;
															}
															else RTUset.mask[7]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 23:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[6]);
													lcd_print(1,23,tempbuf,1);
													sprintf(tempbuf,".%d%d%d",RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,24,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[8]==2&&RTUset.mask[7]>=5)
														{
															if(RTUset.mask[6]>=5)
															{
																RTUset.mask[6]=0;
															}
															else RTUset.mask[6]++;
														}
														else 
														{
															if(RTUset.mask[6]==9)
															{
																RTUset.mask[6]=0;
															}
															else RTUset.mask[6]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.mask[8]==2&&RTUset.mask[7]>=5)
														{
															if(RTUset.mask[6]>5||RTUset.mask[6]==0)
															{
																RTUset.mask[6]=5;
															}
															else RTUset.mask[6]--;
														}
														else
														{
															if(RTUset.mask[6]==0)
															{
																RTUset.mask[6]=9;
															}
															else RTUset.mask[6]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+2;
													}
													break;
												
												case 25:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[11]);
													lcd_print(1,25,tempbuf,1);
													sprintf(tempbuf,"%d%d",RTUset.mask[10],RTUset.mask[9]);
													lcd_print(1,26,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[11]==2)
														{
															RTUset.mask[11]=0;
														}
														else RTUset.mask[11]++;
													}
													else if(buf==2)
													{
														if(RTUset.mask[11]==0)
														{
															RTUset.mask[11]=2;
														}
														else RTUset.mask[11]--;
													}
													else if(buf==16)
													{
														SetCol=SetCol-2;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 26:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[10]);
													lcd_print(1,26,tempbuf,1);
													sprintf(tempbuf,"%d",RTUset.mask[9]);
													lcd_print(1,27,tempbuf,0);
													if(buf==8)
													{
														if(RTUset.mask[11]==2)
														{
															if(RTUset.mask[10]>=5)
															{
																RTUset.mask[10]=0;
															}
															else RTUset.mask[10]++;
														}
														else 
														{
															if(RTUset.mask[10]==9)
															{
																RTUset.mask[10]=0;
															}
															else RTUset.mask[10]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.mask[11]==2)
														{
															if(RTUset.mask[10]>5||RTUset.mask[10]==0)
															{
																RTUset.mask[10]=5;
															}
															else RTUset.mask[10]--;
														}
														else
														{
															if(RTUset.mask[10]==0)
															{
																RTUset.mask[10]=9;
															}
															else RTUset.mask[10]--;
														}
													}  
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetCol=SetCol+1;
													}
													break;
												
												case 27:
													memset(tempbuf,0,16);
													sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10]);
													lcd_print(1,13,tempbuf,0);
													sprintf(tempbuf,"%d",RTUset.mask[9]);
													lcd_print(1,27,tempbuf,1);
													if(buf==8)
													{
														if(RTUset.mask[11]==2&&RTUset.mask[10]>=5)
														{
															if(RTUset.mask[9]>=5)
															{
																RTUset.mask[9]=0;
															}
															else RTUset.mask[9]++;
														}
														else 
														{
															if(RTUset.mask[9]==9)
															{
																RTUset.mask[9]=0;
															}
															else RTUset.mask[9]++;
														}
													}
													else if(buf==2)
													{
														if(RTUset.mask[11]==2&&RTUset.mask[10]>=5)
														{
															if(RTUset.mask[9]>5)
															{
																RTUset.mask[9]=5;
															}
															else
															{
																if(RTUset.mask[9]==0)
																{
																	RTUset.mask[9]=9;
																}
																else RTUset.mask[9]--;
															}
														}
														else
														{
															if(RTUset.mask[9]==0)
															{
																RTUset.mask[9]=9;
															}
															else RTUset.mask[9]--;
														}
													}
													else if(buf==16)
													{
														SetCol=SetCol-1;
													}
													else if(buf==1)
													{
														SetRow=3;
														SetCol=11;
														sprintf(lcdbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10],RTUset.mask[9]);
														lcd_print(1,13,lcdbuf,0);
													}
													break;
													
												}
												break;
												
											case 3:
												switch(SetCol)
												{
													case 11:
														lcd_print(3,11,"上页",1);
														lcd_print(3,17,"确认",0);  
												    	lcd_print(3,23,"放弃",0);
												    	if(buf==4)
														{
													   		setRTUpage=1;
															ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);																					ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
															lcd_print(0,0," 对比度设置",0);
															lcd_print(1,0,"RTU地址设置",0);
															lcd_print(2,0,"I P地址设置",0);
															sprintf(tempbuf,"%d",RTUset.lcd[0]);
															lcd_print(0,15,tempbuf,0);
															sprintf(tempbuf,"%d",RTUset.lcd[1]);
															lcd_print(0,13,tempbuf,0);
															sprintf(lcdbuf,"%d %d %d",RTUset.RTUaddr[2],RTUset.RTUaddr[1],RTUset.RTUaddr[0]);
															lcd_print(1,13,lcdbuf,0);
															sprintf(lcdbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d%d",RTUset.ip[2],RTUset.ip[1],RTUset.ip[0],RTUset.ip[5],RTUset.ip[4],RTUset.ip[3],RTUset.ip[8],RTUset.ip[7],RTUset.ip[6],RTUset.ip[11],RTUset.ip[10],RTUset.ip[9]);
															lcd_print(2,13,lcdbuf,0);
															lcd_print(3,11,"下页",0);
															lcd_print(3,17,"确认",0);
															lcd_print(3,23,"放弃",0);
														}
											   			if(buf==16)
											   			{
															SetCol=27;
															SetRow=1;
															sprintf(tempbuf,"%d%d%d.%d%d%d.%d%d%d.%d%d",RTUset.mask[2],RTUset.mask[1],RTUset.mask[0],RTUset.mask[5],RTUset.mask[4],RTUset.mask[3],RTUset.mask[8],RTUset.mask[7],RTUset.mask[6],RTUset.mask[11],RTUset.mask[10]);
															lcd_print(1,13,tempbuf,0);
															sprintf(tempbuf,"%d",RTUset.mask[9]);
															lcd_print(1,27,tempbuf,1);
															lcd_print(3,11,"上页",0);  
														}
														if(buf==1)
														{
															SetCol=17;
															lcd_print(3,11,"上页",0);
														}
														break;
														
													case 17:
														lcd_print(3,17,"确认",1);  
														lcd_print(3,23,"放弃",0);
														if(buf==4)
														{
															//RTU地址
														   	if((Temp_RTUaddr=RTUset.RTUaddr[2]*100+RTUset.RTUaddr[1]*10+RTUset.RTUaddr[0])>255)
														   		set_check=1;
															//IP地址
															if((Temp_RTUip[0]=RTUset.ip[2]*100+RTUset.ip[1]*10+RTUset.ip[0])>255)
																set_check=1;
															if((Temp_RTUip[1]=RTUset.ip[5]*100+RTUset.ip[4]*10+RTUset.ip[3])>255)
																set_check=1;
														    if((Temp_RTUip[2]=RTUset.ip[8]*100+RTUset.ip[7]*10+RTUset.ip[6])>255)
																set_check=1;
															if((Temp_RTUip[3]=RTUset.ip[11]*100+RTUset.ip[10]*10+RTUset.ip[9])>255)
																set_check=1;
															//子网掩码
															if((Temp_RTUmask[0]=RTUset.mask[2]*100+RTUset.mask[1]*10+RTUset.mask[0])>255)
																set_check=1;
															if((Temp_RTUmask[1]=RTUset.mask[5]*100+RTUset.mask[4]*10+RTUset.mask[3])>255)
																set_check=1;
														    if((Temp_RTUmask[2]=RTUset.mask[8]*100+RTUset.mask[7]*10+RTUset.mask[6])>255)
																set_check=1;
															if((Temp_RTUmask[3]=RTUset.mask[11]*100+RTUset.mask[10]*10+RTUset.mask[9])>255)
																set_check=1;
															//网关地址
															if((Temp_RTUgate[0]=RTUset.gate[2]*100+RTUset.gate[1]*10+RTUset.gate[0])>255)
																set_check=1;
															if((Temp_RTUgate[1]=RTUset.gate[5]*100+RTUset.gate[4]*10+RTUset.gate[3])>255)
																set_check=1;
														    if((Temp_RTUgate[2]=RTUset.gate[8]*100+RTUset.gate[7]*10+RTUset.gate[6])>255)
																set_check=1;
															if((Temp_RTUgate[3]=RTUset.gate[11]*100+RTUset.gate[10]*10+RTUset.gate[9])>255)
																set_check=1;
															//对比度
															backlight=RTUset.lcd[1]*10+RTUset.lcd[0];
															printf("\n************%d",set_check);
															printf("\n%d   %d.%d.%d.%d",Temp_RTUaddr,Temp_RTUip[0],Temp_RTUmask[1],Temp_RTUmask[2],Temp_RTUmask[3]);
							                                if(set_check!=1) 
							                                {
							                                	RTUaddr=Temp_RTUaddr;
																RTUmask[0]=(unsigned char)Temp_RTUmask[0];
																RTUmask[1]=(unsigned char)Temp_RTUmask[1];
																RTUmask[2]=(unsigned char)Temp_RTUmask[2];
																RTUmask[3]=(unsigned char)Temp_RTUmask[3];
																RTUgate[0]=(unsigned char)Temp_RTUgate[0];
																RTUgate[1]=(unsigned char)Temp_RTUgate[1];
																RTUgate[2]=(unsigned char)Temp_RTUgate[2];
																RTUgate[3]=(unsigned char)Temp_RTUgate[3];
																RTUip[0]=(unsigned char)Temp_RTUip[0];
																RTUip[1]=(unsigned char)Temp_RTUip[1];
																RTUip[2]=(unsigned char)Temp_RTUip[2];
																RTUip[3]=(unsigned char)Temp_RTUip[3];
				  	                                            ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
												      			setRTUflag=0;
												   				SetCol=255;
			                                                    SetRow=3;
							                                }
				                             			}
											   			if(buf==16)
											   			{
											   				SetCol=11;
															SetRow=3;
															lcd_print(3,17,"确认",0);  
											   			}
											   			if(buf==1)
											   			{
		                                                	SetCol=23;
											   			}
														break;
												
													case 23:
														lcd_print(3,17,"确认",0);  
														lcd_print(3,23,"放弃",1);
										         		if(buf==4)
										         		{
										            		ioctl(hd_lcd, IOC_LCD_INIT, NULL);
															setRTUflag=0;
											   				SetCol=255;
		                                                    SetRow=3;
		                                                    gs_RTUcfgMng.Getcfg(RTU_IP_NUM,&RTUip[0]);
															gs_RTUcfgMng.Getcfg(RTU_gateway_NUM,&RTUgate[0]);
															gs_RTUcfgMng.Getcfg(RTU_netmask_NUM,&RTUmask[0]);
											       			gs_pwalarmMng.Setthre_val(RTU_backlight_NUM,&backlight);
															gs_RTUcfgMng.Getcfg(RTU_addr_NUM,&RTUaddress[0]);
															RTUaddr=RTUaddress[1];
															RTUaddr=((RTUaddr<<8)|RTUaddress[0]);
															if(RTUaddr>999)
																RTUaddr=0;
			                                                change(backlight,&RTUset.lcd[0]);                              
			                                                changeaddr(RTUaddr,&RTUset.RTUaddr[0]);
															change(RTUip[0],&RTUset.ip[0]);
			                                                change(RTUip[1],&RTUset.ip[3]);
			                                                change(RTUip[2],&RTUset.ip[6]);
			                                                change(RTUip[3],&RTUset.ip[9]);
			                                                change(RTUmask[0],&RTUset.mask[0]);
			                                                change(RTUmask[1],&RTUset.mask[3]);
			                                                change(RTUmask[2],&RTUset.mask[6]);
			                                                change(RTUmask[3],&RTUset.mask[9]);
															change(RTUgate[0],&RTUset.gate[0]);
			                                                change(RTUgate[1],&RTUset.gate[3]);
			                                                change(RTUgate[2],&RTUset.gate[6]);
			                                                change(RTUgate[3],&RTUset.gate[9]);
							                            }
											 			if(buf==16)
											   			{
											   				SetCol=17;
											   			}
											   			if(buf==1)
											   			{
											   				SetRow=0;
		                                                    SetCol=13;
															lcd_print(3,17,"确认",0);  
															lcd_print(3,23,"放弃",0);							  
											   			}
		                                                break;										
		                                        }
												break;   	
                  							}	
										}

										SelfTest.fGetSelftest(8,&feeddog);
										feeddog++;
										if(feeddog>109)
										{feeddog=0;}
										SelfTest.fSetSelftest(8,&feeddog);
										usleep(100000); 
							  		}//end while(setRTUflag==1)
	                           }//end if(buf==4)
	                           else if(buf==1)
	                           {
	                                lcd_print(0,9,"动环监控设备",0);
	                               lcd_print(1,2,"设置网络参数",0);		
	                               lcd_print(1,17,"设置串口参数",1);			  
	                               lcd_print(2,2,"设置AIDI参数",0);		
	                               lcd_print(2,17,"设置数据模块",0);
	                               lcd_print(3,6,"保存",0);		
	                               lcd_print(3,21,"放弃",0);
                                   SetRow=1;   
                                   SetCol=17;
                               }
                               else if(buf==16)
                               {
                                     lcd_print(0,9,"动环监控设备",0);
	                               lcd_print(1,2,"设置网络参数",0);		
	                               lcd_print(1,17,"设置串口参数",0);			  
	                               lcd_print(2,2,"设置AIDI参数",0);		
	                               lcd_print(2,17,"设置数据模块",0);
	                               lcd_print(3,6,"保存",0);		
	                               lcd_print(3,21,"放弃",1);
                                   SetRow=3;   
                                   SetCol=21;
                               }
                               else if(buf==8)
                               {
                                 lcd_print(0,9,"动环监控设备",0);
	                               lcd_print(1,2,"设置网络参数",0);		
	                               lcd_print(1,17,"设置串口参数",0);			  
	                               lcd_print(2,2,"设置AIDI参数",0);		
	                               lcd_print(2,17,"设置数据模块",0);
	                               lcd_print(3,6,"保存",1);		
	                               lcd_print(3,21,"放弃",0);
                                   SetRow=3;   
                                   SetCol=6;
                               }
                               else if(buf==2)
                               {
	                                 lcd_print(0,9,"动环监控设备",0);
		                               lcd_print(1,2,"设置网络参数",0);		
		                               lcd_print(1,17,"设置串口参数",0);			  
		                               lcd_print(2,2,"设置AIDI参数",1);		
		                               lcd_print(2,17,"设置数据模块",0);
		                               lcd_print(3,6,"保存",0);		
		                               lcd_print(3,21,"放弃",0);
									   SetRow=2;
                                       SetCol=2;                                         
                               }
							   break;
							   
					       case 17:
                                lcd_print(0,9,"动环监控设备",0);
                               lcd_print(1,2,"设置网络参数",0);		
                               lcd_print(1,17,"设置串口参数",1);			  
                               lcd_print(2,2,"设置AIDI参数",0);		
                               lcd_print(2,17,"设置数据模块",0);
                               lcd_print(3,6,"保存",0);		
                               lcd_print(3,21,"放弃",0);
							if(buf==4)
                            {
								ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
								setRTUCOMflag=1;               
								SetRow=0;   
								SetCol=7;
								comNUM=1;					   
								while(setRTUCOMflag==1)
								{
									read(key_fd, &buf, 1);
									switch(SetRow)
									{
										case 0:
									    switch(SetCol)
									    {
								   			case 7:
                                               	sprintf(tempbuf,"%d",comNUM);
                                               	lcd_print(0,7,tempbuf,1);		
                                               	lcd_print(0,2,"串口",0);		
                                               	lcd_print(0,17,"功能",0);			  
                                               	lcd_print(1,2,"波特率",0);		
                                               	lcd_print(1,17,"数据位",0);
                                               	lcd_print(2,2,"校验位",0);
                                               	lcd_print(2,17,"停止位",0);		
                                               	lcd_print(3,4,"确认",0); 
                                               	lcd_print(3,21,"放弃",0);  	
                                               	comprint(255,&LCDCOM[(comNUM-1)][0]);
												if(buf==8)
                                                {
	                                                lcd_print(0,22,"        ",0);
	                                                lcd_print(1,9,"     ",0);
	                                                lcd_print(1,24," ",0);
	                                                lcd_print(2,9,"  ",0);
	                                                lcd_print(2,24," ",0);
	  	                                            //ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
													comNUM++;      
													if(comNUM>7)
													{
														comNUM=1;
													}
												}
												else if(buf==2)
												{
													lcd_print(0,22,"        ",0);
													lcd_print(1,9,"     ",0);
													lcd_print(1,24," ",0);
													lcd_print(2,9,"  ",0);
													lcd_print(2,24," ",0);
													//ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
													comNUM--;      
													if(comNUM==0)
													{
														comNUM=7;
													}
												}
                                                else if(buf==1)
	                                    	    {                                                         	      
	                                                SetRow=0;
	                                                SetCol=22;
	                                    	    }
                                                else if(buf==16)
	                                    	    {                                                          	      
	                                                SetRow=3;
	                                                SetCol=21;
	                                    	    }
								    			break;	

								    		case 22:
												sprintf(tempbuf,"%d",comNUM);
												lcd_print(0,7,tempbuf,0);		
												lcd_print(0,2,"串口",0);		
												lcd_print(0,17,"功能",0);			  
												lcd_print(1,2,"波特率",0);		
												lcd_print(1,17,"数据位",0);
												lcd_print(2,2,"校验位",0);
												lcd_print(2,17,"停止位",0);		
												lcd_print(3,4,"确认",0); 
												lcd_print(3,21,"放弃",0);  	
												comprint(0,&LCDCOM[(comNUM-1)][0]);
												if(buf==8)
                                                {
													lcd_print(0,22,"        ",0);
													if(LCDCOM[(comNUM-1)][0]==255)
													LCDCOM[(comNUM-1)][0]=0;
													else
													{
														LCDCOM[(comNUM-1)][0]++;
														if(LCDCOM[(comNUM-1)][0]>9)
														LCDCOM[(comNUM-1)][0]=255;
													}
	  	                                            // ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
                                                }
								    			else if(buf==2)
												{
													lcd_print(0,22,"        ",0);
													if(LCDCOM[(comNUM-1)][0]==255)
													LCDCOM[(comNUM-1)][0]=9;
													else if(LCDCOM[(comNUM-1)][0]==0)
													{
														LCDCOM[(comNUM-1)][0]=255;
													}
													else
													{
														LCDCOM[(comNUM-1)][0]--;															 
													}
													//ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
												}
												else if(buf==1)
												{                                                        	      
													SetRow=1;
													SetCol=9;
												}
												else if(buf==16)
												{                                                         	      
													SetRow=0;
													SetCol=7;
												}
												break;	
										}						
										break;

										case 1:
											switch(SetCol)	
											{
												case 9:
													sprintf(tempbuf,"%d",comNUM);
													lcd_print(0,7,tempbuf,0);		
													lcd_print(0,2,"串口",0);		
													lcd_print(0,17,"功能",0);			  
													lcd_print(1,2,"波特率",0);		
													lcd_print(1,17,"数据位",0);
													lcd_print(2,2,"校验位",0);
													lcd_print(2,17,"停止位",0);		
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0); 
													comprint(1,&LCDCOM[(comNUM-1)][0]);
													if(buf==8)
													{
														lcd_print(1,9,"     ",0);
														LCDCOM[(comNUM-1)][1]++;
														if(LCDCOM[(comNUM-1)][1]>6)
														LCDCOM[(comNUM-1)][1]=0;
													}
													else if(buf==2)
													{
														lcd_print(1,9,"     ",0);
														if(LCDCOM[(comNUM-1)][1]==0)
														LCDCOM[(comNUM-1)][1]=6;
														else LCDCOM[(comNUM-1)][1]--;
													}
													else if(buf==1)
													{                                                          	      
														SetRow=1;
														SetCol=24;
													}
													else if(buf==16)
													{                                                         	      
														SetRow=0;
														SetCol=22;
													}
													break;	

												case 24:
													sprintf(tempbuf,"%d",comNUM);
													lcd_print(0,7,tempbuf,0);		
													lcd_print(0,2,"串口",0);		
													lcd_print(0,17,"功能",0);			  
													lcd_print(1,2,"波特率",0);		
													lcd_print(1,17,"数据位",0);
													lcd_print(2,2,"校验位",0);
													lcd_print(2,17,"停止位",0);		
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0); 
													comprint(2,&LCDCOM[(comNUM-1)][0]);
													if(buf==8)
													{
														lcd_print(1,24," ",0);
														LCDCOM[(comNUM-1)][2]++;
														if(LCDCOM[(comNUM-1)][2]>2)
														LCDCOM[(comNUM-1)][2]=0;
													}
													else if(buf==2)
													{
														lcd_print(1,24," ",0);
														if(LCDCOM[(comNUM-1)][2]==0)
														LCDCOM[(comNUM-1)][2]=2;
														else LCDCOM[(comNUM-1)][2]--;																 
													}
													else if(buf==1)
													{                                                      	      
														SetRow=2;
														SetCol=9;
													}
													else if(buf==16)
													{                                                        	      
														SetRow=1;
														SetCol=9;
													}
													break;	
												}						
												break;														   

										case 2:
											switch(SetCol)	
											{
												case 9:
													sprintf(tempbuf,"%d",comNUM);
													lcd_print(0,7,tempbuf,0);		
													lcd_print(0,2,"串口",0);		
													lcd_print(0,17,"功能",0);			  
													lcd_print(1,2,"波特率",0);		
													lcd_print(1,17,"数据位",0);
													lcd_print(2,2,"校验位",0);
													lcd_print(2,17,"停止位",0);		
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0); 
													comprint(3,&LCDCOM[(comNUM-1)][0]);
													if(buf==8)
													{
														lcd_print(2,9,"  ",0);
														LCDCOM[(comNUM-1)][3]++;
														if(LCDCOM[(comNUM-1)][3]>2)
														LCDCOM[(comNUM-1)][3]=0;
													}
													else if(buf==2)
													{
														lcd_print(2,9,"  ",0);
														if(LCDCOM[(comNUM-1)][3]==0)
														LCDCOM[(comNUM-1)][3]=2;
														else LCDCOM[(comNUM-1)][3]--;
													}
													else if(buf==1)
													{                                                        	      
														SetRow=2;
														SetCol=24;
													}
													else if(buf==16)
													{                                                        	      
														SetRow=1;
														SetCol=24;
													}
													break;	

												case 24:
													sprintf(tempbuf,"%d",comNUM);
													lcd_print(0,7,tempbuf,0);		
													lcd_print(0,2,"串口",0);		
													lcd_print(0,17,"功能",0);			  
													lcd_print(1,2,"波特率",0);		
													lcd_print(1,17,"数据位",0);
													lcd_print(2,2,"校验位",0);
													lcd_print(2,17,"停止位",0);		
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0); 
													comprint(4,&LCDCOM[(comNUM-1)][0]);
													if(buf==8)
													{
														lcd_print(2,24," ",0);
														LCDCOM[(comNUM-1)][4]++;
														if(LCDCOM[(comNUM-1)][4]>2)
														LCDCOM[(comNUM-1)][4]=0;
													}
													else if(buf==2)
													{
														lcd_print(2,24," ",0);
														if(LCDCOM[(comNUM-1)][4]==0)
														LCDCOM[(comNUM-1)][4]=2;	
														else LCDCOM[(comNUM-1)][4]--;															 
													}
													else if(buf==1)
													{                                                         	      
														SetRow=3;
														SetCol=4;
													}
													else if(buf==16)
													{                                                         	      
														SetRow=2;
														SetCol=9;
													}
													break;	
												}						
												break;	
                                                           
										case 3:
											switch(SetCol)
											{
												case 4:       
													sprintf(tempbuf,"%d",comNUM);
													lcd_print(0,7,tempbuf,0);		
													comprint(255,&LCDCOM[(comNUM-1)][0]);										 	
													lcd_print(3,4,"确认",1); 
													lcd_print(3,21,"放弃",0); 
													if(buf==4)
													{
														/*  gs_RTUcfgMng.Setcfg(RTU_COM1_NUM,&LCDCOM[0][0]);
														gs_RTUcfgMng.Setcfg(RTU_COM2_NUM,&LCDCOM[1][0]);
														gs_RTUcfgMng.Setcfg(RTU_COM3_NUM,&LCDCOM[2][0]);
														gs_RTUcfgMng.Setcfg(RTU_COM4_NUM,&LCDCOM[3][0]);
														gs_RTUcfgMng.Setcfg(RTU_COM5_NUM,&LCDCOM[4][0]);*/
														setRTUCOMflag=0;
														SetRow=3;
														SetCol=255;
														ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
													}
													else if(buf==1)
													{                                                         	      
														SetRow=3;
														SetCol=21; 
													}
													else if(buf==16)
													{                                                         	      
														SetRow=2;
														SetCol=24;
														lcd_print(3,4,"确认",0); 
														lcd_print(3,21,"放弃",0); 
													}
													else if(buf==8)
													{                                                         	      
														SetRow=2;
														SetCol=24; 
														lcd_print(3,4,"确认",0); 
														lcd_print(3,21,"放弃",0); 
													}
													break;
													
												case 21:                                                               
													sprintf(tempbuf,"%d",comNUM);
													lcd_print(0,7,tempbuf,0);		
													comprint(255,&LCDCOM[(comNUM-1)][0]);
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",1); 
													if(buf==4)
													{
														gs_RTUcfgMng.Getcfg(RTU_COM1_NUM,&LCDCOM[0][0]);
														gs_RTUcfgMng.Getcfg(RTU_COM2_NUM,&LCDCOM[1][0]);
														gs_RTUcfgMng.Getcfg(RTU_COM3_NUM,&LCDCOM[2][0]);
														gs_RTUcfgMng.Getcfg(RTU_COM4_NUM,&LCDCOM[3][0]);
														gs_RTUcfgMng.Getcfg(RTU_COM5_NUM,&LCDCOM[4][0]);
														gs_RTUcfgMng.Getcfg(RTU_COM6_NUM,&LCDCOM[5][0]);
														gs_RTUcfgMng.Getcfg(RTU_COM7_NUM,&LCDCOM[6][0]);
														setRTUCOMflag=0;
														SetRow=3;
														SetCol=255;
														ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
													}
													else if(buf==1)
													{                                                         	      
														SetRow=0;
														SetCol=7; 
														lcd_print(3,4,"确认",0); 
														lcd_print(3,21,"放弃",0); 
													}
													else if(buf==16)
													{                                                         	      
														SetRow=3;
														SetCol=4;
													}
													else if(buf==8)
													{                                                         	      
														SetRow=2;
														SetCol=24; 
														lcd_print(3,4,"确认",0); 
														lcd_print(3,21,"放弃",0); 
													}
													break;
												}
												break;
                        			}	
									SelfTest.fGetSelftest(8,&feeddog);
									feeddog++;
									if(feeddog>109)
									{
										feeddog=0;
									}
									SelfTest.fSetSelftest(8,&feeddog);
									usleep(100000);
								}											
							}
							else if(buf==1)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",1);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=2;   
								SetCol=2;
							}
							else if(buf==16)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",1);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=1;   
								SetCol=2;
							}
							else if(buf==8)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",1);
								SetRow=3;   
								SetCol=21;
							}
							else if(buf==2)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",1);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=2;   
								SetCol=17;
							}
							break;				
						}		
						break;
		                                  
					case 2:
						switch(SetCol)
						{
							case 2:
							  lcd_print(0,9,"动环监控设备",0);
							lcd_print(1,2,"设置网络参数",0);		
							lcd_print(1,17,"设置串口参数",0);			  
							lcd_print(2,2,"设置AIDI参数",1);		
							lcd_print(2,17,"设置数据模块",0);
							lcd_print(3,6,"保存",0);		
							lcd_print(3,21,"放弃",0);
							if(buf==4)
							{
								AINUM=1;
								DINUM=1;
								DONUM=1;
								setAIDIpage=1;
								setRTUAIDIflag=1;   
								SetRow=1;
								SetCol=5;
								ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
								while(setRTUAIDIflag==1)
								{
									if(setAIDIpage==1)
									{
										  lcd_print(0,9,"动环监控设备",0);
										read(key_fd, &buf, 1);
										switch(SetRow)
										{
											case 1:
												switch(SetCol)	
												{
													case 5:
														lcd_print(1,2,"模拟量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",AINUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,1);											 
														lcd_print(1,16,"功能",0);		
														AIprint(AITASK[AINUM-1],0);													   
														lcd_print(2,2,"开关量",0);
														lcd_print(2,9,"第",0);		
														sprintf(tempbuf, "%02d",DINUM);										 
														lcd_print(2,13,"路",0);								 
														lcd_print(2,11,tempbuf,0);											 
														lcd_print(2,16,"功能",0);	
														DIprint(DITASK[DINUM-1],0);	
														lcd_print(3,4,"下页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0); 
														if(buf==8)
														{
															AINUM++;
															if(AINUM>16)
															AINUM=1;
															lcd_print(1,21,"           ",0);                                                                            
														}
														else if(buf==2)
														{
															AINUM--;
															if(AINUM<1)
															AINUM=16;
															lcd_print(1,21,"           ",0);   
														}
														else if(buf==1)
														{
															SetRow=1;
															SetCol=21;
															//lcd_print(1,21,"           ",0);   
														}
														else if(buf==16)
														{
															SetRow=3;
															SetCol=20;
															//lcd_print(1,21,"           ",0);  
														}
														break;

													case 21:
														lcd_print(1,2,"模拟量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",AINUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16,"功能",0);		
														AIprint(AITASK[AINUM-1],1);													   
														lcd_print(2,2,"开关量",0);
														lcd_print(2,9,"第",0);		
														sprintf(tempbuf, "%02d",DINUM);										 
														lcd_print(2,13,"路",0);								 
														lcd_print(2,11,tempbuf,0);											 
														lcd_print(2,16,"功能",0);	
														DIprint(DITASK[DINUM-1],0);	
														lcd_print(3,4,"下页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0);
														if(buf==8)
														{
															if(AITASK[AINUM-1]>=3&&AITASK[AINUM-1]<14)
															AITASK[AINUM-1]=14;
															else if(AITASK[AINUM-1]==15)
															AITASK[AINUM-1]=255;
															else if(AITASK[AINUM-1]==255)
															AITASK[AINUM-1]=0;
															else 
															AITASK[AINUM-1]++;
															lcd_print(1,21,"           ",0);                                                                            
														}
														else if(buf==2)
														{
															if(AITASK[AINUM-1]==255)
															AITASK[AINUM-1]=15;
															else if(AITASK[AINUM-1]<=14&&AITASK[AINUM-1]>3)
															AITASK[AINUM-1]=3;
															else if(AITASK[AINUM-1]==0)
															AITASK[AINUM-1]=255;
															else 
															AITASK[AINUM-1]--;
															lcd_print(1,21,"           ",0);   
														}
														else if(buf==1)
														{
															SetRow=2;
															SetCol=5;
															lcd_print(1,21,"           ",0);   
														}
														else if(buf==16)
														{
															SetRow=1;
															SetCol=5;
															lcd_print(1,21,"           ",0);  
														}
														break;
												}
												break;
												
											case 2:
												switch(SetCol)
												{
													case 5:
														lcd_print(1,2,"模拟量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",AINUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16,"功能",0);		
														AIprint(AITASK[AINUM-1],0);													   
														lcd_print(2,2,"开关量",0);
														lcd_print(2,9,"第",0);		
														sprintf(tempbuf, "%02d",DINUM);										 
														lcd_print(2,13,"路",0);									 
														lcd_print(2,11,tempbuf,1);											 
														lcd_print(2,16,"功能",0);	
														DIprint(DITASK[DINUM-1],0);	
														lcd_print(3,4,"下页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0);
														if(buf==8)
														{
															DINUM++;
															if(DINUM>16)
															DINUM=1;
															lcd_print(2,21,"           ",0);                                                                            
														}
														else if(buf==2)
														{
															DINUM--;
															if(DINUM<1)
															DINUM=16;
															lcd_print(2,21,"           ",0);   
														}
														else if(buf==1)
														{
															SetRow=2;
															SetCol=21;
															lcd_print(2,21,"           ",0);   
														}
														else if(buf==16)
														{
															SetRow=1;
															SetCol=21;
															//lcd_print(1,21,"           ",0);  
														}
														break;                                                             

													case 21:
														lcd_print(1,2,"模拟量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",AINUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16,"功能",0);		
														AIprint(AITASK[AINUM-1],0);													   
														lcd_print(2,2,"开关量",0);
														lcd_print(2,9,"第",0);		
														sprintf(tempbuf, "%02d",DINUM);										 
														lcd_print(2,13,"路",0);									 
														lcd_print(2,11,tempbuf,0);											 
														lcd_print(2,16,"功能",0);	
														DIprint(DITASK[DINUM-1],1);
														lcd_print(3,4,"下页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0);
														if(buf==8)
														{
															if(DITASK[DINUM-1]==23)
															DITASK[DINUM-1]=255;
															else if(DITASK[DINUM-1]==255)
															DITASK[DINUM-1]=0;
															else 
															DITASK[DINUM-1]++;
															lcd_print(2,21,"           ",0);                                                                            
														}
														else if(buf==2)
														{
															if(DITASK[DINUM-1]==255)
															DITASK[DINUM-1]=23;
															else if(DITASK[DINUM-1]==0)
															DITASK[DINUM-1]=255;
															else 
															DITASK[DINUM-1]--;
															lcd_print(2,21,"           ",0);   
														}
														else if(buf==1)
														{
															SetRow=3;
															SetCol=4;
															lcd_print(2,21,"           ",0);   
														}
														else if(buf==16)
														{
															SetRow=2;
															SetCol=5;
															lcd_print(2,21,"           ",0);  
														}
														break;
												}
	                                            break;	
												
											case 3:
												switch(SetCol)
												{
													case 4:
														lcd_print(1,2,"模拟量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",AINUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16,"功能",0);		
														AIprint(AITASK[AINUM-1],0);													   
														lcd_print(2,2,"开关量",0);
														lcd_print(2,9,"第",0);		
														sprintf(tempbuf, "%02d",DINUM);										 
														lcd_print(2,13,"路",0);								 
														lcd_print(2,11,tempbuf,0);											 
														lcd_print(2,16,"功能",0);	
														DIprint(DITASK[DINUM-1],0);	
														lcd_print(3,4,"下页",1);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0);
														if(buf==4)
														{
															setAIDIpage=2;
															ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
														}
														else if(buf==1)
														{                                                         	      
															SetRow=3;
															SetCol=12; 
														}
														else if(buf==16)
														{                                                         	      
															SetRow=2;
															SetCol=21;
														}				
														break;
													
													case 12:
														lcd_print(1,2,"模拟量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",AINUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16,"功能",0);		
														AIprint(AITASK[AINUM-1],0);													   
														lcd_print(2,2,"开关量",0);
														lcd_print(2,9,"第",0);		
														sprintf(tempbuf, "%02d",DINUM);										 
														lcd_print(2,13,"路",0);								 
														lcd_print(2,11,tempbuf,0);											 
														lcd_print(2,16,"功能",0);	
														DIprint(DITASK[DINUM-1],0);	
														lcd_print(3,4,"下页",0);
														lcd_print(3,12,"确认",1);
														lcd_print(3,20,"放弃",0);
														if(buf==4)
														{
															setRTUAIDIflag=0;
															SetRow=3;
															SetCol=255;
															ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
														}
														else if(buf==1)
														{                                                         	      
															SetRow=3;
															SetCol=20; 
														}
														else if(buf==16)
														{                                                         	      
															SetRow=3;
															SetCol=4;
														}																			  	
														break;

													case 20:
														lcd_print(1,2,"模拟量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",AINUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16,"功能",0);		
														AIprint(AITASK[AINUM-1],0);													   
														lcd_print(2,2,"开关量",0);
														lcd_print(2,9,"第",0);		
														sprintf(tempbuf, "%02d",DINUM);										 
														lcd_print(2,13,"路",0);								 
														lcd_print(2,11,tempbuf,0);											 
														lcd_print(2,16,"功能",0);	
														DIprint(DITASK[DINUM-1],0);	
														lcd_print(3,4,"下页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",1); 
														if(buf==4)
														{
															
															setRTUAIDIflag=0;
															SetRow=3;
															SetCol=255;
															ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
															gs_RTUcfgMng.Getcfg(RTU_AI_NUM,&AITASK[0]);
															gs_RTUcfgMng.Getcfg(RTU_DI_NUM,&DITASK[0]);
															gs_RTUcfgMng.Getcfg(RTU_DO_NUM,&DOTASK[0]);
														}
														else if(buf==1)
														{                                                         	      
															SetRow=1;
															SetCol=5; 
														}
														else if(buf==16)
														{                                                         	      
															SetRow=3;
															SetCol=12; 
														}																		
														break;
												}
												break;
										}
										SelfTest.fGetSelftest(8,&feeddog);
										feeddog++;
										if(feeddog>109)
										{feeddog=0;}
										SelfTest.fSetSelftest(8,&feeddog);
										usleep(100000);
									}
									else if(setAIDIpage==2)
									{
										  lcd_print(0,9,"动环监控设备",0);
										read(key_fd, &buf, 1);
										switch(SetRow)
										{
											case 1:
												switch(SetCol)	
												{
													case 5:
														lcd_print(1,2,"DO 量 ",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",DONUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,1);											 
														lcd_print(1,16," 功能",0);		
														DOprint(DOTASK[DONUM-1],0);													   
														lcd_print(3,4,"上页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0);
														if(buf==8)
														{
															DONUM++;
															if(DONUM>6)
															DONUM=1;
															lcd_print(1,22,"           ",0);
														}
														else if(buf==2)
														{
															DONUM--;
															if(DONUM<1)
															DONUM=6;
															lcd_print(1,22,"           ",0);   
														}
														else if(buf==1)
														{
															SetRow=1;
															SetCol=22;
														}
														else if(buf==16)
														{
															SetRow=3;
															SetCol=20;
														}
														break;
														
													case 22:
														lcd_print(1,2,"DO 量 ",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",DONUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16," 功能",0);		
														DOprint(DOTASK[DONUM-1],1);													   
														lcd_print(3,4,"上页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0);
														if(buf==8)
														{
															if(DOTASK[DONUM-1]>=4&&DOTASK[DONUM-1]<7)
																DOTASK[DONUM-1]=7;
															else if(DOTASK[DONUM-1]==7)
																DOTASK[DONUM-1]=255;
															else if(DOTASK[DONUM-1]==255)
																DOTASK[DONUM-1]=1;
															else 
																DOTASK[DONUM-1]++;
															lcd_print(1,22,"           ",0);                                                                            
														}
														else if(buf==2)
														{
															if(DOTASK[DONUM-1]==255)
																DOTASK[DONUM-1]=7;
															else if(DOTASK[DONUM-1]<=7&&DOTASK[DONUM-1]>4)
																DOTASK[DONUM-1]=4;
															else if(DOTASK[DONUM-1]==1)
																DOTASK[DONUM-1]=255;
															else 
																DOTASK[DONUM-1]--;
															lcd_print(1,22,"           ",0);   
														}
														else if(buf==1)
														{
															SetRow=3;
															SetCol=4;
															lcd_print(1,22,"           ",0);   
														}
														else if(buf==16)
														{
															SetRow=1;
															SetCol=5;
															lcd_print(1,22,"           ",0);  
														}
														break;
												}
												break;
												
											case 3:
												switch(SetCol)
												{
													case 4:
														lcd_print(1,2,"DO 量",0);   
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",DONUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16," 功能",0);		
														DOprint(DOTASK[DONUM-1],0);													   
														lcd_print(3,4,"上页",1);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",0);
														if(buf==4)
														{
															setAIDIpage=1;
															ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
														}
														else if(buf==1)
														{                                                         	      
															SetRow=3;
															SetCol=12; 
														}
														else if(buf==16)
														{                                                         	      
															SetRow=1;
															SetCol=22;
														}
														break;
														
													case 12:
														lcd_print(1,2,"DO 量",0);   
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",DONUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16," 功能",0);		
														DOprint(DOTASK[DONUM-1],0);													   
														lcd_print(3,4,"上页",0);
														lcd_print(3,12,"确认",1);
														lcd_print(3,20,"放弃",0);
														if(buf==4)
														{
															setRTUAIDIflag=0;
															SetRow=3;
															SetCol=255;
															ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
														}
														else if(buf==1)
														{                                                         	      
															SetRow=3;
															SetCol=20; 
														}
														else if(buf==16)
														{                                                         	      
															SetRow=3;
															SetCol=4;
														}																			  	
														break;

													case 20:
														lcd_print(1,2,"DO 量",0);
														lcd_print(1,9,"第",0);		
														sprintf(tempbuf, "%02d",DONUM);										 
														lcd_print(1,13,"路",0);	
														lcd_print(1,11,tempbuf,0);											 
														lcd_print(1,16," 功能",0);		
														DOprint(DOTASK[DONUM-1],0);													   
														lcd_print(3,4,"上页",0);
														lcd_print(3,12,"确认",0);
														lcd_print(3,20,"放弃",1);
														if(buf==4)
														{
															
															setRTUAIDIflag=0;
															SetRow=3;
															SetCol=255;
															ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
															gs_RTUcfgMng.Getcfg(RTU_AI_NUM,&AITASK[0]);
															gs_RTUcfgMng.Getcfg(RTU_DI_NUM,&DITASK[0]);
															gs_RTUcfgMng.Getcfg(RTU_DO_NUM,&DOTASK[0]);

														}
														else if(buf==1)
														{                                                         	      
															SetRow=1;
															SetCol=5; 
														}
														else if(buf==16)
														{                                                         	      
															SetRow=3;
															SetCol=12;
														}
														else if(buf==8)
														{                                                         	      
															SetRow=1;
															SetCol=22; 
														}
														break;
												}
												break;
										}
										SelfTest.fGetSelftest(8,&feeddog);
										feeddog++;
										if(feeddog>109)
										{feeddog=0;}
										SelfTest.fSetSelftest(8,&feeddog);
										usleep(100000);
									}
								}
							}
							else if(buf==1)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",1);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=2;   
								SetCol=17;
							}
							else if(buf==16)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",1);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=1;   
								SetCol=17;
							}
							else if(buf==8)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",1);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=1;   
								SetCol=2;
							}
							else if(buf==2)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",1);		
								lcd_print(3,21,"放弃",0);
								SetRow=3;   
								SetCol=6;
							}
							break;				

						case 17:
							  lcd_print(0,9,"动环监控设备",0);
							lcd_print(1,2,"设置网络参数",0);		
							lcd_print(1,17,"设置串口参数",0);			  
							lcd_print(2,2,"设置AIDI参数",0);		
							lcd_print(2,17,"设置数据模块",1);
							lcd_print(3,6,"保存",0);		
							lcd_print(3,21,"放弃",0);
							if(buf==4)
							{
								ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
								  lcd_print(0,9,"动环监控设备",0);
								setRTUDBflag=1;   
								SetRow=1;
								SetCol=14;
								while(setRTUDBflag==1)
								{
									read(key_fd, &buf, 1);
									switch(SetRow)
									{
										case 1:
											switch(SetCol)	
											{
												case 14:
													lcd_print(1,0,"数据模块",0);
													lcd_print(1,12,"共",0);		
													sprintf(tempbuf, "%d",DB[0]);										 
													lcd_print(1,15,"组",0);	
													lcd_print(1,14,tempbuf,1);
													lcd_print(1,20,"第1组",0);	
													DBprint(1,25,DB[1],0);                   // 1组
													lcd_print(1,27,"节",0);	
													lcd_print(2,0,"第2组",0);	
													DBprint(2,5,DB[2],0);                     // 2组
													lcd_print(2,7,"节",0);	
													lcd_print(2,10,"第3组",0);	
													DBprint(2,15,DB[3],0);                   // 3组
													lcd_print(2,17,"节",0);	
													lcd_print(2,20,"第4组",0);	
													DBprint(2,25,DB[4],0);                   // 4组
													lcd_print(2,27,"节",0);	
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0);                                                                     
													if(buf==8)
													{
														DB[0]++;
														if(DB[0]>4)
														DB[0]=0;                                                                         
													}
													else if(buf==2)
													{
														if(DB[0]==0)
														DB[0]=4;
														else DB[0]--; 
													}
													else if(buf==1)
													{
														SetRow=1;
														SetCol=25; 
													}
													else if(buf==16)
													{
														SetRow=3;
														SetCol=21;
													}										
													break;
													
												case 25:
													lcd_print(1,0,"数据模块",0);
													lcd_print(1,12,"共",0);		
													sprintf(tempbuf, "%d",DB[0]);										 
													lcd_print(1,15,"组",0);	
													lcd_print(1,14,tempbuf,0);
													lcd_print(1,20,"第1组",0);	
													DBprint(1,25,DB[1],1);                   // 1组
													lcd_print(1,27,"节",0);	
													lcd_print(2,0,"第2组",0);	
													DBprint(2,5,DB[2],0);                     // 2组
													lcd_print(2,7,"节",0);	
													lcd_print(2,10,"第3组",0);	
													DBprint(2,15,DB[3],0);                   // 3组
													lcd_print(2,17,"节",0);	
													lcd_print(2,20,"第4组",0);	
													DBprint(2,25,DB[4],0);                   // 4组
													lcd_print(2,27,"节",0);	
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0);                                                                     
													if(buf==8)
													{
														DB[1]++;
														if(DB[1]>48)
														DB[1]=0;                                                                         
													}
													else if(buf==2)
													{
														if(DB[1]==0)
														DB[1]=48;
														else DB[1]--; 
													}
													else if(buf==1)
													{
														SetRow=2;
														SetCol=5; 
													}
													else if(buf==16)
													{
														SetRow=1;
														SetCol=14;
													}										
													break;
											}
											break;
											
										case 2:
											switch(SetCol)	
											{
												case 5:
													lcd_print(1,0,"数据模块",0);
													lcd_print(1,12,"共",0);		
													sprintf(tempbuf, "%d",DB[0]);										 
													lcd_print(1,15,"组",0);	
													lcd_print(1,14,tempbuf,0);
													lcd_print(1,20,"第1组",0);	
													DBprint(1,25,DB[1],0);                   // 1组
													lcd_print(1,27,"节",0);	
													lcd_print(2,0,"第2组",0);	
													DBprint(2,5,DB[2],1);                     // 2组
													lcd_print(2,7,"节",0);	
													lcd_print(2,10,"第3组",0);	
													DBprint(2,15,DB[3],0);                   // 3组
													lcd_print(2,17,"节",0);	
													lcd_print(2,20,"第4组",0);	
													DBprint(2,25,DB[4],0);                   // 4组
													lcd_print(2,27,"节",0);	
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0);                                                                     
													if(buf==8)
													{
														DB[2]++;
														if(DB[2]>48)
														DB[2]=0;                                                                         
													}
													else if(buf==2)
													{
														if(DB[2]==0)
														DB[2]=48;
														else DB[2]--; 
													}
													else if(buf==1)
													{
														SetRow=2;
														SetCol=15; 
													}
													else if(buf==16)
													{
														SetRow=1;
														SetCol=25;
													}										
													break;
													
												case 15:
													lcd_print(1,0,"数据模块",0);
													lcd_print(1,12,"共",0);		
													sprintf(tempbuf, "%d",DB[0]);										 
													lcd_print(1,15,"组",0);	
													lcd_print(1,14,tempbuf,0);
													lcd_print(1,20,"第1组",0);	
													DBprint(1,25,DB[1],0);                   // 1组
													lcd_print(1,27,"节",0);	
													lcd_print(2,0,"第2组",0);	
													DBprint(2,5,DB[2],0);                     // 2组
													lcd_print(2,7,"节",0);	
													lcd_print(2,10,"第3组",0);	
													DBprint(2,15,DB[3],1);                   // 3组
													lcd_print(2,17,"节",0);	
													lcd_print(2,20,"第4组",0);	
													DBprint(2,25,DB[4],0);                   // 4组
													lcd_print(2,27,"节",0);	
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0);                                                                     
													if(buf==8)
													{
														DB[3]++;
														if(DB[3]>48)
														DB[3]=0;                                                                         
													}
													else if(buf==2)
													{
														if(DB[3]==0)
														DB[3]=48;
														else DB[3]--; 
													}
													else if(buf==1)
													{
														SetRow=2;
														SetCol=25; 
													}
													else if(buf==16)
													{
														SetRow=2;
														SetCol=5;
													}										
													break;
													
												case 25:
													lcd_print(1,0,"数据模块",0);
													lcd_print(1,12,"共",0);		
													sprintf(tempbuf, "%d",DB[0]);										 
													lcd_print(1,15,"组",0);	
													lcd_print(1,14,tempbuf,0);
													lcd_print(1,20,"第1组",0);	
													DBprint(1,25,DB[1],0);                   // 1组
													lcd_print(1,27,"节",0);	
													lcd_print(2,0,"第2组",0);	
													DBprint(2,5,DB[2],0);                     // 2组
													lcd_print(2,7,"节",0);	
													lcd_print(2,10,"第3组",0);	
													DBprint(2,15,DB[3],0);                   // 3组
													lcd_print(2,17,"节",0);	
													lcd_print(2,20,"第4组",0);	
													DBprint(2,25,DB[4],1);                   // 4组
													lcd_print(2,27,"节",0);	
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",0);                                                                     
													if(buf==8)
													{
														DB[4]++;
														if(DB[4]>48)
														DB[4]=0;                                                                         
													}
													else if(buf==2)
													{
														if(DB[4]==0)
														DB[4]=48;
														else DB[4]--; 
													}
													else if(buf==1)
													{
														SetRow=3;
														SetCol=4; 
													}
													else if(buf==16)
													{
														SetRow=2;
														SetCol=15;
													}										
													break;
					                        }
											break;
											
										case 3:
											switch(SetCol)
											{
												case 4:
													lcd_print(1,0,"数据模块",0);
													lcd_print(1,12,"共",0);		
													sprintf(tempbuf, "%d",DB[0]);										 
													lcd_print(1,15,"组",0);	
													lcd_print(1,14,tempbuf,0);
													lcd_print(1,20,"第1组",0);	
													DBprint(1,25,DB[1],0);                   // 1组
													lcd_print(1,27,"节",0);	
													lcd_print(2,0,"第2组",0);	
													DBprint(2,5,DB[2],0);                     // 2组
													lcd_print(2,7,"节",0);	
													lcd_print(2,10,"第3组",0);	
													DBprint(2,15,DB[3],0);                   // 3组
													lcd_print(2,17,"节",0);	
													lcd_print(2,20,"第4组",0);	
													DBprint(2,25,DB[4],0);                   // 4组
													lcd_print(2,27,"节",0);	
													lcd_print(3,4,"确认",1); 
													lcd_print(3,21,"放弃",0);
													if(buf==4)
													{
														setRTUDBflag=0;
														SetRow=3;
														SetCol=255;
														ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
													}
													else if(buf==1)
													{                                                         	      
														SetRow=3;
														SetCol=21; 
													}
													else if(buf==16)
													{                                                         	      
														SetRow=2;
														SetCol=25;
														lcd_print(3,4,"确认",0); 
														lcd_print(3,21,"放弃",0); 
													}
													else if(buf==8)
													{                                                         	      
														SetRow=2;
														SetCol=25; 
														lcd_print(3,4,"确认",0); 
														lcd_print(3,21,"放弃",0); 
													}																			  	
													break;
													
												case 21:
													lcd_print(1,0,"数据模块",0);
													lcd_print(1,12,"共",0);		
													sprintf(tempbuf, "%d",DB[0]);										 
													lcd_print(1,15,"组",0);	
													lcd_print(1,14,tempbuf,0);
													lcd_print(1,20,"第1组",0);	
													DBprint(1,25,DB[1],0);                   // 1组
													lcd_print(1,27,"节",0);	
													lcd_print(2,0,"第2组",0);	
													DBprint(2,5,DB[2],0);                     // 2组
													lcd_print(2,7,"节",0);	
													lcd_print(2,10,"第3组",0);	
													DBprint(2,15,DB[3],0);                   // 3组
													lcd_print(2,17,"节",0);	
													lcd_print(2,20,"第4组",0);	
													DBprint(2,25,DB[4],0);                   // 4组
													lcd_print(2,27,"节",0);	
													lcd_print(3,4,"确认",0); 
													lcd_print(3,21,"放弃",1);
													if(buf==4)
													{
														gs_RTUcfgMng.Getcfg(RTU_DB_NUM,&DB[0]);
														setRTUDBflag=0;
														SetRow=3;
														SetCol=255;
														ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
													}
													else if(buf==1)
													{                                                         	      
														SetRow=1;
														SetCol=14; 
													}
													else if(buf==16)
													{                                                         	      
														SetRow=3;
														SetCol=4;
													}
													else if(buf==8)
													{                                                         	      
														SetRow=2;
														SetCol=25; 
														lcd_print(3,4,"确认",0); 
														lcd_print(3,21,"放弃",0); 
													}																			  	
													break;	                                                           
											}
											break;								
									}
									SelfTest.fGetSelftest(8,&feeddog);
									feeddog++;
									if(feeddog>109)
									{
										feeddog=0;
									}
									SelfTest.fSetSelftest(8,&feeddog);
									usleep(100000);
								}
							}
							else if(buf==1)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",1);		
								lcd_print(3,21,"放弃",0);
								SetRow=3;   
								SetCol=6;
							}
							else if(buf==16)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",1);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=2;   
								SetCol=2;
							}
							else if(buf==8)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",1);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0);
								SetRow=1;   
								SetCol=17;
							}
							else if(buf==2)
							{
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",0);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",1);
								SetRow=3;   
								SetCol=21;
							}               
							break;
						}
						break;


					case 3:
						switch(SetCol)
						{
							case 6:                   
								if(buf==4)
								{
									RTUaddress[0]=(RTUaddr&0xff);
									RTUaddress[1]=((RTUaddr>>8)&0xff);
									gs_RTUcfgMng.Setcfg(RTU_COM1_NUM,&LCDCOM[0][0]);
									gs_RTUcfgMng.Setcfg(RTU_COM2_NUM,&LCDCOM[1][0]);
									gs_RTUcfgMng.Setcfg(RTU_COM3_NUM,&LCDCOM[2][0]);
									gs_RTUcfgMng.Setcfg(RTU_COM4_NUM,&LCDCOM[3][0]);
									gs_RTUcfgMng.Setcfg(RTU_COM5_NUM,&LCDCOM[4][0]);
									gs_RTUcfgMng.Setcfg(RTU_COM6_NUM,&LCDCOM[5][0]);
									gs_RTUcfgMng.Setcfg(RTU_COM7_NUM,&LCDCOM[6][0]);
									gs_RTUcfgMng.Setcfg(RTU_AI_NUM,&AITASK[0]);
									gs_RTUcfgMng.Setcfg(RTU_DI_NUM,&DITASK[0]);
									gs_RTUcfgMng.Setcfg(RTU_DO_NUM,&DOTASK[0]);
									gs_RTUcfgMng.Setcfg(RTU_DB_NUM,&DB[0]);                                                               
									gs_RTUcfgMng.Setcfg(RTU_addr_NUM,&RTUaddr);
									gs_RTUcfgMng.Setcfg(RTU_IP_NUM,&RTUip[0]);
									gs_RTUcfgMng.Setcfg(RTU_netmask_NUM,&RTUmask[0]);
									gs_RTUcfgMng.Setcfg(RTU_gateway_NUM,&RTUgate[0]);
									gs_pwalarmMng.Setthre_val(RTU_backlight_NUM,&backlight);
									sleep(2);
									ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
									system("reboot");
								}
								else if(buf==1)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",0);		
									lcd_print(1,17,"设置串口参数",0);			  
									lcd_print(2,2,"设置AIDI参数",0);		
									lcd_print(2,17,"设置数据模块",0);
									lcd_print(3,6,"保存",0);		
									lcd_print(3,21,"放弃",1);
									SetRow=3;   
									SetCol=21;
								}
								else if(buf==16)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",0);		
									lcd_print(1,17,"设置串口参数",0);			  
									lcd_print(2,2,"设置AIDI参数",0);		
									lcd_print(2,17,"设置数据模块",1);
									lcd_print(3,6,"保存",0);		
									lcd_print(3,21,"放弃",0);
									SetRow=2;   
									SetCol=17;
								}
								else if(buf==8)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",0);		
									lcd_print(1,17,"设置串口参数",0);			  
									lcd_print(2,2,"设置AIDI参数",1);		
									lcd_print(2,17,"设置数据模块",0);
									lcd_print(3,6,"保存",0);		
									lcd_print(3,21,"放弃",0);
									SetRow=2;   
									SetCol=2;
								}
								else if(buf==2)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",1);		
									lcd_print(1,17,"设置串口参数",0);			  
									lcd_print(2,2,"设置AIDI参数",0);		
									lcd_print(2,17,"设置数据模块",0);
									lcd_print(3,6,"保存",0);		
									lcd_print(3,21,"放弃",0);
									SetRow=1;   
									SetCol=2;
								}               
								break;
								
							case 21:                   
								if(buf==4)
								{
									gs_RTUcfgMng.Getcfg(RTU_COM1_NUM,&LCDCOM[0][0]);
									gs_RTUcfgMng.Getcfg(RTU_COM2_NUM,&LCDCOM[1][0]);
									gs_RTUcfgMng.Getcfg(RTU_COM3_NUM,&LCDCOM[2][0]);
									gs_RTUcfgMng.Getcfg(RTU_COM4_NUM,&LCDCOM[3][0]);
									gs_RTUcfgMng.Getcfg(RTU_COM5_NUM,&LCDCOM[4][0]);
									gs_RTUcfgMng.Getcfg(RTU_COM6_NUM,&LCDCOM[5][0]);
									gs_RTUcfgMng.Getcfg(RTU_COM7_NUM,&LCDCOM[6][0]);
									gs_RTUcfgMng.Getcfg(RTU_AI_NUM,&AITASK[0]);
									gs_RTUcfgMng.Getcfg(RTU_DI_NUM,&DITASK[0]);
									gs_RTUcfgMng.Getcfg(RTU_DO_NUM,&DOTASK[0]);
									gs_RTUcfgMng.Getcfg(RTU_DB_NUM,&DB[0]);                                                               
									gs_RTUcfgMng.Getcfg(RTU_addr_NUM,&RTUaddress[0]);
									gs_RTUcfgMng.Getcfg(RTU_IP_NUM,&RTUip[0]);
									gs_RTUcfgMng.Getcfg(RTU_netmask_NUM,&RTUmask[0]);
									gs_RTUcfgMng.Getcfg(RTU_gateway_NUM,&RTUgate[0]);
									gs_pwalarmMng.Getthre_val(RTU_backlight_NUM,&backlight);
									Temp_RTUaddr=RTUaddress[1];
									Temp_RTUaddr=(Temp_RTUaddr<<8|RTUaddress[0]);
									if(Temp_RTUaddr>999)
										Temp_RTUaddr=0;
									change(backlight,&RTUset.lcd[0]);                              
									changeaddr(Temp_RTUaddr,&RTUset.RTUaddr[0]);
									change(RTUip[0],&RTUset.ip[0]);
									change(RTUip[1],&RTUset.ip[3]);
									change(RTUip[2],&RTUset.ip[6]);
									change(RTUip[3],&RTUset.ip[9]);
									change(RTUmask[0],&RTUset.mask[0]);
									change(RTUmask[1],&RTUset.mask[3]);
									change(RTUmask[2],&RTUset.mask[6]);
									change(RTUmask[3],&RTUset.mask[9]);
									change(RTUgate[0],&RTUset.gate[0]);
									change(RTUgate[1],&RTUset.gate[3]);
									change(RTUgate[2],&RTUset.gate[6]);
									change(RTUgate[3],&RTUset.gate[9]);
									SetRow=2;
									SetCol=2;
									setRTUparaflag=0;
									ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
									system("hwclock -r");
									system("hwclock -s");
								}
								else if(buf==1)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",1);		
									lcd_print(1,17,"设置串口参数",0);			  
									lcd_print(2,2,"设置AIDI参数",0);		
									lcd_print(2,17,"设置数据模块",0);
									lcd_print(3,6,"保存",0);		
									lcd_print(3,21,"放弃",0);
									SetRow=1;   
									SetCol=2;
								}
								else if(buf==16)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",0);		
									lcd_print(1,17,"设置串口参数",0);			  
									lcd_print(2,2,"设置AIDI参数",0);		
									lcd_print(2,17,"设置数据模块",0);
									lcd_print(3,6,"保存",1);		
									lcd_print(3,21,"放弃",0);
									SetRow=3;   
									SetCol=6;
								}
								else if(buf==8)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",0);		
									lcd_print(1,17,"设置串口参数",0);			  
									lcd_print(2,2,"设置AIDI参数",0);		
									lcd_print(2,17,"设置数据模块",1);
									lcd_print(3,6,"保存",0);		
									lcd_print(3,21,"放弃",0);
									SetRow=2;   
									SetCol=17;
								}
								else if(buf==2)
								{
									  lcd_print(0,9,"动环监控设备",0);
									lcd_print(1,2,"设置网络参数",0);		
									lcd_print(1,17,"设置串口参数",1);			  
									lcd_print(2,2,"设置AIDI参数",0);		
									lcd_print(2,17,"设置数据模块",0);
									lcd_print(3,6,"保存",0);		
									lcd_print(3,21,"放弃",0);
									SetRow=1;   
									SetCol=17;
								}               
								break;
								
							case 255:
								  lcd_print(0,9,"动环监控设备",0);
								lcd_print(1,2,"设置网络参数",1);		
								lcd_print(1,17,"设置串口参数",0);			  
								lcd_print(2,2,"设置AIDI参数",0);		
								lcd_print(2,17,"设置数据模块",0);
								lcd_print(3,6,"保存",0);		
								lcd_print(3,21,"放弃",0); 
								read(key_fd, &buf, 1);
								sleep(1);
								SetRow=1;   
								SetCol=2;								 	
								break;			
						}
						break;					  				
				}
				SelfTest.fGetSelftest(8,&feeddog);
				feeddog++;
				if(feeddog>109)
				{
					feeddog=0;
				}
				SelfTest.fSetSelftest(8,&feeddog);
				usleep(100000);
			}
		}
		else if(buf==1)
		{
			SetCol=17;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",1);
		}
		else if(buf==16)
		{
			SetCol=17;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",1);
		}	
		else if(buf==8)
		{
			SetCol=4;
			SetRow=3;
			lcd_print(3,4,"设置密码",1);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}
		else  if(buf==2)
		{
			SetCol=4;
			SetRow=3;
			lcd_print(3,4,"设置密码",1);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}
		break;


			/////////设置RTU参数
                	
	case 17:
		if(buf==4)
		{
			readstatflag=1;
			readStatePage=1;
			ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
			lcd_print(0,0, "输入状态:",0);
			SetCol=20;
			while(readstatflag==1)
			{
				if(readStatePage==1)
				{
					read(key_fd, &buf, 1);
					for(i=0;i<8;i++)
					{
						switch(i)
						{
							case 0:
								if(DI_val[0]==0)
								{
									lcd_print(1,0,"第1 路:闭",0);
								}
								else if(DI_val[0]==1)
								{
									lcd_print(1,0,"第1 路:开",0);
								}
								break;

							case 1:
								if(DI_val[1]==0)
								{
									lcd_print(1,10,"第2 路:闭",0);
								}
								else if(DI_val[1]==1)
								{
									lcd_print(1,10,"第2 路:开",0);
								}
								break;

							case 2:
								if(DI_val[2]==0)
								{
									lcd_print(1,20,"第3 路:闭",0);
								}
								else if(DI_val[2]==1)
								{
									lcd_print(1,20,"第3 路:开",0);
								}
								break;

							case 3:
								if(DI_val[3]==0)
								{
									lcd_print(2,0,"第4 路:闭",0);
								}
								else if(DI_val[3]==1)
								{
									lcd_print(2,0,"第4 路:开",0);
								}
								break;

							case 4:
								if(DI_val[4]==0)
								{
									lcd_print(2,10,"第5 路:闭",0);
								}
								else if(DI_val[4]==1)
								{
									lcd_print(2,10,"第5 路:开",0);
								}
								break;

							case 5:
								if(DI_val[5]==0)
								{
									lcd_print(2,20,"第6 路:闭",0);
								}
								else if(DI_val[5]==1)
								{
									lcd_print(2,20,"第6 路:开",0);
								}
								break;

							case 6:
								if(DI_val[6]==0)
								{
									lcd_print(3,0,"第7 路:闭",0);
								}
								else if(DI_val[6]==1)
								{
									lcd_print(3,0,"第7 路:开",0);
								}
								break;

							case 7:
								if(DI_val[7]==0)
								{
									lcd_print(3,10,"第8 路:闭",0);
								}
								else if(DI_val[7]==1)
								{
									lcd_print(3,10,"第8 路:开",0);
								}
								break;
						}
					}
					switch(SetCol)
					{
						case 20:
							lcd_print(3,20,"下页",1);
							lcd_print(3,26,"返回",0);
							if(buf==4)
							{
								readStatePage=2;
							}
							else if(buf==16||buf==1)
							{
								SetCol=26;
							}
							break;

						case 26:
							lcd_print(3,20,"下页",0);
							lcd_print(3,26,"返回",1);
							if(buf==4)
							{
								readstatflag=0;
								setflag=0;
								ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
								system("hwclock -r");
								system("hwclock -s");
							}
							else if(buf==16||buf==1)
							{
								SetCol=20;
							}
							break;
					}
				}
				else if(readStatePage==2)
				{
					read(key_fd, &buf, 1);
					for(ii=8;ii<16;ii++)
					{
						switch(ii)
						{
							case 8:
								if(DI_val[8]==0)
								{
									lcd_print(1,0,"第9 路:闭",0);
								}
								else if(DI_val[8]==1)
								{
									lcd_print(1,0,"第9 路:开",0);
								}
								break;

							case 9:
								if(DI_val[9]==0)
								{
									lcd_print(1,10,"第10路:闭",0);
								}
								else if(DI_val[9]==1)
								{
									lcd_print(1,10,"第10路:开",0);
								}
								break;

							case 10:
								if(DI_val[10]==0)
								{
									lcd_print(1,20,"第11路:闭",0);
								}
								else if(DI_val[10]==1)
								{
									lcd_print(1,20,"第11路:开",0);
								}
								break;

							case 11:
								if(DI_val[11]==0)
								{
									lcd_print(2,0,"第12路:闭",0);
								}
								else if(DI_val[11]==1)
								{
									lcd_print(2,0,"第12路:开",0);
								}
								break;

							case 12:
								if(DI_val[12]==0)
								{
									lcd_print(2,10,"第13路:闭",0);
								}
								else if(DI_val[12]==1)
								{
									lcd_print(2,10,"第13路:开",0);
								}
								break;

							case 13:
								if(DI_val[13]==0)
								{
									lcd_print(2,20,"第14路:闭",0);
								}
								else if(DI_val[13]==1)
								{
									lcd_print(2,20,"第14路:开",0);
								}
								break;

							case 14:
								if(DI_val[14]==0)
								{
									lcd_print(3,0,"第15路:闭",0);
								}
								else if(DI_val[14]==1)
								{
									lcd_print(3,0,"第15路:开",0);
								}
								break;

							case 15:
								if(DI_val[15]==0)
								{
									lcd_print(3,10,"第16路:闭",0);
								}
								else if(DI_val[15]==1)
								{
									lcd_print(3,10,"第16路:开",0);
								}
								break;
						}
					}
					switch(SetCol)
					{
						case 20:
							lcd_print(3,20,"上页",1);
							lcd_print(3,26,"返回",0);
							if(buf==4)
							{
								readStatePage=1;
							}
							else if(buf==16||buf==1)
							{
								SetCol=26;
							}
							break;

						case 26:
							lcd_print(3,20,"上页",0);
							lcd_print(3,26,"返回",1);
							if(buf==4)
							{
								readstatflag=0;
								setflag=0;
								ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
								system("hwclock -r");
								system("hwclock -s");
							}
							else if(buf==16||buf==1)
							{
								SetCol=20;
							}
							break;
					}
				}
				SelfTest.fGetSelftest(8,&feeddog);usleep(10000);
				feeddog++;
				if(feeddog>109)
				{
					feeddog=0;
				}
				SelfTest.fSetSelftest(8,&feeddog);	
			}
		}
		else if(buf==1)
		{
			SetCol=2;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);							
			lcd_print(2,2,"设置RTU参数",1);
			lcd_print(2,17,"查看输入状态",0);
		}
		else  if(buf==16)
		{
			SetCol=2;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",1);
			lcd_print(2,17,"查看输入状态",0);
		}	
		else if(buf==8)
		{
			SetCol=21;
			SetRow=3;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",1);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}
		else  if(buf==2)
		{
			SetCol=21;
			SetRow=3;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",1);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}	
		break;

                     ///////////////////  查看输入状态



	case 4:
		if(buf==4)
		{
			memset(password,0,4);
			memset(pw,0,5);
			setpwflag=0;
			ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);   
			//lcd_print(0,2,"请输入原密码",0);   
			  lcd_print(0,2, " 通号通信信息集团有限公司",0);
	             lcd_print(1,9,"动环监控设备",0);
			lcd_print(2,2,"请输入新密码",0);
			//lcd_print(3,7,"确认",0);     
			//lcd_print(3,19,"返回",0);
			SetCol=16;SetRow=2;
			while(setpwflag==0)                      
			{
				read(key_fd, &buf, 1);
				switch(SetRow)
				{
					case 2:
						switch(SetCol)
						{
							case 16:
								sprintf(tempbuf,"%d ",password[0]);	                                      
								lcd_print(2,16,tempbuf,1);                        
								lcd_print(2,18,"* * * ",0);
								// lcd_print(1,16,"* * * *",0);
								lcd_print(3,7,"确认",0);      
								lcd_print(3,19,"返回",0); 
								if(buf==8)
								{
									if(password[0]==9)
									{
										password[0]=0;
									}
									else
										password[0]++;
								}   
								else if(buf==2)
								{
									if(password[0]==0)
									{
										password[0]=9;
									}
									else
										password[0]--;
								} 						  
								else if(buf==16)
								{
									SetCol=22;
								}   
								else if(buf==1)
								{
									SetCol=18;
								} 	
								break;
								
							case 18:
								lcd_print(2,16,"* ",0);
								sprintf(tempbuf,"%d ",password[1]);	                                      
								lcd_print(2,18,tempbuf,1);                        
								lcd_print(2,20,"* * ",0);                        
								//lcd_print(1,16,"* * * *",0);
								lcd_print(3,7,"确认",0);      
								lcd_print(3,19,"返回",0); 
								if(buf==8)
								{
									if(password[1]==9)
									{
										password[1]=0;
									}
									else
										password[1]++;
								}   
								else if(buf==2)
								{
									if(password[1]==0)
									{
									password[1]=9;
									}
									else
										password[1]--;
								} 						  
								else if(buf==16)
								{
									SetCol=16;
								}   
								else if(buf==1)
								{
									SetCol=20;
								} 	
								break;
								
							case 20:
								lcd_print(2,16,"* * ",0);
								sprintf(tempbuf,"%d ",password[2]);	                                      
								lcd_print(2,20,tempbuf,1);                        
								lcd_print(2,22,"* ",0);                        
								// lcd_print(1,16,"* * * *",0);
								lcd_print(3,7,"确认",0);      
								lcd_print(3,19,"返回",0); 
								if(buf==8)
								{
									if(password[2]==9)
									{
										password[2]=0;
									}
									else
										password[2]++;
								}   
								else if(buf==2)
								{
									if(password[2]==0)
									{
										password[2]=9;
									}
									else
										password[2]--;
								} 						  
								else if(buf==16)
								{
									SetCol=18;
								}   
								else if(buf==1)
								{
									SetCol=22;
								} 	
								break;
								
							case 22:
								lcd_print(2,16,"* * * ",0);
								sprintf(tempbuf,"%d ",password[3]);	                                      
								lcd_print(2,22,tempbuf,1);
								// lcd_print(1,16,"* * * *",0);
								lcd_print(3,7,"确认",0);      
								lcd_print(3,19,"返回",0); 
								if(buf==8)
								{
									if(password[3]==9)
									{
										password[3]=0;
									}
									else
										password[3]++;
								}   
								else if(buf==2)
								{
									if(password[3]==0)
									{
										password[3]=9;
									}
									else
										password[3]--;
								} 						  
								else if(buf==16)
								{
									SetCol=20;
								}   
								else if(buf==1)
								{
									SetCol=7;
									SetRow=3;
								} 	
								break;
						}
						break;
						
					case 3:
						switch(SetCol)
						{
							case 7:
								lcd_print(2,16,"* * * * ",0);
								lcd_print(3,7,"确认",1);      
								lcd_print(3,19,"返回",0);   										 
								if(buf==8)
								{
									SetCol=22;
									SetRow=2;
								}   
								else if(buf==2)
								{
									SetCol=22;
									SetRow=2;
								} 						  
								else if(buf==16)
								{
									SetCol=19;
									SetRow=3;
								}   
								else if(buf==1)
								{
									SetCol=19;
									SetRow=3;
								} 	
								else if(buf==4)
								{
									setpwflag=1;
								}
								break;
								
							case 19:	
								lcd_print(2,16,"* * * * ",0);
								lcd_print(3,7,"确认",0);      
								lcd_print(3,19,"返回",1);   										 
								if(buf==8)
								{
									SetCol=22;
									SetRow=2;
								}   
								else if(buf==2)
								{
									SetCol=22;
									SetRow=2;
								} 						  
								else if(buf==16)
								{
									SetCol=7;
									SetRow=3;
								}   
								else if(buf==1)
								{
									SetCol=7;
									SetRow=3;
								} 	
								else if(buf==4)
								{
									setpwflag=2;
									ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
									system("hwclock -r");
									system("hwclock -s");
									setflag=0;
								} 		                              
								break;
						}
						break;
				}
				SelfTest.fGetSelftest(8,&feeddog);
				feeddog++;
				if(feeddog>109)
				{
					feeddog=0;
				}
				SelfTest.fSetSelftest(8,&feeddog);
			}
			if(setpwflag==1)
			{
				passwordint=password[0]*1000+password[1]*100+password[2]*10+password[3];
				itoa(passwordint,pw);
				if(writesysfile(files, keys, pw)==1)
				{
					ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
					  lcd_print(0,2, " 通号通信信息集团有限公司",0);
	                             lcd_print(1,9,"动环监控设备",0);
					lcd_print(2,7,"密 码 设 置 成 功",0); sleep(3);
					setflag=0;
				}
				else
				{
					ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
					  lcd_print(0,2, " 通号通信信息集团有限公司",0);
	                             lcd_print(1,9,"动环监控设备",0);
					lcd_print(2,7,"密 码 设 置 失 败",0); sleep(3);
					setflag=0;
				}
			}                                        
		}	

		else  if(buf==1)
		{
			SetCol=21;
			SetRow=3;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",1);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}
		else  if(buf==16)
		{
			SetCol=21;
			SetRow=3;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",1);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}	
		else if(buf==8)
		{
			SetCol=2;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",1);
			lcd_print(2,17,"查看输入状态",0);
		}
		else  if(buf==2)
		{
			SetCol=2;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",1);
			lcd_print(2,17,"查看输入状态",0);
		}	
		break;

	case 21:
		if(buf==4)
		{ 
			ioctl(hd_lcd, IOC_CLEAR_SCREEN, NULL);
			setflag=0;
			system("hwclock -r");
			system("hwclock -s");
			break;
		}
		else  if(buf==1)
		{
			SetCol=4;
			SetRow=3;
			lcd_print(3,4,"设置密码",1);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}
		else  if(buf==16)
		{
			SetCol=4;
			SetRow=3;
			lcd_print(3,4,"设置密码",1);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",0);
		}	
		else if(buf==8)
		{
			SetCol=17;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",1);
		}
		else  if(buf==2)
		{
			SetCol=17;
			SetRow=2;
			lcd_print(3,4,"设置密码",0);		
			lcd_print(3,21,"返回",0);		
			lcd_print(2,2,"设置RTU参数",0);
			lcd_print(2,17,"查看输入状态",1);
		}	
		break;
}
SelfTest.fGetSelftest(8,&feeddog);
feeddog++;
if(feeddog>109)
{
	feeddog=0;
}
SelfTest.fSetSelftest(8,&feeddog);	
}
}
}
SelfTest.fGetSelftest(8,&feeddog);
if(feeddog>109)
{
	feeddog=0;
}
SelfTest.fSetSelftest(8,&feeddog);	
// printf("\n**************%d\n",feeddog);
if(feeddog>107)
{
	//ioctl(hd_lcd, IOC_LCD_INIT, NULL);
	feeddog=110;
	SelfTest.fGetSelftest(8,&feeddog);
	system("hwclock -s");
}

//system("ps");
}

}

