--[[
	code - Algorithm
	Date:2022.06.24
	File:/Algorithm/Quick_Sort.lua
	By MIT License
]]

local fn = require("fn");

local partition = function(arr,left,right)
	local main = arr[right];
	local pos = left;
	for i = left,right - 1
	do
		if main > arr[i]
		then
			arr[pos],arr[i] = arr[i],arr[pos];
			pos = pos + 1;
		end
	end
	arr[pos],arr[right] = arr[right],arr[pos];
	return pos;
end

local sort;
sort = function(arr,left,right)
	if left >= right
	then
		return arr;
	end

	local mid = partition(arr,left,right);
	sort(arr,left,mid - 1);
	sort(arr,mid + 1,left);
	return arr;
end

local quick_sort = function(arr)
	return sort(arr,1,#arr);
end

--[[
local array = fn.range(function() return math.random(1,100) end,
		       1,1,10);
]]

local array = {4,3,2,1};

local printTable = fn.foreach(print);
printTable(array);
quick_sort(array);
print();
printTable(array);
