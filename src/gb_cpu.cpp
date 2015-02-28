#include "gb.h"
#include <map>

unsigned short Gameboy::getHL() {
	unsigned short temp = l;
	temp |= (h<<8);
	return temp;
}

void Gameboy::setHL(unsigned short value) {
	l = value&0x00FF;
	h = (value&0xFF00)>>8;
}

unsigned short Gameboy::getBC() {
	unsigned short temp = c;
	temp |= (b<<8);
	return temp;
}

void Gameboy::setBC(unsigned short value) {
	c = value&0x00FF;
	b = (value&0xFF00)>>8;
}

unsigned short Gameboy::getDE() {
	unsigned short temp = e;
	temp |= (d<<8);
	return temp;
}

void Gameboy::setDE(unsigned short value) {
	e = value&0x00FF;
	d = (value&0xFF00)>>8;
}

void Gameboy::SZF() {
	f |= 0x80;
}

void Gameboy::CZF() {
	f &= 0x70;
}

void Gameboy::NOP() {
	printf("NOP\n");
}

void Gameboy::HALT() {
	haltFlag = true;
}

void Gameboy::STOP() {
	stopFlag = true;
}

void Gameboy::SCF() {
	f |= 0x10;
}

void Gameboy::CCF() {
	f &= 0xE0;
}

void Gameboy::DAA() {
	unsigned char th = ((a%100)/10);
	unsigned char tl = (a % 10);
	a = ((th << 4) | tl);
}

void Gameboy::DI() {
	interruptsFlag = false;
	writeByte(0, 0xFFFF);
}

void Gameboy::EI() {
	interruptsFlag = true;
	writeByte(1, 0xFFFF);
}

void Gameboy::LDrr_a_b() {
	a = b;
}

void Gameboy::LDrr_a_c() {
	a = c;
}

void Gameboy::LDrr_a_d() {
	a = d;
}

void Gameboy::LDrr_a_e() {
	a = e;
}

void Gameboy::LDrr_a_h() {
	a = h;
}

void Gameboy::LDrr_a_l() {
	a = l;
}

void Gameboy::LDrr_b_a() {
	b = a;
}

void Gameboy::LDrr_b_c() {
	b = c;
}

void Gameboy::LDrr_b_d() {
	b = d;
}

void Gameboy::LDrr_b_e() {
	b = e;
}

void Gameboy::LDrr_b_h() {
	b = h;
}

void Gameboy::LDrr_b_l() {
	b = l;
}

void Gameboy::LDrr_c_a() {
	c = a;
}

void Gameboy::LDrr_c_b() {
	c = b;
}

void Gameboy::LDrr_c_d() {
	c = d;
}

void Gameboy::LDrr_c_e() {
	c = e;
}

void Gameboy::LDrr_c_h() {
	c = h;
}

void Gameboy::LDrr_c_l() {
	c = l;
}

void Gameboy::LDrr_d_a() {
	d = a;
}

void Gameboy::LDrr_d_b() {
	d = b;
}

void Gameboy::LDrr_d_c() {
	d = c;
}

void Gameboy::LDrr_d_e() {
	d = e;
}

void Gameboy::LDrr_d_h() {
	d = h;
}

void Gameboy::LDrr_d_l() {
	d = l;
}

void Gameboy::LDrr_e_a() {
	e = a;
}

void Gameboy::LDrr_e_b() {
	e = b;
}

void Gameboy::LDrr_e_c() {
	e = c;
}

void Gameboy::LDrr_e_d() {
	e = d;
}

void Gameboy::LDrr_e_h() {
	e = h;
}

void Gameboy::LDrr_e_l() {
	e = l;
}

void Gameboy::LDrr_h_a() {
	h = a;
}

void Gameboy::LDrr_h_b() {
	h = b;
}

void Gameboy::LDrr_h_c() {
	h = c;
}

void Gameboy::LDrr_h_d() {
	h = d;
}

void Gameboy::LDrr_h_e() {
	h = e;
}

void Gameboy::LDrr_h_l() {
	h = l;
}

void Gameboy::LDrr_l_a() {
	l = a;
}

