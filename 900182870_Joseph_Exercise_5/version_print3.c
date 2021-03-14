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
	
	int j=0;


//	for(int i=0;i<16;i++){
//		address[i]=read_buffer[0];
//	}

	while(read_buffer[0]!=c){

			buf[j]=read_buffer[0];
			j++;
			kfree(read_buffer);
			read_buffer = kmalloc(1024,GFP_DMA|GFP_KERNEL);
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

	while(strstr(funct_name,"sys_call_table")==NULL){
		//printk(KERN_INFO "%s\n", funct_name);

		memset(address,0,1024);
		memset(funct_name,0,1024);

		int i;
		for(i=0;i<16;i++){		
			memset(read_buffer,0,1024);
			ret=vfs_read(mf->f,read_buffer,1,&mf->pos);	
			address[i]=read_buffer[0];
		}

		for(i=0;i<3;i++){			
			memset(read_buffer,0,1024);
			ret=vfs_read(mf->f,read_buffer,1,&mf->pos);
		}
		
		//mf->pos += 3;

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
	struct myfile *file;
//	file = open_file_for_read("/proc/version");
	file = open_file_for_read("/boot/System.map-4.19.0-13-amd64");
	char* read_buffer = kmalloc(1024,GFP_DMA|GFP_KERNEL);
//	read_from_file_until(file,read_buffer,1024,'(');
//	printk(KERN_INFO "%s\n", read_buffer);
	
	//close_file(file);


/*	struct myfile *file2;
	file2 = open_file_for_read("/boot/System.map-4.19.0-13-amd64");

	char* line = kmalloc(1024,GFP_DMA|GFP_KERNEL);
	read_from_file_until(file2,line,1024,'\n');
	printk(KERN_INFO "%s\n", line);*/

	int i;
//	for(i=0;i<1;i++){

	//int ret=1;	
	//while(ret>0){
		kfree(read_buffer);
		read_buffer=kmalloc(1024,GFP_DMA|GFP_KERNEL);
		memset(read_buffer,0,1024);
		char* address = kmalloc(1024,GFP_DMA|GFP_KERNEL);
		memset(address,0,1024);
		read_from_file_until_1(file,address,read_buffer,1024,'\n');
		printk(KERN_INFO "%s\n", read_buffer);
	//}
		//printk(KERN_INFO "%s\n", address);
//
//		char delim[] = " ";
//		char *ptr=strsep(read_buffer,delim);
//		while(ptr != NULL){
//			printk(KERN_INFO "%s\n", ptr);
//			ptr = strsep(NULL,delim);
//		}
//


//	}

	close_file(file);

//	while(  ){
	
	
//	}



	return 0;
}

static void __exit exit(void)
{
	printk(KERN_INFO "Bye bye CSCE-3402 :)\n");
}

module_init(main);
module_exit(exit);
MODULE_LICENSE("GPL");
