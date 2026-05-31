CC = gcc
AR = ar

CFLAGS = \
	-ffreestanding \
	-fno-builtin \
	-nostdlib \
	-nostartfiles \
	-nodefaultlibs \
	-no-pie \
	-Wall \
	-Wextra \
	-I../include

BUILD = ../build/libc
LIB = ../sysroot/lib

SRC_C := $(shell find src -name "*.c")

OBJ := $(patsubst %.c,$(BUILD)/%.o,$(SRC_C))

TARGET := $(LIB)/libc.a

all: $(TARGET)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@mkdir -p $(LIB)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -rf $(BUILD)