all: hello
	@echo "build finished!"
hello: main.o func.o
	arm-linux-gnueabihf-gcc -o hello main.o func.o
main.o: main.c
	arm-linux-gnueabihf-gcc -c main.c
func.o: func.c
	arm-linux-gnueabihf-gcc -c func.c
clean:
	@rm -f hello main.o func.o
	@echo "clean finished!"
