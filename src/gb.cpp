#include "gb.h"
#include <iostream> 
#include <fstream>
#include <algorithm>

bool Gameboy::initialize(bool debug) {

	bool result = true;

	cycle_num = 0;

	a = 0;
	f = 0;
	b = 0;
	c = 0;
	d = 0;
	e = 0;
	h = 0;
	l = 0;

	opcode = 0;
	pc = 0;
	sp = 0;

	biosFlag = true;
	haltFlag = false;
	stopFlag = false;
	interruptsFlag = true;
	drawFlag = false;

	rom.clear();
	eram.clear();
	vram.fill(0);
	wram.fill(0);
	oam.fill(0);
	zram.fill(0);
	ioregs.fill(0);

	if(debug) {
		debugFlag = debug;
		//dumpRam(BIOS);
	}

	return result;
}

bool Gameboy::loadGame(std::string path) {
	std::ifstream roms;
  roms.open(path, std::ios::binary);
  roms.seekg (0, roms.end);
  unsigned int length = roms.tellg();
  roms.seekg (0, roms.beg);

  char* buffer = new char[length];

  roms.read(buffer,length);
  if (!roms) {
    std::cout << "error: only " << roms.gcount() << " could be read" << std::endl;
    return false;
  }

  roms.close();

  rom.reserve(length);
  std::copy(buffer, (buffer+length), rom.begin());
  return true;
}

void Gameboy::EXT() {
	opcode = readByte(pc++);
	if(debugFlag) {
		printf("EXT Opcode: %X\n", opcode);
	}

	unsigned char high = 0;
	if((opcode&0x0F) > 0x07) {
		high = 1;
	} 

	switch(opcode & 0xF0) {
		case 0x00:
			if(high == 0) {
				RLC();
			}
			else {
				RRC();
			}
			break;
		case 0x10:
			if(high == 0) {
				RL();
			}
			else {
				RR();
			}
			break;
		case 0x20:
			if(high == 0) {
				SLA();
			}
			else {
				SRA();
			}
			break;
		case 0x30:
			if(high == 1) {
				SRL();
				break;
			}
			(*this.*opMapExt[(opcode&0xF0)>>4][opcode&0x0F])();
			break;
		case 0x40:
		case 0x50:
		case 0x60:
		case 0x70:
			BIT((((((opcode&0xF0)>>4)%4)*2)+high), ((opcode&0x0F)%8));
			break;
		case 0x80:
		case 0x90:
		case 0xA0:
		case 0xB0:
			RES((((((opcode&0xF0)>>4)%4)*2)+high), ((opcode&0x0F)%8));
			break;
		case 0xC0:
		case 0xD0:
		case 0xE0:
		case 0xF0:
			SET((((((opcode&0xF0)>>4)%4)*2)+high), ((opcode&0x0F)%8));
			break;
	}

}

bool Gameboy::emulateCycle(unsigned long delta) {

	bool result = true;
	cycle_num++;

	if(haltFlag || stopFlag) {
		printf("Stalled!\n");
		result = false;
	}
	else {
		if(debugFlag) {
			printf("%lu microseconds\n\n", delta);
		}
		opcode = readByte(pc++);
		(*this.*opMap[(opcode&0xF0)>>4][opcode&0x0F])();
		if(debugFlag) {
			printDebug();
		}
	}

	if(pc > 0x100) {
		haltFlag = true;
	}

	return result;
}

void Gameboy::printDebug() {
	printf("Cycle: %u\n", cycle_num);
	printf("Opcode: %02X\n", opcode);
	printf("Registers: \n");
	printf("A: %02X B: %02X C: %02X D: %02X E: %02X H: %02X L: %02X\n", a ,b, c, d, e, h, l);
	printf("F: %02X SP: %04X PC: %04X\n", f, sp, pc);
	printf("Flags: \n");
	printf("BIOS: %d HALT: %d STOP: %d\n", biosFlag, haltFlag, stopFlag);
}