
/* Kernel headers, needed for e.g. KERN_ALERT. */
#include <linux/kernel.h>
/* Type definitions, needed for e.g. ssize_t. */
#include <linux/types.h>
/* Module headers, needed for various Kernel module-specific functions and globals. */
#include <linux/module.h>
/* Device headers, needed for managing a device. */
#include <linux/device.h>
/* File structure headers, needed for defining and creating a character device. */
#include <linux/fs.h>
/* Uaccess-headers, needed for copying data between user space and Kernel space. */
#include <asm/uaccess.h>/* for put_user */

#include <linux/uaccess.h>

#include <linux/version.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/seq_file.h>

#include <linux/proc_fs.h>

#define CIPHER_LEN 4096
#define CIPHER_KEY_LEN 128

#define MAX_DEVICES	2
dev_t device_number;
bool dynamic = true;
struct class *my_class;
static struct cdev my_cdev[MAX_DEVICES];
static int Major;


/* Function prototype for the rc4 based encryption. */
void rc4(unsigned char * p, unsigned char * k, unsigned char * c,int l);

/* Initialize memory for the message. */
static unsigned char key[CIPHER_KEY_LEN] = {0};

static unsigned char encrypted_data[CIPHER_LEN] = {0};

static unsigned char decrypted_data[CIPHER_LEN] = {0};

static unsigned char data_buffer[CIPHER_LEN] = {0};

#define DEVICE_NAME "cipher"


static ssize_t write_dev_cipher_key(struct file *file, const char *buffer, size_t len, loff_t * off);
static ssize_t read_dev_cipher_key(struct file *filp, char *buff, size_t len, loff_t *off);
static int open_dev_cipher_key(struct inode *inod, struct file *fil);
static int write(struct seq_file *m,void *v);
static int write1(struct seq_file *m,void *v);
static int release_dev_cipher_key(struct inode *inodep, struct file *filep);

static struct file_operations fops_cipher_key = {
  .read = seq_read,
  .write = write_dev_cipher_key,
  .open = open_dev_cipher_key,
  .release = release_dev_cipher_key
};

static unsigned long buffer_size = 0;

static ssize_t write_dev_cipher_key(struct file *file, const char *buffer, size_t len, loff_t * off)
{

	if ( len > CIPHER_KEY_LEN)	{
		buffer_size = CIPHER_KEY_LEN;
	}
	else	{
		buffer_size  = len;
	}

	memset(key,0,buffer_size);
	if ( copy_from_user(key, buffer, buffer_size ) ) {
		return -EFAULT;
	}
	single_open(file,write,NULL);
	printk(KERN_INFO "write_dev_cipher: write %lu bytes\n", buffer_size);

	return buffer_size;
}

static ssize_t read_dev_cipher_key(struct file *filp, char *buff, size_t len, loff_t *off)
{
    static char *procfs_buffer = "Go away silly one, you cannot see my key >-:\n";
    static unsigned long procfs_buffer_size = sizeof(procfs_buffer );
    if ( copy_to_user(key, buff, sizeof(key)) ) {
		return -EFAULT;
	}
	return 0;
}

static int open_dev_cipher_key(struct inode *inod, struct file *fil)
{
    /* If there is no encryption key, return an invalid argument error. */
/*	if (key == NULL) {
		printk(KERN_NOTICE "User tried to use the device when there was no encryption key present.");
		return -EINVAL;
	}*/

	single_open(fil,write1,NULL);

	return 0;
}

static int write1(struct seq_file *m,void *v){
	seq_printf(m,"%s\n","Go away silly one, you cannot see my key >-:");
}

static int write(struct seq_file *m,void *v){
	seq_printf(m,"%s\n",key);
}
/* This is called when a process closes the character device file. */
static int release_dev_cipher_key(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "cryptor: Device closed succesfully.\n");
	return 0;

}

static ssize_t write_dev_cipher(struct file *file, const char *buffer, size_t len, loff_t * off);
static int open_dev_key(struct inode *inod, struct file *fil);
static int write2(struct seq_file *m,void *v);
static int release_dev_key(struct inode *inodep, struct file *filep);

static int open_dev_key_1(struct inode *inod, struct file *fil);
static int write3(struct seq_file *m,void *v);
static int release_dev_key_1(struct inode *inodep, struct file *filep);



static struct file_operations fops_cipher_1 = {
  .read = seq_read,
  .write = write_dev_cipher,
  .open = open_dev_key_1,
  .release = release_dev_key_1
};


