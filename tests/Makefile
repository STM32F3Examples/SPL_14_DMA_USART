SOURCE_DIRS:= ./source ../source ../retarget/source
INCLUDE_DIRS:= ./include ../include ../retarget/include
LINKER_DIRS:= ./gmock

GTEST_DIR = $(GMOCK_HOME)/gtest
GMOCK_DIR = $(GMOCK_HOME)
GMOCK_LIB:=./gmock/gmock_main.a

TESTS:= gmock_test

TEST_FILES:= $(notdir $(wildcard ./source/*.cc ))

C_SOURCE_FILES:=
CXX_SOURCE_FILES:= $(TEST_FILES)
ASM_SOURCE_FILES:=
LINKER_FILES:= $(MYLIB)

C_OBJECTS:= $(C_SOURCE_FILES:.c=.o)
CXX_OBJECTS:= $(CXX_SOURCE_FILES:.cc=.o)
ASM_OBJECTS:= $(ASM_SOURCE_FILES:.S=.o)

ARCH_FLAGS:=
COMMON_FLAGS:=
CPP_FLAGS_USER := -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include
ASM_FLAGS:=
C_FLAGS:= -std=c99
CXX_FLAGS+= -g -Wall -Wextra -pthread -std=c++11
LINKER_FLAGS:= $(CXX_FLAGS) -lpthread

INCLUDE_FLAGS:= $(patsubst %,-I%,$(INCLUDE_DIRS))
CPP_FLAGS:= $(INCLUDE_FLAGS) $(CPP_FLAGS_USER)

OBJECTS_DIR:= objects
BIN_DIR:= bin

DIRS_TO_CREATE:= $(OBJECTS_DIR) $(BIN_DIR)

OBJECTS:= $(C_OBJECTS) $(CXX_OBJECTS) $(ASM_OBJECTS)
OBJECTS_WITH_PATH:= $(patsubst %,$(OBJECTS_DIR)/%,$(OBJECTS))

CC=gcc
CXX=g++
AS=g++
LN=g++

vpath %.c $(SOURCE_DIRS)
vpath %.cc $(SOURCE_DIRS)
vpath %.S $(SOURCE_DIRS)
vpath %.o $(OBJECTS_DIR)
vpath %.a $(BIN_DIR) $(LINKER_DIRS)

.PHONY: disp clean test

all: $(TESTS)
$(TESTS): $(OBJECTS) $(LINKER_FILES) $(GMOCK_LIB)
	$(LN) $(CPP_FLAGS) $(OBJECTS_WITH_PATH) $(LINKER_FILES) $(GMOCK_LIB) $(LINKER_FLAGS) -o $@
$(DIRS_TO_CREATE): %:
	mkdir $@
$(C_OBJECTS): %.o : %.c | $(OBJECTS_DIR)
	$(CC) -c $(C_FLAGS) $(CPP_FLAGS) $< -o $(OBJECTS_DIR)/$@
$(ASM_OBJECTS): %.o : %.S | $(OBJECTS_DIR)
	$(AS) -c $(ASM_FLAGS) $(CPP_FLAGS) $< -o $(OBJECTS_DIR)/$@
$(CXX_OBJECTS): %.o : %.cc | $(OBJECTS_DIR)
	$(CXX) -c $(CXX_FLAGS) $(CPP_FLAGS) $< -o $(OBJECTS_DIR)/$@
clean:
	rm -rf $(DIRS_TO_CREATE) $(TESTS)
dist_clean: clean
	$(MAKE) --directory=./gmock clean
$(GMOCK_LIB):
	$(MAKE) --directory=./gmock
test: $(TESTS)
	./$(TESTS)
