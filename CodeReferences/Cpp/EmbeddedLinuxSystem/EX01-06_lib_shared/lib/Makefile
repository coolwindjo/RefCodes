TARGET = libmycal.so
LINK12 = $(TARGET).1.2
LINK1 = $(TARGET).1
OBJS = plus.o minus.o
CC = arm-linux-gnueabihf-gcc
CFLAGS = -c -fPIC
NFS = /nfsroot

all: $(TARGET)
	sudo cp -a $(LINK12) $(LINK1)  $(NFS)
	@echo "build finished!"
$(TARGET): $(LINK12) $(LINK1)
	ln -s $(LINK12) $(TARGET)
$(LINK1): $(LINK12)
	ln -s $(LINK12) $(LINK1)
$(LINK12): $(OBJS)
	$(CC) -shared -Wl,-soname,$(LINK1) -o $(LINK12) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) $<
clean:
	@rm -f $(TARGET) $(OBJS) $(LINK1) $(LINK12)
	@rm $(NFS)/$(LINK12) $(NFS)/$(LINK1)
	@echo "clean finished!"
