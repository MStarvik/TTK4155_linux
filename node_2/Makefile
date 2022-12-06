LDSCRIPT = sam/flash.ld
BOOTUP = sam/sam3x/source/exceptions.c sam/sam3x/source/startup_sam3x.c sam/sam3x/source/system_sam3x.c
MCUTYPE = __SAM3X8E__
# List all source files to be compiled; separate with space
SOURCE_FILES=$(BOOTUP) src/main.c src/uart/uart.c src/uart/printf-stdarg.c src/can/can_controller.c src/can/can_interrupt.c

# Feel free to ignore anything below this line
VPATH:= $(dir $(SOURCE_FILES))
BUILD_DIR := build
OBJS := $(patsubst %.c, $(BUILD_DIR)/%$(ARCH)$(DEBUG).o, $(notdir $(SOURCE_FILES)))
#Tools
CC:=arm-none-eabi-gcc
LD:=arm-none-eabi-gcc
AR:=arm-none-eabi-ar
AS:=arm-none-eabi-as

ELF=$(BUILD_DIR)/main.elf

LDFLAGS:= -T$(LDSCRIPT) -mthumb -mcpu=cortex-m3 -Wl,--gc-sections
CFLAGS:= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -g -std=c11 -MMD
CFLAGS+= -I/usr/arm-none-eabi/include -Isam -Isam/sam3x/include -Isam/sam3x/source -Isam/cmsis
CFLAGS+= -D $(MCUTYPE)

.DEFAULT_GOAL := $(ELF)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@
	#$(CC) -MM $(CFLAGS) $< > $@.d

$(BUILD_DIR)/%.o: %.s
	$(AS) $< -o $@

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: debug
debug: $(ELF)
	if pidof openocd; then killall -s 9 openocd; fi
	x-terminal-emulator -e openocd -f sam/openocd.cfg -c "program $(ELF) verify"
	sleep 5
	arm-eabi-gdb -tui -iex "target extended-remote localhost:3333" $(ELF)
	killall -s 9 openocd	

.PHONY: flash
flash: $(ELF)
	#./sam/write_bin.sh sam/openocd.cfg $(BUILD_DIR)/main.elf
	if pidof openocd; then killall -s 9 openocd; fi
	openocd -f sam/openocd.cfg -c "program ${BUILD_DIR}/main.elf verify reset exit"

# pull in dependencies
-include	$(OBJS:.o=.d)
