program p5050
implicit none
integer :: res,num

res = 0

do num=1,100,1
	res = num + res
end do

print *,res

end program p5050
