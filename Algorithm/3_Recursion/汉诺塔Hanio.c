#include <stdio.h>
static void Hanoi( char A, char B, char C, int n )		//要将n个环从A借助B移到C上步骤：将n-1个环从A借助C移到B，将第n个环移到C，将n-1个从B借助A移到C
{
	if( 1 == n )
	{
		printf("%c -> %c\n", A, C);
		return;
	}
	Hanoi(A, C, B, n-1);
	printf("%c -> %c\n", A, C);
	Hanoi(B, A, C, n-1);
}

int main()
{
	Hanoi('A', 'B', 'C', 3);
	return 0;
}