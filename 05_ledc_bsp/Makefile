CROSS_COMPILE = arm-linux-gnueabihf-
TARGET = led

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

INCDIRS := imx6u \
		  bsp/clk \
		  bsp/led \
		  bsp/delay

SRCDIRS := project \
		  bsp/clk \
		  bsp/led \
		  bsp/delay

INCLUDE := $(patsubst %, -I %, $(INCDIRS))
SFILES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

CNDFILES = $(notdir $(CFILES))
SNDFILES = $(notdir $(SFILES))
COBJS := $(patsubst %.c, obj/%.o, $(CNDFILES))
SOBJS := $(patsubst %.s, obj/%.o, $(SNDFILES))
OBJS := $(SOBJS) $(COBJS)

VPATH := $(SRCDIRS)


$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -c $(INCLUDE) -o $@ $<
$(COBJS) : obj/%.o : %.c
	$(CC) -c $(INCLUDE) -o $@ $<

#start.o : project/start.s
#	arm-linux-gnueabihf-gcc -c -I project -o $@ $<

#bsp_clk.o : bsp/clk/bsp_clk.c
#	arm-linux-gnueabihf-gcc -c -I bsp/clk -I imx6u -o $@ $<

#bsp_led.o : bsp/led/bsp_led.c
#	arm-linux-gnueabihf-gcc -c -I bsp/led -I imx6u -o $@ $<

#bsp_delay.o : bsp/delay/bsp_delay.c
#	arm-linux-gnueabihf-gcc -c -I bsp/delay -o $@ $<

#main.o : project/main.c
#	arm-linux-gnueabihf-gcc -c -I project -I bsp/clk -I bsp/led -I bsp/delay -I imx6u -o $@ $<

.PHONY : clean
clean :
	rm $(OBJS) $(TARGET).elf $(TARGET).dis $(TARGET).bin

print : 
	@echo $(INCLUDE)
	@echo $(SFILES)
	@echo $(CFILES)
	@echo $(SNDFILES)
	@echo $(CNDFILES)
	@echo $(OBJS)