#include <stdio.h>
#include <limits.h>
#include <stdint.h>

/* Branching clamp: clamp x into [0,255] using plain ifs */
int
clamp_branch(int x)
{
	if (x < 0)
		return 0;
	if (x > 255)
		return 255;
	return x;
}

/* Branchless clamp: clamp x into [0,255] WITHOUT any if/else, ?:, or
   explicit jumps. Replace the body below with an arithmetic/bitwise
   implementation (use masks derived from comparisons). */
int
clamp_branchless(int x)
{
	x *= x > 0;
	x ^= ((x ^ 255) & -(x > 255));
	return x;
}

int
main(void)
{
	int tests[] =
	{
		-5,
		0,
		100,
		255,
		256,
		300,
		INT_MIN,
		INT_MAX,
		-1,
		1023,
	};
	size_t n = sizeof(tests) / sizeof(tests[0]);

	for (size_t i = 0; i < n; ++i)
	{
		int x = tests[i];
		printf("x=%12d | branch=%3d | branchless=%3d\n",
		       x, clamp_branch(x), clamp_branchless(x));
	}

	return 0;
}
