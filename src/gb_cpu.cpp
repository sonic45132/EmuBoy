#include "gb_cpu.h"
#include <map>

unsigned short GameboyCPU::getHL() {
	unsigned short temp = l;
	temp |= (h<<8);
	return temp;
}

void GameboyCPU::setHL(unsigned short value) {
	l = value&0x00FF;
	h = (value&0xFF00)>>8;
}

unsigned short GameboyCPU::getBC() {
	unsigned short temp = c;
	temp |= (b<<8);
	return temp;
}

void GameboyCPU::setBC(unsigned short value) {
	c = value&0x00FF;
	b = (value&0xFF00)>>8;
}

unsigned short GameboyCPU::getDE() {
	unsigned short temp = e;
	temp |= (d<<8);
	return temp;
}

void GameboyCPU::setDE(unsigned short value) {
	e = value&0x00FF;
	d = (value&0xFF00)>>8;
}

inline void GameboyCPU::SZF() {
	f |= 0x80;
}

inline void GameboyCPU::CZF() {
	f &= 0x70;
}

inline void GameboyCPU::SOF() {
	f |= 0x40;
}

inline void GameboyCPU::COF() {
	f &= 0xB0;
}

inline void GameboyCPU::SHF() {
	f |= 0x20;
}

inline void GameboyCPU::CHF() {
	f &= 0xD0;
}

void GameboyCPU::NOP() {
	printf("NOP\n");
}

void GameboyCPU::HALT() {
	haltFlag = true;
}

void GameboyCPU::STOP() {
	stopFlag = true;
}

void GameboyCPU::SCF() {
	f |= 0x10;
}

void GameboyCPU::CCF() {
	f &= 0x90;
	f ^= (1 << 4);
}

inline void GameboyCPU::ZCF() {
	f &= 0xE0;
}

void GameboyCPU::DAA() {
	unsigned char th = ((a%100)/10);
	unsigned char tl = (a % 10);
	a = ((th << 4) | tl);
}

void GameboyCPU::DI() {
	interruptsFlag = false;
	mem->writeByte(0, 0xFFFF);
}

void GameboyCPU::EI() {
	interruptsFlag = true;
	mem->writeByte(1, 0xFFFF);
}

void GameboyCPU::LDrr_a_b() {
	a = b;
}

void GameboyCPU::LDrr_a_c() {
	a = c;
}

void GameboyCPU::LDrr_a_d() {
	a = d;
}

void GameboyCPU::LDrr_a_e() {
	a = e;
}

void GameboyCPU::LDrr_a_h() {
	a = h;
}

void GameboyCPU::LDrr_a_l() {
	a = l;
}

void GameboyCPU::LDrr_b_a() {
	b = a;
}

void GameboyCPU::LDrr_b_c() {
	b = c;
}

void GameboyCPU::LDrr_b_d() {
	b = d;
}

void GameboyCPU::LDrr_b_e() {
	b = e;
}

void GameboyCPU::LDrr_b_h() {
	b = h;
}

void GameboyCPU::LDrr_b_l() {
	b = l;
}

void GameboyCPU::LDrr_c_a() {
	c = a;
}

void GameboyCPU::LDrr_c_b() {
	c = b;
}

void GameboyCPU::LDrr_c_d() {
	c = d;
}

void GameboyCPU::LDrr_c_e() {
	c = e;
}

void GameboyCPU::LDrr_c_h() {
	c = h;
}

void GameboyCPU::LDrr_c_l() {
	c = l;
}

void GameboyCPU::LDrr_d_a() {
	d = a;
}

void GameboyCPU::LDrr_d_b() {
	d = b;
}

void GameboyCPU::LDrr_d_c() {
	d = c;
}

void GameboyCPU::LDrr_d_e() {
	d = e;
}

void GameboyCPU::LDrr_d_h() {
	d = h;
}

void GameboyCPU::LDrr_d_l() {
	d = l;
}

void GameboyCPU::LDrr_e_a() {
	e = a;
}

void GameboyCPU::LDrr_e_b() {
	e = b;
}

void GameboyCPU::LDrr_e_c() {
	e = c;
}

void GameboyCPU::LDrr_e_d() {
	e = d;
}

void GameboyCPU::LDrr_e_h() {
	e = h;
}

void GameboyCPU::LDrr_e_l() {
	e = l;
}

void GameboyCPU::LDrr_h_a() {
	h = a;
}

void GameboyCPU::LDrr_h_b() {
	h = b;
}

void GameboyCPU::LDrr_h_c() {
	h = c;
}

void GameboyCPU::LDrr_h_d() {
	h = d;
}

void GameboyCPU::LDrr_h_e() {
	h = e;
}

void GameboyCPU::LDrr_h_l() {
	h = l;
}

