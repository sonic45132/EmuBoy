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
					//OAM
					if(addr < 0xFEA0) {
						return gpu->readByte(addr); 
					}
					else {
						return 0;
					}
				case 0xF00:
					if(addr >= 0xFF80 && addr < 0xFFFF) { 
						if(debugFlag) { accessList.push_back({false, addr, zram[addr&0x7F]}); }
						return zram[addr&0x7F]; 
					} 
					else if(addr <= 0xFF7F){ 
						//GPU Regs
						if(addr >= 0xFF40) { 
							return  gpu->readByte(addr); 
						}
						else { 
							//IO Regs
							return getReg(addr&0x00FF);
						}
					}
					else {
						return (
							(intEnFlags[0]) ? 0x1 : 0x0 |
							(intEnFlags[1]) ? 0x2 : 0x0 |
							(intEnFlags[2]) ? 0x4 : 0x0 |
							(intEnFlags[3]) ? 0x8 : 0x0 |
							(intEnFlags[4]) ? 0x10 : 0x0
							);
					}
				default:
					return wram[addr&0x1FFF];
			}
		default:
			printf("Default in mem read\n");
			return (unsigned char)0xDEAD;
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
			gpu->writeByte(data, addr);
			break;
		//EXTERNAL RAM
		case 0xA000:
		case 0xB000:
			eram[addr&0x1FFF] = data;
			// dumpRam(ERAM);
			break;
		//WORKING RAM
		case 0xC000:
		case 0xD000:
			wram[addr&0x1FFF] = data;
			// dumpRam(WRAM);
			break;
		//RAM SHADOW
		case 0xE000:
			wram[addr&0x1FFF] = data;
			// dumpRam(WRAM);
			break;
		//RAM SHADOW/IO/ZERO PAGE
		case 0xF000:
			switch(addr&0xF00) {
				case 0xE00:
					if(addr < 0xFEA0) {
						gpu->writeByte(data, addr);
					}
					else {
						return false;
					}
					break;
				case 0xF00:
					if(addr >= 0xFF80) { 
						zram[addr&0x7F] = data; 
						// dumpRam(ZRAM);
					} 
					else if(addr <= 0xFF7F) { 
						if(addr <= 0xFF4B && addr >= 0xFF40) { 
							gpu->writeByte(data, addr); 
						}
						else { 
							setReg(addr, data);
						}
						// dumpRam(IOREGS);
					}
					else {
						intEnFlags[0] = (data&0x1) ? true : false;
						intEnFlags[1] = (data&0x2) ? true : false;
						intEnFlags[2] = (data&0x4) ? true : false;
						intEnFlags[3] = (data&0x8) ? true : false;
						intEnFlags[4] = (data&0x10) ? true : false;
					}
					break;
				default:
					wram[addr&0xFF] = data;
					// dumpRam(WRAM);
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

void GameboyMemory::setReg(unsigned short reg, unsigned char data) {
	ioregs[reg] = data;
	switch(reg) {
		case 16:
			interrupts[0] = (data | 0x01) ? true : false;
			interrupts[1] = (data | 0x02) ? true : false;
			interrupts[2] = (data | 0x04) ? true : false;
			interrupts[3] = (data | 0x08) ? true : false;
			interrupts[4] = (data | 0x010) ? true : false;
			break;
	}
}

unsigned char GameboyMemory::getReg(unsigned short reg) {
	unsigned char low = 0;
	unsigned char temp = 0;
	unsigned char bank = 0;
	switch(reg) {
		case 0: 
			bank = ((ioregs[reg] & 0x30) >> 4) - 1;
			bank = 1 - bank;
			for(int i = 0; i < 4; i++) {
				temp = (keyStates[i+(bank*4)] ? 0 : 1) << i;
				low |= temp;
			}
			return (bank << 4) | temp;
		case 16:
			return (
				(interrupts[0]) ? 0x1 : 0x0 |
				(interrupts[1]) ? 0x2 : 0x0 |
				(interrupts[2]) ? 0x4 : 0x0 |
				(interrupts[3]) ? 0x8 : 0x0 |
				(interrupts[4]) ? 0x10 : 0x0
			);
		default:
			return ioregs[reg];
	}
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
		case ZRAM:
			dump.open("dumps/zram.bin", std::ios::binary);
			for(int i=0;i<zram.size();i++) {
				dump << zram[i];
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
	wram.fill(0);
	zram.fill(0);
	ioregs.fill(0);

	intEnFlags.fill(false);
	interrupts.fill(false);

	biosFlag = true;
	debugFlag = debug;

	return true;
}

bool GameboyMemory::loadRom(std::string path) {
	if(path.empty()) {
		rom.reserve(1024*32);
		return true;
	}
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