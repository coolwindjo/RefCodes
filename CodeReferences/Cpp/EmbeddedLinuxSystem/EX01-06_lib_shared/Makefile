TARGET = mycalDynamic
MAIN = main.o
CC = arm-linux-gnueabihf-gcc
AR = arm-linux-gnueabihf-ar
NM = arm-linux-gnueabihf-nm
LIB_DIR = lib
LIB = mycal
LIBNM = lib$(LIB).so
CFLAGS = -c
NFS = /nfsroot

all: $(TARGET)
	sudo cp $(TARGET) $(NFS)
	@echo "build finished!"
$(TARGET): $(MAIN) $(LIBNM)
	$(CC) -o $(TARGET) $(MAIN) -L$(LIB_DIR) -l$(LIB)
$(LIBNM):
	@cd $(LIB_DIR) && $(MAKE) all
%.o: %.c
	$(CC) $(CFLAGS) $<
clean:
	@rm -f $(TARGET) $(NFS)/$(TARGET)
	@cd $(LIB_DIR) && $(MAKE) clean
	@echo "clean finished!"