void GameboyCPU::LDrr_l_a() {
	l = a;
}

void GameboyCPU::LDrr_l_b() {
	l = b;
}

void GameboyCPU::LDrr_l_c() {
	l = c;
}

void GameboyCPU::LDrr_l_d() {
	l = d;
}

void GameboyCPU::LDrr_l_e() {
	l = e;
}

void GameboyCPU::LDrr_l_h() {
	l = h;
}

void GameboyCPU::LDrr_sp_hl() {
	sp = getHL();
}

void GameboyCPU::LDHLrr_hl_sp() {
	char temp = mem->readByte(pc++);
	short temp2 = sp;
	f &= 0x30;
	short hl = ((short)sp + temp);
	setHL(hl);
	(temp2 > hl) ? SCF() : ZCF();
	((temp2&0x00FF) > (hl&0x00FF)) ? SHF() : CHF();
}

void GameboyCPU::LDrn_a() {
	a = mem->readByte(pc);
	pc++;
}

void GameboyCPU::LDrn_b() {
	b = mem->readByte(pc);
	pc++;
}

void GameboyCPU::LDrn_c() {
	c = mem->readByte(pc);
	pc++;
}

void GameboyCPU::LDrn_d() {
	d = mem->readByte(pc);
	pc++;
}

void GameboyCPU::LDrn_e() {
	e = mem->readByte(pc);
	pc++;
}

void GameboyCPU::LDrn_h() {
	h = mem->readByte(pc);
	pc++;
}

void GameboyCPU::LDrn_l() {
	l = mem->readByte(pc);
	pc++;
}

void GameboyCPU::LDrw_bc() {
	unsigned short temp = mem->readWord(pc);
	setBC(temp);
	pc += 2;
}

void GameboyCPU::LDrw_de() {
	unsigned short temp = mem->readWord(pc);
	setDE(temp);
	pc += 2;
}

void GameboyCPU::LDrw_hl() {
	setHL(mem->readWord(pc));
	pc += 2;
}

void GameboyCPU::LDrw_sp() {
	sp = mem->readWord(pc);
	pc+=2;
}

void GameboyCPU::LDrm_a_hl() {
	a = mem->readByte(getHL());
}

void GameboyCPU::LDrm_b_hl() {
	b = mem->readByte(getHL());
}

void GameboyCPU::LDrm_c_hl() {
	c = mem->readByte(getHL());
}

void GameboyCPU::LDrm_d_hl() {
	d = mem->readByte(getHL());
}

void GameboyCPU::LDrm_e_hl() {
	e = mem->readByte(getHL());
}

void GameboyCPU::LDrm_h_hl() {
	h = mem->readByte(getHL());
}

void GameboyCPU::LDrm_l_hl() {
	l = mem->readByte(getHL());
}

void GameboyCPU::LDrm_a_bc() {
	a = mem->readByte(getBC());
}

void GameboyCPU::LDrm_a_de() {
	a = mem->readByte(getDE());
}

void GameboyCPU::LDrm_a_w() {
	unsigned short temp = mem->readWord(pc);
	pc += 2;
	a = mem->readByte(temp);
}

void GameboyCPU::LDIrm_a_hl() {
	a = mem->readByte(getHL());
	setHL((getHL()+1));
}

void GameboyCPU::LDDrm_a_hl() {
	a = mem->readByte(getHL());
	setHL((getHL()-1));
}

void GameboyCPU::LDHrm_a_n() {
	unsigned short temp = (0xFF00 | mem->readByte(pc));
	pc++;
	a = mem->readByte(temp);
}

void GameboyCPU::LDmr_hl_a() {
	mem->writeByte(a, getHL());
}

void GameboyCPU::LDmr_hl_b() {
	mem->writeByte(b, getHL());	
}

void GameboyCPU::LDmr_hl_c() {
	mem->writeByte(c, getHL());
}

void GameboyCPU::LDmr_hl_d() {
	mem->writeByte(d, getHL());
}

void GameboyCPU::LDmr_hl_e() {
	mem->writeByte(e, getHL());
}

void GameboyCPU::LDmr_hl_h() {
	mem->writeByte(h, getHL());
}

void GameboyCPU::LDmr_hl_l() {
	mem->writeByte(l, getHL());
}

void GameboyCPU::LDmr_bc_a() {
	unsigned short bc = getBC();
	mem->writeByte(a, bc);
}

void GameboyCPU::LDmr_de_a() {
	unsigned short de = e;
	de |= (d << 8);
	mem->writeByte(a, de);
}

void GameboyCPU::LDmr_w_a() {
	mem->writeByte(a, mem->readWord(pc));
	pc+=2;
}

void GameboyCPU::LDmr_w_sp() {
	mem->writeByte(sp, mem->readWord(pc));
	pc+=2;
}

