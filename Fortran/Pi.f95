!	code
!	File:/Fortran/Pi.f95
!	Date:2021.07.05
!	By MIT License.
!	Copyright(C) 2021 Suote127.All rights reserved.

program Pi;
	implicit none;
	integer(kind=8) loopTarget,loopCount;
	integer(kind=1) s;
	real(kind=16) res;

	res = 1.0
	loopCount = 0;
	s = 1;

	read *,loopTarget;

	do loopCount=1,loopTarget,1
		s   = -s;
		res = res + s * ( 1. / (loopCount * 2 + 1) )
	end do

	print *,res * 4

end program Pi;
