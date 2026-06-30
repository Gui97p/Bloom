CC = gcc

CFLAGS = \
	-ffreestanding \
	-fno-builtin \
	-nostdlib \
	-nostartfiles \
	-nodefaultlibs \
	-no-pie \
	-Wall \
	-Wextra \
	-Iinclude \
	-mno-sse -mno-sse2 -mno-mmx -mno-avx

LDFLAGS = \
	-ffreestanding \
	-nostdlib \
	-nostartfiles \
	-nodefaultlibs \
	-no-pie \
	-T linker.ld

BUILD = build

LIBC = build/libc/libc.a
GLIB = build/glib/glib.a

CRT_SRC := $(shell find crt -name "*.S")
ARCH_SRC := $(shell find arch -name "*.S")

APPS_SRC := $(shell find apps -name "*.c")
SERVICES_SRC := $(shell find services -name "*.c")
INIT_SRC := $(shell find init -name "*.c")
DRIVER_SRC := $(shell find drivers -name "*.c")

CRT_OBJ := $(patsubst %.S,$(BUILD)/%.o,$(CRT_SRC))
ARCH_OBJ := $(patsubst %.S,$(BUILD)/%.o,$(ARCH_SRC))

APPS_OBJ := $(patsubst %.c,$(BUILD)/%.o,$(APPS_SRC))
SERVICES_OBJ := $(patsubst %.c,$(BUILD)/%.o,$(SERVICES_SRC))
INIT_OBJ := $(patsubst %.c,$(BUILD)/%.o,$(INIT_SRC))
DRIVER_OBJ := $(patsubst %.c,$(BUILD)/%.o,$(DRIVER_SRC))

TARGET := build/init.elf

all: libs $(TARGET) copy

debug: CFLAGS += -DDEBUG -g
debug: all

copy:
	@cp build/init.elf ../rootfs/sysinit

libs:
	$(MAKE) -C libs

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): libs \
	$(CRT_OBJ) \
	$(ARCH_OBJ) \
	$(INIT_OBJ) \
	$(DRIVER_OBJ) \
	$(APPS_OBJ) \
	$(SERVICES_OBJ)

	$(CC) \
	$(LDFLAGS) \
	-o $@ \
	$(CRT_OBJ) \
	$(ARCH_OBJ) \
	$(INIT_OBJ) \
	$(DRIVER_OBJ) \
	$(APPS_OBJ) \
	$(SERVICES_OBJ) \
	$(GLIB) \
	$(LIBC)

clean:
	rm -rf build

	$(MAKE) -C libs clean

.PHONY: all libs clean