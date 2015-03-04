#include "gb_mem.h"
#include <iostream> 
#include <fstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <array>

unsigned char GameboyMemory::readByte(unsigned short addr) {
	switch(addr & 0xF000) {
		//BIOS AND ROM BANK 0
		case 0x0000:
			if(biosFlag) {
				if(addr < 0x100) {
					if(debugFlag) { accessList.push_back({false, addr, bios[addr]}); }
					return bios[addr];
				}
			}
			else {
				if(debugFlag) { accessList.push_back({false, addr, rom[addr]}); }
				return rom[addr];
			}
		//ROM BANK 0
		case 0x1000:
		case 0x2000:
		case 0x3000:
			if(debugFlag) { accessList.push_back({false, addr, rom[addr]}); }
			return rom[addr];
		//SWITCHED ROM BANK
		case 0x4000:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			if(debugFlag) { accessList.push_back({false, addr, rom[addr]}); }
			return rom[addr];
		//VRAM
		case 0x8000:
		case 0x9000:
			if(debugFlag) { accessList.push_back({false, addr, vram[addr&0x1FFF]}); }
			return gpu->readByte(addr);
		//EXTERNAL RAM
		case 0xA000:
		case 0xB000:
			return eram[addr&0x1FFF];
		//WORKING RAM
		case 0xC000:
		case 0xD000:
			return wram[addr&0x1FFF];
		//RAM SHADOW
		case 0xE000:
			return wram[addr&0x1FFF];
		//RAM SHADOW/IO/ZERO PAGE
		case 0xF000:
			switch(addr&0xF00) {
				case 0xE00:
					if(addr < 0xFEA0) {
						return gpu->readByte(addr); 
					}
					else {
						return 0;
					}
				case 0xF00:
					if(addr >= 0xFF80) { 
						return zram[addr&0x7F]; 
					} 
					else if(addr <= 0xFF7F){ 
						if(addr <= 0xFF4B && addr >= 0xFF40) { 
							return  gpu->readByte(addr); 
						}
						else { 
							return ioregs[addr&0x00FF];
						}
					}
					else {
						return (
							(interrupts.vblank) ? 0x1 : 0x0 |
							(interrupts.lcdc) ? 0x2 : 0x0 |
							(interrupts.timer) ? 0x4 : 0x0 |
							(interrupts.serial) ? 0x8 : 0x0 |
							(interrupts.input) ? 0x10 : 0x0
							);
					}
				default:
					return wram[addr&0x1FFF];
			}
	}
}

bool GameboyMemory::writeByte(unsigned char data, unsigned short addr) {
	if(debugFlag) { accessList.push_back({true, addr, data}); }
	switch(addr & 0xF000) {
		//BIOS AND ROM
		case 0x0000:
		case 0x1000:
		case 0x2000:
		case 0x3000:
		case 0x4000:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			return false;
		//VRAM
		case 0x8000:
		case 0x9000:
			vram[addr&0x1FFF] = data;
			dumpRam(VRAM);
			break;
		//EXTERNAL RAM
		case 0xA000:
		case 0xB000:
			eram[addr&0x1FFF] = data;
			dumpRam(ERAM);
			break;
		//WORKING RAM
		case 0xC000:
		case 0xD000:
			wram[addr&0x1FFF] = data;
			dumpRam(WRAM);
			break;
		//RAM SHADOW
		case 0xE000:
			wram[addr&0x1FFF] = data;
			dumpRam(WRAM);
			break;
		//RAM SHADOW/IO/ZERO PAGE
		case 0xF000:
			switch(addr&0xF00) {
				case 0xE00:
					if(addr < 0xFEA0) {
						oam[addr&0xFF] = data;
						dumpRam(OAM);
					}
					else {
						return false;
					}
					break;
				case 0xF00:
					if(addr >= 0xFF80) { 
						zram[addr&0x7F] = data; 
						dumpRam(ZRAM);
					} 
					else if(addr <= 0xFF7F) { 
						if(addr <= 0xFF4B && addr >= 0xFF40) { 
							gpu->writeByte(data, addr); 
						}
						else { 
							ioregs[addr&0x00FF] = data; 
						}
						dumpRam(IOREGS);
					}
					else {
						interrupts.vblank = (data&0x1) ? true : false;
						interrupts.lcdc = (data&0x2) ? true : false;
						interrupts.timer = (data&0x4) ? true : false;
						interrupts.serial = (data&0x8) ? true : false;
						interrupts.input = (data&0x10) ? true : false;
					}
					break;
				default:
					wram[addr&0xFF] = data;
					dumpRam(WRAM);
					break;
			}
	}

	return true;
}

unsigned short GameboyMemory::readWord(unsigned short addr) {
	unsigned short temp = 0;
	temp = readByte(addr);
	temp |= (readByte(addr+1) << 8);
	if(debugFlag) { accessList.push_back({false, addr, temp}); }
	return temp;
}


bool GameboyMemory::writeWord(unsigned short data, unsigned short addr) {
	if(!writeByte(data&0x00FF, addr)) {
		return false;
	}
	else {
		if(!writeByte((data&0xFF00)>>8, addr)) {
			return false;
		}
	}
	return true;
}

void GameboyMemory::dumpRam(RamType type) {
	std::ofstream dump;

	switch(type) {
		case BIOS:
			dump.open("dumps/bios.bin", std::ios::binary);
			for(int i=0;i<bios.size();i++) {
				dump << bios[i];
			}
			break;
		case ROM:
			dump.open("dumps/rom.bin", std::ios::binary);
			printf("%lu\n", rom.capacity());
			for(int i=0;i<rom.capacity();i++) {
				dump << rom[i];
			}
			break;
		case ERAM:
			dump.open("dumps/eram.bin", std::ios::binary);
			for(int i=0;i<eram.capacity();i++) {
				dump << eram[i];
			}
			break;
		case WRAM:
			dump.open("dumps/wram.bin", std::ios::binary);
			for(int i=0;i<wram.size();i++) {
				dump << wram[i];
			}
			break;
		case VRAM:
			dump.open("dumps/vram.bin", std::ios::binary);
			for(int i=0;i<vram.size();i++) {
				dump << vram[i];
			}
			break;
		case ZRAM:
			dump.open("dumps/zram.bin", std::ios::binary);
			for(int i=0;i<zram.size();i++) {
				dump << zram[i];
			}
			break;
		case OAM:
			dump.open("dumps/oam.bin", std::ios::binary);
			for(int i=0;i<oam.size();i++) {
				dump << oam[i];
			}
			break;
		case IOREGS:
			dump.open("dumps/ioregs.bin", std::ios::binary);
			for(int i=0;i<ioregs.size();i++) {
				dump << ioregs[i];
			}
			break;
	}
	dump.close();
}

void GameboyMemory::printList() {
	for(int i=0; i<accessList.size(); i++) {
		if(accessList[i].write) {
			printf("Wrote 0x%02X to 0x%04X\n", accessList[i].data, accessList[i].addr);	
		}
		else {
			printf("Read 0x%02X from 0x%04X\n", accessList[i].data, accessList[i].addr);
		}
	}
	accessList.clear();
}

void GameboyMemory::setBios(bool bios) {
	biosFlag = bios;
}

bool GameboyMemory::init(GameboyGPU* gpuPtr, bool debug) {
	gpu = gpuPtr;

	rom.clear();
	eram.clear();
	vram.fill(0);
	wram.fill(0);
	oam.fill(0);
	zram.fill(0);
	ioregs.fill(0);

	biosFlag = true;
	debugFlag = debug;

	return true;
}

bool GameboyMemory::loadRom(std::string path) {
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