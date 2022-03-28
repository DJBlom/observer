###########################################################
# Contents: Makefile for all the tests of observer.
#
# Author: Dawid Blom.
#
# Date: 28/03/2022.
###########################################################

# Cross Compiler.
CC 		:= g++



# Paths.
MAKEFILE_DIR	:= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
PROJECT_DIR	:= $(realpath $(MAKEFILE_DIR)..)
TEST_DIR	:= $(PROJECT_DIR)/test
CPPUTEST_HOME	:= /usr/include/cpputest
SRC_DIRS	:= $(PROJECT_DIR)
INCLUDE_DIRS	:= $(PROJECT_DIR)
TEST_SRC_DIRS	:= $(TEST_DIR)

# Add this to avoid problems when including cpputest headers on test files
INCLUDE_DIRS	+= $(CPPUTEST_HOME)/include


# What to call the test binary
TEST_TARGET 	:= tests


include $(CPPUTEST_HOME)/build/MakefileWorker.mk
