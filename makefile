# makefile for Sudoku puzzle generator

# project information
NAME := puzzleGen
VERSION := 0.1.0
OBJ_DIR := obj

# define project source files
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# define compiler and flags
CPP := g++
LFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS :=

# utilities
RM := rm -f
RMRF := rm -rf

# edit make flags
MAKEFLAGS += --no-print-directory

###########
# Recipes #
###########

# default target
all: $(OBJ_DIR) $(NAME)

# create obj dir if not exists
$(OBJ_DIR):
	mkdir -p $@
	$(info CREATED $@/)

# create executable
$(NAME): $(OBJS)
	$(CPP) -o $@ $^ $(LFLAGS)
	$(info CREATED $@)

# create obj files
$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -c -o $@ $< $(CFLAGS)
	$(info COMPILED $<)

# remove all obj files and obj dir
mostlyclean:
	$(RMRF) $(OBJ_DIR)
	$(info REMOVED $(OBJ_DIR)/)

# remove all compilation files
clean: mostlyclean
	$(RM) $(NAME)
	$(info REMOVED $(NAME))

# recompile
re:
	$(MAKE) clean
	$(MAKE) all

# run after recompiling everything
run: re
	-./$(NAME)

# recompile what's necessary and run
rerun:
	$(MAKE) all
	-./$(NAME)

# debug
debug: CFLAGS += -g
debug: $(OBJ_DIR) $(NAME)
	$(info DEBUGGING $(NAME))
	gdb $(NAME)

.PHONY: mostlyclean clean re run rerun debug
.SILENT: 

