!	code
!	File:/Fortran/5050.f95
!	Date:2021.07.07
!	By MIT License.
!	Copyright(C) 2021 Suote127.All rights reserved

program p5050
implicit none
integer :: res,num

res = 0

do num=1,100,1
	res = num + res
end do

print *,res

end program p5050
