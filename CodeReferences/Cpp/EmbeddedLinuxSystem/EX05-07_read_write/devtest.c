#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#define MAX_BUF 26
static char rbuf[MAX_BUF];
static char wbuf[MAX_BUF];

static unsigned int device_major = 241;
static unsigned int device_minor_start = 0;
static unsigned int device_minor_count = 4;
static dev_t devt;
static struct cdev *my_cdev;

static ssize_t device_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t rlen; 

	printk("devtest: device_read (minor = %d)\n", iminor(filp->f_path.dentry->d_inode));

	/* Implement code */
	//2
	if (MAX_BUF < count) {
		count = MAX_BUF;
	}
	rlen = count;

	//3
	if (copy_to_user(buf, rbuf, rlen) == -EFAULT) {
		//4
		return -EFAULT;
	}

	printk("devtest: read %d bytes\n", rlen);

	return rlen;
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t wlen;

	printk("devtest: device_write (minor = %d)\n", iminor(filp->f_path.dentry->d_inode));

	/* Implement code */
	//2
	if (MAX_BUF < count) {
		count = MAX_BUF;
	}
	wlen = count;

	//3
	if (copy_from_user(wbuf, buf, wlen) == -EFAULT) {
		//4
		return -EFAULT;
	}

	printk("devtest: wrote %d bytes\n", wlen);
	
	return wlen;
}

static int device_open(struct inode *inode, struct file *filp)
{
	printk("device_open (minor = %d)\n", iminor(inode));
	return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
	printk("devtest: device_release\n");
	return 0;
}


static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	/* Implement code */
	//1
	.read = device_read,
	.write = device_write,
	.release = device_release,
};

static int __init device_init(void)
{
	int ret, i;

	printk("devtest: device_init\n");

	devt = MKDEV(device_major, device_minor_start);
	ret = register_chrdev_region(devt, device_minor_count, "my_device");

	if(ret < 0) {
		printk("devtest: can't get major %d\n", device_major);
		return ret;
	}

	my_cdev = cdev_alloc();
	my_cdev->ops = &my_fops;
	my_cdev->owner = THIS_MODULE;
	ret = cdev_add(my_cdev, devt, device_minor_count);
	if(ret) {
		printk("devtest: can't add device %d\n", devt);
		unregister_chrdev_region(devt, device_minor_count);
		return ret;
	}

	/* init buffers */
	for(i=0; i<MAX_BUF; i++) rbuf[i] = 'A' + i;
	for(i=0; i<MAX_BUF; i++) wbuf[i] = 0;

	return 0;
}

static void __exit device_exit(void)
{
	cdev_del(my_cdev);
	unregister_chrdev_region(devt, device_minor_count);
	printk("devtest: device_exit\n");
}

module_init(device_init);
module_exit(device_exit);

MODULE_LICENSE("GPL");

