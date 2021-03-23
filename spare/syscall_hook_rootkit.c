#include <linux/cred.h>
#include <linux/fs.h>
#include <linux/kallsyms.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joseph Boulis");

int counter=0;

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs*);

static sys_call_ptr_t *sys_call_table1;
static sys_call_ptr_t old_fork;

static asmlinkage long my_fork(const struct pt_regs *regs)
{
    counter++;
    if(counter%2){
    	    printk(KERN_INFO "counter = %d\n",counter);
    }
    return old_fork(regs);
}


inline void mywrite_cr0(unsigned long val)
{
    asm volatile("mov %0,%%cr0": "+r" (val), "+m" (__force_order));
}

static void enable_write_protection(void)
{
  unsigned long cr0 = read_cr0();
  set_bit(16, &cr0);
  mywrite_cr0(cr0);
}

static void disable_write_protection(void)
{
  unsigned long cr0 = read_cr0();
  clear_bit(16, &cr0);
  mywrite_cr0(cr0);
}


static int __init syscall_rootkit_init(void)
{
    sys_call_table1 = (sys_call_ptr_t *)kallsyms_lookup_name("sys_call_table");
    old_fork = sys_call_table1[__NR_clone];
    disable_write_protection();
    sys_call_table1[__NR_clone] = my_fork;
    enable_write_protection();

    printk(KERN_INFO "All lights are green...\n");
    return 0;
}

static void __exit syscall_rootkit_exit(void)
{
    disable_write_protection();
    sys_call_table1[__NR_clone] = old_fork;
    enable_write_protection();
}

module_init(syscall_rootkit_init);
module_exit(syscall_rootkit_exit);
