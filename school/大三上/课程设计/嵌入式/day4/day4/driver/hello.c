#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include "mycmd.h"
#include <linux/io.h>
int devnumber;
int major;
int minor;
struct cdev  *pdev;
MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhang san, 1111@163.com, 139xxxx");
MODULE_DESCRIPTION("THIS MODULE IS DRIVER FOR XXX CAMERA");


unsigned int *pcnt,*pcmp,*pcfg0,*pcfg1,*pcon,*pgpd0;


#define TCNTB0   0X139D000C  
#define TCMPB0   0X139D0010  
#define TCFG0   0X139D0000  
#define TCFG1   0X139D0004
#define TCON   0X139D0008
#define GPD0CON   0X114000A0

void pwm_init(void)
{
	unsigned int tmp;
	pcnt = ioremap(TCNTB0,4);
	pcmp = ioremap(TCMPB0,4);
	pcfg0 = ioremap(TCFG0,4);
	pcfg1 = ioremap(TCFG1,4);
	pcon = ioremap(TCON,4);
	pgpd0 = ioremap(GPD0CON,4);


/*
		GPD0CON = GPD0CON & ~0xf  | 2;
		TCFG0 = TCFG0 & ~(0xff);
		TCFG0 = TCFG0 | 155;
		TCFG1 = TCFG1 & ~(0xf);
		TCFG1 = TCFG1 | 4;
		
		
		TCON = TCON | (1<<3);
		TCON = TCON & ~(1<<2);
*/
}
void pwm_start(unsigned int freq)// 当前timer0 的工作时钟 === 100m/156/16 ===== 40064
{
	unsigned int tmp;

	//处理计数寄存器 比较寄存器
	
/*	
		TCON = TCON | (1<<1);

		TCON = TCON & ~(1<<1);
				TCON = TCON | (1<<0);
*/
}

void pwm_stop(void)
{
	unsigned int tmp;
/*
			TCON = TCON & ~(1<<0);
*/

}

void pwm_unmap(void)
{
	iounmap(pcnt);
	iounmap(pcmp);
	iounmap(pcfg0);
	iounmap(pcfg1);
	iounmap(pcon);
	iounmap(pgpd0);
}






int hello_open (struct inode *  inode, struct file *  f)
{
	printk("now , open\n");
	return 0;
}
int hello_release (struct inode * inode, struct file * f)
{
	printk("now, release\n");
	return 0;
}
ssize_t hello_read (struct file *f, char __user *ubuf, size_t size, loff_t *pos)
{
	printk("now, reading\n");
	return 0;
}
ssize_t hello_write (struct file *f, const char __user *ubuf, size_t size, loff_t *pos)
{
	printk("now, writing\n");
	return 0;
}
long hello_ioctl (struct file *f, unsigned int cmd , unsigned long para)
{
	switch(cmd)
	{
		case PLAY_TONE:
			
			printk("play tone, cmd = %u, para = %u\n",cmd, para);
			break;
		case PLAY_STOP:
			printk("stop, cmd = %u\n",cmd);
			
	}
	printk("now, control device\n");
	return 0;
}
struct file_operations  helloops = {
	.owner = THIS_MODULE, 
	.open = hello_open, 
	.release = hello_release,
	.read = hello_read,
	.write = hello_write,
	.unlocked_ioctl = hello_ioctl,
	
};


//模块入口
//int init_module(void)   
int hello_init(void )
{
	int ret;
	ret = alloc_chrdev_region(&devnumber, 100, 1,"hello");
	if(ret < 0)
	{
		printk("alloc failed\n");
		return -1;
	}
	printk("major = %d\n",MAJOR(devnumber));
	printk("minor = %d\n",MINOR(devnumber));	
	
	pdev = cdev_alloc();
	if(pdev == NULL)
		goto CDEV_ALLOC_ERROR;

	cdev_init(pdev,&helloops); 	

	ret = cdev_add(pdev, devnumber, 1);
	if(ret < 0) 
		goto CDEV_ADD_ERR;
	

	printk("hello,init\n");
	return 0;
CDEV_ADD_ERR:
	cdev_del(pdev);
CDEV_ALLOC_ERROR:
	unregister_chrdev_region(devnumber, 1);
	
	return -1;
}
//模块出口
//void cleanup_module(void) 
void hello_exit(void )
{
	
	cdev_del(pdev);
	unregister_chrdev_region(devnumber, 1);
	printk("hello, cleanup\n");
}

module_init(hello_init);
module_exit(hello_exit);
