objs = start.o main.o

led.bin : $(objs)
	arm-linux-gnueabihf-ld -Ttext 0x87800000 -o led.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S led.elf $@

%.o : %.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<
%.o : %.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

.PHONY : clean
clean :
	rm *.o led.bin led.elf