void Gameboy::LDrr_l_b() {
	l = b;
}

void Gameboy::LDrr_l_c() {
	l = c;
}

void Gameboy::LDrr_l_d() {
	l = d;
}

void Gameboy::LDrr_l_e() {
	l = e;
}

void Gameboy::LDrr_l_h() {
	l = h;
}

void Gameboy::LDrr_sp_hl() {
	sp = getHL();
}

void Gameboy::LDHLrr_hl_sp() {
	char temp = readByte(sp);
	short hl = ((short)sp + temp);
	setHL(hl);
	pc++;
	f &= 0x30;
}

void Gameboy::LDrn_a() {
	a = readByte(pc);
	pc++;
}

void Gameboy::LDrn_b() {
	b = readByte(pc);
	pc++;
}

void Gameboy::LDrn_c() {
	c = readByte(pc);
	pc++;
}

void Gameboy::LDrn_d() {
	d = readByte(pc);
	pc++;
}

void Gameboy::LDrn_e() {
	e = readByte(pc);
	pc++;
}

void Gameboy::LDrn_h() {
	h = readByte(pc);
	pc++;
}

void Gameboy::LDrn_l() {
	l = readByte(pc);
	pc++;
}

void Gameboy::LDrw_bc() {
	unsigned short temp = readWord(pc);
	setBC(temp);
	pc += 2;
}

void Gameboy::LDrw_de() {
	unsigned short temp = readWord(pc);
	setDE(temp);
	pc += 2;
}

void Gameboy::LDrw_hl() {
	setHL(readWord(pc));
	pc += 2;
}

void Gameboy::LDrw_sp() {
	sp = readWord(pc);
	pc+=2;
}

void Gameboy::LDrm_a_hl() {
	a = readByte(getHL());
}

void Gameboy::LDrm_b_hl() {
	b = readByte(getHL());
}

void Gameboy::LDrm_c_hl() {
	c = readByte(getHL());
}

void Gameboy::LDrm_d_hl() {
	d = readByte(getHL());
}

void Gameboy::LDrm_e_hl() {
	e = readByte(getHL());
}

void Gameboy::LDrm_h_hl() {
	h = readByte(getHL());
}

void Gameboy::LDrm_l_hl() {
	l = readByte(getHL());
}

void Gameboy::LDrm_a_bc() {
	a = readByte(getBC());
}

void Gameboy::LDrm_a_de() {
	a = readByte(getDE());
}

void Gameboy::LDrm_a_w() {
	unsigned short temp = readWord(pc);
	pc += 2;
	a = readByte(temp);
}

void Gameboy::LDIrm_a_hl() {
	a = readByte(getHL());
	setHL((getHL()+1));
}

void Gameboy::LDDrm_a_hl() {
	a = readByte(getHL());
	setHL((getHL()-1));
}

void Gameboy::LDHrm_a_n() {
	unsigned short temp = (0xFF00 | readByte(pc));
	pc++;
	a = readByte(temp);
}

void Gameboy::LDmr_hl_a() {
	writeByte(a, getHL());
}

void Gameboy::LDmr_hl_b() {
	writeByte(b, getHL());	
}

void Gameboy::LDmr_hl_c() {
	writeByte(c, getHL());
}

void Gameboy::LDmr_hl_d() {
	writeByte(d, getHL());
}

void Gameboy::LDmr_hl_e() {
	writeByte(e, getHL());
}

void Gameboy::LDmr_hl_h() {
	writeByte(h, getHL());
}

void Gameboy::LDmr_hl_l() {
	writeByte(l, getHL());
}

void Gameboy::LDmr_bc_a() {
	unsigned short bc = getBC();
	writeByte(a, bc);
}

void Gameboy::LDmr_de_a() {
	unsigned short de = e;
	de |= (d << 8);
	writeByte(a, de);
}

void Gameboy::LDmr_w_a() {
	unsigned short temp = readWord(pc);
	pc+=2;
	writeByte(a, temp);
}

void Gameboy::LDmr_w_sp() {
	unsigned short temp = readWord(pc);
	pc+=2;
	writeWord(sp, temp);
}

