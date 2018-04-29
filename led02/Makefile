ARMGNU ?= arm-none-eabi

LINKFILE := linker.ld

TARGET := led02.img

# OBJECTS :=  start.o code.o
OBJECTS := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))
OBJECTS += $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))

all: $(TARGET)

$(TARGET) : output.elf
	$(ARMGNU)-objcopy output.elf -O binary $(TARGET)

output.elf: $(OBJECTS) $(LINKFILE)
	$(ARMGNU)-ld --no-undefined $(OBJECTS) -o output.elf -T $(LINKFILE)

%.o : %.c
	$(ARMGNU)-gcc -c $< -o $@

%.o : %.s
	$(ARMGNU)-as $< -o $@

clean:
	@rm -f *.o *.elf
	@rm -f $(TARGET)
