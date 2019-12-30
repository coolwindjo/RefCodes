NFS = /nfsroot
TARGET = devtest
APP = apptest
CC = arm-linux-gnueabihf-gcc 
CFLA = -Wall

obj-m := $(TARGET).o

KERNELDIR := ~/work/linux
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CC) $(CFLA) -o $(APP) $(APP).c
	sudo cp $(TARGET).ko $(NFS)
	sudo cp $(APP) $(NFS)

clean:
	rm -f $(NFS)/$(APP)
	rm -f $(NFS)/$(TARGET).ko
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -f .*.*.cmd .*.*.*.cmd
	rm -rf .tmp_versions
	rm -f apptest
