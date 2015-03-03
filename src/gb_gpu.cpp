#include "gb.h"

unsigned char Gameboy::gpu_readByte(unsigned short addr) {
	switch(addr & 0x000F) {
		case 0x0:
			break;
		case 0x1:
			break;
		case 0x2:
			return gpuReg.yscrl;
		case 0x3:
			return gpuReg.xscrl;
		case 0x4:
			return gpuReg.ly;
		case 0x5:
			return gpuReg.lyc;
		default:
			return ioregs[addr&0x01FF];
	}
}

bool Gameboy::gpu_writeByte(unsigned char data, unsigned short addr) {
	ioregs[addr&0xFF] = data;
	switch(addr & 0x000F) {
		case 0x0:
			gpuReg.lcdOn = (data&0x80) ? true : false;
			gpuReg.bgTileBase = (data&0x10) ? 0x0000 : 0x0800;
			gpuReg.bgMapBase = (data&0x08) ? 0x1C00 : 0x1800;
			gpuReg.objSize = (data&0x04) ? true :false;
			gpuReg.objOn = (data&0x02) ? true : false;
			gpuReg.bgOn = (data&0x01) ? true : false;
			break;
		case 0x2:
			gpuReg.yscrl = data;
			break;
		case 0x3:
			gpuReg.xscrl = data;
			break;
		case 0x4:
			gpuReg.ly = 0;
			break;
		case 0x5:
			gpuReg.lyc = data;
			break;
	}
}

bool Gameboy::gpuInit() {
	gpuReg.ly = 0;
	gpuReg.lyc = 0;
	gpuReg.yscrl = 0;
	gpuReg.xscrl = 0;
	gpuReg.bgTileBase = 0x0000;
	gpuReg.bgMapBase = 0x1800;
	gpuReg.objSize = false;
	gpuReg.lcdOn = false;
	gpuReg.bgOn = false;
	gpuReg.objOn = true;
	gpuReg.mode = 2;
}
