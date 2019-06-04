#include <stdio.h>
static void Hanoi( char A, char B, char C, int n )		//Ҫ��n������A����B�Ƶ�C�ϲ��裺��n-1������A����C�Ƶ�B������n�����Ƶ�C����n-1����B����A�Ƶ�C
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