objs := start.o main.o
ld := arm-linux-gnueabihf-ld
gcc := arm-linux-gnueabihf-gcc
objcopy := arm-linux-gnueabihf-objcopy
objdump := arm-linux-gnueabihf-objdump

ledc.bin : $(objs)
	$(ld) -Timx6u