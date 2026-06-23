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

BUILD = ../../build/glib

SRC_C := $(shell find -name "*.c")
OBJ := $(patsubst %.c,$(BUILD)/%.o,$(SRC_C))

TARGET := $(BUILD)/glib.a

all: $(TARGET)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD)
	$(AR) rcs $@ $(OBJ)

HOST_CC = gcc
HOST_CFLAGS = -Wall -Wextra -g -Itest/include -I../../include
HOST_BUILD = ../../build/glib-host
HOST_OBJ := $(patsubst %.c,$(HOST_BUILD)/%.o,$(SRC_C))
HOST_TARGET := $(HOST_BUILD)/glib_host.a

host: $(HOST_TARGET)

$(HOST_BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(HOST_CC) $(HOST_CFLAGS) -c $< -o $@

$(HOST_TARGET): $(HOST_OBJ)
	@mkdir -p $(HOST_BUILD)
	$(AR) rcs $@ $(HOST_OBJ)

test: $(HOST_TARGET)
	$(HOST_CC) $(HOST_CFLAGS) test/main.c $(HOST_TARGET) -o $(HOST_BUILD)/test_glib
	$(HOST_BUILD)/test_glib

clean:
	rm -rf $(BUILD) $(HOST_BUILD)
