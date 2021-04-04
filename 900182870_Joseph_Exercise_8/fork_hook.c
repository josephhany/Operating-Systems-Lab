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

#include<linux/proc_fs.h>
#include<linux/sched.h>
#include<linux/uaccess.h>
#include<linux/seq_file.h>


int counter=0;

//-------------------------------------------
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fcntl.h>

/*static void write_file(char *filename, char *data)
{
  struct file *file;
  loff_t pos = 0;
  int fd;

  mm_segment_t old_fs = get_fs();
  set_fs(KERNEL_DS);

  fd = sys_open(filename, O_WRONLY|O_CREAT, 0644);
  if (fd >= 0) {
    sys_write(fd, data, strlen(data));
    file = fget(fd);
    if (file) {
      vfs_write(file, data, strlen(data), &pos);
      fput(file);
    }
    sys_close(fd);
  }
  set_fs(old_fs);
}*/
//--------------------------------

static char *str = NULL;

static int my_proc_show(struct seq_file *m,void *v){
	//seq_printf(m,"hello from proc file\n");
	seq_printf(m,"counter = %d\n",counter);
	//seq_printf(m,"%s\n",str);
	return 0;
}

static ssize_t my_proc_write(struct file* file,const char __user *buffer,size_t count,loff_t *f_pos){
	char *tmp = kzalloc((count+1),GFP_KERNEL);
	if(!tmp)return -ENOMEM;
	if(copy_from_user(tmp,buffer,count)){
		kfree(tmp);
		return EFAULT;
	}
	kfree(str);
	str=tmp;
	return count;
}

static int my_proc_open(struct inode *inode,struct file *file){
	return single_open(file,my_proc_show,NULL);
}

static struct file_operations my_fops={
	.owner = THIS_MODULE,
	.open = my_proc_open,
	.release = single_release,
	.read = seq_read,
	.llseek = seq_lseek,
	.write = my_proc_write
};


//--------------------------------



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
 	struct proc_dir_entry *entry;
	entry = proc_create("fork_count",0777,NULL,&my_fops);
	if(!entry){
		return -1;	
	}else{
		printk(KERN_INFO "create proc file successfully\n");
	}

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
	
	remove_proc_entry("fork_count",NULL);

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

//-------------------------------



