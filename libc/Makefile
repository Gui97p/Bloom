CC = gcc

CFLAGS  = -ffreestanding -nostdlib -Wall -Wextra -Iinclude
LDFLAGS = -nostdlib

BUILD = build
BIN   = bin

SRC_C := $(shell find src -name "*.c")
SRC_S := $(shell find arch -name "*.S") $(shell find crt -name "*.S")
TEST_C := test/main.c

OBJ_C := $(patsubst %.c,$(BUILD)/%.o,$(SRC_C))
OBJ_S := $(patsubst %.S,$(BUILD)/%.o,$(SRC_S))
OBJ_T := $(BUILD)/test/main.o

OBJ := $(OBJ_C) $(OBJ_S) $(OBJ_T)

TARGET := $(BIN)/libc_test

all: $(TARGET)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@mkdir -p $(BIN)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

clean:
	rm -rf $(BUILD) $(BIN)