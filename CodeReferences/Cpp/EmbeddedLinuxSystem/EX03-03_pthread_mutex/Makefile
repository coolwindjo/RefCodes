TARGET1 = pthread_mutex
LFLAGS = -pthread
NFS = /nfsroot
include ../common.mk
clean2:
	$(MAKE) clean
	@rm -f $(TARGET1) $(NFS)/$(TARGET1)
	@echo "clean finished!"
