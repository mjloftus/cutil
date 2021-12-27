SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := test

SO := $(BIN_DIR)/libcutil.so
TEST_EXE := $(BIN_DIR)/run_tests

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ := $(TEST:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS := -Wall -Werror -fpic

LDFLAGS := -Lbin -Wl,-rpath=bin
LDLIBS := -lcheck -lcutil

.PHONY: all clean test

all: $(SO)

$(SO): $(OBJ) | $(BIN_DIR)
	$(CC) -shared $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean: 
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)

test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(SO) $(TEST_OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(TEST_OBJ) -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
