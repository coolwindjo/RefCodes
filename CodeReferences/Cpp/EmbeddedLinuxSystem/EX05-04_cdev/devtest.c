#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define CDEV_ALLOC_DYNAMIC 1

unsigned int device_major = 241;
unsigned int device_minor_start = 0;
unsigned int device_minor_count = 4;
dev_t devt;

#if CDEV_ALLOC_DYNAMIC
struct cdev *my_cdev;
#else
struct cdev my_cdev;
#endif

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
};

static int __init device_init(void)
{
	int ret;

	printk("device_init\n");

	if(device_major) {
		devt = MKDEV(device_major, device_minor_start);
		ret = register_chrdev_region(devt, device_minor_count, "my_device");
	}
	else {
		ret = alloc_chrdev_region(&devt, device_minor_start, device_minor_count, "my_device");
		device_major = MAJOR(devt);
	}

	if(ret < 0) {
		printk("can't get major %d\n", device_major);
		return ret;
	}

#if CDEV_ALLOC_DYNAMIC
	/* Implement code */
	my_cdev = cdev_alloc();
	my_cdev->ops = &my_fops;
	my_cdev->owner = THIS_MODULE;
	//ret = /* Implement code */
	ret = cdev_add(my_cdev, devt, device_minor_count);
	if(ret) {
		printk("can't add device %d\n", devt);
		unregister_chrdev_region(devt, device_minor_count);
		return ret;
	}
#else
	//cdev_init(/* Implement code */);
	cdev_init(&my_cdev, &my_fops);
	my_cdev.owner = THIS_MODULE;
	//ret = /* Implement code */
	ret = cdev_add(&my_dev, devt, device_minor_count);
	if(ret) {
		printk("can't add device %d\n", devt);
		unregister_chrdev_region(devt, device_minor_count);
		return ret;
	}
#endif

	return 0;
}

static void __exit device_exit(void)
{
#if CDEV_ALLOC_DYNAMIC
	cdev_del(my_cdev);
#else
	cdev_del(&my_cdev);
#endif
	unregister_chrdev_region(devt, device_minor_count);
	printk("device_exit\n");
}

module_init(device_init);
module_exit(device_exit);

MODULE_LICENSE("GPL");

