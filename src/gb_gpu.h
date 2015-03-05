#ifndef GAMEBOYGPU_H
#define GAMEBOYGPU_H

#include <array>

class GameboyMemory;
class GameboyGPU {

private:
	GameboyMemory* mem;

	bool debugFlag;

	int clocks;
	int mode;

	std::array<unsigned char, 8192>  vram;
	std::array<unsigned char, 256>   oam;
	std::array<unsigned char, 64>    regs;

	std::array<unsigned char, 69120> screen;

	struct IORegs {
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
	IORegs ioReg;

public:
	bool init(GameboyMemory* memory, bool debug);
	bool tick(int mClocks);

	unsigned char readByte(unsigned short addr);
	bool writeByte(unsigned char data, unsigned short addr);

	void* getScreen();
};

#endif