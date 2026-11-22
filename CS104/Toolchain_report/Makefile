CC		:= gcc
AS		:= as
CFLAGS	:= -std=c11 -Wall -Wextra -pedantic -O0

SRC_DIR   := src
BUILD_DIR := build

TARGET := $(BUILD_DIR)/programa
OBJS   := $(BUILD_DIR)/main.o $(BUILD_DIR)/util.o

.PHONY: all stages run clean

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

stages: $(BUILD_DIR)
	$(CC) -E $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.i
	$(CC) -E $(SRC_DIR)/util.c -o $(BUILD_DIR)/util.i
	$(CC) -S $(CFLAGS) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.s
	$(CC) -S $(CFLAGS) $(SRC_DIR)/util.c -o $(BUILD_DIR)/util.s
	$(AS) $(BUILD_DIR)/main.s -o $(BUILD_DIR)/main.o
	$(AS) $(BUILD_DIR)/util.s -o $(BUILD_DIR)/util.o
	$(CC) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/*