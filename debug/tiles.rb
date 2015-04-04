tiles = Array.new

ARGV.each do |a|
	tiles.push(a.to_i(16))
end

for i in 0...(ARGV.length/16) do
	for j in 0...16 do
		next if((j+1)%2==0)
		low = tiles[(i*16)+j]
		high = tiles[(i*16)+j+1]
		for k in 0...8 do
			n = 7-k
			print (high[n]*2 + low[n]).to_s + " "
		end
		print "\n"
	end
	puts "\n\n"
end