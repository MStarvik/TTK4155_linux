# List all source files to be compiled; separate with space
SOURCE_FILES := src/main.c src/usart_driver/usart_driver.c src/xmem_driver/xmem_driver.c src/adc_driver/adc_driver.c src/oled_driver/oled_driver.c src/oled_buffer/oled_buffer.c src/user_interface/user_interface.c src/fonts/fonts.c src/spi_driver/spi_driver.c src/mcp2515_driver/mcp2515_driver.c src/can_driver/can_driver.c src/joystick/joystick.c

# Set this flag to "yes" (no quotes) to use JTAG; otherwise ISP (SPI) is used
PROGRAM_WITH_JTAG := yes

# Feel free to ignore anything below this line
PROGRAMMER := atmelice_isp
ifeq ($(PROGRAM_WITH_JTAG), yes)
	PROGRAMMER := atmelice
endif

BUILD_DIR := build
TARGET_CPU := atmega162
TARGET_DEVICE := m162

CC := avr-gcc
CFLAGS := -O -std=c11 -mmcu=$(TARGET_CPU) -ggdb

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

.DEFAULT_GOAL := $(BUILD_DIR)/main.hex
	
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.hex: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/a.out
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/a.out $(BUILD_DIR)/main.hex

.PHONY: flash
flash: $(BUILD_DIR)/main.hex
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U flash:w:$(BUILD_DIR)/main.hex:i

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: erase
erase:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -e
	
.PHONY: debug
debug:
	if pgrep avarice; then pkill avarice; fi
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U flash:w:$(BUILD_DIR)/main.hex:i
	alacritty -e avarice --edbg --ignore-intr :4242
	sleep 2
	avr-gdb -tui -iex "target remote localhost:4242" $(BUILD_DIR)/a.out
	killall -s 9 avarice