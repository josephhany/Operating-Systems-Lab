#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

#include <linux/slab.h>
#include <linux/gfp.h>

MODULE_AUTHOR("Joseph H. Boulis");

struct myfile{
	struct file *f;
	mm_segment_t fs;
	loff_t pos;
};

struct myfile * open_file_for_read(char * filename){
	struct myfile *filp=kmalloc(1024,GFP_DMA|GFP_KERNEL);
	struct file *f=NULL;
	f=filp_open(filename,O_RDWR,0);
	filp->f=f;

	mm_segment_t fs=get_fs();
	filp->fs=fs;

	set_fs(get_ds());
	set_fs(fs);

	
	int error=0;

	if(IS_ERR(f)){
		error = PTR_ERR(f);
		return NULL;
	}
	return filp;
}

volatile int read_from_file_until(struct myfile * mf, char * buf, unsigned long vlen, char c){
	mm_segment_t fs = get_fs();
	mf->fs=fs;
	set_fs(get_ds());

	char* read_buffer = kmalloc(1024,GFP_DMA|GFP_KERNEL);
	int ret = vfs_read(mf->f,read_buffer,vlen,&mf->pos);

	int i=0;
	int j=0;
	while(read_buffer[i]!=c){
		if(read_buffer[i]==' ')j=0;
		buf[j]=read_buffer[i];
		i++;
		j++;
	}

	set_fs(fs);
	return ret;
}

void close_file (struct myfile * mf){
	filp_close(mf->f,NULL);
}

static int __init main(void)
{
	struct myfile *file;
	file = open_file_for_read("/proc/version");
	printk(KERN_INFO "opened successfully\n");

	char* read_buffer = kmalloc(1024,GFP_DMA|GFP_KERNEL);
	read_from_file_until(file,read_buffer,1024,'(');
	printk(KERN_INFO "%s\n", read_buffer);


	close_file(file);
	printk(KERN_INFO "closed successfully\n");
	return 0;
}

static void __exit exit(void)
{
	printk(KERN_INFO "Bye bye CSCE-3402 :)\n");
}

module_init(main);
module_exit(exit);
MODULE_LICENSE("GPL");