###########################################################
# Contents: Observer Tests Makefile.
#
# Author: Dawid Blom.
#
# Date: 28/03/2022.
#
# NOTE: This makefile handels all the test compilation
# 	for the observer project.
###########################################################



# Cross Compiler.
CC = g++



# Paths.
MAKEFILE_DIR = /home/odin/workspace/Embedded_Projects/observer/test
PROJECT_DIR = /home/odin/workspace/Embedded_Projects/observer
TEST_DIR = $(PROJECT_DIR)/test
CPPUTEST_HOME = $(TEST_DIR)/cpputest
SRC_DIRS = $(PROJECT_DIR)
INCLUDE_DIRS = $(PROJECT_DIR)
INCLUDE_DIRS += $(CPPUTEST_HOME)/include
TEST_SRC_DIRS = $(TEST_DIR)


TEST_TARGET = tests



#run MakefileWorker.mk with the variables defined here
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
