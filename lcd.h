/*==========================================================================*
 *    Copyright(c) 2007-2010, Emerson Network Power Co., Ltd.
 *                     ALL RIGHTS RESERVED
 *
 *   PRODUCT  : NGMC-HF
 *
 *  FILENAME : lcd.h
 *  CREATOR  : Tony(Han Tao)                DATE: 2007-11-07 14:03
 *  VERSION  : V1.00
 *  PURPOSE  :
 *
 *
 *==========================================================================*/

#ifndef __AT91SAM9263_LCD_H
#define __AT91SAM9263_LCD_H

#define _LCDDEBUG

#ifdef	_LCDDEBUG
#define MSG(string, args...) printk(string, ##args)
#else
#define MSG(string, args...)
#endif


#define SMC_SETUP0 	(0x0000) 	/**<  Setup Register for CS 0 */
#define SMC_PULSE0 	(0x0004) 	/**<  Pulse Register for CS 0 */
#define SMC_CYCLE0 	(0x0008) 	/**<  Cycle Register for CS 0 */
#define SMC_CTRL0 	(0x000C) 	/**<  Control Register for CS 0 */
#define LCD_RESET_PIN 	AT91_PIN_PA24
#define LCD_BUZZ_PIN	AT91_PIN_PA30
#define DIO_NAME "dev/dio"

#define CSLCD_OFFSET      (6<<12)

#define LCD_CMD_ADDR     1
#define LCD_DATA_ADDR	0


//#define	CMD_CAN_INIT		1



#define LCD_NAME			"/dev/lcd"
#define LCD_MAJOR			243  
#define LCD_NUMBER 			1
#define LCD_MINOR			0

#define AT91C_EXT_BASE_ADD  (0x70000000 + CSLCD_OFFSET)
#define SIZE_OF_LCD	0x3//for use LCD_ADD(A13)

#define DEFAULT_LCDB_REP_DELAY  (HZ/4)
#define DEFAULT_LCDB_REP_RATE   (HZ/12)

#define LCD_TIMER_DELAY 	30			// 30 ms	


#define CMD_SYS_SET				0x40 //initialize device and display
#define CMD_SLEEP_IN				0x53
#define CMD_DISP_OFF				0x58
#define CMD_DISP_ON				0x59
#define CMD_SCROLL_BLOCK			0x44 //set display start address and display region/set the scroll block start address and contained lines
#define CMD_SET_CURSOR_TYPE			0x5d //set cusor type
#define CMD_SET_CGRAMADDR			0x5c //set cg ram address
#define CMD_SET_CURSOR_AUTO_RIGHT	        0x4c //set cursor auto increment direction
#define CMD_SET_CURSOR_AUTO_LEFT	        0x4d
#define CMD_SET_CURSOR_AUTO_UP		        0x4e
#define CMD_SET_CURSOR_AUTO_DOWN	        0x4f
#define CMD_SET_HORIZON_SCROLL_POS	        0x5a  //set horizontal scroll position
#define CMD_SET_OVLAY				0x5b  //set display overlay format
#define CMD_SET_CURSOR_ADDR			0x46  //set cursor address
#define CMD_GET_CURSOR_ADDR			0x47  //get cursor address
#define CMD_WRITE_TO_VRAM			0x42  //write to display mem
#define CMD_READ_FROM_VRAM			0x43  //read from display mem

#define IOC_TEXT_MODE		       _IOW(LCD_MAJOR, 1, unsigned long)
#define IOC_GRAPHIC_MODE		_IOW(LCD_MAJOR, 2, unsigned long)
#define IOC_SET_CURSOR_DIR	       _IOW(LCD_MAJOR, 3, unsigned long)
#define IOC_SET_CURSOR_SHAPE	_IOW(LCD_MAJOR, 4, unsigned long)
#define IOC_SET_BL		              _IOW(LCD_MAJOR, 5, unsigned long)
#define IOC_LCD_INIT		       _IOW(LCD_MAJOR, 6, unsigned long)
#define IOC_CLEAR_SCREEN		_IOW(LCD_MAJOR, 7, unsigned long)
#define IOC_DISP_OFF	              _IOW(LCD_MAJOR, 8, unsigned long)
#define IOC_DISP_ON   	              _IOW(LCD_MAJOR, 9, unsigned long)
#define IOC_CURSOR_ON		       _IOW(LCD_MAJOR, 10, unsigned long)
#define IOC_CURSOR_OFF		       _IOW(LCD_MAJOR, 11, unsigned long)
#define IOC_BEEP_ON		              _IOW(LCD_MAJOR, 12, unsigned long)
#define IOC_BEEP_OFF	              _IOW(LCD_MAJOR, 13, unsigned long)

#define IOC_XOR_MODE	             _IOW(LCD_MAJOR, 14, unsigned long)
#define IOC_OR_MODE		      _IOW(LCD_MAJOR, 15, unsigned long)
#define IOC_AND_MODE		      _IOW(LCD_MAJOR, 16, unsigned long)
#define IOC_NXOR_MODE		      _IOW(LCD_MAJOR, 17, unsigned long)
#define IOC_FILL_SCREEN	             _IOW(LCD_MAJOR, 18, unsigned long)
#define IOC_COPY_MODE   	      _IOW(LCD_MAJOR, 19, unsigned long)
#define IOC_SET_LCD_CURSOR	      _IOW(LCD_MAJOR, 20, unsigned long)
#define IOC_SET_WRITE_MODE      _IOW(LCD_MAJOR, 21, unsigned long)
#define IOC_SET_ROLL_DEGREE	_IOW(LCD_MAJOR, 22, unsigned long)

#define SCREEN_SIZE_ROW	64
#define SCREEN_SIZE_COL		240
#define FONT_HEIGHT				16  //lines
#define FONT_WIDTH				8	//pixels
#define MAX_ROW	(SCREEN_SIZE_ROW/FONT_HEIGHT -1)
#define MAX_COL	(SCREEN_SIZE_COL/FONT_WIDTH-1)

#define NEW_LCD
struct lcd_cursor
{
	unsigned char row;			
	unsigned char col;			
};
void init_T6963c(void);
void disp_byte(unsigned char row, unsigned char col, unsigned char *pByte);
int lcd_write(unsigned char *pbuf, int count);
void reset(void);
void set_backlight(u_char backlight);
int set_cursor(unsigned char onoff, unsigned char row, unsigned char col);
void clear(u_char ucData);


#endif /* __AT91SAM9263_LCD_H */


