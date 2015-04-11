#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include <vector>
#include <array>

#include "gb_mem.h"
#include "gb_cpu.h"
#include "gb_gpu.h"
#include "texture.h"

class Gameboy {

friend class Debug;

private:

	GameboyMemory* mem;
	GameboyCPU* cpu;
	GameboyGPU* gpu;
	Texture* screen;

	bool debugFlag;	

public:

	Gameboy();
	~Gameboy();

	bool drawFlag;

	bool initialize(bool debug = false, Texture* texture = NULL);
	bool reset();
	bool loadGame(std::string path);
	bool emulateCycle(unsigned long delta);
	bool getKeys(std::array<bool, 8> keys);

};

#endif