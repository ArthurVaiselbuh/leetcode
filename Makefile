CC = gcc
INCLUDES = -Iutils -Iunity
CFLAGS = -g -Wall $(INCLUDES)
OUT_DIR = out
TARGET = $(OUT_DIR)/run_tests
SRCS = tests/test_utils.c utils/vector.c utils/stack.c
UNITY_SRC = unity/unity.c

all: test

build_tests: $(OUT_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(UNITY_SRC) # -DDEBUG

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)

test: build_tests
	./$(TARGET)
