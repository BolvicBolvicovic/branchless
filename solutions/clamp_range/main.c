#include <stdio.h>
#include <limits.h>
#include <stdint.h>

/*
 	.globl	clamp_range_branch
	.type	clamp_range_branch, @function
clamp_range_branch:
	.cfi_startproc
	cmp	esi, edx	# lo cmp with hi
	mov	eax, esi	# tmp = lo
	cmovle	esi, edx	# if le then lo = hi
	cmovg	eax, edx	# else tmp = hi
				# After that the high bound is in lo and the low bound tmp.
				# I will refer to them as:
				#	- tmp = lb for low bound
				# 	- lo  = hb for high bound
	cmp	esi, edi	# hb cmp with x
	cmovg	esi, edi	# if g then hi = x
	cmp	eax, edi	# lb cmp with x
	cmovle	eax, esi	# if le then lb = hb
	ret
	.cfi_endproc
...
	.globl	clamp_range_branchless
	.type	clamp_range_branchless, @function
clamp_range_branchless:
	.cfi_startproc
	cmp	esi, edx	# lo cmp with hi
	mov	eax, edx	# res = hi
	cmovle	eax, esi	# if le then res = lo
	cmp	eax, edi	# res cmp with x
	cmovl	eax, edi	# if l then res = x
	cmp	esi, edx	# lo cmp with hi
	cmovl	esi, edx	# if l then lo = hi
	cmp	esi, eax	# lo cmp with res
	cmovle	eax, esi	# if le then res = lo
	ret
	.cfi_endproc
 * */

/* Branching clamp to an arbitrary [lo, hi] range (handles lo>hi by swapping) */
int
clamp_range_branch(int x, int lo, int hi)
{
	/* ensure lo <= hi */
	if (lo > hi)
	{
		int t = lo; lo = hi; hi = t;
	}
	if (x < lo) return lo;
	if (x > hi) return hi;
	return x;
}

/* Branchless clamp to [lo, hi]. Replace the body below with a branchless
   implementation. Constraints: no if/else, no ?:, no explicit jumps. */
int
clamp_range_branchless(int x, int lo, int hi)
{
	int	range = (lo ^ hi) & -(lo > hi);

	lo = lo ^ range;
	hi = hi ^ range;
	x  = x  ^ ((lo ^ x ) & -(x  < lo));
	x  = x  ^ ((hi ^ x ) & -(x  > hi));

	return x;
}

int
main(void)
{
	int tests[][3] =
	{
		{ -5,   0, 255 },   /* x < lo */
		{ 100,   0, 255 },  /* in range */
		{ 300,   0, 255 },  /* x > hi */
		{ 42,   50, 10 },   /* lo>hi (swap needed) */
		{ INT_MIN, -100, 100 }, /* extremes */
		{ INT_MAX, -100, 100 },
		{ -50, -100, -10 }, /* negative range */
		{ -120, -100, -10 },/* below negative range */
		{  500, 1000, 2000 },/* far above */
		{ 1500, 1000, 2000 },/* inside swapped or not */
	};
	size_t n = sizeof(tests) / sizeof(tests[0]);

	for (size_t i = 0; i < n; ++i)
	{
		int x = tests[i][0], lo = tests[i][1], hi = tests[i][2];
		printf("x=%12d lo=%12d hi=%12d | branch=%12d | branchless=%12d\n",
		       x, lo, hi,
		       clamp_range_branch(x, lo, hi),
		       clamp_range_branchless(x, lo, hi));
	}
	return 0;
}
