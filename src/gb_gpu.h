#ifndef GAMEBOYGPU_H
#define GAMEBOYGPU_H

#include <array>
#include <map>
#include "gb_mem.h"

class GameboyMemory;
class GameboyGPU {

private:
	friend class Debug;
	GameboyMemory* mem;

	bool debugFlag;

	int clocks;
	unsigned char mode;

	std::array<unsigned char, 8192>  vram;
	std::array<unsigned char, 256>   oam;
	std::array<unsigned char, 16>    regs;

	std::array<unsigned int, 92160> screen;
	std::array<std::array<unsigned char, 64>, 384> tiles;

	//std::map<unsigned char, unsigned int> colors;
	std::array<unsigned int, 6> palette;

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
		unsigned char bgp;
	};
	IORegs ioReg;

	struct SPRITE_DATA {
		short x;
		short y;
		unsigned char tile;
		bool flippedX;
		bool flippedY;
		bool palette;
		bool below;
	};
	std::array<SPRITE_DATA, 40> sprites;

	void renderBackground(std::array<unsigned char, 160>& scanline);
	void renderSprites(std::array<unsigned char, 160>& scanline);
	void renderScanline();
	void updateTiles();
	void updateSprites();
	void updatePalette();
	unsigned int color(unsigned char r, unsigned char g, unsigned char b);

public:
	bool init(GameboyMemory* memory, bool debug);
	bool tick(int mClocks, bool* drawFlag);

	unsigned char readByte(unsigned short addr);
	bool writeByte(unsigned char data, unsigned short addr);

	void* getScreen();
};

#endif