void Gameboy::LDmn_hl_n() {
	writeByte(readByte(pc++), getHL());
}

void Gameboy::LDImr_hl_a() {
	writeByte(a, getHL());
	setHL((getHL())+1);
}

void Gameboy::LDDmr_hl_a() {
	unsigned short hl = getHL();
	writeByte(a, hl);
	setHL(hl-1);
}

void Gameboy::LDHmr_n_a() {
	unsigned short temp = (0xFF00 | readByte(pc));
	pc++;
	writeByte(a, temp);
}

void Gameboy::LDHmr_c_a() {
	unsigned short temp = (0xFF00 | c);
	writeByte(a, temp);
}

void Gameboy::INCr_a() {
	a += 1;
	f &= 0xB0;
	if(a == 0) {
		f |= 0x80;
	}
}

void Gameboy::INCr_b() {
	b += 1;
	f &= 0xB0;
	if(b == 0) {
		f |= 0x80;
	}
}

void Gameboy::INCr_c() {
	c += 1;
	f &= 0xB0;
	if(c == 0) {
		f |= 0x80;
	}
}

void Gameboy::INCr_d() {
	d += 1;
	f &= 0xB0;
	if(d == 0) {
		f |= 0x80;
	}
}

void Gameboy::INCr_e() {
	e += 1;
	f &= 0xB0;
	if(e == 0) {
		f |= 0x80;
	}
}

void Gameboy::INCr_h() {
	h += 1;
	f &= 0xB0;
	if(h == 0) {
		f |= 0x80;
	}
}

void Gameboy::INCr_l() {
	l += 1;
	f &= 0xB0;
	if(l == 0) {
		f |= 0x80;
	}
}

void Gameboy::INCr_bc() {
	unsigned short bc = getBC();
	bc++;
	setBC(bc);
}

void Gameboy::INCr_de() {
	unsigned short de = getDE();
	de++;
	setDE(de);
}

void Gameboy::INCr_hl() {
	setHL(getHL()+1);
}

void Gameboy::INCr_sp() {
	sp += 1;
}

