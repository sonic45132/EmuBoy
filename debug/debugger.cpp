#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <array>
#include <string>

struct MEM_OP 
{
	bool write;
	unsigned char value;
	unsigned short addr;
};

class Operation 
{
public:
	unsigned short op;
	std::array<unsigned char, 8> regs_before;
	std::array<unsigned char, 8> regs_after;
	unsigned short param;
	std::vector<MEM_OP> memops;

	Operation(unsigned short op, rb, std::array<unsigned char, 8> ra, 
		std::array<unsigned char, 8> std::vector<MEM_OP> memo) 
	{		
		this->op = op;
		regs_before = rb;
		regs_after = ra;
		memops = memo
	}

};

int main() 
{
	
}