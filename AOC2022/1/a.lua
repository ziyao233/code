local io		= require "io";
local math		= require "math";

local thisElf, maxElf = 0, 0;

for line in io.lines()
do
	if line == ""
	then
		maxElf, thisElf = math.max(thisElf, maxElf), 0;
	else
		thisElf = thisElf + line;
	end
end

print(maxElf);
