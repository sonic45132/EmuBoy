#include "gb_gpu.h"
#include <array>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GREY 75

unsigned char GameboyGPU::readByte(unsigned short addr) {
	switch(addr & 0xF000) {
		case 0x8000:
		case 0x9000:
			return vram[addr & 0x1FFF];
		case 0xF000:
			if((addr & 0x0F00) == 0x0E00) {
				return oam[addr & 0x00FF];
			}
			else {
				switch(addr & 0x000F) {
					case 0x1:
						return mode;
					case 0x2:
						return ioReg.yscrl;
					case 0x3:
						return ioReg.xscrl;
					case 0x4:
						return ioReg.ly;
					case 0x5:
						return ioReg.lyc;
					default:
						return regs.at(addr&0x000F);
				}
			}
		default:
			return (unsigned char)0xDEAD;
	}
}

bool GameboyGPU::writeByte(unsigned char data, unsigned short addr) {
	switch(addr & 0xF000) {
		case 0x8000:
		case 0x9000:
      //printf("Writing 0x%X to 0x%X.\n", data, addr);
			vram[addr & 0x1FFF] = data;
			updateTiles();
			break;
		case 0xF000:
			if((addr & 0x0F00) == 0x0E00) {
				oam[addr & 0xFF] = data;
				updateSprites();
			}
			else {
				regs.at(addr&0x000F) = data;
				switch(addr & 0x000F) {
					case 0x0:
						ioReg.lcdOn = (data&0x80) ? true : false;
						ioReg.bgTileBase = (data&0x10) ? 0x0000 : 0x0800;
						ioReg.bgMapBase = (data&0x08) ? 0x1C00 : 0x1800;
						ioReg.objSize = (data&0x04) ? true :false;
						ioReg.objOn = (data&0x02) ? true : false;
						ioReg.bgOn = (data&0x01) ? true : false;
						break;
					case 0x2:
						ioReg.yscrl = data;
						break;
					case 0x3:
						ioReg.xscrl = data;
						break;
					case 0x4:
						ioReg.ly = 0;
						break;
					case 0x5:
						ioReg.lyc = data;
						break;
					case 0x6:
						DMA((data * 0x100));
						break;
					case 0x7:
            updatePalette();
						break;
				}
			}
	}
	return true;
}

bool GameboyGPU::init(GameboyMemory* memory, bool debug) {
	srand(time(NULL));
	mem = memory;
	ioReg.ly = 0;
	ioReg.lyc = 0;
	ioReg.yscrl = 0;
	ioReg.xscrl = 0;
	ioReg.bgTileBase = 0x0000;
	ioReg.bgMapBase = 0x1800;
	ioReg.objSize = false;
	ioReg.lcdOn = false;
	ioReg.bgOn = false;
	ioReg.objOn = true;
	mode = 2;
	vram.fill(0);
	oam.fill(0);
	regs.fill(0);
	screen.fill(0);
	debugFlag = debug;

	for(int i = 0; i < 4; i++) {
        palette.at(i) = color(255-(GREY*i), 255-(GREY*i), 255-(GREY*i));
	}
	palette.at(4) = color(0,0,255);
	palette.at(5) = color(255,0,0);

	for(int i = 0; i < tiles.size(); i++) {
		tiles[i].fill(0);
	}

	return true;
}

bool GameboyGPU::tick(int mClocks, bool* drawFlag) {
	clocks += mClocks;
	
	switch(mode) {
		case 0:
			if(clocks >= 51) {
				if(ioReg.ly == 143) {
					mode = 1;
					*drawFlag = true;
				}
				else {
					mode = 2;
				}
				ioReg.ly++;
				clocks = 0;
			}
			break;

		case 1:
			if(clocks >= 114) {
				clocks = 0;
				ioReg.ly++;
				if(ioReg.ly > 153) {
					ioReg.ly = 0;
					mode = 2;
				}
			}
			mem->interrupts[0] = true;
			break;

		case 2:
			if(clocks >= 20) {
				clocks = 0;
				mode = 3;
			}
			break;

		case 3:
			mode = 0;
			renderScanline();
			break;
	};

	return true;
}

void GameboyGPU::DMA(unsigned short addr) {
	printf("DMA.\n");
	for(int i = 0; i < 40*4; i++) {
		writeByte(mem->readByte((addr + i)), (0xFE00 + i));
	}
}

