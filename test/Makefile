########################################################
# Contents: 	Build system of observer.
#
# Author: 	Dawid Blom.
#
# Date: 	27/03/2022.
#
#
#
# NOTE: This Makefile is specific to the observer unit
# 	testing process.
########################################################




# Project Paths.
SRC_DIR := src_test
OBJ_DIR := objects_test
BIN_DIR := test


# File Extensions
SRCEXT 	:= .c
OBJEXT 	:= .o




# Final executable.
EXE := $(BIN_DIR)/test
SRC := $(wildcard $(SRC_DIR)/*$(SRCEXT))
OBJ := $(patsubst $(SRC_DIR)/%$(SRCEXT), $(OBJ_DIR)/%$(OBJEXT), $(SRC)) 
DEB := $(OBJ:.o=.d)


# Compilation Instructions.
CC 		:= g++
CPPFLAGS 	+= -I$(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS 		:= -I$(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.hg -g -O0 -Wall -Werror 
LD_LIBRARIES 	:= -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
LDLIBS 		:= -lpthread -lrt





.PHONY: all clean

# Target.
all: $(EXE)
	sudo ./$(EXE) -c




# Linking Phase.
$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ $(LDLIBS) -o $@ $(LD_LIBRARIES)

# Compiling phase.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%$(SRCEXT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Creating the directories required for comilation.
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Cleaning up the project directory.
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)

# Automatic dependency generation for the header files.
-include $(DEB)
