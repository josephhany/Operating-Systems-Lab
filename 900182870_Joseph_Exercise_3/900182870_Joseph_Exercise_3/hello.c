#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_AUTHOR("Joseph H. Boulis");

static int num = 1;
static char *str = "Hello World CSCE-3402 :)";

module_param(num, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(num, "An integer");
module_param(str, charp, 0000);
MODULE_PARM_DESC(str, "A character string");


static int __init hello_init(void)
{
	int i;
	
	//printk(KERN_INFO "num is an integer: %d\n", num);
	

	for (i = 0; i < num; i++)
	{
		printk(KERN_INFO "%s\n", str);
	}

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Bye bye CSCE-3402 :)\n");
}

module_init(hello_init);
module_exit(hello_exit);