#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include <array>
#include <vector>

class Gameboy {

friend class GameBoyTest;

private:
	unsigned short opcode;
	unsigned short pc;
	unsigned short sp;

	unsigned int cycle_num;

	bool biosFlag;
	bool haltFlag;
	bool stopFlag;
	bool interruptsFlag;
	bool debugFlag;

	unsigned char a;
	unsigned char f;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned char e;
	unsigned char h;
	unsigned char l;

	std::array<unsigned char, 256> bios = {{
		0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
		0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
		0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
		0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
		0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
		0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
		0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
		0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
		0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
		0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
		0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
		0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
		0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
		0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x4C,
		0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
		0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
	}};

	std::vector<unsigned char>       rom;
	std::vector<unsigned char>       eram;
	std::array<unsigned char, 8192>  vram;
	std::array<unsigned char, 8192>  wram;
	std::array<unsigned char, 256>   oam;
	std::array<unsigned char, 128>   zram;
	std::array<unsigned char, 128>   ioregs;


	enum RamType {BIOS, ROM, VRAM, ERAM, WRAM, OAM, ZRAM, IOREGS};

	unsigned char readByte(unsigned short addr);
	unsigned short readWord(unsigned short addr);

	bool writeByte(unsigned char data, unsigned short addr);
	bool writeWord(unsigned short data, unsigned short addr);

	unsigned short getHL();
	void setHL(unsigned short value);
	unsigned short getBC();
	unsigned short getDE();
	void setBC(unsigned short value);
	void setDE(unsigned short value);
	
	//Flag operations
	void SZF();
	void CZF();
	void SOF();
	void COF();
	void SHF();
	void CHF();
	void SCF();
	//Instruction to toggle carry flag
	void CCF();
	//Zeros carry flag
	void ZCF();

	void EXT();

	void dumpRam(RamType type);
	void printDebug();

	//Misc
	void NOP();
	void STOP();
	void HALT();
	void DAA();
	void DI();
	void EI();

	//Register loads
	void LDrr_b_a();
	void LDrr_b_c();
	void LDrr_b_d();
	void LDrr_b_e();
	void LDrr_b_h();
	void LDrr_b_l();
	void LDrr_c_a();
	void LDrr_c_b();
	void LDrr_c_d();
	void LDrr_c_e();
	void LDrr_c_h();
	void LDrr_c_l();
	void LDrr_d_a();
	void LDrr_d_b();
	void LDrr_d_c();
	void LDrr_d_e();
	void LDrr_d_h();
	void LDrr_d_l();
	void LDrr_e_a();
	void LDrr_e_b();
	void LDrr_e_c();
	void LDrr_e_d();
	void LDrr_e_h();
	void LDrr_e_l();
	void LDrr_h_a();
	void LDrr_h_b();
	void LDrr_h_c();
	void LDrr_h_d();
	void LDrr_h_e();
	void LDrr_h_l();
	void LDrr_l_a();
	void LDrr_l_b();
	void LDrr_l_c();
	void LDrr_l_d();
	void LDrr_l_e();
	void LDrr_l_h();
	void LDrr_a_b();
	void LDrr_a_c();
	void LDrr_a_d();
	void LDrr_a_e();
	void LDrr_a_h();
	void LDrr_a_l();
	void LDrr_sp_hl();
	void LDHLrr_hl_sp();

	//Immediate Loads
	void LDrn_a();
	void LDrn_b();
	void LDrn_c();
	void LDrn_d();
	void LDrn_e();
	void LDrn_h();
	void LDrn_l();
	void LDrw_bc();
	void LDrw_de();
	void LDrw_hl();
	void LDrw_sp();

	//Memory Loads
	void LDrm_a_hl();
	void LDrm_b_hl();
	void LDrm_c_hl();
	void LDrm_d_hl();
	void LDrm_e_hl();
	void LDrm_h_hl();
	void LDrm_l_hl();
	void LDrm_a_bc();
	void LDrm_a_de();
	void LDrm_a_w();
	void LDIrm_a_hl();
	void LDDrm_a_hl();
	void LDHrm_a_n();

	//Memory Stores
	void LDmr_hl_a();
	void LDmr_hl_b();
	void LDmr_hl_c();
	void LDmr_hl_d();
	void LDmr_hl_e();
	void LDmr_hl_h();
	void LDmr_hl_l();
	void LDmr_bc_a();
	void LDmr_de_a();
	void LDmr_w_a();
	void LDmr_w_sp();
	void LDmn_hl_n();
	void LDImr_hl_a();
	void LDDmr_hl_a();
	void LDHmr_n_a();
	void LDHmr_c_a();

