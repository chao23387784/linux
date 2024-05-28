CROSS_COMPILE = arm-linux-gnueabihf-
TARGET = led

LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
CC = $(CROSS_COMPILE)gcc

INCDIRS = imx6u \
		  bsp/clk \
		  bsp/led \
		  bsp/delay \
		  bsp/beep \
		  bsp/key \
		  bsp/gpio \
		  bsp/int \
		  bsp/exti 

SRCDIRS = project \
		  bsp/clk \
		  bsp/led \
		  bsp/delay \
		  bsp/beep \
		  bsp/key \
		  bsp/gpio \
		  bsp/int \
		  bsp/exti  

INCLUDE = $(patsubst %,-I %,$(INCDIRS))
SFILES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SNDFILES = $(notdir $(SFILES))
CNDFILES = $(notdir $(CFILES))

SOBJS = $(patsubst %.s,obj/%.o,$(SNDFILES))
COBJS = $(patsubst %.c,obj/%.o,$(CNDFILES))
OBJS = $(SOBJS) $(COBJS)

VPATH = $(SRCDIRS)

$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -c $(INCLUDE) -O2 -o $@ $<
$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c $(INCLUDE) -O2 -o $@ $<

.PHONY : clean
clean :
	rm $(OBJS) $(TARGET).elf $(TARGET).dis $(TARGET).bin

print : 
	@echo $(INCLUDE)
	@echo $(SFILES)
	@echo $(CFILES)
	@echo $(SNDFILES)
	@echo $(CNDFILES)
	@echo $(SOBJS)
	@echo $(COBJS)
	@echo $(OBJS)