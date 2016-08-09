
#ifndef __AT91SAM9263_JUMP_H
#define __AT91SAM9263_JUMP_H

#define _DEBUG

#ifdef	_DEBUG
#define MSG(string, args...) printk(string, ##args)
#else
#define MSG(string, args...)
#endif


#define SMC_SETUP0 	(0x0000) 	/**<  Setup Register for CS 0 */
#define SMC_PULSE0 	(0x0004) 	/**<  Pulse Register for CS 0 */
#define SMC_CYCLE0 	(0x0008) 	/**<  Cycle Register for CS 0 */
#define SMC_CTRL0 	(0x000C) 	/**<  Control Register for CS 0 */

#define WDOG_NAME			"wd"
#define WDOG_MAJOR			241 

//#define IOCTL_INIT		0x6b06 //init port 
#define IOCTL_EN_WD	     _IOW(WDOG_MAJOR, 1, unsigned long)
#define IOCTL_DIS_WD      _IOW(WDOG_MAJOR, 2, unsigned long)
#define IOCTL_FEED_WD    _IOW(WDOG_MAJOR, 3, unsigned long)
#define IOCTL_SET_TIMER   _IOW(WDOG_MAJOR, 4, unsigned long)
#define AT91_WD_MODE     0xFFFFFD08
#define AT91_WD_VALUE    0x01
#define AT91_RSTC_MRX	(0xfffffd08 - AT91_BASE_SYS)

#define WDOG_TIMER_DELAY 	200			// 100 ms	




int at91_wdog_open(struct inode *inode, struct file *filp); 
int at91_wdog_release(struct inode *inode, struct file *filp); 
//static ssize_t at91_wdog_read(struct file * file, char __user *p_cUsrBuf, size_t count, loff_t *ppos);
int at91_wdog_ioctl (struct inode *inode, struct file *file, unsigned int uiCmd, unsigned long arg); 

static int wdog_hw_init(void);

void smc_reg_init(void);

#endif /* __AT91SAM9263_LED_H */

