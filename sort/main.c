#include <stdio.h>

/* Branching version: swap *a and *b if *a > *b */
void
sort_branch(int* a, int* b)
{
	if (*a > *b)
	{
		int	t = *a;
		*a = *b;
		*b = t;
	}
}

/* Branchless version: implement this so that it swaps *a and *b if *a > *b
   without using any if/else or conditional jumps. Replace the body below. */
void
sort_branchless(int* a, int* b)
{
	int	xor = (*a ^ *b) & -(*a < *b);
	int	t = *a;
	*a = *b ^ xor;
	*b = t ^ xor;
}

int
main(void)
{
    int a, b;

    a = 3; b = 7;
    printf("before: a=%d b=%d\n", a, b);
    sort_branch(&a, &b);
    printf("after sort_branch: a=%d b=%d\n\n", a, b);

    a = 9; b = 2;
    printf("before: a=%d b=%d\n", a, b);
    sort_branchless(&a, &b);
    printf("after sort_branchless: a=%d b=%d\n\n", a, b);

    return 0;
}
