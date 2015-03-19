#include "gb.h"
#include "texture.h"
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

bool Gameboy::initialize(bool debug, Texture* texture) {

	bool result = true;
	debugFlag = debug;
	drawFlag = true;

	screen = texture;

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
	bool result = true;
	int mClocks = 0;
	drawFlag = false;
	
	if(debugFlag) {
		printf("%lu microseconds\n\n", delta);
	}

	result = cpu->execute(&mClocks);
	result = gpu->tick(mClocks, &drawFlag);

	if(drawFlag) {
		screen->lockTexture();
		screen->copyPixels(gpu->getScreen());
		screen->unlockTexture();
	}
	return true;
}
