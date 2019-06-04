#include <iostream>
#define IMPOSSIBLE  65535
#define KEY    22
#define MAX    20

int Fibonacci_Search( int *array, int n, int key );

int main()
{
    int array[MAX] = {-5, 0, 2, 6, 8, 10, 22, 25, 46, 100};
    int i = Fibonacci_Search(array, 10, KEY);
    
    if( i == IMPOSSIBLE )
    {
        std::cout << KEY << "不存在数组中\n\n";
    }
    else
    {
        std::cout << KEY << "位于第" << i+1 << "个数字\n\n";
    }
    system("pause");
    return 0;
}


void Fibonacci( int *f )
{
    f[0] = 1;
    f[1] = 1;
    for( int i = 2; i < MAX; i++ )
    {
        f[i] = f[i-1] + f[i-2];
    }
}

int Fibonacci_Search( int *array, int n, int key )
{
    int low = 0, high = n-1;
    int F[MAX];
    Fibonacci(F);
    int k = 0;
    while( n > F[k] - 1 )       // n >= F(k)
    {
        ++k;
    }

    //把F[k]-1中比n多的位数以0补齐
    for( int i = n; i < F[k]-1; i++ )
    {
        array[i] = array[high];
    }

    while( low <= high )
    {       
        int mid = low + F[k-1] -1;
        if( array[mid] == key )
        {
            if( mid > high )
                return high;
            else
                return mid;
            
        }
        if( array[mid] > key )
        {
            high = mid - 1;
            k -= 1;
        }
        if( array[mid] < key )
        {
            low = mid + 1;
            k -= 2;
        }
    }
    return IMPOSSIBLE;
}
 