/* skeleton.c*/
#include <linux/module.h>  /* needed by all modules */ 
#include <linux/init.h>  /* needed for macros */  
#include <linux/kernel.h>  /* needed for debugging */ 
#include <linux/moduleparam.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */
#include <linux/cdev.h>
#include <linux/kdev_t.h>

static unsigned char value = 0;
module_param(value,ushort, 0);
void *map;

static char s_buffer[100];

static dev_t skeleton_dev;
static struct cdev skeleton_cdev;

static ssize_t skeleton_write(struct file *f, const char __user *buf, size_t sz, loff_t *off);
static ssize_t skeleton_read(struct file *f, char __user *buf, size_t sz, loff_t *off);
static int skeleton_release(struct inode *i, struct file *f);
static int skeleton_open(struct inode *i, struct file *f);

static struct file_operations skeleton_fops =
{ .read = skeleton_read, .write = skeleton_write, .open = skeleton_open,
		.release = skeleton_release };

static int __init skeleton_init(void)
{
	pr_info("Linux module ex2driver loaded\n");
	int status= alloc_chrdev_region(&skeleton_dev, 0, 1, "skeleton");
	if (status== 0)
	{
		cdev_init(&skeleton_cdev, &skeleton_fops);
		skeleton_cdev.owner= THIS_MODULE;
		status= cdev_add(&skeleton_cdev, skeleton_dev, 1);
	}
	map=ioremap(0xd6000000,0x100);
	if(map!=NULL)
	{
		pr_info("Coucou\n");
		//Pin output config
		writeb(0xFF,map+0x12);
	}
	else
	{
		pr_err("ioremap error\n");
	}
	return 0;
}
static void __exit skeleton_exit(void)
{
	pr_info("Linux module ex2driver unloaded\n");
	cdev_del(&skeleton_cdev);
	unregister_chrdev_region(skeleton_dev, 1);
	iounmap(map);
}

static int skeleton_open(struct inode *i, struct file *f)
{
	pr_info("skeleton: open operation... major:%d, minor:%d\n", imajor(i),
			iminor(i));
	if ((f->f_mode & (FMODE_READ | FMODE_WRITE)) != 0)
	{
		pr_info("skeleton: openedfor reading& writing...\n");
	}
	else if ((f->f_mode & FMODE_READ) != 0)
	{
		pr_info("skeleton: openedfor reading...\n");
	}
	else if ((f->f_mode & FMODE_WRITE) != 0)
	{
		pr_info("skeleton: openedfor writing...\n");
	}
	return 0; /* success*/

}

static int skeleton_release(struct inode *i, struct file *f)
{
	pr_info("skeleton: release operation...\n");
	return 0; /* success*/
}

static ssize_t skeleton_read(struct file *f, char __user *buf, size_t sz, loff_t *off)
{
	pr_info("skeleton: read operation not implemented");
}

static ssize_t skeleton_write(struct file *f, const char __user *buf, size_t sz, loff_t *off)
{
	int temp=0;
	ssize_t transferred = -EIO;
	ssize_t remaining = sizeof(s_buffer) - (ssize_t)(*off);
	if (remaining > sz)
	{
		if (copy_from_user(s_buffer+ *off, buf, sz))
		{
			transferred= -EFAULT;
		}
		else
		{
			transferred= sz;
			*off += sz;
		}
	}
	temp=((s_buffer[0]-0x30)*10)+s_buffer[1]-0x30;
	pr_info("temp=%d",temp);
	writeb(temp,map+0x10);
	pr_info("skeleton: write operation... written=%d\n", transferred);
	return transferred;
}

module_init( skeleton_init);
module_exit( skeleton_exit);

MODULE_AUTHOR("Alexandre Schnegg <alexandre.schnegg@master.hes-so.ch>");
MODULE_DESCRIPTION("Module ex2driver");
MODULE_LICENSE("GPL");
