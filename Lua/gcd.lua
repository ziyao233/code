--[[
	code
	File:/Lua/gcd.lua
	Date:2021.07.03
	By MIT License.
	Copyright(C) 2021 Ziyao.All rights reserved.
]]

local math	= require("math");
local os	= require("os");

local gcd;
gcd		= function(a,b)
	return a % b == 0 and b or gcd(b,a%b);
end

math.randomseed(os.time());

for i = 1,128
do
	local a,b = math.random(1,math.maxinteger),math.random(1,math.maxinteger);
	print(string.format("gcd(%d,%d) = %d",a,b,gcd(a,b)));
end

return 0;
