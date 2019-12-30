#include <linux/ioctl.h>

#define MY_IOCTL_MAGIC 'k'

#define MY_IOCTL_CMD_ONE	_IO(MY_IOCTL_MAGIC, 1)
#define MY_IOCTL_CMD_TWO	_IOW(MY_IOCTL_MAGIC, 2, int)
#define MY_IOCTL_CMD_THREE	_IO(MY_IOCTL_MAGIC, 3)

