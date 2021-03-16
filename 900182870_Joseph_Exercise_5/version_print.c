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

#include <linux/string.h>
#include <linux/kallsyms.h>

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

	filp->pos=0;
	
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
	int ret = vfs_read(mf->f,read_buffer,1,&mf->pos);

	int i=0;	
	int j=0;
	while(read_buffer[0]!='('){
			if(read_buffer[0]==' ' && i<2){
				memset(buf,0,1024);
				j=0;
				i++;
			}
			buf[j]=read_buffer[0];
			j++;
			memset(read_buffer,0,1024);
			ret=vfs_read(mf->f,read_buffer,1,&mf->pos);	
	}

	set_fs(fs);
	return ret;
}

volatile int read_from_file_until_1(struct myfile * mf, char * address, char * funct_name, unsigned long vlen, char c){
	mm_segment_t fs = get_fs();
	mf->fs=fs;
	set_fs(get_ds());

	int ret;
	char* read_buffer = kmalloc(1024,GFP_DMA|GFP_KERNEL);

	while(strcmp(funct_name,"sys_call_table")!=0){

		memset(address,0,1024);
		memset(funct_name,0,1024);

		int i;
		for(i=0;i<16;i++){		
			memset(read_buffer,0,1024);
			ret=vfs_read(mf->f,read_buffer,1,&mf->pos);	
			address[i]=read_buffer[0];
		}
		
		mf->pos += 3;

		memset(read_buffer,0,1024);
		ret=vfs_read(mf->f,read_buffer,1,&mf->pos);	
	
		i=0;
		while(read_buffer[0] != '\n'){
			funct_name[i] = read_buffer[0];
			i++;
			memset(read_buffer,0,1024);
			ret=vfs_read(mf->f,read_buffer,1,&mf->pos);	
		}
	}

	set_fs(fs);
	return ret;
}


void close_file (struct myfile * mf){
	filp_close(mf->f,NULL);
}

static int __init main(void)
{

	char first_part[100]="/boot/System.map-";
	first_part[strlen(first_part)]='\0';


//	printk(KERN_INFO "version:%s\n", first_part);

	char* version = kmalloc(1024,GFP_DMA|GFP_KERNEL);
	struct myfile *file1;
	file1 = open_file_for_read("/proc/version");
	read_from_file_until(file1,version,1024,'\n');
//	printk(KERN_INFO "version:%s\n", version);
	close_file(file1);


	char version_part[40];
	strcpy(version_part,version);
	version_part[strlen(version_part)]='\0';

	int c=strlen(first_part);
	int p=c;
	for(;p<strlen(version_part)+c-1;p++){
		first_part[p]=version_part[p-c+1];
	}

	first_part[strlen(first_part)-1]='\0';

	printk(KERN_INFO "version complete:%s\n",first_part);
//	printk(KERN_INFO "version complete:/boot/System.map-4.19.0-13-amd64\n");




	struct myfile *file;
//	file = open_file_for_read("/boot/System.map-4.19.0-13-amd64");
	file = open_file_for_read(first_part);

	char* read_buffer = kmalloc(1024,GFP_DMA|GFP_KERNEL);


	int i;
	kfree(read_buffer);
	read_buffer=kmalloc(1024,GFP_DMA|GFP_KERNEL);
	memset(read_buffer,0,1024);
	char* address = kmalloc(1024,GFP_DMA|GFP_KERNEL);
	memset(address,0,1024);
	read_from_file_until_1(file,address,read_buffer,1024,'\n');
	
	printk(KERN_INFO "%s : ", read_buffer);
	printk(KERN_INFO "%s\n", address);


	close_file(file);

	sys_call_ptr_t *sys_call_table;
	char *sys_call_table_addr;
	unsigned long ul;
	sscanf(address,"%lx",&ul);
	sys_call_table = (sys_call_ptr_t *)ul;
	printk(KERN_INFO "fork address : %px\n",sys_call_table[__NR_fork]);

	return 0;
}

static void __exit exit(void)
{
	printk(KERN_INFO "Bye bye CSCE-3402 :)\n");
}

module_init(main);
module_exit(exit);
MODULE_LICENSE("GPL");
