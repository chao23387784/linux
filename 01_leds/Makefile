led.bin : led.s
	arm-linux-gnueabihf-gcc -g -c led.s -o led.o
	arm-linux-gnueabihf-ld -Ttext 0x87800000 led.o -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin
	arm-linux-gnueabihf-objdump -D led.elf > eld.dis

clean : 
	rm -rf *.o led.bin led.elf led.dis



name = zc
curname := $(name)
curname += zhangchao
name = zhangchao

.PHONY:print

print:
	@echo curname = $(curname)