void GameboyGPU::renderBackground(std::array<unsigned char, 160>& scanline) {
	unsigned short mapBase = ioReg.bgMapBase;
	mapBase += ((((ioReg.ly + ioReg.yscrl) & 255) >> 3)*32); 

	unsigned short lineOffset = (ioReg.xscrl >> 3);

	unsigned short tile = vram[mapBase + lineOffset];

	unsigned char x = ioReg.xscrl & 7;
	unsigned char y = (ioReg.ly + ioReg.yscrl) & 7;

	for(int i = 0; i < 160; i++) {

		scanline.at(i) = tiles[tile][(y * 8) + x];

		x++;
		if(x == 8) {
			x = 0;
			lineOffset = (lineOffset + 1) & 31;
			tile = vram[mapBase + lineOffset];
			//scanline.at(i) = 4;
		}
		if(y == 7) {
			//scanline.at(i) = 5;
		}
	}
}

void GameboyGPU::renderSprites(std::array<unsigned char, 160>& scanline) {
	for(int i = 0; i < sprites.size(); i++) {
		SPRITE_DATA sprite = sprites.at(i);
		if((sprite.y - 16) <= ioReg.ly && sprite.y >= ioReg.ly) {
			if((sprite.x) > 0 && (sprite.x - 8) < 160) {
				int start = ((sprite.x - 8) > 0) ? 0 : abs(sprite.x - 8);
				int end = (sprite.x < 160) ? 0 : (160 - (sprite.x - 8));
				for(int j = start; j < end; j++) {
					scanline.at((sprite.x - 8) + j) = tiles[sprite.tile][((ioReg.ly - (sprite.y - 16)) * 8) + j];
				}
			}
		}
	}
}

void GameboyGPU::renderScanline() {
	std::array<unsigned char, 160> scanline;
	renderBackground(scanline);
	renderSprites(scanline);

	int screenOffset = ioReg.ly * 160;

	for(int i = 0; i < scanline.size(); i++) {
		screen[screenOffset + i] = palette[scanline[i]];
	}
}

void GameboyGPU::updateTiles() {
  //printf("Updating tiles.\n");
	unsigned char colorLower = 0;
	unsigned char colorUpper = 0;
	unsigned char lowerBit = 0;
	unsigned char upperBit = 0;

	for(int i = 0; i < 384; i++) {
		for(int j = 0; j < 8; j++) {
			colorLower = vram[(i * 16) + (j * 2)];
			colorUpper = vram[(i * 16) + (j * 2) + 1];
			for(int k = 0; k < 8; k++) {
				lowerBit = (colorLower & (1 << (7 - k))) >> (7 - k);
				upperBit = (colorUpper & (1 << (7 - k))) >> (7 - k);
				tiles[i][(j * 8) + k] = (upperBit * 2) + lowerBit;
			}
		}
	}
}

void GameboyGPU::updateSprites() {
	for(int i = 0; i < 40; i++) {
		SPRITE_DATA temp;
		temp.y = oam[0+(i*4)] - 16;
		temp.x = oam[1+(i*4)] - 8;
		temp.tile = oam[2+(i*4)];
		temp.flippedX = ((oam[3+(i*4)] & 0x20) != 0) ? true: false;
		temp.flippedY = ((oam[3+(i*4)] & 0x40) != 0) ? true: false;
		temp.palette = ((oam[3+(i*4)] & 0x10) != 0) ? true: false;
		temp.below = ((oam[3+(i*4)] & 0x80) != 0) ? true: false;
		sprites[i] = temp;
	}
}

void GameboyGPU::updatePalette() {
	unsigned char data = regs[0x7];
     for(int i = 0; i < 4; i++) {
        unsigned char temp = ((data & (0x3 << (2 * i))) >> 2*i);
        palette.at(i) = color(255-(GREY*temp), 255-(GREY*temp), 255-(GREY*temp));
     }
}

void* GameboyGPU::getScreen() {
	for(int i=0; i<160; i++) {
		screen[i+160*143] = color(sin(i * M_PI / 180.0)*255, 0, 255);
	}
	return (void*)screen.data();
}

unsigned int GameboyGPU::color(unsigned char r, unsigned char g, unsigned char b) {
	unsigned int temp = 0;
	temp |= r << 24;
	temp |= g << 16;
	temp |= b << 8;
	return temp;
}