static struct file_operations fops_cipher = {
  .read = seq_read,
  .write = write_dev_cipher,
  .open = open_dev_key,
  .release = release_dev_key
};


static ssize_t write_dev_cipher(struct file *file, const char *buffer, size_t len, loff_t * off)
{
		buffer_size = CIPHER_LEN;
	if ( len > CIPHER_LEN)	{
		buffer_size = CIPHER_LEN;
	}
	else	{
		buffer_size = len;
	}

        memset(data_buffer,0,buffer_size);

	if ( copy_from_user(data_buffer, buffer, buffer_size) ) {
		return -EFAULT;
	}

	printk(KERN_INFO "write_dev_cipher: write %lu bytes\n", buffer_size);

	return buffer_size;
}


static int write2(struct seq_file *m,void *v){
	seq_printf(m,"%s\n",encrypted_data);
	return 0;
}

static int open_dev_key(struct inode *inod, struct file *fil)
{
    /* If there is no encryption key, return an invalid argument error. */
/*	if (key == NULL) {
		printk(KERN_NOTICE "User tried to use the device when there was no encryption key present.");
		return -EINVAL;
	}*/
	single_open(fil,write2,NULL);

	return 0;
}

/* This is called when a process closes the character device file. */
static int release_dev_key(struct inode *inodep, struct file *filep)
{	
	memset(encrypted_data,0,CIPHER_LEN);
	printk(KERN_INFO "data_buffer = %s and size =%d\n",data_buffer,sizeof(data_buffer));
    rc4(data_buffer,key,encrypted_data,sizeof(data_buffer));
	printk(KERN_INFO "Device closed succesfully.\n");
	return 0;
}


static int write3(struct seq_file *m,void *v){
	memset(decrypted_data,0,CIPHER_LEN);
    rc4( encrypted_data,key,decrypted_data,sizeof(encrypted_data));
	seq_printf(m,"%s\n",decrypted_data);
	return 0;
}
static int open_dev_key_1(struct inode *inod, struct file *fil)
{
    /* If there is no encryption key, return an invalid argument error. */
/*	if (key == NULL) {
		printk(KERN_NOTICE "User tried to use the device when there was no encryption key present.");
		return -EINVAL;
	}*/    
	single_open(fil,write3,NULL);

	return 0;
}
/* This is called when a process closes the character device file. */
static int release_dev_key_1(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Device closed succesfully.\n");
	return 0;
}

/*
 * This function is called when the module is loaded
 */
int main(void)
{
    int retval;
       retval = alloc_chrdev_region(&device_number, 0, MAX_DEVICES, "cipher");
    if (!retval) {
	    int major = MAJOR(device_number);
	    printk("major = %d",major);
        cdev_init(&my_cdev[0], &fops_cipher);
        cdev_add(&my_cdev[0], MKDEV(major,0), 1);
        cdev_init(&my_cdev[1], &fops_cipher_key);
        cdev_add(&my_cdev[1], MKDEV(major,1), 1);
    }

    struct proc_dir_entry *entry;
    entry = proc_create("cipher",0777,NULL,&fops_cipher_1);
    if(!entry){
	    return -1;
    }
    else{
	    printk(KERN_INFO "proc file created successfully\n");
    }

    struct proc_dir_entry *entry1;
    entry1 = proc_create("cipher_key",0777,NULL,&fops_cipher_key);
    if(!entry1){
	    return -1;
    }
    else{
	    printk(KERN_INFO "proc file created successfully\n");
    }

	return 0;
}

/*
 * This function is called when the module is unloaded
 */
void exit(void)
{
  /*
   * Unregister the device
   */
  unregister_chrdev(Major, DEVICE_NAME);
}


void rc4(unsigned char * p, unsigned char * k, unsigned char * c,int l)
{
        unsigned char s [256];
        unsigned char t [256];
        unsigned char temp;
        unsigned char kk;
        int i,j,x;
        for ( i  = 0 ; i  < 256 ; i ++ )
        {
                s[i] = i;
                t[i]= k[i % 4];
        }
        j = 0 ;
        for ( i  = 0 ; i  < 256 ; i ++ )
        {
                j = (j+s[i]+t[i])%256;
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
        }

        i = j = -1;
        for ( x = 0 ; x < l ; x++ )
        {
                i = (i+1) % 256;
                j = (j+s[i]) % 256;
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
                kk = (s[i]+s[j]) % 256;
                c[x] = p[x] ^ s[kk];
        }
}

module_init(main);
module_exit(exit);
MODULE_LICENSE("GPL");
