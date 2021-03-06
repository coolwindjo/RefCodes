#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <asm/io.h>

#include "my_ioctl.h"

#define MAX_BUF 26

static unsigned int device_major = 241;
static unsigned int device_minor_start = 0;
static unsigned int device_minor_count = 4;
static dev_t devt;
static struct cdev *my_cdev;

static char rbuf[MAX_BUF];
static char wbuf[MAX_BUF];

#define PAD_PHY_BASE		0x11000000
#define PAD_PHY_SIZE		0x1000
#define GPM4CON			0x2e0
#define GPM4DAT			0x2e4

static volatile unsigned long pad_base;
static struct resource *pad_mem;

static void led_off(void)
{
	/* Implement code */
        iowrite32(ioread32((void *)(pad_base+GPM4DAT)) & ~(0x3<<4), (void *)(pad_base+GPM4DAT));
}

static void led_init(void)
{
	/* Implement code */
        iowrite32((ioread32((void *)(pad_base+GPM4CON)) & ~(0xff<<16)) | (0x11<<16), (void *)(pad_base+GPM4CON));
	led_off();
}

static void led_on(void)
{
	/* Implement code */
        iowrite32(ioread32((void *)(pad_base+GPM4DAT)) | (0x3<<4), (void *)(pad_base+GPM4DAT));
}


static long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret = 0, data;

	switch(cmd) {
		case MY_IOCTL_CMD_ONE:
			printk("devtest: MY_IOCTL_CMD_ONE\n");
			break;
		case MY_IOCTL_CMD_TWO:
			if(copy_from_user(&data, (int *)arg, sizeof(int))) {
				return -EFAULT;
			}
			printk("devtest: MY_IOCTL_CMD_TWO(%d)\n", data);
			ret = 2;
			break;
		case MY_IOCTL_CMD_LED_ON:
			printk("devtest: MY_IOCTL_CMD_LED_ON\n");
			led_on();
			break;
		case MY_IOCTL_CMD_LED_OFF:
			printk("devtest: MY_IOCTL_CMD_LED_OFF\n");
			led_off();
			break;
		default:
			printk("devtest: unknown command\n");
			ret = -EINVAL;
			break;
	}

	return ret;
}

static ssize_t device_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t rlen; 

	printk("devtest: device_read (minor = %d)\n", iminor(filp->f_path.dentry->d_inode));
	rlen = MAX_BUF;
	if(rlen > count) {
		rlen = count;
	}
	if(copy_to_user(buf, rbuf, rlen)) {
		return -EFAULT;
	}
	printk("devtest: read %d bytes\n", rlen);

	return rlen;
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t wlen;

	printk("devtest: device_write (minor = %d)\n", iminor(filp->f_path.dentry->d_inode));
	wlen = MAX_BUF;
	if(wlen > count) {
		wlen = count;
	}
	if(copy_from_user(wbuf, buf, wlen)) {
		return -EFAULT;
	}
	printk("devtest: wrote %d bytes\n", wlen);
	
	return wlen;
}

static int device_open(struct inode *inode, struct file *filp)
{
	printk("devtest: device_open (minor = %d)\n", iminor(inode));
	return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
	printk("devtest: device_release\n");
	return 0;
}


static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = device_ioctl,
	.open = device_open,
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
		goto err1;
	}

	/* init buffers */
	for(i=0; i<MAX_BUF; i++) rbuf[i] = 'A' + i;
	for(i=0; i<MAX_BUF; i++) wbuf[i] = 0;

	//pad_mem = request_mem_region(/* Implement code */);
	pad_mem = request_mem_region(PAD_PHY_BASE, PAD_PHY_SIZE, "pad-base");
	if (pad_mem == NULL) {
		printk("devtest: failed to get memory region\n");
		ret = -EIO;
		goto err2;
	}

	//pad_base = (unsigned long)ioremap(/* Implement code */);
	pad_base = (unsigned long)ioremap(PAD_PHY_BASE, PAD_PHY_SIZE);
	if (pad_base == 0) {
		printk("devtest: led to ioremap() region\n");
		ret = -EIO;
		goto err3;
	}

	led_init();

	return 0;

err3:
	release_mem_region(PAD_PHY_BASE, PAD_PHY_SIZE);
err2:
	cdev_del(my_cdev);
err1:
	unregister_chrdev_region(devt, device_minor_count);

	return ret;
}

static void __exit device_exit(void)
{
	iounmap((void *)pad_base);
	release_mem_region(PAD_PHY_BASE, PAD_PHY_SIZE);
	cdev_del(my_cdev);
	unregister_chrdev_region(devt, device_minor_count);

	printk("devtest: device_exit\n");
}

module_init(device_init);
module_exit(device_exit);

MODULE_LICENSE("GPL");
