NFS = /nfsroot
TARGET = devtest
APP = apptest
TEST_SCRT = test.sh
CC = arm-linux-gnueabihf-gcc 
CFLA = -Wall
APP_TEST = "cat test.sh\ninsmod devtest.ko\n./apptest R 10\n./apptest R 30\n./apptest W 1234567890\n./apptest W 123456789012345678901234567890\nrmmod devtest.ko"

obj-m := $(TARGET).o

KERNELDIR := ~/work/linux
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CC) $(CFLA) -o $(APP) $(APP).c
	echo $(APP_TEST) > $(TEST_SCRT)
	sudo cp $(TARGET).ko $(NFS)
	sudo cp $(APP) $(NFS)
	sudo cp $(TEST_SCRT) $(NFS)

clean:
	rm -f $(TEST_SCRT) $(NFS)/$(TEST_SCRT)
	rm -f $(APP) $(NFS)/$(APP)
	rm -f $(NFS)/$(TARGET).ko
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -f .*.*.cmd .*.*.*.cmd
	rm -rf .tmp_versions
