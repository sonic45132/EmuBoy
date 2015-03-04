#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include <vector>
#include <array>

#include "gb_mem.h"
#include "gb_cpu.h"
#include "gb_gpu.h"

class Gameboy {

friend class GameBoyTest;

private:

	GameboyMemory* mem;
	GameboyCPU* cpu;
	GameboyGPU* gpu;

	bool debugFlag;	

public:

	Gameboy();
	~Gameboy();

	bool drawFlag;

	bool initialize(bool debug = false);
	bool reset();
	bool loadGame(std::string path);
	bool emulateCycle(unsigned long delta);
	bool getKeys(std::array<char, 8> keys);

};

#endif