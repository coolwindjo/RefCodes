TARGET = mycalStatic
MAIN = main.o
OBJS = plus.o minus.o
CC = arm-linux-gnueabihf-gcc
AR = arm-linux-gnueabihf-ar
NM = arm-linux-gnueabihf-nm
FOLDER = lib
LIB = mycal
LIBNM = lib$(LIB).a
CFLAGS = -c

all: $(TARGET)
	@echo "build finished!"
$(TARGET): $(MAIN) $(LIBNM)
	$(CC) -o $(TARGET) $(MAIN) -L$(FOLDER) -l$(LIB)
nm: $(LIBNM)
	$(NM) $(LIBNM) -L$(FOLDER)
$(LIBNM): #$(OBJS)
	cd $(FOLDER) && $(MAKE) all
	#$(AR) crv $(LIBNM) $(OBJS) -L$(FOLDER)
%.o: %.c
	$(CC) $(CFLAGS) $<
clean:
	@rm -f $(TARGET) $(OBJS) && cd $(FOLDER) && $(MAKE) clean
	@echo "clean finished!"
