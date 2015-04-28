#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include <vector>
#include <array>
#include <unordered_map>

#include "gb_gpu.h"
#include "gb_mem.h"
#include "gb_cpu.h"
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

	enum GB_KEYS {
		GB_A = 0,
		GB_B,
		GB_SELECT,
		GB_START,
		GB_RIGHT,
		GB_LEFT,
		GB_UP,
		GB_DOWN	
	};

	bool initialize(bool debug = false, Texture* texture = NULL);
	bool reset();
	bool loadGame(std::string path);
	bool emulateCycle(unsigned long delta);
	bool getKeys(std::array<bool, 8> keys);

};

#endif