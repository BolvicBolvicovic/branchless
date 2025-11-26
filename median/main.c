#include <stdio.h>
#include <limits.h>

/* Branching version: return the median of a, b, c using comparisons */
int
median_branch(int a, int b, int c)
{
	if (a > b)
	{
		if (b > c)
			return b; /* a > b > c */
		else if (a > c)
			return c; /* a > c >= b */
		else
			return a; /* c >= a > b */
	}
	else
	{
		if (a > c)
			return a; /* b >= a > c */
		else if (b > c)
			return c; /* b > c >= a */
		else
			return b; /* c >= b >= a */
	}
}

/* Branchless version: return the median of a, b, c without any if/else/jumps.
   Replace the body below with a branchless expression or sequence. */
int
median_branchless(int a, int b, int c)
{
	int	a_sup_b	= -(a < b);
	int	a_sup_c = -(a < c);
	int	b_sup_c = -(b < c);
							// case c<
	int	ab_min	= b ^ ((a ^ b) & a_sup_b);	// a || b
	int	ac_min	= c ^ ((a ^ c) & a_sup_c);	// c
	int	bc_min	= c ^ ((b ^ c) & b_sup_c);	// c
	
	return ab_min ^ ac_min ^ bc_min;
}

int
main(void)
{
	int tests[][3] =
	{
		{3, 7, 5},
		{9, 2, 4},
		{1, 1, 2},
		{5, 5, 5},
		{INT_MIN, 0, INT_MAX},
		{-3, -7, -5},
	};
	
	for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i)
	{
		int a = tests[i][0], b = tests[i][1], c = tests[i][2];
		printf("inputs: %d %d %d | branch median=%d | branchless median=%d\n",
		       a, b, c, median_branch(a,b,c), median_branchless(a,b,c));
	}
	return 0;
}
