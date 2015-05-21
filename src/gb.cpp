#include "gb.h"
#include "texture.h"
#include <iostream> 
#include <fstream>
#include <algorithm>

Gameboy::Gameboy() {
	mem = new GameboyMemory();
	cpu = new GameboyCPU();
	gpu = new GameboyGPU();
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

	mem->init(gpu, debugFlag);
	cpu->init(mem, debugFlag);
	gpu->init(mem, debugFlag);

	return result;
}

bool Gameboy::loadGame(std::string path) {
	return mem->loadRom(path);
}

bool Gameboy::getKeys(std::array<bool, 8> keys) {
	if(keys != mem->keyStates) {
		mem->interrupts[4] = true;
	}
	mem->keyStates = keys;
	return true;
}

bool Gameboy::emulateCycle(unsigned long delta) {
	bool result = true;
	int mClocks = 0;
	drawFlag = false;
	
	if(debugFlag) {
		//printf("%lu microseconds\n\n", delta);
	}

	result = cpu->execute(&mClocks);

	if(!result) return false;

	result = gpu->tick(mClocks, &drawFlag);

	if(drawFlag) {
		screen->lockTexture();
		screen->copyPixels(gpu->getScreen());
		screen->unlockTexture();
	}
	return result;
}
