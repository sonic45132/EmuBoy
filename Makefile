#OBJS specifies which files to compile as part of the project
SOURCES = src/gb.cpp src/gb_cpu.cpp src/gb_gpu.cpp src/gb_mem.cpp src/texture.cpp src/main.cpp
TEST_SOURCES = src/gb.cpp src/gb_cpu.cpp src/gb_gpu.cpp src/gb_mem.cpp src/texture.cpp src/test_main.cpp
OBJS=$(SOURCES:.cpp=.o)
TEST_OBJS=$(TEST_SOURCES:.cpp=.o)

#CC specifies which compiler we're using
CC = g++
#clang-3.5

CFLAGS =-c -std=c++11 -g

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = $(CFLAGS) $(shell sdl2-config --cflags)

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = $(shell sdl2-config --libs) -lSDL2_image 
#-lstdc++

#OBJ_NAME specifies the name of our exectuable
EXEC_NAME = gameboy
TEST_NAME = gbtest

#This is the target that compiles our executable
all: gameboy test

gameboy: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o bin/$(EXEC_NAME)

test: $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(LINKER_FLAGS) -o bin/$(TEST_NAME)

.cpp.o:
	$(CC) $(COMPILER_FLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f src/*.o