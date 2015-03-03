#ifndef GAMEBOYGPU_H
#define GAMEBOYGPU_H

#include <array>

class GameboyMemory;
class GameboyGPU {

private:
	GameboyMemory* mem;

	bool debugFlag;

	struct gpuRegs {
		unsigned char ly;
		unsigned char lyc;
		unsigned char yscrl;
		unsigned char xscrl;
		unsigned short bgTileBase;
		unsigned short bgMapBase;
		bool objSize;
		bool lcdOn;
		bool bgOn;
		bool objOn;
		unsigned char mode;
	};
	gpuRegs gpuReg;

	std::array<unsigned char, 64> regs;

public:
	bool init(GameboyMemory* memory, bool debug);

	unsigned char gpu_readByte(unsigned short addr);
	bool gpu_writeByte(unsigned char data, unsigned short addr);
};

#endif