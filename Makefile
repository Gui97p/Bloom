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
	-Ilibc/include \
	-mno-sse -mno-sse2 -mno-mmx -mno-avx

LDFLAGS = \
	-ffreestanding \
	-nostdlib \
	-nostartfiles \
	-nodefaultlibs \
	-no-pie \
	-T linker.ld

OBJCOPY = objcopy

BUILD = build
BIN = bin

LIBC = sysroot/lib/libc.a

CRT_SRC := crt/crt0.S
CRT_OBJ := $(BUILD)/crt/crt0.o

ARCH_SRC := arch/x86_64/syscalls.S
ARCH_OBJ := $(BUILD)/arch/x86_64/syscalls.o

APP_SRC := apps/test/main.c
APP_OBJ := $(BUILD)/apps/test/main.o

TARGET := $(BIN)/start
ELF_TARGET := ../rootfs/sysinit/userspace.elf

all: libc $(TARGET) $(ELF_TARGET)

libc:
	$(MAKE) -C libc

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(CRT_OBJ) $(ARCH_OBJ) $(APP_OBJ)
	@mkdir -p $(BIN)
	$(CC) \
	$(LDFLAGS) \
	-o $@ \
	$(CRT_OBJ) \
	$(ARCH_OBJ) \
	$(APP_OBJ) \
	$(LIBC)

$(ELF_TARGET): $(TARGET)
	@mkdir -p $(dir $@)
	cp $< $@

clean:
	rm -rf build bin
	$(MAKE) -C libc clean

.PHONY: all libc clean