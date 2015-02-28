#OBJS specifies which files to compile as part of the project
OBJS = src/gb.cpp src/gb_cpu.cpp src/gb_mem.cpp src/main.cpp

#CC specifies which compiler we're using
CC = g++

CFLAGS = -std=c++11

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = $(CFLAGS) $(shell sdl2-config --cflags)

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = $(shell sdl2-config --libs) -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = gameboy

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)