void GameboyCPU::LDmn_hl_n() {
	mem->writeByte(mem->readByte(pc++), getHL());
}

void GameboyCPU::LDImr_hl_a() {
	mem->writeByte(a, getHL());
	setHL((getHL())+1);
}

void GameboyCPU::LDDmr_hl_a() {
	unsigned short hl = getHL();
	mem->writeByte(a, hl);
	setHL(hl-1);
}

void GameboyCPU::LDHmr_n_a() {
	unsigned short temp = (0xFF00 | mem->readByte(pc));
	pc++;
	mem->writeByte(a, temp);
}

void GameboyCPU::LDHmr_c_a() {
	unsigned short temp = (0xFF00 | c);
	mem->writeByte(a, temp);
}

void GameboyCPU::INCr_a() {
	unsigned char temp = a;
	a += 1;
	COF();
	(a == 0) ? SZF() : CZF();
	((a&0x5) < (temp&0xf)) ? SHF() : CHF();
}

void GameboyCPU::INCr_b() {
	unsigned char temp = b;
	b += 1;
	COF();
	(b == 0) ? SZF() : CZF();
	((b&0x5) < (temp&0xf)) ? SHF() : CHF();
}

void GameboyCPU::INCr_c() {
	unsigned char temp = c;
	c += 1;
	COF();
	(c == 0) ? SZF() : CZF();
	((c&0x5) < (temp&0xf)) ? SHF() : CHF();
}

void GameboyCPU::INCr_d() {
	unsigned char temp = d;
	d += 1;
	COF();
	(d == 0) ? SZF() : CZF();
	((d&0x5) < (temp&0xf)) ? SHF() : CHF();
}

void GameboyCPU::INCr_e() {
	unsigned char temp = e;
	e += 1;
	COF();
	(e == 0) ? SZF() : CZF();
	((e&0x5) < (temp&0xf)) ? SHF() : CHF();
}

void GameboyCPU::INCr_h() {
	unsigned char temp = h;
	h += 1;
	COF();
	(h == 0) ? SZF() : CZF();
	((h&0x5) < (temp&0xf)) ? SHF() : CHF();
}

void GameboyCPU::INCr_l() {
	unsigned char temp = l;
	l += 1;
	COF();
	(l == 0) ? SZF() : CZF();
	((l&0x5) < (temp&0xf)) ? SHF() : CHF();
}

void GameboyCPU::INCr_bc() {
	unsigned short bc = getBC();
	bc++;
	setBC(bc);
}

void GameboyCPU::INCr_de() {
	unsigned short de = getDE();
	de++;
	setDE(de);
}

void GameboyCPU::INCr_hl() {
	setHL(getHL()+1);
}

void GameboyCPU::INCr_sp() {
	sp += 1;
}

void GameboyCPU::INCm_hl() {
	unsigned char temp = mem->readByte(getHL());
	unsigned char temp2 = temp;
	temp += 1;
	COF();
	(temp == 0) ? SZF() : CZF();
	((temp&0x5) < (temp2&0xf)) ? SHF() : CHF();
	mem->writeByte(temp, getHL());
}