	//Increment/Decrement
	void INCr_a();
	void INCr_b();
	void INCr_c();
	void INCr_d();
	void INCr_e();
	void INCr_h();
	void INCr_l();
	void INCr_bc();
	void INCr_de();
	void INCr_hl();
	void INCr_sp();
	void INCm_hl();
	void DECr_a();
	void DECr_b();
	void DECr_c();
	void DECr_d();
	void DECr_e();
	void DECr_h();
	void DECr_l();
	void DECr_bc();
	void DECr_de();
	void DECr_hl();
	void DECr_sp();
	void DECm_hl();

	//Addition
	void ADDrr_a_a();
	void ADDrr_a_b();
	void ADDrr_a_c();
	void ADDrr_a_d();
	void ADDrr_a_e();
	void ADDrr_a_h();
	void ADDrr_a_l();
	void ADDrr_hl_bc();
	void ADDrr_hl_de();
	void ADDrr_hl_hl();
	void ADDrr_hl_sp();
	void ADDrn_a();
	void ADDrn_sp();
	void ADDrm_a_hl();
	void ADCrr_a_a();
	void ADCrr_a_b();
	void ADCrr_a_c();
	void ADCrr_a_d();
	void ADCrr_a_e();
	void ADCrr_a_h();
	void ADCrr_a_l();
	void ADCrm_a_hl();
	void ADCrn_a();

	//Subtraction
	void SUBrr_a_a();
	void SUBrr_a_b();
	void SUBrr_a_c();
	void SUBrr_a_d();
	void SUBrr_a_e();
	void SUBrr_a_h();
	void SUBrr_a_l();
	void SUBrn_a();
	void SUBrm_a_hl();
	void SBCrr_a_a();
	void SBCrr_a_c();
	void SBCrr_a_b();
	void SBCrr_a_d();
	void SBCrr_a_e();
	void SBCrr_a_h();
	void SBCrr_a_l();
	void SBCrm_a_hl();
	void SBCrn_a();

	//Logical Operation
	void ANDrr_a_a();
	void ANDrr_a_b();
	void ANDrr_a_c();
	void ANDrr_a_d();
	void ANDrr_a_e();
	void ANDrr_a_h();
	void ANDrr_a_l();
	void ANDrn_a();
	void ANDrm_a_hl();
	void ORrr_a_a();
	void ORrr_a_b();
	void ORrr_a_c();
	void ORrr_a_d();
	void ORrr_a_e();
	void ORrr_a_h();
	void ORrr_a_l();
	void ORrn_a();
	void ORrm_a_hl();
	void XORrr_a_a();
	void XORrr_a_b();
	void XORrr_a_c();
	void XORrr_a_d();
	void XORrr_a_e();
	void XORrr_a_h();
	void XORrr_a_l();
	void XORrn_a();
	void XORrm_a_hl();
	void CPL();

	//Comparisoin
	void CPrr_a_a();
	void CPrr_a_b();
	void CPrr_a_c();
	void CPrr_a_d();
	void CPrr_a_e();
	void CPrr_a_h();
	void CPrr_a_l();
	void CPrn_a();
	void CPrm_a_hl();

	//Stack
	void POPr_bc();
	void POPr_de();
	void POPr_af();
	void POPr_hl();
	void PUSHr_bc();
	void PUSHr_de();
	void PUSHr_af();
	void PUSHr_hl();

	//Jumps/Branches
	void JP();
	void JP_hl();
	void JP_c();
	void JP_z();
	void JP_nz();
	void JP_nc();
	void JR();
	void JR_c();
	void JR_z();
	void JR_nz();
	void JR_nc();

	//Calls
	void CALL();
	void CALL_c();
	void CALL_z();
	void CALL_nc();
	void CALL_nz();

	//Restarts
	void RST_0();
	void RST_8();
	void RST_10();
	void RST_18();
	void RST_20();
	void RST_28();
	void RST_30();
	void RST_38();

	//Returns
	void RET();
	void RETI();
	void RET_c();
	void RET_z();
	void RET_nc();
	void RET_nz();

