########################################################
# Contents: 	Build system of observer.
#
# Author: 	Dawid Blom.
#
# Date: 	27/03/2022.
#
#
#
# NOTE: This Makefile aims to simplify the build process
# 	of the observer project. Furthermore, this file
# 	is used for the main build of the project. What
# 	I mean is, this Makefile will not aid in the 
# 	construction of test code. For the test Makefile
# 	please navigate to the test directory where you
# 	can find it.
########################################################




# Project Paths.
SRC_DIR := src_test
OBJ_DIR := build_test
BIN_DIR := tests



# Final executable.
EXE := $(BIN_DIR)/test
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) 



# Compilation Instructions.
CC 		:= g++
CPPFLAGS 	+= -I$(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS 		:= -I$(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.hg -g -O0 -Wall -Werror 
LD_LIBRARIES 	:= -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
LDLIBS 		:= -lpthread -lrt





.PHONY: all clean

# Target.
all: $(EXE)
	./$(EXE) -c




# Linking Phase.
$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ $(LDLIBS) -o $@ $(LD_LIBRARIES)

# Compiling phase.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Creating the directories required for comilation.
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Cleaning up the project directory.
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)

# Automatic dependency generation for the header files.
-include $(OBJ:.o=.d)
