#OBJS specifies which files to compile as part of the project
OBJS = src/gb.cpp src/gb_cpu.cpp src/gb_gpu.cpp src/gb_mem.cpp src/main.cpp src/texture.cpp
TEST_OBJS = src/gb.cpp src/gb_cpu.cpp src/gb_gpu.cpp src/gb_mem.cpp src/test_main.cpp src/texture.cpp

#CC specifies which compiler we're using
CC = g++

CFLAGS = -std=c++11 -g

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = $(CFLAGS) $(shell sdl2-config --cflags)

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = $(shell sdl2-config --libs) -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = gameboy
TEST_NAME = gbtest

#This is the target that compiles our executable
all : $(OBJS) test
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)

test : $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(TEST_NAME)