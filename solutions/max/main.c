#include <stdio.h>

int
max_branch(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int
max_branchless(int a, int b)
{
	return (-(a < b) & (a ^ b)) ^ a;
}
/*
Note: both codes compile to branchless: cmp/mov/cmovge

	w = 1010
	z = 1100
	x = 0110
	s = 1111 // -(w < z)	<=> w > z ? 0 : 0xff
	xs= 0110 // x & s	<=> w > z ? 0 : x
	r = 1100 // w ^ xs	<=> w > z ? w : z (z=w^w^z)

*/

int
main(void)
{
	int a = 3, b = 7;
	printf("max(%d, %d) = %d\n", a, b, max_branch(a, b));
	printf("max(%d, %d) = %d\n", a, b, max_branchless(a, b));
	return 0;
}
