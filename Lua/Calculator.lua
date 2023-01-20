--[[
--	code
--	Calculator in Lua
--	File:/Lua/Calculator.lua
--	Date:2023.01.20
--	By MIT License.
--	Copyright (c) 2023 Ziyao.
--]]

local io	= require "io";
local string	= require "string";

local gExpr,gIndex;

local function at(s,i)
	return string.sub(s,i,i);
end

local function fetch()
	local c = at(gExpr,gIndex);

	if c == ""
	then
		return nil,gIndex;
	elseif c >= '0' and c <= '9'
	then
		local num = string.match(gExpr,"%d+",gIndex);
		return tonumber(num),gIndex + #num;
	elseif c == '+' or c == '-' or c == '*' or c == '/' or
	       c == '(' or c == ')'
	then return c,gIndex + 1;
	else
		error(("%d: Unrecognised character %s"):
		      format(gIndex,c));
	end
end

local function nextToken()
	local tok,idx = fetch();
	gIndex = idx;
	return tok,idx - 1;
end

local function match(expect)
	local tok,pos = nextToken();
	if expect == "number"
	then
		if type(tok) ~= "number"
		then
			error(("%d: Expect number, got %s"):
			      format(pos,tok));
		end
	else
		if tok ~= tok
		then
			error(("%d: Expect %s, got %s"):
			      format(pos,expect,tok));
		end
	end
	return tok;
end

--[[
--	FullExpr	::= '+' Expr | '-' Expr | Expr
--	Expr		::= Term '+' Expr | Term '-' Expr | Term
--	Term		::= Factor '*' Term | Factor '/' Term | Factor
--	Factor		::= Number | '(' FullExpr ')'
--]]

local pFullExpr,pExpr,pTerm,pFactor;

pFullExpr = function()
	local sign = fetch();
	if sign == '-' or sign == '+'
	then
		nextToken();
	end
	return pExpr(sign == '-' and (-1) or 1);
end;

pExpr = function(sign)
	local term = pTerm() * sign;

	local opt = fetch();
	if opt == '+'
	then
		nextToken();
		return term + pExpr(1);
	elseif opt == '-'
	then
		nextToken();
		return term - pExpr(1);
	else
		return term;
	end
end;

pTerm = function()
	local factor = pFactor();

	local opt = fetch();
	if opt == '*'
	then
		nextToken();
		return factor * pTerm();
	elseif opt == '/'
	then
		nextToken();
		return factor / pTerm();
	else
		return factor;
	end
end;

pFactor = function()
	local start = nextToken();

	if type(start) == "number"
	then
		return start;
	elseif start == '('
	then
		local value = pFullExpr();
		match(')');
		return value;
	else
		error(("Unexpected character %s"):
		      format(start));
	end
end;

local input = io.read("l");
while input ~= "exit" and input
do
	gExpr,gIndex = string.gsub(input,"[%s\n]",""),1;
	print(pFullExpr(input));
	input = io.read("l");
end
