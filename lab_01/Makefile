CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Werror -Iinc/
LDFLAGS :=

TARGET := build/lab_01
TEST_TARGET := build/tests
INCLUDE_DIRS := inc
SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:src/%.c=build/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)
TEST_SOURCES := tests/test_main.c src/big_int.c src/big_float.c src/calc.c src/str.c

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

$(TEST_TARGET): $(TEST_SOURCES) | build
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf build

-include $(DEPENDENCIES)