void GameboyCPU::DECr_a() {
	a -= 1;
	f |= 0x40;
	if(a == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::DECr_b() {
	b -= 1;
	f |= 0x40;
	if(b == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::DECr_c() {
	c -= 1;
	f |= 0x40;
	if(c == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::DECr_d() {
	d -= 1;
	f |= 0x40;
	if(d == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::DECr_e() {
	e -= 1;
	f |= 0x40;
	if(e == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::DECr_h() {
	h -= 1;
	f |= 0x40;
	if(h == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::DECr_l() {
	l -= 1;
	f |= 0x40;
	if(l == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::DECr_bc() {
	unsigned short bc = c;
	bc |= (b << 8);
	bc--;
	b = (bc & 0xF0) >> 8;
	c = (bc & 0x0F);
}

void GameboyCPU::DECr_de() {
	unsigned short de = e;
	de |= (d << 8);
	de--;
	d = (de & 0xF0) >> 8;
	e = (de & 0x0F);
}

void GameboyCPU::DECr_hl() {
	setHL(getHL()-1);
}

void GameboyCPU::DECr_sp() {
	sp -= 1;
}

void GameboyCPU::DECm_hl() {
	unsigned char temp = mem->readByte(getHL());
	temp -= 1;
	mem->writeByte(temp, getHL());
	f |= 0x40;
	if(temp == 0) {
		SZF();
	}
	else {
		CZF();
	}
}

void GameboyCPU::ADDrr_a_a(){ 
	unsigned char temp = a;
	a += a;
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrr_a_b(){ 
	unsigned char temp = a;
	a += b;
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrr_a_c(){ 
	unsigned char temp = a;
	a += c;
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrr_a_d(){ 
	unsigned char temp = a;
	a += d;
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrr_a_e(){ 
	unsigned char temp = a;
	a += e;
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrr_a_h(){ 
	unsigned char temp = a;
	a += h;
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrr_a_l(){ 
	unsigned char temp = a;
	a += l;
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrr_hl_bc() {
	unsigned short temp = c;
	unsigned short prev = getHL();
	temp |= (b << 8);
	setHL((getHL()+ temp));
	f &= 0xB0;
	if(a < prev) { SCF(); }
	if((getHL()&0x3) < (prev&0x3)) { SHF(); }
}

void GameboyCPU::ADDrr_hl_de() {
	unsigned short temp = e;
	unsigned short prev = getHL();
	temp |= (d << 8);
	setHL((getHL()+ temp));
	f &= 0xB0;
	if(a < prev) { SCF(); }
	if((getHL()&0x3) < (prev&0x3)) { SHF(); }
}

void GameboyCPU::ADDrr_hl_hl() {
	unsigned short prev = getHL();
	setHL((getHL()*2));
	f &= 0xB0;
	if(a < prev) { SCF(); }
	if((getHL()&0x3) < (prev&0x3)) { SHF(); }
}

void GameboyCPU::ADDrr_hl_sp() {
	unsigned short prev = getHL();
	setHL(getHL()+sp);
	f &= 0xB0;
	if(a < prev) { SCF(); }
	if((getHL()&0x3) < (prev&0x3)) { SHF(); }
}

void GameboyCPU::ADDrn_a() {
	unsigned char temp = a;
	a += mem->readByte(pc++);
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADDrn_sp() {
	unsigned short prev = sp;
	sp += mem->readByte(pc++);
	f &= 0xC0;
	if(a < prev) { SCF(); }
	if((sp&0x3) < (prev&0x3)) { SHF(); }
}

void GameboyCPU::ADDrm_a_hl() {
	unsigned char temp = a;
	a += mem->readByte(getHL());
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrr_a_a() {
	unsigned char temp = a;
	a += (a + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrr_a_b() {
	unsigned char temp = a;
	a += (b + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrr_a_c() {
	unsigned char temp = a;
	a += (c + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrr_a_d() {
	unsigned char temp = a;
	a += (d + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrr_a_e() {
	unsigned char temp = a;
	a += (e + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrr_a_h() {
	unsigned char temp = a;
	a += (h + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrr_a_l() {
	unsigned char temp = a;
	a += (l + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrm_a_hl() {
	unsigned char temp = a;
	a += (mem->readByte(getHL()) + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ADCrn_a() {
	unsigned char temp = a;
	a += (mem->readByte(pc++) + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrr_a_a() {
	unsigned char temp = a;
	a -= a;
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrr_a_b() {
	unsigned char temp = a;
	a -= b;
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrr_a_c() {
	unsigned char temp = a;
	a -= c;
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrr_a_d() {
	unsigned char temp = a;
	a -= d;
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrr_a_e() {
	unsigned char temp = a;
	a -= e;
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrr_a_h() {
	unsigned char temp = a;
	a -= h;
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrr_a_l() {
	unsigned char temp = a;
	a -= l;
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrn_a() {
	unsigned char temp = a;
	a -= mem->readByte(pc++);
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SUBrm_a_hl() {
	unsigned char temp = a;
	a -= mem->readByte(getHL());
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrr_a_a() {
	unsigned char temp = a;
	a -= (a + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrr_a_c() {
	unsigned char temp = a;
	a -= (c + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrr_a_b() {
	unsigned char temp = a;
	a -= (b + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrr_a_d() {
	unsigned char temp = a;
	a -= (d + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrr_a_e() {
	unsigned char temp = a;
	a -= (e + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrr_a_h() {
	unsigned char temp = a;
	a -= (h + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrr_a_l() {
	unsigned char temp = a;
	a -= (l + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrm_a_hl() {
	unsigned char temp = a;
	a -= (mem->readByte(getHL()) + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::SBCrn_a() {
	unsigned char temp = a;
	a -= (mem->readByte(pc++) + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { SCF(); } else { ZCF(); }
	if((a&0x5) < (temp&0x5)) { SHF(); } else { CHF(); }
	if(a == 0) { SZF(); } else { CZF(); }
}

//Logical Operations
void GameboyCPU::ANDrr_a_a() {
	a &= a;
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrr_a_b() {
	a &= b;
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrr_a_c() {
	a &= c;
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrr_a_d() {
	a &= d;
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrr_a_e() {
	a &= e;
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrr_a_h() {
	a &= h;
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrr_a_l() {
	a &= l;
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrn_a() {
	a &= mem->readByte(pc++);
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ANDrm_a_hl() {
	a &= mem->readByte(getHL());
	SHF();
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrr_a_a() {
	a |= a;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrr_a_b() {
	a |= b;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrr_a_c() {
	a |= c;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrr_a_d() {
	a |= d;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrr_a_e() {
	a |= e;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrr_a_h() {
	a |= h;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrr_a_l() {
	a |= l;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrn_a() {
	a |= mem->readByte(pc++);
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::ORrm_a_hl() {
	a |= mem->readByte(getHL());
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrr_a_a() {
	a ^= a;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrr_a_b() {
	a ^= b;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrr_a_c() {
	a ^= c;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrr_a_d() {
	a ^= d;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrr_a_e() {
	a ^= e;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrr_a_h() {
	a ^= h;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrr_a_l() {
	a ^= l;
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrn_a() {
	a ^= mem->readByte(pc++);
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::XORrm_a_hl() {
	a ^= mem->readByte(getHL());
	f &= 0x80;
	if(a == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPL() {
	a = ~a;
	SHF();
	SOF();
}

//Comparison
void GameboyCPU::CPrr_a_a() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= a;
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrr_a_b() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= b;
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrr_a_c() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= c;
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrr_a_d() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= d;
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrr_a_e() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= e;
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrr_a_h() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= h;
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrr_a_l() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= l;
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrn_a() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= mem->readByte(pc++);
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

void GameboyCPU::CPrm_a_hl() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= mem->readByte(getHL());
	f |= 0x40;
	if(temp < prev) { SCF(); } else { ZCF(); }
	if((temp&0x5) < (prev&0x3)) { SHF(); } else { CHF(); }
	if(temp == 0) { SZF(); } else { CZF(); }
}

//Stack operations
void GameboyCPU::POPr_bc() {
	b = mem->readByte(sp+1);
	c = mem->readByte(sp);
	sp += 2;
}

void GameboyCPU::POPr_de() {
	d = mem->readByte(sp+1);
	e = mem->readByte(sp);
	sp += 2;
}

void GameboyCPU::POPr_af() {
	a = mem->readByte(sp+1);
	f = mem->readByte(sp);
	sp += 2;
}

void GameboyCPU::POPr_hl() {
	h = mem->readByte(sp+1);
	l = mem->readByte(sp);
	sp += 2;
}

void GameboyCPU::PUSHr_bc() {
	mem->writeByte(b, sp-1);
	mem->writeByte(c, sp-2);
	sp -= 2;
}

void GameboyCPU::PUSHr_de() {
	mem->writeByte(d, sp-1);
	mem->writeByte(e, sp-2);
	sp -= 2;
}

void GameboyCPU::PUSHr_af() {
	mem->writeByte(a, sp-1);
	mem->writeByte(f, sp-2);
	sp -= 2;
}

void GameboyCPU::PUSHr_hl() {
	mem->writeByte(h, sp-1);
	mem->writeByte(l, sp-2);
	sp -= 2;
}

//Jumps/Branches
void GameboyCPU::JP() {
	pc = mem->readWord(pc);
}

void GameboyCPU::JP_hl() {
	pc = mem->readWord(getHL());
}

void GameboyCPU::JP_c() {
	if(f&0x10 > 0) {
		pc = mem->readWord(pc);
	}
	else {
		pc += 2;
	}
}

void GameboyCPU::JP_z() {
	if(f&0x80 > 0) {
		pc = mem->readWord(pc);
	}
	else {
		pc += 2;
	}
}

void GameboyCPU::JP_nz() {
	if(f&0x80 == 0) {
		pc = mem->readWord(pc);
	}
	else {
		pc += 2;
	}
}

void GameboyCPU::JP_nc() {
	if(f&0x10 == 0) {
		pc = mem->readWord(pc);
	}
	else {
		pc += 2;
	}
}

void GameboyCPU::JR() {
	pc = ((char)pc + (char)mem->readByte(pc++));
}

void GameboyCPU::JR_c() {
	if((f&0x10) > 0) {
		pc = ((char)pc + (char)mem->readByte(pc++));
	}
	else {
		pc += 1;
	}
}

void GameboyCPU::JR_z() {
	if((f&0x80) > 0) {
		pc = ((char)pc + (char)mem->readByte(pc++));
	}
	else {
		pc += 1;
	}
}

void GameboyCPU::JR_nz() {
	if((f&0x80) == 0) {
		char temp = (char)mem->readByte(pc++);
		pc += temp;
	}
	else {
		pc += 1;
	}
}

void GameboyCPU::JR_nc() {
	if(f&0x10 == 0) {
		pc = ((char)pc + (char)mem->readByte(pc++));
	}
	else {
		pc += 1;
	}
}

void GameboyCPU::CALL() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xFF00)>>8, sp-1);
	mem->writeByte((temp&0x00FF), sp-2);
	pc = mem->readWord(pc);
	sp -= 2;
}

void GameboyCPU::CALL_c() {
	if((f&0x10) > 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		mem->writeByte((temp&0xF0)>>8, sp-1);
		mem->writeByte((temp&0x0F), sp-2);
		pc = mem->readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

void GameboyCPU::CALL_z() {
	if((f&0x80) > 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		mem->writeByte((temp&0xF0)>>8, sp-1);
		mem->writeByte((temp&0x0F), sp-2);
		pc = mem->readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

void GameboyCPU::CALL_nc() {
	if((f&0x10) == 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		mem->writeByte((temp&0xF0)>>8, sp-1);
		mem->writeByte((temp&0x0F), sp-2);
		pc = mem->readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

void GameboyCPU::CALL_nz() {
	if((f&0x80) == 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		mem->writeByte((temp&0xF0)>>8, sp-1);
		mem->writeByte((temp&0x0F), sp-2);
		pc = mem->readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

//Restarts
void GameboyCPU::RST_0() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0000;
}

void GameboyCPU::RST_8() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0008;
}

void GameboyCPU::RST_10() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0010;
}

void GameboyCPU::RST_18() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0018;
}

void GameboyCPU::RST_20() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0020;
}

void GameboyCPU::RST_28() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0028;
}

void GameboyCPU::RST_30() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0030;
}

void GameboyCPU::RST_38() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	mem->writeByte((temp&0xF0)>>8, sp-1);
	mem->writeByte((temp&0x0F), sp-2);
	pc = 0x0038;
}

//Returns
void GameboyCPU::RET() {
	pc = mem->readByte(sp);
	pc |= (mem->readByte(sp+1) << 8);
	sp += 2;
}

void GameboyCPU::RETI() {
	pc = mem->readByte(sp);
	pc |= (mem->readByte(sp+1) << 8);
	sp += 2;
	EI();
}

void GameboyCPU::RET_c() {
	if((f&0x10) > 0) {
		pc = mem->readByte(sp);
		pc |= (mem->readByte(sp+1) << 8);
		sp += 2;
	}
}

void GameboyCPU::RET_z() {
	if((f&0x80) > 0) {
		pc = mem->readByte(sp);
		pc |= (mem->readByte(sp+1) << 8);
		sp += 2;
	}
}

void GameboyCPU::RET_nc() {
	if((f&0x10) == 0) {
		pc = mem->readByte(sp);
		pc |= (mem->readByte(sp+1) << 8);
		sp += 2;
	}
}

void GameboyCPU::RET_nz() {
	if((f&0x80) == 0) {
		pc = mem->readByte(sp);
		pc |= (mem->readByte(sp+1) << 8);
		sp += 2;
	}
}

//Bit Rotations
void GameboyCPU::RL() {
	std::map<int, unsigned char GameboyCPU::*> regMap = 
		{{0, &GameboyCPU::b}, {1, &GameboyCPU::c}, {2, &GameboyCPU::d}, {3, &GameboyCPU::e}, {4, &GameboyCPU::h}, {5, &GameboyCPU::l}, {6, NULL}, {7, &GameboyCPU::a}};


	int regNum = opcode & 0x0F;
	unsigned char GameboyCPU::* reg = regMap[regNum];
	unsigned char temp;
	unsigned short temp2;

	if(reg == NULL) {
		temp = mem->readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	temp2 = temp;
	temp2 = temp2 << 1;

	temp = temp2;
	temp |= ((f&0x10)>>4);

	if(temp2&0x0100 > 0) {
		SCF();
	}
	else {
		ZCF();
	}

	if(reg == NULL) {
		mem->writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}
}

void GameboyCPU::RLC() {
	std::map<int, unsigned char GameboyCPU::*> regMap = 
		{{0, &GameboyCPU::b}, {1, &GameboyCPU::c}, {2, &GameboyCPU::d}, {3, &GameboyCPU::e}, {4, &GameboyCPU::h}, {5, &GameboyCPU::l}, {6, NULL}, {7, &GameboyCPU::a}};

	
	int regNum = opcode & 0x0F;
	unsigned char GameboyCPU::* reg = regMap[regNum];
	unsigned char temp;
	unsigned short temp2;

	if(reg == NULL) {
		temp = mem->readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	temp2 = temp;
	temp2 = temp2 << 1;

	if(temp2&0x0100 > 0) {
		SCF();
	}
	else {
		ZCF();
	}

	temp = temp2;
	temp |= ((f&0x10)>>4);

	if(reg == NULL) {
		mem->writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}	
}

void GameboyCPU::RR() {
	std::map<int, unsigned char GameboyCPU::*> regMap = 
		{{0, &GameboyCPU::b}, {1, &GameboyCPU::c}, {2, &GameboyCPU::d}, {3, &GameboyCPU::e}, {4, &GameboyCPU::h}, {5, &GameboyCPU::l}, {6, NULL}, {7, &GameboyCPU::a}};

	int regNum = opcode & 0x0F;
	unsigned char GameboyCPU::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = mem->readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}	

	if(temp&0x01 > 0) {
		temp = temp >> 1;
		temp |= ((f&0x10)<<3);
		SCF();
	}
	else {
		temp = temp >> 1;
		temp |= ((f&0x10)<<3);
		ZCF();
	}

	if(reg == NULL) {
		mem->writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}
}

void GameboyCPU::RRC() {
	std::map<int, unsigned char GameboyCPU::*> regMap = 
		{{0, &GameboyCPU::b}, {1, &GameboyCPU::c}, {2, &GameboyCPU::d}, {3, &GameboyCPU::e}, {4, &GameboyCPU::h}, {5, &GameboyCPU::l}, {6, NULL}, {7, &GameboyCPU::a}};

	int regNum = opcode & 0x0F;
	unsigned char GameboyCPU::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = mem->readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	if(temp&0x01 > 0) {
		SCF();
	}
	else {
		ZCF();
	}

	temp = temp >> 1;
	temp |= ((f&0x10)<<3);

	if(reg == NULL) {
		mem->writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}	
}

//Bit Shifts
void GameboyCPU::SLA() {
	std::map<int, unsigned char GameboyCPU::*> regMap = 
		{{0, &GameboyCPU::b}, {1, &GameboyCPU::c}, {2, &GameboyCPU::d}, {3, &GameboyCPU::e}, {4, &GameboyCPU::h}, {5, &GameboyCPU::l}, {6, NULL}, {7, &GameboyCPU::a}};

	int regNum = opcode & 0x0F;
	unsigned char GameboyCPU::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = mem->readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	(temp & 0x80 > 0) ? SCF() : ZCF();

	temp = temp << 1;

	(temp == 0) ? SZF() : CZF();

	if(reg == NULL) {
		mem->writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}

}

void GameboyCPU::SRA() {
	std::map<int, unsigned char GameboyCPU::*> regMap = 
		{{0, &GameboyCPU::b}, {1, &GameboyCPU::c}, {2, &GameboyCPU::d}, {3, &GameboyCPU::e}, {4, &GameboyCPU::h}, {5, &GameboyCPU::l}, {6, NULL}, {7, &GameboyCPU::a}};

	int regNum = opcode & 0x0F;
	unsigned char GameboyCPU::* reg = regMap[regNum];
	char temp;

	if(reg == NULL) {
		temp = (char)mem->readByte(getHL());
	}
	else {
		temp = (char)(*this.*reg);
	}

	(temp & 0x01 > 0) ? SCF() : ZCF();

	temp = temp >> 1;

	(temp == 0) ? SZF() : CZF();

	if(reg == NULL) {
		mem->writeByte((unsigned char)temp, getHL());
	}
	else {
		*this.*reg = (unsigned char)temp;
	}

}

void GameboyCPU::SRL() {
	std::map<int, unsigned char GameboyCPU::*> regMap = 
		{{0, &GameboyCPU::b}, {1, &GameboyCPU::c}, {2, &GameboyCPU::d}, {3, &GameboyCPU::e}, {4, &GameboyCPU::h}, {5, &GameboyCPU::l}, {6, NULL}, {7, &GameboyCPU::a}};

	int regNum = opcode & 0x0F;
	unsigned char GameboyCPU::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = mem->readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	(temp & 0x01 > 0) ? SCF() : ZCF();

	temp = temp >> 1;
	temp &= ~(0x80);

	(temp == 0) ? SZF() : CZF();

	if(reg == NULL) {
		mem->writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}

}

//Swap functions
void GameboyCPU::SWAPr_a() {
	unsigned char th = (a & 0xC) >> 4;
	unsigned char tl = (a & 0x3) << 4;
	a = (th | tl);
}

void GameboyCPU::SWAPr_b() {
	unsigned char th = (b & 0xC) >> 4;
	unsigned char tl = (b & 0x3) << 4;
	b = (th | tl);	
}

void GameboyCPU::SWAPr_c() {
	unsigned char th = (c & 0xC) >> 4;
	unsigned char tl = (c & 0x3) << 4;
	c = (th | tl);
}

void GameboyCPU::SWAPr_d() {
	unsigned char th = (d & 0xC) >> 4;
	unsigned char tl = (d & 0x3) << 4;
	d = (th | tl);
}

void GameboyCPU::SWAPr_e() {
	unsigned char th = (e & 0xC) >> 4;
	unsigned char tl = (e & 0x3) << 4;
	e = (th | tl);
}

void GameboyCPU::SWAPr_h() {
	unsigned char th = (h & 0xC) >> 4;
	unsigned char tl = (h & 0x3) << 4;
	h = (th | tl);
}

void GameboyCPU::SWAPr_l() {
	unsigned char th = (l & 0xC) >> 4;
	unsigned char tl = (l & 0x3) << 4;
	l = (th | tl);
}

void GameboyCPU::SWAPm_hl() {
	unsigned char temp = mem->readByte(getHL());
	unsigned char th = (temp & 0xC) >> 4;
	unsigned char tl = (temp & 0x3) << 4;
	temp = (th | tl);
	mem->writeByte(temp, getHL());
}

void GameboyCPU::BIT(unsigned char bNum, unsigned char loc) {
	unsigned char temp;
	COF();
	SHF();
	switch(loc) {
		case 0:
			temp = (b & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
		case 1:
			temp = (c & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
		case 2:
			temp = (d & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
		case 3:
			temp = (e & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
		case 4:
			temp = (h & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
		case 5:
			temp = (l & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
		case 6:
			temp = (mem->readByte(getHL()) & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
		case 7:
			temp = (a & (1 << bNum)) >> bNum;
			if(temp == 0) {
				SZF();
			}
			else {
				CZF();
			}
			break;
	}
}

void GameboyCPU::RES(unsigned char bNum, unsigned char loc) {
	unsigned char temp;
	switch(loc) {
		case 0:
			b &= ~(1 << bNum);
			break;
		case 1:
			c &= ~(1 << bNum);
			break;
		case 2:
			d &= ~(1 << bNum);
			break;
		case 3:
			e &= ~(1 << bNum);
			break;
		case 4:
			h &= ~(1 << bNum);
			break;
		case 5:
			l &= ~(1 << bNum);
			break;
		case 6:
			temp  = mem->readByte(getHL());
			temp &= ~(1 << bNum);
			mem->writeByte(temp, getHL());
			break;
		case 7:
			a &= ~(1 << bNum);
			break;
	}
}

void GameboyCPU::SET(unsigned char bNum, unsigned char loc) {
	unsigned char temp;
	switch(loc) {
		case 0:
			b |= (1 << bNum);
			break;
		case 1:
			c |= (1 << bNum);
			break;
		case 2:
			d |= (1 << bNum);
			break;
		case 3:
			e |= (1 << bNum);
			break;
		case 4:
			h |= (1 << bNum);
			break;
		case 5:
			l |= (1 << bNum);
			break;
		case 6:
			temp  = mem->readByte(getHL());
			temp |= ~(1 << bNum);
			mem->writeByte(temp, getHL());
			break;
		case 7:
			a |= (1 << bNum);
			break;
	}
}

void GameboyCPU::printDebug() {
	printf("Cycle: %u\n", cycle_num);
	printf("Opcode: %02X\n", opcode);
	printf("Registers: \n");
	printf("A: %02X B: %02X C: %02X D: %02X E: %02X H: %02X L: %02X\n", a ,b, c, d, e, h, l);
	printf("F: %02X SP: %04X PC: %04X\n", f, sp, pc);
	printf("Flags: \n");
	printf("BIOS: %d HALT: %d STOP: %d\n", biosFlag, haltFlag, stopFlag);
	mem->printList();
}

bool GameboyCPU::init(GameboyMemory* memory, bool debug) {
	cycle_num = 0;

	opcode = 0;
	sp = 0;
	pc = 0;

	mTime = 0;

	a = 0;
	b = 0;
	c = 0;
	d = 0;
	e = 0;
	h = 0;
	l = 0;
	f = 0;

	biosFlag = true;
	haltFlag = false;
	stopFlag = false;
	interruptsFlag = false;
	debugFlag = debug;

	mem = memory;
	mem->setBios(biosFlag);
}

void GameboyCPU::EXT() {
	opcode = mem->readByte(pc++);
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

bool GameboyCPU::execute(int* mClocks) {
	bool result = true;
	cycle_num++;

	if(haltFlag || stopFlag) {
		printf("Stalled!\n");
		result = false;
	}
	else {
		if(pc > 0x100) {
			biosFlag = false;
			mem->setBios(biosFlag);
		}
		opcode = mem->readByte(pc++);
		//printf("%02X\n", opcode);
		(*this.*opMap[(opcode&0xF0)>>4][opcode&0x0F])();
		*mClocks = 2; //mTime;

		if(debugFlag) {
			printDebug();
		}
	}

	if(pc > 0x100) {
		haltFlag = true;
	}
	return result;
}