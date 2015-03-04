#include "gb.h"
#include <iostream> 
#include <fstream>
#include <algorithm>

Gameboy::Gameboy() {
	printf("Gameboy construtor start.\n");
	mem = new GameboyMemory();
	cpu = new GameboyCPU();
	gpu = new GameboyGPU();
	printf("Gameboy construtor end.\n");
}

Gameboy::~Gameboy() {
	delete cpu;
	delete gpu;
	delete mem;
}

bool Gameboy::initialize(bool debug) {

	bool result = true;
	debugFlag = debug;

	printf("Gameboy init start.\n");
	mem->init(gpu, debugFlag);
	cpu->init(mem, debugFlag);
	gpu->init(mem, debugFlag);
	printf("Gameboy init end.\n");

	return result;
}

bool Gameboy::loadGame(std::string path) {
	return mem->loadRom(path);
}

bool Gameboy::emulateCycle(unsigned long delta) {
	if(debugFlag) {
		printf("%lu microseconds\n\n", delta);
	}
	return cpu->execute();
}
