require "csv"

ops = CSV.read("docs/ops.csv")
extops = CSV.read("docs/extops.csv")

# ops.each do |arr|
# 	arr.each do |item|
# 		print item.to_s+" "
# 	end
# 	p ""
# end


ignore_next = false;

f = File.open("debug/log.txt", "r")
out = File.open("debug/log2.txt", "w")
f.each_line do |line|
	cap = /^EXT Opcode: ([0-9A-F]*)$/.match(line)
	if cap != nil
		ignore_next = true
		opcode = cap[1].hex
		op_string = extops[(opcode&0xF0)>>4][(opcode&0x0F)]
		out.write(line.to_s.gsub("\n",'')+" : "+op_string+"\n")
		p op_string
	end
  cap = /^Opcode: ([0-9A-F]*)$/.match(line)
  if cap != nil && !ignore_next
  	opcode = cap[1].hex
  	op_string = ops[(opcode&0xF0)>>4][(opcode&0x0F)]
		out.write(line.to_s.gsub("\n",'')+" : "+op_string+"\n")
		p op_string
  elsif cap != nil && ignore_next
  	ignore_next = false
  else
  	out.write(line.to_s)
  end
end
f.close