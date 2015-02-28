require "csv"

bios = CSV.read("debug/bios.csv")
ops = CSV.read("docs/ops.csv")
extops = CSV.read("docs/extops.csv")

bios.each do |line|
	line.each do |op|
		opcode = op.hex
		p op.to_s.strip+" "+ops[(opcode&0xF0)>>4][(opcode&0x0F)]
	end
end