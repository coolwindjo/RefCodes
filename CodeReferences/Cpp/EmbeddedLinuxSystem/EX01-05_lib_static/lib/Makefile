TARGET = libmycal.a
OBJS = plus.o minus.o
CC = arm-linux-gnueabihf-gcc
AR = arm-linux-gnueabihf-ar
NM = arm-linux-gnueabihf-nm
CFLAGS = -c

all: $(TARGET)
	@echo "build finished!"
nm: $(TARGET)
	$(NM) $(TARGET)
$(TARGET): $(OBJS)
	$(AR) crv $(TARGET) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) $<
clean:
	@rm -f $(TARGET) $(OBJS)
	@echo "clean finished!"
