#include <linux/cred.h>
#include <linux/fs.h>
#include <linux/kallsyms.h>
#include <linux/module.h>

#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

#include <linux/slab.h>
#include <linux/gfp.h>

#include <linux/string.h>

MODULE_AUTHOR("Joseph H. Boulis");

int counter=0;

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs*);

static sys_call_ptr_t save_original_fork;
static sys_call_ptr_t *sys_tb;


static asmlinkage long my_fork(const struct pt_regs *regs)
{
    counter++;
    if(counter%10==0){
    	    printk(KERN_INFO "counter = %d\n",counter);
    }
    return save_original_fork(regs);
}

static int __init main(void)
{
    
    sys_tb = (sys_call_ptr_t *)kallsyms_lookup_name("sys_call_table");

    save_original_fork= sys_tb[__NR_clone];	

    //disable_write_protection
    unsigned long cr0 = read_cr0();
    clear_bit(16, &cr0);
    asm volatile("mov %0,%%cr0": "+r" (cr0), "+m" (__force_order));

   
    sys_tb[__NR_clone] = my_fork;

    //enable_write_protection 
    set_bit(16, &cr0);
    asm volatile("mov %0,%%cr0": "+r" (cr0), "+m" (__force_order));



    return 0;
}

static void __exit exit(void)
{
    //disable_write_protection
    unsigned long cr0 = read_cr0();
    clear_bit(16, &cr0);
    asm volatile("mov %0,%%cr0": "+r" (cr0), "+m" (__force_order));

    sys_tb[__NR_clone] = save_original_fork;

    //enable_write_protection 
    set_bit(16, &cr0);
    asm volatile("mov %0,%%cr0": "+r" (cr0), "+m" (__force_order));

}

module_init(main);
module_exit(exit);
MODULE_LICENSE("GPL");