	//Bit Rotations
	void RL();
	// void RLr_a();
	// void RLr_b();
	// void RLr_c();
	// void RLr_d();
	// void RLr_e();
	// void RLr_h();
	// void RLr_l();
	// void RLm_hl();
	void RLC();
	// void RLCr_a();
	// void RLCr_b();
	// void RLCr_c();
	// void RLCr_d();
	// void RLCr_e();
	// void RLCr_h();
	// void RLCr_l();
	// void RLCm_hl();
	void RR();
	// void RRr_a();
	// void RRr_b();
	// void RRr_c();
	// void RRr_d();
	// void RRr_e();
	// void RRr_h();
	// void RRr_l();
	// void RRm_hl();
	void RRC();
	// void RRCr_a();
	// void RRCr_b();
	// void RRCr_c();
	// void RRCr_d();
	// void RRCr_e();
	// void RRCr_h();
	// void RRCr_l();
	// void RRCm_hl();

	//Bit Shifts
	void SLA();
	// void SLAr_a();
	// void SLAr_b();
	// void SLAr_c();
	// void SLAr_d();
	// void SLAr_e();
	// void SLAr_h();
	// void SLAr_l();
	// void SLAm_hl();
	void SRA();
	// void SRAr_a();
	// void SRAr_b();
	// void SRAr_c();
	// void SRAr_d();
	// void SRAr_e();
	// void SRAr_h();
	// void SRAr_l();
	// void SRAm_hl();
	void SRL();
	// void SRLr_a();
	// void SRLr_b();
	// void SRLr_c();
	// void SRLr_d();
	// void SRLr_e();
	// void SRLr_h();
	// void SRLr_l();
	// void SRLm_hl();

	//Swaps
	void SWAPr_a();
	void SWAPr_b();
	void SWAPr_c();
	void SWAPr_d();
	void SWAPr_e();
	void SWAPr_h();
	void SWAPr_l();
	void SWAPm_hl();

	//Test bit
	void BIT(unsigned char bNum, unsigned char loc);

	///Clear bit
	void RES(unsigned char bNum, unsigned char loc);

	//Set bit
	void SET(unsigned char bNum, unsigned char loc);

