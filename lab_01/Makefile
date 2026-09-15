CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Werror -Iinc/
LDFLAGS :=

TARGET := build/lab_01
INCLUDE_DIRS := inc
SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:src/%.c=build/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | build
	$(CC) $(LDFLAGS) $^ -o $@

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

build:
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

test:
	python3 tests/test_main.py

clean:
	rm -rf build

-include $(DEPENDENCIES)
