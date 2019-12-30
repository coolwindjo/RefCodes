NFS = /nfsroot
TARGET = devtest

obj-m := $(TARGET).o

KERNELDIR := ~/work/linux
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	sudo cp $(TARGET).ko $(NFS)

clean:
	rm -f $(NFS)/$(TARGET).ko
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -f .*.*.cmd .*.*.*.cmd
	rm -rf .tmp_versions
	@echo "clean finished!"
