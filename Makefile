FREERTOS_SOURCE_DIR = FreeRTOS_v8.2.3
APPLICATION_SOURCE_DIR = src
BUILD_DIR = build

CROSS_COMPILE ?= arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

# compiler options
CFLAGS = -mcpu=cortex-m3 -mthumb -DGCC_ARMCM_OMAP -O2
CFLAGS += \
	-I$(APPLICATION_SOURCE_DIR) \
	-I$(FREERTOS_SOURCE_DIR)/Source/include \
	-I$(FREERTOS_SOURCE_DIR)/Source/portable/GCC/ARM_CM3 \

# linker options
LDFLAGS = -Tomap4_cm3.ld
LIBGCC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-libgcc-file-name)
LIBC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-file-name=libc.a)

FREERTOS_SOURCE_DIRS = \
	$(FREERTOS_SOURCE_DIR)/Source \
	$(FREERTOS_SOURCE_DIR)/Source/portable/MemMang \
	$(FREERTOS_SOURCE_DIR)/Source/portable/GCC/ARM_CM3

VPATH = $(FREERTOS_SOURCE_DIRS):$(APPLICATION_SOURCE_DIR)

APPLICATION_OBJS = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/startup.o \
	$(BUILD_DIR)/remoteproc.o \
	$(BUILD_DIR)/nvic.o \
	$(BUILD_DIR)/gpio.o \
	$(BUILD_DIR)/led.o \
	$(BUILD_DIR)/debug.o

FREERTOS_OBJS = \
	$(BUILD_DIR)/list.o \
	$(BUILD_DIR)/queue.o \
	$(BUILD_DIR)/tasks.o \
	$(BUILD_DIR)/port.o \
	$(BUILD_DIR)/heap_1.o

all: omap4-ipu-fw.xem3

omap4-ipu-fw.xem3: $(APPLICATION_OBJS) $(FREERTOS_OBJS) $(LIBGCC) $(LIBC) omap4_cm3.ld
	$(LD) $(LDFLAGS) $(APPLICATION_OBJS) $(FREERTOS_OBJS) $(LIBGCC) $(LIBC) -o omap4-ipu-fw.xem3

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BUILD_DIR)/*.o
	rmdir $(BUILD_DIR)
	rm -f omap4-ipu-fw.xem3

.PHONY: clean
