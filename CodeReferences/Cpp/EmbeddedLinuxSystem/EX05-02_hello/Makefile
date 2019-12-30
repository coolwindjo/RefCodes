NFS = /nfsroot
TARGET = hello

obj-m := $(TARGET).o

KERNELDIR := ~/work/linux
PWD := $(shell pwd)


all: $(TARGET)
	sudo cp $(TARGET).ko $(NFS)

$(TARGET):
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -f $(NFS)/$(TARGET).ko
	rm -f *.o *.ko *.mod.c modules.order Module.symbers
	rm -f .*.*.cmd .*.*.*.cmd
	rm -rf .tmp_versions
	@echo "clean finished!"
