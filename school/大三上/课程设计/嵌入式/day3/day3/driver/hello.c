#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
int devnumber;
int major;
int minor;
MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhang san, 1111@163.com, 139xxxx");
MODULE_DESCRIPTION("THIS MODULE IS DRIVER FOR XXX CAMERA");
//模块入口
//int init_module(void)   
int hello_init(void )
{
	int ret;
	ret = alloc_chrdev_region(&devnumber, 0, 1,"hello");
	if(ret < 0)
	{
		printk("alloc failed\n");
		return -1;
	}

	printk("hello,init\n");
	return 0;
}
//模块出口
//void cleanup_module(void) 
void hello_exit(void )
{
	printk("hello, cleanup\n");
}

module_init(hello_init);
module_exit(hello_exit);
