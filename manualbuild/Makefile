OBJS = src/main.cpp src/util.cpp src/menu.cpp src/level.cpp
CC = gcc
CXX = g++

COMPILER_FLAGS = -w -std=c++23 -g -pthread
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = main

all: $(OBJS)
	$(CXX) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)
