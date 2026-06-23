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
	-I../../include

BUILD = ../../build/libc

SRC_C := $(shell find -name "*.c")
OBJ := $(patsubst %.c,$(BUILD)/%.o,$(SRC_C))

TARGET := $(BUILD)/libc.a

all: $(TARGET)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -rf $(BUILD)