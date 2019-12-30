TARGET = hello
OBJS = main.o func.o
CC = arm-linux-gnueabihf-gcc
CFLAGS = -c

all: $(TARGET)
	@echo "build finished!"

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< 

clean:
	@rm -f $(TARGET) $(OBJS)
	@echo "clean finished!"

