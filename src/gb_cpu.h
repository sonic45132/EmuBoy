#ifndef GAMEBOYCPU_H
#define GAMEBOYCPU_H

#include "gb_mem.h"

class GameboyCPU {

private: 
	unsigned short opcode;
	unsigned short pc;
	unsigned short sp;

	GameboyMemory* mem;

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

	
	void printDebug();

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

	void (GameboyCPU::*opMap[16][16])(void) = 
	{	//0
		{&GameboyCPU::NOP         , &GameboyCPU::LDrw_bc    , &GameboyCPU::LDmr_bc_a , &GameboyCPU::INCr_bc  , &GameboyCPU::INCr_b   , &GameboyCPU::DECr_b   , &GameboyCPU::LDrn_b    , &GameboyCPU::RLC, 
		 &GameboyCPU::LDmr_w_sp   , &GameboyCPU::ADDrr_hl_bc, &GameboyCPU::LDrm_a_bc , &GameboyCPU::DECr_bc  , &GameboyCPU::INCr_c   , &GameboyCPU::DECr_c   , &GameboyCPU::LDrn_c    , &GameboyCPU::RRC},
		//1
		{&GameboyCPU::STOP        , &GameboyCPU::LDrw_de    , &GameboyCPU::LDmr_de_a , &GameboyCPU::INCr_de  , &GameboyCPU::INCr_d   , &GameboyCPU::DECr_d   , &GameboyCPU::LDrn_d   , &GameboyCPU::RL, 
		 &GameboyCPU::JR          , &GameboyCPU::ADDrr_hl_de, &GameboyCPU::LDrm_a_de , &GameboyCPU::DECr_de  , &GameboyCPU::INCr_e   , &GameboyCPU::DECr_e   , &GameboyCPU::LDrn_e    , &GameboyCPU::RR},
		//2
		{&GameboyCPU::JR_nz       , &GameboyCPU::LDrw_hl    , &GameboyCPU::LDImr_hl_a, &GameboyCPU::INCr_hl  , &GameboyCPU::INCr_h   , &GameboyCPU::DECr_h   , &GameboyCPU::LDrn_h    , &GameboyCPU::DAA, 
		 &GameboyCPU::JR_z        , &GameboyCPU::ADDrr_hl_hl, &GameboyCPU::LDIrm_a_hl, &GameboyCPU::DECr_hl  , &GameboyCPU::INCr_l   , &GameboyCPU::DECr_l   , &GameboyCPU::LDrn_l    , &GameboyCPU::CPL},
		//3
		{&GameboyCPU::JR_nc       , &GameboyCPU::LDrw_sp    , &GameboyCPU::LDDmr_hl_a, &GameboyCPU::INCr_sp  , &GameboyCPU::INCm_hl  , &GameboyCPU::DECm_hl  , &GameboyCPU::LDmn_hl_n , &GameboyCPU::SCF, 
		 &GameboyCPU::JR_c        , &GameboyCPU::ADDrr_hl_sp, &GameboyCPU::LDDrm_a_hl, &GameboyCPU::DECr_sp  , &GameboyCPU::INCr_a   , &GameboyCPU::DECr_a   , &GameboyCPU::LDrn_a    , &GameboyCPU::CCF},
		//4
		{&GameboyCPU::NOP         , &GameboyCPU::LDrr_b_c   , &GameboyCPU::LDrr_b_d  , &GameboyCPU::LDrr_b_e , &GameboyCPU::LDrr_b_h , &GameboyCPU::LDrr_b_l , &GameboyCPU::LDrm_b_hl , &GameboyCPU::LDrr_b_a, 
		 &GameboyCPU::LDrr_c_b    , &GameboyCPU::NOP        , &GameboyCPU::LDrr_c_d  , &GameboyCPU::LDrr_c_e , &GameboyCPU::LDrr_c_h , &GameboyCPU::LDrr_c_l , &GameboyCPU::LDrm_c_hl , &GameboyCPU::LDrr_c_a},
		//5
		{&GameboyCPU::LDrr_d_b    , &GameboyCPU::LDrr_d_c   , &GameboyCPU::NOP       , &GameboyCPU::LDrr_d_e , &GameboyCPU::LDrr_d_h , &GameboyCPU::LDrr_d_l , &GameboyCPU::LDrm_d_hl , &GameboyCPU::LDrr_d_a, 
		 &GameboyCPU::LDrr_e_b    , &GameboyCPU::LDrr_e_c   , &GameboyCPU::LDrr_e_d  , &GameboyCPU::NOP      , &GameboyCPU::LDrr_e_h , &GameboyCPU::LDrr_e_l , &GameboyCPU::LDrm_e_hl , &GameboyCPU::LDrr_e_a},
		//6
		{&GameboyCPU::LDrr_h_b    , &GameboyCPU::LDrr_h_c   , &GameboyCPU::LDrr_h_d  , &GameboyCPU::LDrr_h_e , &GameboyCPU::NOP      , &GameboyCPU::LDrr_h_l , &GameboyCPU::LDrm_h_hl , &GameboyCPU::LDrr_h_a, 
		 &GameboyCPU::LDrr_l_b    , &GameboyCPU::LDrr_l_c   , &GameboyCPU::LDrr_l_d  , &GameboyCPU::LDrr_l_e , &GameboyCPU::LDrr_l_h , &GameboyCPU::NOP      , &GameboyCPU::LDrm_l_hl , &GameboyCPU::LDrr_l_a},
		//7
		{&GameboyCPU::LDmr_hl_b   , &GameboyCPU::LDmr_hl_c  , &GameboyCPU::LDmr_hl_d , &GameboyCPU::LDmr_hl_e, &GameboyCPU::LDmr_hl_h, &GameboyCPU::LDmr_hl_l, &GameboyCPU::HALT      , &GameboyCPU::LDmr_hl_a, 
		 &GameboyCPU::LDrr_a_b    , &GameboyCPU::LDrr_a_c   , &GameboyCPU::LDrr_a_d  , &GameboyCPU::LDrr_a_e , &GameboyCPU::LDrr_a_h , &GameboyCPU::LDrr_a_l , &GameboyCPU::LDrm_a_hl , &GameboyCPU::NOP},
		//8
		{&GameboyCPU::ADDrr_a_b   , &GameboyCPU::ADDrr_a_c  , &GameboyCPU::ADDrr_a_d , &GameboyCPU::ADDrr_a_e, &GameboyCPU::ADDrr_a_h, &GameboyCPU::ADDrr_a_l, &GameboyCPU::ADDrm_a_hl, &GameboyCPU::ADDrr_a_a, 
		 &GameboyCPU::ADCrr_a_b   , &GameboyCPU::ADCrr_a_c  , &GameboyCPU::ADCrr_a_d , &GameboyCPU::ADCrr_a_e, &GameboyCPU::ADCrr_a_h, &GameboyCPU::ADCrr_a_l, &GameboyCPU::ADCrm_a_hl, &GameboyCPU::ADCrr_a_a},
		//9
		{&GameboyCPU::SUBrr_a_b   , &GameboyCPU::SUBrr_a_c  , &GameboyCPU::SUBrr_a_d , &GameboyCPU::SUBrr_a_e, &GameboyCPU::SUBrr_a_h, &GameboyCPU::SUBrr_a_l, &GameboyCPU::SUBrm_a_hl, &GameboyCPU::SUBrr_a_a, 
		 &GameboyCPU::SBCrr_a_b   , &GameboyCPU::SBCrr_a_c  , &GameboyCPU::SBCrr_a_d , &GameboyCPU::SBCrr_a_e, &GameboyCPU::SBCrr_a_h, &GameboyCPU::SBCrr_a_l, &GameboyCPU::SBCrm_a_hl, &GameboyCPU::SBCrr_a_a},
		//A
		{&GameboyCPU::ANDrr_a_b   , &GameboyCPU::ANDrr_a_c  , &GameboyCPU::ANDrr_a_d , &GameboyCPU::ANDrr_a_e, &GameboyCPU::ANDrr_a_h, &GameboyCPU::ANDrr_a_l, &GameboyCPU::ANDrm_a_hl, &GameboyCPU::ANDrr_a_a, 
		 &GameboyCPU::XORrr_a_b   , &GameboyCPU::XORrr_a_c  , &GameboyCPU::XORrr_a_d , &GameboyCPU::XORrr_a_e, &GameboyCPU::XORrr_a_h, &GameboyCPU::XORrr_a_l, &GameboyCPU::XORrm_a_hl, &GameboyCPU::XORrr_a_a},
		//B
		{&GameboyCPU::ORrr_a_b    , &GameboyCPU::ORrr_a_c   , &GameboyCPU::ORrr_a_d  , &GameboyCPU::ORrr_a_e , &GameboyCPU::ORrr_a_h , &GameboyCPU::ORrr_a_l , &GameboyCPU::ORrm_a_hl , &GameboyCPU::ORrr_a_a, 
		 &GameboyCPU::CPrr_a_b    , &GameboyCPU::CPrr_a_c   , &GameboyCPU::CPrr_a_d  , &GameboyCPU::CPrr_a_e , &GameboyCPU::CPrr_a_h , &GameboyCPU::CPrr_a_l , &GameboyCPU::CPrm_a_hl, &GameboyCPU::CPrr_a_a},
		//C
		{&GameboyCPU::RET_nz      , &GameboyCPU::POPr_bc    , &GameboyCPU::JP_nz     , &GameboyCPU::JP       , &GameboyCPU::CALL_nz  , &GameboyCPU::PUSHr_bc , &GameboyCPU::ADDrn_a   , &GameboyCPU::RST_0, 
		 &GameboyCPU::RET_z       , &GameboyCPU::RET        , &GameboyCPU::JP_z      , &GameboyCPU::EXT      , &GameboyCPU::CALL_z   , &GameboyCPU::CALL     , &GameboyCPU::ADCrn_a   , &GameboyCPU::RST_8},
		//D
		{&GameboyCPU::RET_nc      , &GameboyCPU::POPr_de    , &GameboyCPU::JP_nc     , &GameboyCPU::NOP      , &GameboyCPU::CALL_nc  , &GameboyCPU::PUSHr_de , &GameboyCPU::SUBrn_a   , &GameboyCPU::RST_10, 
		 &GameboyCPU::RET_c       , &GameboyCPU::RETI       , &GameboyCPU::JP_c      , &GameboyCPU::NOP      , &GameboyCPU::CALL_c   , &GameboyCPU::NOP      , &GameboyCPU::SBCrn_a   , &GameboyCPU::RST_18},
		//E
		{&GameboyCPU::LDHmr_n_a   , &GameboyCPU::POPr_hl    , &GameboyCPU::LDHmr_c_a , &GameboyCPU::NOP      , &GameboyCPU::NOP      , &GameboyCPU::PUSHr_hl , &GameboyCPU::ANDrn_a   , &GameboyCPU::RST_20, 
		 &GameboyCPU::ADDrn_sp    , &GameboyCPU::JP_hl      , &GameboyCPU::LDmr_w_a  , &GameboyCPU::NOP      , &GameboyCPU::NOP      , &GameboyCPU::NOP      , &GameboyCPU::XORrn_a   , &GameboyCPU::RST_28},
		//F
		{&GameboyCPU::LDHrm_a_n   , &GameboyCPU::POPr_af    , &GameboyCPU::NOP       , &GameboyCPU::DI       , &GameboyCPU::NOP      , &GameboyCPU::PUSHr_af , &GameboyCPU::ORrn_a    , &GameboyCPU::RST_30, 
		 &GameboyCPU::LDHLrr_hl_sp, &GameboyCPU::LDrr_sp_hl , &GameboyCPU::LDrm_a_w  , &GameboyCPU::EI       , &GameboyCPU::NOP      , &GameboyCPU::NOP      , &GameboyCPU::CPrn_a    , &GameboyCPU::RST_38}
	};

	void (GameboyCPU::*opMapExt[4][16])(void) = 
	{
		{&GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP,	&GameboyCPU::NOP, 
		 &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP},

		{&GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, 
		 &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP},

		{&GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, 
		 &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP},

		{&GameboyCPU::SWAPr_b, &GameboyCPU::SWAPr_c, &GameboyCPU::SWAPr_d, &GameboyCPU::SWAPr_e, &GameboyCPU::SWAPr_h, &GameboyCPU::SWAPr_l, &GameboyCPU::SWAPm_hl, &GameboyCPU::SWAPr_a, 
		 &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP, &GameboyCPU::NOP}
	};

public:
	bool init(GameboyMemory* memory, bool debug);
	bool execute();


};

#endif