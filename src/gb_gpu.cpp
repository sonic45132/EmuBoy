#include "gb_gpu.h"
#include <array>

unsigned char GameboyGPU::readByte(unsigned short addr) {
	switch(addr & 0xFF00) {
		case 0x8000:
		case 0x9000:
			return vram[addr & 0x1FFF];
		case 0xFE00:
			return oam[addr & 0x00FF];
		case 0xFF00:
			switch(addr & 0x000F) {
				case 0x0:
					break;
				case 0x1:
					break;
				case 0x2:
					return ioReg.yscrl;
				case 0x3:
					return ioReg.xscrl;
				case 0x4:
					return ioReg.ly;
				case 0x5:
					return ioReg.lyc;
				default:
					return regs[addr&0x01FF];
			}
	}
}

bool GameboyGPU::writeByte(unsigned char data, unsigned short addr) {
	regs[addr&0xFF] = data;
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
	}
}

bool GameboyGPU::init(GameboyMemory* memory, bool debug) {
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
	ioReg.mode = 2;
	vram.fill(0);
	oam.fill(0);
	regs.fill(0);
	debugFlag = debug;
	return true;
}

bool GameboyGPU::tick(int mClocks) {
	clocks += mClocks;
	
	switch(ioReg.mode) {
		case 0:
			if(clocks >= 51) {
				if(ioReg.ly == 143) {
					ioReg.mode = 1;

				}
				else {
					ioReg.mode = 2;
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
					ioReg.mode = 2;
				}
			}
			break;

		case 2:
			if(clocks >= 20) {
				clocks = 0;
				ioReg.mode = 3;
			}
			break;

		case 3:
			break;
	};

	return true;
}
