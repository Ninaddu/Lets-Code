#include <stdio.h>

static int Average( int a[], int low, int high, int n )
{
	int mid;
	if( low > high )
	{
		printf("\n查找数字不存在\n");
		return 0;
	}
	mid = (low + high) / 2;
	if( a[mid] == n )
	{
		printf("\n数字在数组第%d位\n", mid+1);
		return 1;
	}
	else if( a[mid] > n )
	{
		high = mid - 1;
	}
	else
	{
		low = mid + 1;
	}
	return (Average(a, low, high, n));
}

int main()
{
	int a[10] = {0,3,5,9,12,15,19,20,30,59};
	int n;
	scanf("%d", &n);
	Average(a, 0, 9, n);	
	return 0;
}