void Gameboy::INCm_hl() {
	unsigned char temp = readByte(getHL());
	temp += 1;
	f &= 0xB0;
	if(temp == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
	writeByte(temp, getHL());
}

void Gameboy::DECr_a() {
	a -= 1;
	f |= 0x40;
	if(a == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::DECr_b() {
	b -= 1;
	f |= 0x40;
	if(b == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::DECr_c() {
	c -= 1;
	f |= 0x40;
	if(c == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::DECr_d() {
	d -= 1;
	f |= 0x40;
	if(d == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::DECr_e() {
	e -= 1;
	f |= 0x40;
	if(e == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::DECr_h() {
	h -= 1;
	f |= 0x40;
	if(h == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::DECr_l() {
	l -= 1;
	f |= 0x40;
	if(l == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::DECr_bc() {
	unsigned short bc = c;
	bc |= (b << 8);
	bc--;
	b = (bc & 0xF0) >> 8;
	c = (bc & 0x0F);
}

void Gameboy::DECr_de() {
	unsigned short de = e;
	de |= (d << 8);
	de--;
	d = (de & 0xF0) >> 8;
	e = (de & 0x0F);
}

void Gameboy::DECr_hl() {
	setHL(getHL()-1);
}

void Gameboy::DECr_sp() {
	sp -= 1;
}

void Gameboy::DECm_hl() {
	unsigned char temp = readByte(getHL());
	temp -= 1;
	writeByte(temp, getHL());
	f |= 0x40;
	if(temp == 0) {
		f |= 0x80;
	}
	else {
		CZF();
	}
}

void Gameboy::ADDrr_a_a(){ 
	unsigned char temp = a;
	a += a;
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrr_a_b(){ 
	unsigned char temp = a;
	a += b;
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrr_a_c(){ 
	unsigned char temp = a;
	a += c;
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrr_a_d(){ 
	unsigned char temp = a;
	a += d;
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrr_a_e(){ 
	unsigned char temp = a;
	a += e;
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrr_a_h(){ 
	unsigned char temp = a;
	a += h;
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrr_a_l(){ 
	unsigned char temp = a;
	a += l;
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrr_hl_bc() {
	unsigned short temp = c;
	unsigned short prev = getHL();
	temp |= (b << 8);
	setHL((getHL()+ temp));
	f &= 0xB0;
	if(a < prev) { f |= 0x10; }
	if((getHL()&0x3) < (prev&0x3)) { f |= 0x20; }
}

void Gameboy::ADDrr_hl_de() {
	unsigned short temp = e;
	unsigned short prev = getHL();
	temp |= (d << 8);
	setHL((getHL()+ temp));
	f &= 0xB0;
	if(a < prev) { f |= 0x10; }
	if((getHL()&0x3) < (prev&0x3)) { f |= 0x20; }
}

void Gameboy::ADDrr_hl_hl() {
	unsigned short prev = getHL();
	setHL((getHL()*2));
	f &= 0xB0;
	if(a < prev) { f |= 0x10; }
	if((getHL()&0x3) < (prev&0x3)) { f |= 0x20; }
}

void Gameboy::ADDrr_hl_sp() {
	unsigned short prev = getHL();
	setHL(getHL()+sp);
	f &= 0xB0;
	if(a < prev) { f |= 0x10; }
	if((getHL()&0x3) < (prev&0x3)) { f |= 0x20; }
}

void Gameboy::ADDrn_a() {
	unsigned char temp = a;
	a += readByte(pc++);
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADDrn_sp() {
	unsigned short prev = sp;
	sp += readByte(pc++);
	f &= 0xC0;
	if(a < prev) { f |= 0x10; }
	if((sp&0x3) < (prev&0x3)) { f |= 0x20; }
}

void Gameboy::ADDrm_a_hl() {
	unsigned char temp = a;
	a += readByte(getHL());
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrr_a_a() {
	unsigned char temp = a;
	a += (a + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrr_a_b() {
	unsigned char temp = a;
	a += (b + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrr_a_c() {
	unsigned char temp = a;
	a += (c + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrr_a_d() {
	unsigned char temp = a;
	a += (d + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrr_a_e() {
	unsigned char temp = a;
	a += (e + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrr_a_h() {
	unsigned char temp = a;
	a += (h + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrr_a_l() {
	unsigned char temp = a;
	a += (l + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrm_a_hl() {
	unsigned char temp = a;
	a += (readByte(getHL()) + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ADCrn_a() {
	unsigned char temp = a;
	a += (readByte(pc++) + ((f&0x10)>>4));
	f &= 0xB0;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrr_a_a() {
	unsigned char temp = a;
	a -= a;
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrr_a_b() {
	unsigned char temp = a;
	a -= b;
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrr_a_c() {
	unsigned char temp = a;
	a -= c;
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrr_a_d() {
	unsigned char temp = a;
	a -= d;
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrr_a_e() {
	unsigned char temp = a;
	a -= e;
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrr_a_h() {
	unsigned char temp = a;
	a -= h;
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrr_a_l() {
	unsigned char temp = a;
	a -= l;
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrn_a() {
	unsigned char temp = a;
	a -= readByte(pc++);
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SUBrm_a_hl() {
	unsigned char temp = a;
	a -= readByte(getHL());
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrr_a_a() {
	unsigned char temp = a;
	a -= (a + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrr_a_c() {
	unsigned char temp = a;
	a -= (c + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrr_a_b() {
	unsigned char temp = a;
	a -= (b + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrr_a_d() {
	unsigned char temp = a;
	a -= (d + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrr_a_e() {
	unsigned char temp = a;
	a -= (e + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrr_a_h() {
	unsigned char temp = a;
	a -= (h + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrr_a_l() {
	unsigned char temp = a;
	a -= (l + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrm_a_hl() {
	unsigned char temp = a;
	a -= (readByte(getHL()) + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::SBCrn_a() {
	unsigned char temp = a;
	a -= (readByte(pc++) + ((f&0x10)>>4));
	f |= 0x40;
	if(a < temp) { f |= 0x10; } else { f &= ~(0x1F); }
	if((a&0x3) < (temp&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

//Logical Operations
void Gameboy::ANDrr_a_a() {
	a &= a;
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrr_a_b() {
	a &= b;
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrr_a_c() {
	a &= c;
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrr_a_d() {
	a &= d;
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrr_a_e() {
	a &= e;
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrr_a_h() {
	a &= h;
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrr_a_l() {
	a &= l;
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrn_a() {
	a &= readByte(pc++);
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ANDrm_a_hl() {
	a &= readByte(getHL());
	f |= 0x20;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrr_a_a() {
	a |= a;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrr_a_b() {
	a |= b;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrr_a_c() {
	a |= c;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrr_a_d() {
	a |= d;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrr_a_e() {
	a |= e;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrr_a_h() {
	a |= h;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrr_a_l() {
	a |= l;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrn_a() {
	a |= readByte(pc++);
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::ORrm_a_hl() {
	a |= readByte(getHL());
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrr_a_a() {
	a ^= a;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrr_a_b() {
	a ^= b;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrr_a_c() {
	a ^= c;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrr_a_d() {
	a ^= d;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrr_a_e() {
	a ^= e;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrr_a_h() {
	a ^= h;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrr_a_l() {
	a ^= l;
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrn_a() {
	a ^= readByte(pc++);
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::XORrm_a_hl() {
	a ^= readByte(getHL());
	f &= 0x80;
	if(a == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPL() {
	a = ~a;
	f |= 0x60;
}

//Comparison
void Gameboy::CPrr_a_a() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= a;
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrr_a_b() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= b;
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrr_a_c() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= c;
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrr_a_d() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= d;
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrr_a_e() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= e;
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrr_a_h() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= h;
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrr_a_l() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= l;
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrn_a() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= readByte(pc++);
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

void Gameboy::CPrm_a_hl() {
	unsigned char prev = a;
	unsigned char temp = a;
	temp -= readByte(getHL());
	f |= 0x40;
	if(temp < prev) { f |= 0x10; } else { f &= ~(0x1F); }
	if((temp&0x3) < (prev&0x3)) { f |= 0x20; } else { f &= ~(0x2F); }
	if(temp == 0) { f |= 0x80; } else { f &= ~(0x8F); }
}

//Stack operations
void Gameboy::POPr_bc() {
	b = readByte(sp+1);
	c = readByte(sp);
	sp += 2;
}

void Gameboy::POPr_de() {
	d = readByte(sp+1);
	e = readByte(sp);
	sp += 2;
}

void Gameboy::POPr_af() {
	a = readByte(sp+1);
	f = readByte(sp);
	sp += 2;
}

void Gameboy::POPr_hl() {
	h = readByte(sp+1);
	l = readByte(sp);
	sp += 2;
}

void Gameboy::PUSHr_bc() {
	writeByte(b, sp-1);
	writeByte(c, sp-2);
	sp -= 2;
}

void Gameboy::PUSHr_de() {
	writeByte(d, sp-1);
	writeByte(e, sp-2);
	sp -= 2;
}

void Gameboy::PUSHr_af() {
	writeByte(a, sp-1);
	writeByte(f, sp-2);
	sp -= 2;
}

void Gameboy::PUSHr_hl() {
	writeByte(h, sp-1);
	writeByte(l, sp-2);
	sp -= 2;
}

//Jumps/Branches
void Gameboy::JP() {
	pc = readWord(pc);
}

void Gameboy::JP_hl() {
	pc = readWord(getHL());
}

void Gameboy::JP_c() {
	if(f&0x10 > 0) {
		pc = readWord(pc);
	}
	else {
		pc += 2;
	}
}

void Gameboy::JP_z() {
	if(f&0x80 > 0) {
		pc = readWord(pc);
	}
	else {
		pc += 2;
	}
}

void Gameboy::JP_nz() {
	if(f&0x80 == 0) {
		pc = readWord(pc);
	}
	else {
		pc += 2;
	}
}

void Gameboy::JP_nc() {
	if(f&0x10 == 0) {
		pc = readWord(pc);
	}
	else {
		pc += 2;
	}
}

void Gameboy::JR() {
	pc = ((char)pc + (char)readByte(pc++));
}

void Gameboy::JR_c() {
	if((f&0x10) > 0) {
		pc = ((char)pc + (char)readByte(pc++));
	}
	else {
		pc += 1;
	}
}

void Gameboy::JR_z() {
	if((f&0x80) > 0) {
		pc = ((char)pc + (char)readByte(pc++));
	}
	else {
		pc += 1;
	}
}

void Gameboy::JR_nz() {
	if((f&0x80) == 0) {
		char temp = (char)readByte(pc++);
		pc += temp;
	}
	else {
		pc += 1;
	}
}

void Gameboy::JR_nc() {
	if(f&0x10 == 0) {
		pc = ((char)pc + (char)readByte(pc++));
	}
	else {
		pc += 1;
	}
}

void Gameboy::CALL() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xFF00)>>8, sp-1);
	writeByte((temp&0x00FF), sp-2);
	pc = readWord(pc);
	sp -= 2;
}

void Gameboy::CALL_c() {
	if((f&0x10) > 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		writeByte((temp&0xF0)>>8, sp-1);
		writeByte((temp&0x0F), sp-2);
		pc = readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

void Gameboy::CALL_z() {
	if((f&0x80) > 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		writeByte((temp&0xF0)>>8, sp-1);
		writeByte((temp&0x0F), sp-2);
		pc = readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

void Gameboy::CALL_nc() {
	if((f&0x10) == 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		writeByte((temp&0xF0)>>8, sp-1);
		writeByte((temp&0x0F), sp-2);
		pc = readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

void Gameboy::CALL_nz() {
	if((f&0x80) == 0) {
		//Incerment pc by two for storage to skip address when returning
		unsigned short temp = pc;
		temp +=2;
		writeByte((temp&0xF0)>>8, sp-1);
		writeByte((temp&0x0F), sp-2);
		pc = readWord(pc);
		sp -= 2;
	}
	else {
		pc += 2;
	}
}

//Restarts
void Gameboy::RST_0() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0000;
}

void Gameboy::RST_8() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0008;
}

void Gameboy::RST_10() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0010;
}

void Gameboy::RST_18() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0018;
}

void Gameboy::RST_20() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0020;
}

void Gameboy::RST_28() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0028;
}

void Gameboy::RST_30() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0030;
}

void Gameboy::RST_38() {
	//Incerment pc by two for storage to skip address when returning
	unsigned short temp = pc;
	temp +=2;
	writeByte((temp&0xF0)>>8, sp-1);
	writeByte((temp&0x0F), sp-2);
	pc = 0x0038;
}

//Returns
void Gameboy::RET() {
	pc = readByte(sp);
	pc |= (readByte(sp+1) << 8);
	sp += 2;
}

void Gameboy::RETI() {
	pc = readByte(sp);
	pc |= (readByte(sp+1) << 8);
	sp += 2;
	EI();
}

void Gameboy::RET_c() {
	if((f&0x10) > 0) {
		pc = readByte(sp);
		pc |= (readByte(sp+1) << 8);
		sp += 2;
	}
}

void Gameboy::RET_z() {
	if((f&0x80) > 0) {
		pc = readByte(sp);
		pc |= (readByte(sp+1) << 8);
		sp += 2;
	}
}

void Gameboy::RET_nc() {
	if((f&0x10) == 0) {
		pc = readByte(sp);
		pc |= (readByte(sp+1) << 8);
		sp += 2;
	}
}

void Gameboy::RET_nz() {
	if((f&0x80) == 0) {
		pc = readByte(sp);
		pc |= (readByte(sp+1) << 8);
		sp += 2;
	}
}

//Bit Rotations
void Gameboy::RL() {
	std::map<int, unsigned char Gameboy::*> regMap = 
		{{0, &Gameboy::b}, {1, &Gameboy::c}, {2, &Gameboy::d}, {3, &Gameboy::e}, {4, &Gameboy::h}, {5, &Gameboy::l}, {6, NULL}, {7, &Gameboy::a}};


	int regNum = opcode & 0x0F;
	unsigned char Gameboy::* reg = regMap[regNum];
	unsigned char temp;
	unsigned short temp2;

	printf("regNum: %d\n", regNum);

	if(reg == NULL) {
		temp = readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	printf("reg value: %02X\n", temp);

	temp2 = temp;
	temp2 = temp2 << 1;

	temp = temp2;
	temp |= ((f&0x10)>>4);

	if(temp2&0x0100 > 0) {
		SCF();
	}
	else {
		CCF();
	}

	if(reg == NULL) {
		writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}
}

void Gameboy::RLC() {
	std::map<int, unsigned char Gameboy::*> regMap = 
		{{0, &Gameboy::b}, {1, &Gameboy::c}, {2, &Gameboy::d}, {3, &Gameboy::e}, {4, &Gameboy::h}, {5, &Gameboy::l}, {6, NULL}, {7, &Gameboy::a}};

	
	int regNum = opcode & 0x0F;
	unsigned char Gameboy::* reg = regMap[regNum];
	unsigned char temp;
	unsigned short temp2;

	if(reg == NULL) {
		temp = readByte(getHL());
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
		CCF();
	}

	temp = temp2;
	temp |= ((f&0x10)>>4);

	if(reg == NULL) {
		writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}	
}

void Gameboy::RR() {
	std::map<int, unsigned char Gameboy::*> regMap = 
		{{0, &Gameboy::b}, {1, &Gameboy::c}, {2, &Gameboy::d}, {3, &Gameboy::e}, {4, &Gameboy::h}, {5, &Gameboy::l}, {6, NULL}, {7, &Gameboy::a}};

	int regNum = opcode & 0x0F;
	unsigned char Gameboy::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = readByte(getHL());
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
		CCF();
	}

	if(reg == NULL) {
		writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}
}

void Gameboy::RRC() {
	std::map<int, unsigned char Gameboy::*> regMap = 
		{{0, &Gameboy::b}, {1, &Gameboy::c}, {2, &Gameboy::d}, {3, &Gameboy::e}, {4, &Gameboy::h}, {5, &Gameboy::l}, {6, NULL}, {7, &Gameboy::a}};

	int regNum = opcode & 0x0F;
	unsigned char Gameboy::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	if(temp&0x01 > 0) {
		SCF();
	}
	else {
		CCF();
	}

	temp = temp >> 1;
	temp |= ((f&0x10)<<3);

	if(reg == NULL) {
		writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}	
}

//Bit Shifts
void Gameboy::SLA() {
	std::map<int, unsigned char Gameboy::*> regMap = 
		{{0, &Gameboy::b}, {1, &Gameboy::c}, {2, &Gameboy::d}, {3, &Gameboy::e}, {4, &Gameboy::h}, {5, &Gameboy::l}, {6, NULL}, {7, &Gameboy::a}};

	int regNum = opcode & 0x0F;
	unsigned char Gameboy::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	if(temp & 0x80 > 0) {
		SCF();
	} 
	else {
		CCF();
	}
	temp = temp << 1;

	if(reg == NULL) {
		writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}

}

void Gameboy::SRA() {
	std::map<int, unsigned char Gameboy::*> regMap = 
		{{0, &Gameboy::b}, {1, &Gameboy::c}, {2, &Gameboy::d}, {3, &Gameboy::e}, {4, &Gameboy::h}, {5, &Gameboy::l}, {6, NULL}, {7, &Gameboy::a}};

	int regNum = opcode & 0x0F;
	unsigned char Gameboy::* reg = regMap[regNum];
	char temp;

	if(reg == NULL) {
		temp = (char)readByte(getHL());
	}
	else {
		temp = (char)(*this.*reg);
	}

	if(temp & 0x01 > 0) {
		SCF();
	} 
	else {
		CCF();
	}
	temp = temp >> 1;

	if(reg == NULL) {
		writeByte((unsigned char)temp, getHL());
	}
	else {
		*this.*reg = (unsigned char)temp;
	}

}

void Gameboy::SRL() {
	std::map<int, unsigned char Gameboy::*> regMap = 
		{{0, &Gameboy::b}, {1, &Gameboy::c}, {2, &Gameboy::d}, {3, &Gameboy::e}, {4, &Gameboy::h}, {5, &Gameboy::l}, {6, NULL}, {7, &Gameboy::a}};

	int regNum = opcode & 0x0F;
	unsigned char Gameboy::* reg = regMap[regNum];
	unsigned char temp;

	if(reg == NULL) {
		temp = readByte(getHL());
	}
	else {
		temp = *this.*reg;
	}

	if(temp & 0x01 > 0) {
		SCF();
	} 
	else {
		CCF();
	}
	temp = temp >> 1;

	if(reg == NULL) {
		writeByte(temp, getHL());
	}
	else {
		*this.*reg = temp;
	}

}

//Swap functions
void Gameboy::SWAPr_a() {
	unsigned char th = (a & 0xC) >> 4;
	unsigned char tl = (a & 0x3) << 4;
	a = (th | tl);
}

void Gameboy::SWAPr_b() {
	unsigned char th = (b & 0xC) >> 4;
	unsigned char tl = (b & 0x3) << 4;
	b = (th | tl);	
}

void Gameboy::SWAPr_c() {
	unsigned char th = (c & 0xC) >> 4;
	unsigned char tl = (c & 0x3) << 4;
	c = (th | tl);
}

void Gameboy::SWAPr_d() {
	unsigned char th = (d & 0xC) >> 4;
	unsigned char tl = (d & 0x3) << 4;
	d = (th | tl);
}

void Gameboy::SWAPr_e() {
	unsigned char th = (e & 0xC) >> 4;
	unsigned char tl = (e & 0x3) << 4;
	e = (th | tl);
}

void Gameboy::SWAPr_h() {
	unsigned char th = (h & 0xC) >> 4;
	unsigned char tl = (h & 0x3) << 4;
	h = (th | tl);
}

void Gameboy::SWAPr_l() {
	unsigned char th = (l & 0xC) >> 4;
	unsigned char tl = (l & 0x3) << 4;
	l = (th | tl);
}

void Gameboy::SWAPm_hl() {
	unsigned char temp = readByte(getHL());
	unsigned char th = (temp & 0xC) >> 4;
	unsigned char tl = (temp & 0x3) << 4;
	temp = (th | tl);
	writeByte(temp, getHL());
}

void Gameboy::BIT(unsigned char bNum, unsigned char loc) {
	unsigned char temp;
	f &= 0xA0;
	f |= 0x20;
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
				f |= 0x80;
			}
			else {
				CZF();
			}
			break;
		case 2:
			temp = (d & (1 << bNum)) >> bNum;
			if(temp == 0) {
				f |= 0x80;
			}
			else {
				CZF();
			}
			break;
		case 3:
			temp = (e & (1 << bNum)) >> bNum;
			if(temp == 0) {
				f |= 0x80;
			}
			else {
				CZF();
			}
			break;
		case 4:
			temp = (h & (1 << bNum)) >> bNum;
			if(temp == 0) {
				f |= 0x80;
			}
			else {
				CZF();
			}
			break;
		case 5:
			temp = (l & (1 << bNum)) >> bNum;
			if(temp == 0) {
				f |= 0x80;
			}
			else {
				CZF();
			}
			break;
		case 6:
			temp = (readByte(getHL()) & (1 << bNum)) >> bNum;
			if(temp == 0) {
				f |= 0x80;
			}
			else {
				CZF();
			}
			break;
		case 7:
			temp = (a & (1 << bNum)) >> bNum;
			if(temp == 0) {
				f |= 0x80;
			}
			else {
				CZF();
			}
			break;
	}
}

void Gameboy::RES(unsigned char bNum, unsigned char loc) {
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
			temp  = readByte(getHL());
			temp &= ~(1 << bNum);
			writeByte(temp, getHL());
			break;
		case 7:
			a &= ~(1 << bNum);
			break;
	}
}

void Gameboy::SET(unsigned char bNum, unsigned char loc) {
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
			temp  = readByte(getHL());
			temp |= ~(1 << bNum);
			writeByte(temp, getHL());
			break;
		case 7:
			a |= (1 << bNum);
			break;
	}
}