	void (Gameboy::*opMap[16][16])(void) = 
	{	//0
		{&Gameboy::NOP         , &Gameboy::LDrw_bc    , &Gameboy::LDmr_bc_a , &Gameboy::INCr_bc  , &Gameboy::INCr_b   , &Gameboy::DECr_b   , &Gameboy::LDrn_b    , &Gameboy::RLC, 
		 &Gameboy::LDmr_w_sp   , &Gameboy::ADDrr_hl_bc, &Gameboy::LDrm_a_bc , &Gameboy::DECr_bc  , &Gameboy::INCr_c   , &Gameboy::DECr_c   , &Gameboy::LDrn_c    , &Gameboy::RRC},
		//1
		{&Gameboy::STOP        , &Gameboy::LDrw_de    , &Gameboy::LDmr_de_a , &Gameboy::INCr_de  , &Gameboy::INCr_d   , &Gameboy::DECr_d   , &Gameboy::LDrn_d   , &Gameboy::RL, 
		 &Gameboy::JR          , &Gameboy::ADDrr_hl_de, &Gameboy::LDrm_a_de , &Gameboy::DECr_de  , &Gameboy::INCr_e   , &Gameboy::DECr_e   , &Gameboy::LDrn_e    , &Gameboy::RR},
		//2
		{&Gameboy::JR_nz       , &Gameboy::LDrw_hl    , &Gameboy::LDImr_hl_a, &Gameboy::INCr_hl  , &Gameboy::INCr_h   , &Gameboy::DECr_h   , &Gameboy::LDrn_h    , &Gameboy::DAA, 
		 &Gameboy::JR_z        , &Gameboy::ADDrr_hl_hl, &Gameboy::LDIrm_a_hl, &Gameboy::DECr_hl  , &Gameboy::INCr_l   , &Gameboy::DECr_l   , &Gameboy::LDrn_l    , &Gameboy::CPL},
		//3
		{&Gameboy::JR_nc       , &Gameboy::LDrw_sp    , &Gameboy::LDDmr_hl_a, &Gameboy::INCr_sp  , &Gameboy::INCm_hl  , &Gameboy::DECm_hl  , &Gameboy::LDmn_hl_n , &Gameboy::SCF, 
		 &Gameboy::JR_c        , &Gameboy::ADDrr_hl_sp, &Gameboy::LDDrm_a_hl, &Gameboy::DECr_sp  , &Gameboy::INCr_a   , &Gameboy::DECr_a   , &Gameboy::LDrn_a    , &Gameboy::CCF},
		//4
		{&Gameboy::NOP         , &Gameboy::LDrr_b_c   , &Gameboy::LDrr_b_d  , &Gameboy::LDrr_b_e , &Gameboy::LDrr_b_h , &Gameboy::LDrr_b_l , &Gameboy::LDrm_b_hl , &Gameboy::LDrr_b_a, 
		 &Gameboy::LDrr_c_b    , &Gameboy::NOP        , &Gameboy::LDrr_c_d  , &Gameboy::LDrr_c_e , &Gameboy::LDrr_c_h , &Gameboy::LDrr_c_l , &Gameboy::LDrm_c_hl , &Gameboy::LDrr_c_a},
		//5
		{&Gameboy::LDrr_d_b    , &Gameboy::LDrr_d_c   , &Gameboy::NOP       , &Gameboy::LDrr_d_e , &Gameboy::LDrr_d_h , &Gameboy::LDrr_d_l , &Gameboy::LDrm_d_hl , &Gameboy::LDrr_d_a, 
		 &Gameboy::LDrr_e_b    , &Gameboy::LDrr_e_c   , &Gameboy::LDrr_e_d  , &Gameboy::NOP      , &Gameboy::LDrr_e_h , &Gameboy::LDrr_e_l , &Gameboy::LDrm_e_hl , &Gameboy::LDrr_e_a},
		//6
		{&Gameboy::LDrr_h_b    , &Gameboy::LDrr_h_c   , &Gameboy::LDrr_h_d  , &Gameboy::LDrr_h_e , &Gameboy::NOP      , &Gameboy::LDrr_h_l , &Gameboy::LDrm_h_hl , &Gameboy::LDrr_h_a, 
		 &Gameboy::LDrr_l_b    , &Gameboy::LDrr_l_c   , &Gameboy::LDrr_l_d  , &Gameboy::LDrr_l_e , &Gameboy::LDrr_l_h , &Gameboy::NOP      , &Gameboy::LDrm_l_hl , &Gameboy::LDrr_l_a},
		//7
		{&Gameboy::LDmr_hl_b   , &Gameboy::LDmr_hl_c  , &Gameboy::LDmr_hl_d , &Gameboy::LDmr_hl_e, &Gameboy::LDmr_hl_h, &Gameboy::LDmr_hl_l, &Gameboy::HALT      , &Gameboy::LDmr_hl_a, 
		 &Gameboy::LDrr_a_b    , &Gameboy::LDrr_a_c   , &Gameboy::LDrr_a_d  , &Gameboy::LDrr_a_e , &Gameboy::LDrr_a_h , &Gameboy::LDrr_a_l , &Gameboy::LDrm_a_hl , &Gameboy::NOP},
		//8
		{&Gameboy::ADDrr_a_b   , &Gameboy::ADDrr_a_c  , &Gameboy::ADDrr_a_d , &Gameboy::ADDrr_a_e, &Gameboy::ADDrr_a_h, &Gameboy::ADDrr_a_l, &Gameboy::ADDrm_a_hl, &Gameboy::ADDrr_a_a, 
		 &Gameboy::ADCrr_a_b   , &Gameboy::ADCrr_a_c  , &Gameboy::ADCrr_a_d , &Gameboy::ADCrr_a_e, &Gameboy::ADCrr_a_h, &Gameboy::ADCrr_a_l, &Gameboy::ADCrm_a_hl, &Gameboy::ADCrr_a_a},
		//9
		{&Gameboy::SUBrr_a_b   , &Gameboy::SUBrr_a_c  , &Gameboy::SUBrr_a_d , &Gameboy::SUBrr_a_e, &Gameboy::SUBrr_a_h, &Gameboy::SUBrr_a_l, &Gameboy::SUBrm_a_hl, &Gameboy::SUBrr_a_a, 
		 &Gameboy::SBCrr_a_b   , &Gameboy::SBCrr_a_c  , &Gameboy::SBCrr_a_d , &Gameboy::SBCrr_a_e, &Gameboy::SBCrr_a_h, &Gameboy::SBCrr_a_l, &Gameboy::SBCrm_a_hl, &Gameboy::SBCrr_a_a},
		//A
		{&Gameboy::ANDrr_a_b   , &Gameboy::ANDrr_a_c  , &Gameboy::ANDrr_a_d , &Gameboy::ANDrr_a_e, &Gameboy::ANDrr_a_h, &Gameboy::ANDrr_a_l, &Gameboy::ANDrm_a_hl, &Gameboy::ANDrr_a_a, 
		 &Gameboy::XORrr_a_b   , &Gameboy::XORrr_a_c  , &Gameboy::XORrr_a_d , &Gameboy::XORrr_a_e, &Gameboy::XORrr_a_h, &Gameboy::XORrr_a_l, &Gameboy::XORrm_a_hl, &Gameboy::XORrr_a_a},
		//B
		{&Gameboy::ORrr_a_b    , &Gameboy::ORrr_a_c   , &Gameboy::ORrr_a_d  , &Gameboy::ORrr_a_e , &Gameboy::ORrr_a_h , &Gameboy::ORrr_a_l , &Gameboy::ORrm_a_hl , &Gameboy::ORrr_a_a, 
		 &Gameboy::CPrr_a_b    , &Gameboy::CPrr_a_c   , &Gameboy::CPrr_a_d  , &Gameboy::CPrr_a_e , &Gameboy::CPrr_a_h , &Gameboy::CPrr_a_l , &Gameboy::CPrm_a_hl, &Gameboy::CPrr_a_a},
		//C
		{&Gameboy::RET_nz      , &Gameboy::POPr_bc    , &Gameboy::JP_nz     , &Gameboy::JP       , &Gameboy::CALL_nz  , &Gameboy::PUSHr_bc , &Gameboy::ADDrn_a   , &Gameboy::RST_0, 
		 &Gameboy::RET_z       , &Gameboy::RET        , &Gameboy::JP_z      , &Gameboy::EXT      , &Gameboy::CALL_z   , &Gameboy::CALL     , &Gameboy::ADCrn_a   , &Gameboy::RST_8},
		//D
		{&Gameboy::RET_nc      , &Gameboy::POPr_de    , &Gameboy::JP_nc     , &Gameboy::NOP      , &Gameboy::CALL_nc  , &Gameboy::PUSHr_de , &Gameboy::SUBrn_a   , &Gameboy::RST_10, 
		 &Gameboy::RET_c       , &Gameboy::RETI       , &Gameboy::JP_c      , &Gameboy::NOP      , &Gameboy::CALL_c   , &Gameboy::NOP      , &Gameboy::SBCrn_a   , &Gameboy::RST_18},
		//E
		{&Gameboy::LDHmr_n_a   , &Gameboy::POPr_hl    , &Gameboy::LDHmr_c_a , &Gameboy::NOP      , &Gameboy::NOP      , &Gameboy::PUSHr_hl , &Gameboy::ANDrn_a   , &Gameboy::RST_20, 
		 &Gameboy::ADDrn_sp    , &Gameboy::JP_hl      , &Gameboy::LDmr_w_a  , &Gameboy::NOP      , &Gameboy::NOP      , &Gameboy::NOP      , &Gameboy::XORrn_a   , &Gameboy::RST_28},
		//F
		{&Gameboy::LDHrm_a_n   , &Gameboy::POPr_af    , &Gameboy::NOP       , &Gameboy::DI       , &Gameboy::NOP      , &Gameboy::PUSHr_af , &Gameboy::ORrn_a    , &Gameboy::RST_30, 
		 &Gameboy::LDHLrr_hl_sp, &Gameboy::LDrr_sp_hl , &Gameboy::LDrm_a_w  , &Gameboy::EI       , &Gameboy::NOP      , &Gameboy::NOP      , &Gameboy::CPrn_a    , &Gameboy::RST_38}
	};

	void (Gameboy::*opMapExt[4][16])(void) = 
	{
		{&Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP,	&Gameboy::NOP, 
		 &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP},

		{&Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, 
		 &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP},

		{&Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, 
		 &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP},

		{&Gameboy::SWAPr_b, &Gameboy::SWAPr_c, &Gameboy::SWAPr_d, &Gameboy::SWAPr_e, &Gameboy::SWAPr_h, &Gameboy::SWAPr_l, &Gameboy::SWAPm_hl, &Gameboy::SWAPr_a, 
		 &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP, &Gameboy::NOP}
	};

public:
	bool drawFlag;

	bool initialize(bool debug = false);
	bool reset();
	bool loadGame(std::string path);
	bool emulateCycle(unsigned long delta);
	bool getKeys(char* keys);

};

#endif