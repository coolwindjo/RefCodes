TARGET = hello
OBJS = main.o func.o
CC = arm-linux-gnueabihf-gcc
CFLAGS = -c

all: $(TARGET)
	@echo "build finished!"

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) $< 

func.o: func.c
	$(CC) $(CFLAGS) $< 

clean:
	@rm -f $(TARGET) $(OBJS)
	@echo "clean finished!"

